#include <xc.h>
#include <stdbool.h>
#include <string.h>

#include "../platform.h"

// Functions "exported" by this file
void platform_usart_pms_init(void);
void platform_usart_init(void);
void platform_usart_tick_handler(const platform_timespec_t *tick);

/////////////////////////////////////////////////////////////////////////////

/**
 * State variables for UART
 * 
 * Separate contexts for PMS7003 (SERCOM0) and Laptop (SERCOM3)
 */
typedef struct ctx_usart_type {
    /// Pointer to the underlying register set
    sercom_usart_int_registers_t *regs;

    /// State variables for the transmitter
    struct {
        volatile platform_usart_tx_bufdesc_t *desc;
        volatile uint16_t nr_desc;
        volatile const char *buf;
        volatile uint16_t len;
    } tx;

    /// State variables for the receiver
    struct {
        volatile platform_usart_rx_async_desc_t *volatile desc;
        volatile platform_timespec_t ts_idle;
        volatile uint16_t idx;
    } rx;

    /// Configuration items
    struct {
        platform_timespec_t ts_idle_timeout;
    } cfg;

} ctx_usart_t;

static ctx_usart_t ctx_uart_pms;     // Context for PMS7003 (SERCOM0)
static ctx_usart_t ctx_uart_laptop;  // Context for Laptop (SERCOM3)

// Configure PMS7003 UART (SERCOM0)
void platform_usart_pms_init(void) {
    #define UART_REGS (&(SERCOM0_REGS->USART_INT))
    
    MCLK_REGS->MCLK_APBCMASK |= (1 << 1);
    GCLK_REGS->GCLK_PCHCTRL[17] = 0x00000042;
    while ((GCLK_REGS->GCLK_PCHCTRL[17] & 0x00000040) == 0) asm("nop");

    memset(&ctx_uart_pms, 0, sizeof(ctx_uart_pms));
    ctx_uart_pms.regs = UART_REGS;

    UART_REGS->SERCOM_CTRLA = 0x01;
    while ((UART_REGS->SERCOM_SYNCBUSY & 0x01) != 0) asm("nop");
    UART_REGS->SERCOM_CTRLA = (uint32_t)(0x4);
    
    UART_REGS->SERCOM_CTRLA |= (1 << 20) | (0 << 24) | (1 << 30);
    UART_REGS->SERCOM_BAUD = 63019;
    
    ctx_uart_pms.cfg.ts_idle_timeout.nr_sec = 0;
    ctx_uart_pms.cfg.ts_idle_timeout.nr_nsec = 10648750;
    
    UART_REGS->SERCOM_CTRLB |= (0 << 0) | (0 << 6) | (1 << 16) | (1 << 17) | (1 << 22) | (1 << 23);
    while ((UART_REGS->SERCOM_SYNCBUSY & (1<<2)) != 0) asm("nop");
    
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 4);
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[4] = 0x1;
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[2] = 0x33;
    
    PORT_SEC_REGS->GROUP[0].PORT_DIRCLR = (1 << 5);
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[5] = 0x3;
    
    UART_REGS->SERCOM_CTRLA |= (1<<1);
    while ((UART_REGS->SERCOM_SYNCBUSY & (1 << 1)) != 0) asm("nop");
    return;
}

// Configure Laptop UART (SERCOM3)
void platform_usart_init(void) {
    #define UART_REGS (&(SERCOM3_REGS->USART_INT))
    
    MCLK_REGS->MCLK_APBCMASK |= (1 << 4);
    GCLK_REGS->GCLK_PCHCTRL[20] = 0x00000042;
    while ((GCLK_REGS->GCLK_PCHCTRL[20] & 0x00000040) == 0) asm("nop");
    
    memset(&ctx_uart_laptop, 0, sizeof(ctx_uart_laptop));
    ctx_uart_laptop.regs = UART_REGS;
    
    UART_REGS->SERCOM_CTRLA = 0x01;
    while ((UART_REGS->SERCOM_SYNCBUSY & 0x01) != 0) asm("nop");
    UART_REGS->SERCOM_CTRLA = (uint32_t)(0x4);
    
    UART_REGS->SERCOM_CTRLA |= (1 << 20) | (1 << 24) | (1 << 30);
    UART_REGS->SERCOM_BAUD = 63019;
    
    ctx_uart_laptop.cfg.ts_idle_timeout.nr_sec = 0;
    ctx_uart_laptop.cfg.ts_idle_timeout.nr_nsec = 468750;
    
    UART_REGS->SERCOM_CTRLB |= (1 << 16)|(1 << 17)|(0b11 << 22);
    while ((UART_REGS->SERCOM_SYNCBUSY & (1<<2)) != 0) asm("nop");
    
    PORT_SEC_REGS->GROUP[1].PORT_DIRSET = (1 << 8);
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[8] = 0x1;
    PORT_SEC_REGS->GROUP[1].PORT_PMUX[4] = 0x33;
    
    PORT_SEC_REGS->GROUP[1].PORT_DIRCLR = (1 << 9);
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[9] = 0x3;
    
    UART_REGS->SERCOM_CTRLA |= (1<<1);
    while ((UART_REGS->SERCOM_SYNCBUSY & (1<<1)) != 0) asm("nop");
    return;
}

static void usart_rx_abort_helper(ctx_usart_t *ctx)
{
 if (ctx->rx.desc != NULL) {
  ctx->rx.desc->compl_type = PLATFORM_USART_RX_COMPL_DATA;
  ctx->rx.desc->compl_info.data_len = ctx->rx.idx;
  ctx->rx.desc = NULL;
 }
 ctx->rx.ts_idle.nr_sec = 0;
 ctx->rx.ts_idle.nr_nsec = 0;
 ctx->rx.idx = 0;
 return;
}

static void usart_tick_handler_common(
 ctx_usart_t *ctx, const platform_timespec_t *tick)
{
 uint16_t status = 0x0000;
 uint8_t data = 0x00;
 platform_timespec_t ts_delta;
	
 if ((ctx->regs->SERCOM_INTFLAG & (1 << 0)) != 0) {
  if (ctx->tx.len > 0) {
   ctx->regs->SERCOM_DATA = *(ctx->tx.buf++);
   --ctx->tx.len;
  }
  if (ctx->tx.len == 0) {
   ctx->tx.buf = NULL;
   if (ctx->tx.nr_desc > 0) {
    ctx->tx.buf = ctx->tx.desc->buf;
    ctx->tx.len = ctx->tx.desc->len;
    
    ++ctx->tx.desc;
    --ctx->tx.nr_desc;
     
    if (ctx->tx.buf == NULL || ctx->tx.len == 0) {
     ctx->tx.buf = NULL;
     ctx->tx.len = 0;
    }
   } else {
    ctx->regs->SERCOM_INTENCLR = 0x01;
    ctx->tx.desc = NULL;
    ctx->tx.buf = NULL;
   }
  }
 }
	
 if ((ctx->regs->SERCOM_INTFLAG & (1 << 2)) != 0) {
  status = ctx->regs->SERCOM_STATUS | 0x8000;
  data = (uint8_t)(ctx->regs->SERCOM_DATA);
 }
 do {
  if (ctx->rx.desc == NULL) {
   break;
  }

  if ((status & 0x8003) == 0x8000) {
   ctx->rx.desc->buf[ctx->rx.idx++] = data;
   ctx->rx.ts_idle = *tick;
  }
  ctx->regs->SERCOM_STATUS |= (status & 0x00F7);

  if (ctx->rx.idx >= ctx->rx.desc->max_len) {
   usart_rx_abort_helper(ctx);
   break;
  } else if (ctx->rx.idx > 0) {
   platform_tick_delta(&ts_delta, tick, &ctx->rx.ts_idle);
   if (platform_timespec_compare(&ts_delta, &ctx->cfg.ts_idle_timeout) >= 0) {
    usart_rx_abort_helper(ctx);
    break;
   }
  }
 } while (0);
	
 return;
}
void platform_usart_tick_handler(const platform_timespec_t *tick)
{
 usart_tick_handler_common(&ctx_uart_pms, tick);
 usart_tick_handler_common(&ctx_uart_laptop, tick);
}

#define NR_USART_CHARS_MAX (65528)
#define NR_USART_TX_FRAG_MAX (32)

static bool usart_tx_busy(ctx_usart_t *ctx)
{
 return (ctx->tx.len > 0) || (ctx->tx.nr_desc > 0) ||
  ((ctx->regs->SERCOM_INTFLAG & (1 << 0)) == 0);
}
static bool usart_tx_async(ctx_usart_t *ctx,
 const platform_usart_tx_bufdesc_t *desc,
 unsigned int nr_desc)
{
 uint16_t avail = NR_USART_CHARS_MAX;
 unsigned int x, y;
	
 if (!desc || nr_desc == 0)
  return true;
 else if (nr_desc > NR_USART_TX_FRAG_MAX)
  return false;
	
 if (usart_tx_busy(ctx))
  return false;
	
 for (x = 0, y = 0; x < nr_desc; ++x) {
  if (desc[x].len > avail) {
   return false;
  }
  
  avail -= desc[x].len;
  ++y;
 }
	
 ctx->tx.desc = desc;
 ctx->tx.nr_desc = nr_desc;
 return true;
}
static void usart_tx_abort(ctx_usart_t *ctx)
{
 ctx->tx.nr_desc = 0;
 ctx->tx.desc = NULL;
 ctx->tx.len = 0;
 ctx->tx.buf = NULL;
 return;
}

bool platform_usart_cdc_tx_async(
 const platform_usart_tx_bufdesc_t *desc,
 unsigned int nr_desc)
{
 return usart_tx_async(&ctx_uart_laptop, desc, nr_desc);
}
bool platform_usart_cdc_tx_busy(void)
{
 return usart_tx_busy(&ctx_uart_laptop);
}
void platform_usart_cdc_tx_abort(void)
{
 usart_tx_abort(&ctx_uart_laptop);
 return;
}

bool platform_usart_pms_tx_async(
 const platform_usart_tx_bufdesc_t *desc,
 unsigned int nr_desc)
{
 return usart_tx_async(&ctx_uart_pms, desc, nr_desc);
}
bool platform_usart_pms_tx_busy(void)
{
 return usart_tx_busy(&ctx_uart_pms);
}
void platform_usart_pms_tx_abort(void)
{
 usart_tx_abort(&ctx_uart_pms);
 return;
}

static bool usart_rx_busy(ctx_usart_t *ctx)
{
 return (ctx->rx.desc) != NULL;
}
static bool usart_rx_async(ctx_usart_t *ctx, platform_usart_rx_async_desc_t *desc)
{
 if (!desc|| !desc->buf || desc->max_len == 0 || desc->max_len > NR_USART_CHARS_MAX)
  return false;
	
 if ((ctx->rx.desc) != NULL)
  return false;
	
 desc->compl_type = PLATFORM_USART_RX_COMPL_NONE;
 desc->compl_info.data_len = 0;
 ctx->rx.idx = 0;
 platform_tick_hrcount(&ctx->rx.ts_idle);
 ctx->rx.desc = desc;
 return true;
}

bool platform_usart_cdc_rx_async(platform_usart_rx_async_desc_t *desc)
{
 return usart_rx_async(&ctx_uart_laptop, desc);
}
bool platform_usart_cdc_rx_busy(void)
{
 return usart_rx_busy(&ctx_uart_laptop);
}
void platform_usart_cdc_rx_abort(void)
{
 usart_rx_abort_helper(&ctx_uart_laptop);
}

bool platform_usart_pms_rx_async(platform_usart_rx_async_desc_t *desc)
{
 return usart_rx_async(&ctx_uart_pms, desc);
}
bool platform_usart_pms_rx_busy(void)
{
 return usart_rx_busy(&ctx_uart_pms);
}
void platform_usart_pms_rx_abort(void)
{
 usart_rx_abort_helper(&ctx_uart_pms);
}
/* 
 * File:   usart.c
 * Author: Shaquil
 *
 * Created on March 16, 2025, 9:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "sam.h"  // CMSIS header for PIC32CM LS00

// BAUD RATE settings
#define F_CPU 4000000  // Assume 4 MHz main clock
#define BAUD_RATE 9600
#define BAUD_VALUE ((F_CPU / (16 * BAUD_RATE)) - 1)

void uart_init(void);
void uart_send(uint8_t data);
uint8_t uart_receive(void);
void uart_send_string(const char *str);

void uart_init(void) {
    // Enable APB clock for SERCOM0
    MCLK->APBAMASK.reg |= MCLK_APBAMASK_SERCOM0;

    // Configure GCLK for SERCOM0
    GCLK->PCHCTRL[SERCOM0_GCLK_ID_CORE].reg = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN;
    while (!(GCLK->PCHCTRL[SERCOM0_GCLK_ID_CORE].reg & GCLK_PCHCTRL_CHEN));

    // Configure PA04 (TX) and PA05 (RX) for SERCOM0
    PORT->Group[0].PINCFG[4].bit.PMUXEN = 1;  // Enable peripheral mux on PA04
    PORT->Group[0].PINCFG[5].bit.PMUXEN = 1;  // Enable peripheral mux on PA05

    // PMUX[0] controls pins 0/1, 2/3, 4/5, so use PMUX[2] for 4/5
    PORT->Group[0].PMUX[4 >> 1].reg |= PORT_PMUX_PMUXE_D | PORT_PMUX_PMUXO_D;  // Function D for SERCOM0

    // Reset SERCOM0
    SERCOM0->USART.CTRLA.reg = SERCOM_USART_CTRLA_SWRST;
    while (SERCOM0->USART.SYNCBUSY.bit.SWRST);

    // Configure SERCOM0 for internal clock, UART mode
    SERCOM0->USART.CTRLA.reg =
        SERCOM_USART_CTRLA_MODE_USART_INT_CLK |    // Internal clock
        SERCOM_USART_CTRLA_RXPO(1) |               // PAD1 = RX
        SERCOM_USART_CTRLA_TXPO(0) |               // PAD0 = TX
        SERCOM_USART_CTRLA_DORD;                   // LSB first

    // Set baud rate
    SERCOM0->USART.BAUD.reg = BAUD_VALUE;

    // Enable RX and TX
    SERCOM0->USART.CTRLB.reg =
        SERCOM_USART_CTRLB_RXEN |
        SERCOM_USART_CTRLB_TXEN;
    while (SERCOM0->USART.SYNCBUSY.bit.CTRLB);

    // Enable SERCOM0 USART
    SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
    while (SERCOM0->USART.SYNCBUSY.bit.ENABLE);
}

void uart_send(uint8_t data) {
    // Wait until data register is empty
    while (!(SERCOM0->USART.INTFLAG.bit.DRE));
    SERCOM0->USART.DATA.reg = data;
}

uint8_t uart_receive(void) {
    // Wait until data is received
    while (!(SERCOM0->USART.INTFLAG.bit.RXC));
    return SERCOM0->USART.DATA.reg;
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_send(*str++);
    }
}

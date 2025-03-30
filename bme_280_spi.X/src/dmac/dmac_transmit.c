#include "dmac_transmit.h"

#define DMAC_CHANNELS_NUMBER        4U

#define DMAC_CRC_CHANNEL_OFFSET     0x20U

/* DMAC channels object configuration structure */
typedef struct
{
    uint8_t                inUse;
    DMAC_CHANNEL_CALLBACK  callback;

    uintptr_t              context;

    bool                busyStatus;

} DMAC_CH_OBJECT ;

/* Initial write back memory section for DMAC */
 static  dmac_descriptor_registers_t write_back_section[DMAC_CHANNELS_NUMBER]    __ALIGNED(8);

/* Descriptor section for DMAC */
 static  dmac_descriptor_registers_t  descriptor_section[DMAC_CHANNELS_NUMBER]    __ALIGNED(8);

/* DMAC Channels object information structure */
static volatile DMAC_CH_OBJECT dmacChannelObj[DMAC_CHANNELS_NUMBER];

void DMAC_Initialize( void )
{
    volatile DMAC_CH_OBJECT *dmacChObj = &dmacChannelObj[0];
    uint16_t channel = 0U;

    /* Initialize DMAC Channel objects */
    for(channel = 0U; channel < DMAC_CHANNELS_NUMBER; channel++)
    {
        dmacChObj->inUse = 0U;
        dmacChObj->callback = NULL;
        dmacChObj->context = 0U;
        dmacChObj->busyStatus = false;

        /* Point to next channel object */
        dmacChObj += 1U;
    }

    /* Update the Base address and Write Back address register */
    DMAC_REGS->DMAC_BASEADDR = (uint32_t) descriptor_section;
    DMAC_REGS->DMAC_WRBADDR  = (uint32_t) write_back_section;

    /* Update the Priority Control register */
    DMAC_REGS->DMAC_PRICTRL0 = DMAC_PRICTRL0_LVLPRI0(1UL) | DMAC_PRICTRL0_RRLVLEN0_Msk | DMAC_PRICTRL0_LVLPRI1(1UL) | DMAC_PRICTRL0_RRLVLEN1_Msk | DMAC_PRICTRL0_LVLPRI2(1UL) | DMAC_PRICTRL0_RRLVLEN2_Msk | DMAC_PRICTRL0_LVLPRI3(1UL) | DMAC_PRICTRL0_RRLVLEN3_Msk;

    /***************** Configure DMA channel 0 ********************/

    DMAC_REGS->DMAC_CHID = 0U;

    DMAC_REGS->DMAC_CHCTRLB = DMAC_CHCTRLB_TRIGACT(2UL) | DMAC_CHCTRLB_TRIGSRC(11UL) | DMAC_CHCTRLB_LVL(0UL) ;

    descriptor_section[0].DMAC_BTCTRL = (uint16_t)(DMAC_BTCTRL_BLOCKACT_INT | DMAC_BTCTRL_BEATSIZE_BYTE | DMAC_BTCTRL_VALID_Msk | DMAC_BTCTRL_SRCINC_Msk );

    dmacChannelObj[0].inUse = 1U;
    DMAC_REGS->DMAC_CHINTENSET = (uint8_t)(DMAC_CHINTENSET_TERR_Msk | DMAC_CHINTENSET_TCMPL_Msk);

    /***************** Configure DMA channel 1 ********************/

    DMAC_REGS->DMAC_CHID = 1U;

    DMAC_REGS->DMAC_CHCTRLB = DMAC_CHCTRLB_TRIGACT(2UL) | DMAC_CHCTRLB_TRIGSRC(10UL) | DMAC_CHCTRLB_LVL(0UL) ;

    descriptor_section[1].DMAC_BTCTRL = (uint16_t)(DMAC_BTCTRL_BLOCKACT_INT | DMAC_BTCTRL_BEATSIZE_BYTE | DMAC_BTCTRL_VALID_Msk | DMAC_BTCTRL_DSTINC_Msk );

    dmacChannelObj[1].inUse = 1U;
    DMAC_REGS->DMAC_CHINTENSET = (uint8_t)(DMAC_CHINTENSET_TERR_Msk | DMAC_CHINTENSET_TCMPL_Msk);

    /***************** Configure DMA channel 2 ********************/

    DMAC_REGS->DMAC_CHID = 2U;

    DMAC_REGS->DMAC_CHCTRLB = DMAC_CHCTRLB_TRIGACT(2UL) | DMAC_CHCTRLB_TRIGSRC(9UL) | DMAC_CHCTRLB_LVL(0UL) ;

    descriptor_section[2].DMAC_BTCTRL = (uint16_t)(DMAC_BTCTRL_BLOCKACT_INT | DMAC_BTCTRL_BEATSIZE_BYTE | DMAC_BTCTRL_VALID_Msk | DMAC_BTCTRL_SRCINC_Msk );

    dmacChannelObj[2].inUse = 1U;
    DMAC_REGS->DMAC_CHINTENSET = (uint8_t)(DMAC_CHINTENSET_TERR_Msk | DMAC_CHINTENSET_TCMPL_Msk);

    /***************** Configure DMA channel 3 ********************/

    DMAC_REGS->DMAC_CHID = 3U;

    DMAC_REGS->DMAC_CHCTRLB = DMAC_CHCTRLB_TRIGACT(2UL) | DMAC_CHCTRLB_TRIGSRC(8UL) | DMAC_CHCTRLB_LVL(0UL) ;

    descriptor_section[3].DMAC_BTCTRL = (uint16_t)(DMAC_BTCTRL_BLOCKACT_INT | DMAC_BTCTRL_BEATSIZE_BYTE | DMAC_BTCTRL_VALID_Msk | DMAC_BTCTRL_DSTINC_Msk );

    dmacChannelObj[3].inUse = 1U;
    DMAC_REGS->DMAC_CHINTENSET = (uint8_t)(DMAC_CHINTENSET_TERR_Msk | DMAC_CHINTENSET_TCMPL_Msk);

    /* Enable the DMAC module & Priority Level x Enable */
    DMAC_REGS->DMAC_CTRL = (uint16_t)(DMAC_CTRL_DMAENABLE_Msk | DMAC_CTRL_LVLEN0_Msk | DMAC_CTRL_LVLEN1_Msk | DMAC_CTRL_LVLEN2_Msk | DMAC_CTRL_LVLEN3_Msk);

    __DMB();
    __enable_irq();

    /* Enable the interrupt sources and configure the priorities as configured
     * from within the "Interrupt Manager" of MHC. */
    NVIC_SetPriority(DMAC_0_IRQn, 3);
    NVIC_EnableIRQ(DMAC_0_IRQn);
    NVIC_SetPriority(DMAC_1_IRQn, 3);
    NVIC_EnableIRQ(DMAC_1_IRQn);
    NVIC_SetPriority(DMAC_2_IRQn, 3);
    NVIC_EnableIRQ(DMAC_2_IRQn);
    NVIC_SetPriority(DMAC_3_IRQn, 3);
    NVIC_EnableIRQ(DMAC_3_IRQn);
}

/*******************************************************************************
    This function schedules a DMA transfer on the specified DMA channel.
********************************************************************************/

bool DMAC_ChannelTransfer( DMAC_CHANNEL channel, const void *srcAddr, const void *destAddr, size_t blockSize )
{
    uint8_t beat_size = 0U;
    uint8_t channelId = 0U;
    bool returnStatus = false;
    bool triggerCondition = false;
    const uint32_t* pu32srcAddr = (const uint32_t*)srcAddr;
    const uint32_t* pu32dstAddr = (const uint32_t*)destAddr;
    bool busyStatus = dmacChannelObj[channel].busyStatus;

    /* Save channel ID */
    channelId = DMAC_REGS->DMAC_CHID;

    /* Set the DMA channel */
    DMAC_REGS->DMAC_CHID = (uint8_t)channel;

    if (((DMAC_REGS->DMAC_CHINTFLAG & (DMAC_CHINTENCLR_TCMPL_Msk | DMAC_CHINTENCLR_TERR_Msk)) != 0U) || (busyStatus == false))
    {
        /* Clear the transfer complete flag */
        DMAC_REGS->DMAC_CHINTFLAG = DMAC_CHINTENCLR_TCMPL_Msk | DMAC_CHINTENCLR_TERR_Msk;

        dmacChannelObj[channel].busyStatus = true;

        /* Get a pointer to the module hardware instance */
        dmac_descriptor_registers_t *const dmacDescReg = &descriptor_section[channel];

        /* Set source address */
        if ((dmacDescReg->DMAC_BTCTRL & DMAC_BTCTRL_SRCINC_Msk) == DMAC_BTCTRL_SRCINC_Msk)
        {
            dmacDescReg->DMAC_SRCADDR = ((uintptr_t)pu32srcAddr + blockSize);
        }
        else
        {
            dmacDescReg->DMAC_SRCADDR = (uintptr_t)(pu32srcAddr);
        }

        /* Set destination address */
        if ((dmacDescReg->DMAC_BTCTRL & DMAC_BTCTRL_DSTINC_Msk) == DMAC_BTCTRL_DSTINC_Msk)
        {
            dmacDescReg->DMAC_DSTADDR = ((uintptr_t)pu32dstAddr + blockSize);
        }
        else
        {
            dmacDescReg->DMAC_DSTADDR = (uintptr_t)(pu32dstAddr);
        }

        /* Calculate the beat size and then set the BTCNT value */
        beat_size = (uint8_t)((dmacDescReg->DMAC_BTCTRL & DMAC_BTCTRL_BEATSIZE_Msk) >> DMAC_BTCTRL_BEATSIZE_Pos);

        /* Set Block Transfer Count */
        dmacDescReg->DMAC_BTCNT = (uint16_t)(blockSize / (1UL << beat_size));

        /* Enable the channel */
        DMAC_REGS->DMAC_CHCTRLA |= (uint8_t)DMAC_CHCTRLA_ENABLE_Msk;

        /* Verify if Trigger source is Software Trigger */
        triggerCondition = ((DMAC_REGS->DMAC_CHCTRLB & DMAC_CHCTRLB_EVIE_Msk) != DMAC_CHCTRLB_EVIE_Msk);
        triggerCondition = (((DMAC_REGS->DMAC_CHCTRLB & DMAC_CHCTRLB_TRIGSRC_Msk) >> DMAC_CHCTRLB_TRIGSRC_Pos) == 0x00U) && triggerCondition;
        if (triggerCondition)
        {
            /* Trigger the DMA transfer */
            DMAC_REGS->DMAC_SWTRIGCTRL |= (1UL << (uint32_t)channel);
        }

        returnStatus = true;
    }

    /* Restore channel ID */
    DMAC_REGS->DMAC_CHID = channelId;

    return returnStatus;
}

/*******************************************************************************
    This function returns the status of the channel.
********************************************************************************/

bool DMAC_ChannelIsBusy ( DMAC_CHANNEL channel )
{
    uint8_t channelId = 0U;
    bool busyStatus = dmacChannelObj[channel].busyStatus;
    bool isBusy = false;

    /* Save channel ID */
    channelId = (uint8_t)DMAC_REGS->DMAC_CHID;

    /* Set the DMA channel */
    DMAC_REGS->DMAC_CHID = (uint8_t)channel;

    if (((DMAC_REGS->DMAC_CHINTFLAG & (DMAC_CHINTENCLR_TCMPL_Msk | DMAC_CHINTENCLR_TERR_Msk)) == 0U) && (busyStatus == true))
    {
        isBusy = true;
    }

    /* Restore channel ID */
    DMAC_REGS->DMAC_CHID = channelId;

    return isBusy;
}


/*******************************************************************************
    This function function allows a DMAC PLIB client to set an event handler.
********************************************************************************/
void DMAC_ChannelCallbackRegister( DMAC_CHANNEL channel, const DMAC_CHANNEL_CALLBACK eventHandler, const uintptr_t contextHandle )
{
    dmacChannelObj[channel].callback = eventHandler;

    dmacChannelObj[channel].context  = contextHandle;
}

/*******************************************************************************
    This function handles the DMA interrupt events.
*/


void __attribute__((interrupt())) DMAC_0_Handler( void )
{
    volatile DMAC_CH_OBJECT  *dmacChObj;
    /* Get active channel number */
    uint8_t channel = 0U;
    uint8_t channelId = 0U;
    volatile uint32_t chanIntFlagStatus = 0U;
    DMAC_TRANSFER_EVENT event = DMAC_TRANSFER_EVENT_ERROR;

    dmacChObj = &dmacChannelObj[channel];

    /* Save channel ID */
    channelId = DMAC_REGS->DMAC_CHID;

    /* Update the DMAC channel ID */
    DMAC_REGS->DMAC_CHID = channel;

    /* Get the DMAC channel interrupt status */
    chanIntFlagStatus = (uint32_t)DMAC_REGS->DMAC_CHINTFLAG;

    /* Verify if DMAC Channel Transfer complete flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TCMPL_Msk) == DMAC_CHINTENCLR_TCMPL_Msk)
    {
        /* Clear the transfer complete flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TCMPL_Msk;

        event = DMAC_TRANSFER_EVENT_COMPLETE;

        dmacChObj->busyStatus = false;
    }

    /* Verify if DMAC Channel Error flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TERR_Msk) == DMAC_CHINTENCLR_TERR_Msk)
    {
        /* Clear transfer error flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TERR_Msk;

        event = DMAC_TRANSFER_EVENT_ERROR;

        dmacChObj->busyStatus = false;
    }

    /* Execute the callback function */
    if (dmacChObj->callback != NULL)
    {
        uintptr_t context = dmacChObj->context;

        dmacChObj->callback (event, context);
    }

    /* Restore channel ID */
    DMAC_REGS->DMAC_CHID = channelId;
}
void __attribute__((interrupt())) DMAC_1_Handler( void )
{
    volatile DMAC_CH_OBJECT  *dmacChObj;
    /* Get active channel number */
    uint8_t channel = 1U;
    uint8_t channelId = 0U;
    volatile uint32_t chanIntFlagStatus = 0U;
    DMAC_TRANSFER_EVENT event = DMAC_TRANSFER_EVENT_ERROR;

    dmacChObj = &dmacChannelObj[channel];

    /* Save channel ID */
    channelId = DMAC_REGS->DMAC_CHID;

    /* Update the DMAC channel ID */
    DMAC_REGS->DMAC_CHID = channel;

    /* Get the DMAC channel interrupt status */
    chanIntFlagStatus = (uint32_t)DMAC_REGS->DMAC_CHINTFLAG;

    /* Verify if DMAC Channel Transfer complete flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TCMPL_Msk) == DMAC_CHINTENCLR_TCMPL_Msk)
    {
        /* Clear the transfer complete flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TCMPL_Msk;

        event = DMAC_TRANSFER_EVENT_COMPLETE;

        dmacChObj->busyStatus = false;
    }

    /* Verify if DMAC Channel Error flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TERR_Msk) == DMAC_CHINTENCLR_TERR_Msk)
    {
        /* Clear transfer error flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TERR_Msk;

        event = DMAC_TRANSFER_EVENT_ERROR;

        dmacChObj->busyStatus = false;
    }

    /* Execute the callback function */
    if (dmacChObj->callback != NULL)
    {
        uintptr_t context = dmacChObj->context;

        dmacChObj->callback (event, context);
    }

    /* Restore channel ID */
    DMAC_REGS->DMAC_CHID = channelId;
}
void __attribute__((interrupt())) DMAC_2_Handler( void )
{
    volatile DMAC_CH_OBJECT  *dmacChObj;
    /* Get active channel number */
    uint8_t channel = 2U;
    uint8_t channelId = 0U;
    volatile uint32_t chanIntFlagStatus = 0U;
    DMAC_TRANSFER_EVENT event = DMAC_TRANSFER_EVENT_ERROR;

    dmacChObj = &dmacChannelObj[channel];

    /* Save channel ID */
    channelId = DMAC_REGS->DMAC_CHID;

    /* Update the DMAC channel ID */
    DMAC_REGS->DMAC_CHID = channel;

    /* Get the DMAC channel interrupt status */
    chanIntFlagStatus = (uint32_t)DMAC_REGS->DMAC_CHINTFLAG;

    /* Verify if DMAC Channel Transfer complete flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TCMPL_Msk) == DMAC_CHINTENCLR_TCMPL_Msk)
    {
        /* Clear the transfer complete flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TCMPL_Msk;

        event = DMAC_TRANSFER_EVENT_COMPLETE;

        dmacChObj->busyStatus = false;
    }

    /* Verify if DMAC Channel Error flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TERR_Msk) == DMAC_CHINTENCLR_TERR_Msk)
    {
        /* Clear transfer error flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TERR_Msk;

        event = DMAC_TRANSFER_EVENT_ERROR;

        dmacChObj->busyStatus = false;
    }

    /* Execute the callback function */
    if (dmacChObj->callback != NULL)
    {
        uintptr_t context = dmacChObj->context;

        dmacChObj->callback (event, context);
    }

    /* Restore channel ID */
    DMAC_REGS->DMAC_CHID = channelId;
}
void __attribute__((interrupt())) DMAC_3_Handler( void )
{
    volatile DMAC_CH_OBJECT  *dmacChObj;
    /* Get active channel number */
    uint8_t channel = 3U;
    uint8_t channelId = 0U;
    volatile uint32_t chanIntFlagStatus = 0U;
    DMAC_TRANSFER_EVENT event = DMAC_TRANSFER_EVENT_ERROR;

    dmacChObj = &dmacChannelObj[channel];

    /* Save channel ID */
    channelId = DMAC_REGS->DMAC_CHID;

    /* Update the DMAC channel ID */
    DMAC_REGS->DMAC_CHID = channel;

    /* Get the DMAC channel interrupt status */
    chanIntFlagStatus = (uint32_t)DMAC_REGS->DMAC_CHINTFLAG;

    /* Verify if DMAC Channel Transfer complete flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TCMPL_Msk) == DMAC_CHINTENCLR_TCMPL_Msk)
    {
        /* Clear the transfer complete flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TCMPL_Msk;

        event = DMAC_TRANSFER_EVENT_COMPLETE;

        dmacChObj->busyStatus = false;
    }

    /* Verify if DMAC Channel Error flag is set */
    if ((chanIntFlagStatus & DMAC_CHINTENCLR_TERR_Msk) == DMAC_CHINTENCLR_TERR_Msk)
    {
        /* Clear transfer error flag */
        DMAC_REGS->DMAC_CHINTFLAG = (uint8_t)DMAC_CHINTENCLR_TERR_Msk;

        event = DMAC_TRANSFER_EVENT_ERROR;

        dmacChObj->busyStatus = false;
    }

    /* Execute the callback function */
    if (dmacChObj->callback != NULL)
    {
        uintptr_t context = dmacChObj->context;

        dmacChObj->callback (event, context);
    }

    /* Restore channel ID */
    DMAC_REGS->DMAC_CHID = channelId;
}


/***************************************************************************//**
* \file LCDSPI_SPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCDSPI_PVT.h"
#include "LCDSPI_SPI_UART_PVT.h"

#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const LCDSPI_SPI_INIT_STRUCT LCDSPI_configSpi =
    {
        LCDSPI_SPI_MODE,
        LCDSPI_SPI_SUB_MODE,
        LCDSPI_SPI_CLOCK_MODE,
        LCDSPI_SPI_OVS_FACTOR,
        LCDSPI_SPI_MEDIAN_FILTER_ENABLE,
        LCDSPI_SPI_LATE_MISO_SAMPLE_ENABLE,
        LCDSPI_SPI_WAKE_ENABLE,
        LCDSPI_SPI_RX_DATA_BITS_NUM,
        LCDSPI_SPI_TX_DATA_BITS_NUM,
        LCDSPI_SPI_BITS_ORDER,
        LCDSPI_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) LCDSPI_SCB_IRQ_INTERNAL,
        LCDSPI_SPI_INTR_RX_MASK,
        LCDSPI_SPI_RX_TRIGGER_LEVEL,
        LCDSPI_SPI_INTR_TX_MASK,
        LCDSPI_SPI_TX_TRIGGER_LEVEL,
        (uint8) LCDSPI_SPI_BYTE_MODE_ENABLE,
        (uint8) LCDSPI_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) LCDSPI_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: LCDSPI_SpiInit
    ****************************************************************************//**
    *
    *  Configures the LCDSPI for SPI operation.
    *
    *  This function is intended specifically to be used when the LCDSPI 
    *  configuration is set to “Unconfigured LCDSPI” in the customizer. 
    *  After initializing the LCDSPI in SPI mode using this function, 
    *  the component can be enabled using the LCDSPI_Start() or 
    * LCDSPI_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void LCDSPI_SpiInit(const LCDSPI_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            LCDSPI_SetPins(LCDSPI_SCB_MODE_SPI, config->mode, LCDSPI_DUMMY_PARAM);

            /* Store internal configuration */
            LCDSPI_scbMode       = (uint8) LCDSPI_SCB_MODE_SPI;
            LCDSPI_scbEnableWake = (uint8) config->enableWake;
            LCDSPI_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            LCDSPI_rxBuffer      =         config->rxBuffer;
            LCDSPI_rxDataBits    = (uint8) config->rxDataBits;
            LCDSPI_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            LCDSPI_txBuffer      =         config->txBuffer;
            LCDSPI_txDataBits    = (uint8) config->txDataBits;
            LCDSPI_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            LCDSPI_CTRL_REG     = LCDSPI_GET_CTRL_OVS(config->oversample)           |
                                            LCDSPI_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            LCDSPI_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            LCDSPI_CTRL_SPI;

            LCDSPI_SPI_CTRL_REG = LCDSPI_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            LCDSPI_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          LCDSPI_SPI_MODE_TI_PRECEDES_MASK) |
                                            LCDSPI_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            LCDSPI_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            LCDSPI_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            LCDSPI_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            LCDSPI_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            LCDSPI_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            LCDSPI_RX_CTRL_REG     =  LCDSPI_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                LCDSPI_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                LCDSPI_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                LCDSPI_SPI_RX_CTRL;

            LCDSPI_RX_FIFO_CTRL_REG = LCDSPI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            LCDSPI_TX_CTRL_REG      = LCDSPI_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                LCDSPI_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                LCDSPI_SPI_TX_CTRL;

            LCDSPI_TX_FIFO_CTRL_REG = LCDSPI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (LCDSPI_ISR_NUMBER);
            CyIntSetPriority(LCDSPI_ISR_NUMBER, LCDSPI_ISR_PRIORITY);
            (void) CyIntSetVector(LCDSPI_ISR_NUMBER, &LCDSPI_SPI_UART_ISR);

            /* Configure interrupt sources */
            LCDSPI_INTR_I2C_EC_MASK_REG = LCDSPI_NO_INTR_SOURCES;
            LCDSPI_INTR_SPI_EC_MASK_REG = LCDSPI_NO_INTR_SOURCES;
            LCDSPI_INTR_SLAVE_MASK_REG  = LCDSPI_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            LCDSPI_INTR_MASTER_MASK_REG = LCDSPI_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            LCDSPI_INTR_RX_MASK_REG     = LCDSPI_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            LCDSPI_INTR_TX_MASK_REG     = LCDSPI_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            LCDSPI_IntrTxMask = LO16(LCDSPI_INTR_TX_MASK_REG);

            /* Set active SS0 */
            LCDSPI_SpiSetActiveSlaveSelect(LCDSPI_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            LCDSPI_rxBufferHead     = 0u;
            LCDSPI_rxBufferTail     = 0u;
            LCDSPI_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            LCDSPI_txBufferHead = 0u;
            LCDSPI_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: LCDSPI_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void LCDSPI_SpiInit(void)
    {
        /* Configure SPI interface */
        LCDSPI_CTRL_REG     = LCDSPI_SPI_DEFAULT_CTRL;
        LCDSPI_SPI_CTRL_REG = LCDSPI_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        LCDSPI_RX_CTRL_REG      = LCDSPI_SPI_DEFAULT_RX_CTRL;
        LCDSPI_RX_FIFO_CTRL_REG = LCDSPI_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        LCDSPI_TX_CTRL_REG      = LCDSPI_SPI_DEFAULT_TX_CTRL;
        LCDSPI_TX_FIFO_CTRL_REG = LCDSPI_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(LCDSPI_SCB_IRQ_INTERNAL)
            CyIntDisable    (LCDSPI_ISR_NUMBER);
            CyIntSetPriority(LCDSPI_ISR_NUMBER, LCDSPI_ISR_PRIORITY);
            (void) CyIntSetVector(LCDSPI_ISR_NUMBER, &LCDSPI_SPI_UART_ISR);
    #endif /* (LCDSPI_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        LCDSPI_INTR_I2C_EC_MASK_REG = LCDSPI_SPI_DEFAULT_INTR_I2C_EC_MASK;
        LCDSPI_INTR_SPI_EC_MASK_REG = LCDSPI_SPI_DEFAULT_INTR_SPI_EC_MASK;
        LCDSPI_INTR_SLAVE_MASK_REG  = LCDSPI_SPI_DEFAULT_INTR_SLAVE_MASK;
        LCDSPI_INTR_MASTER_MASK_REG = LCDSPI_SPI_DEFAULT_INTR_MASTER_MASK;
        LCDSPI_INTR_RX_MASK_REG     = LCDSPI_SPI_DEFAULT_INTR_RX_MASK;
        LCDSPI_INTR_TX_MASK_REG     = LCDSPI_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        LCDSPI_IntrTxMask = LO16(LCDSPI_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (LCDSPI_SPI_MASTER_CONST)
        LCDSPI_SpiSetActiveSlaveSelect(LCDSPI_SPI_SLAVE_SELECT0);
    #endif /* (LCDSPI_SPI_MASTER_CONST) */

    #if(LCDSPI_INTERNAL_RX_SW_BUFFER_CONST)
        LCDSPI_rxBufferHead     = 0u;
        LCDSPI_rxBufferTail     = 0u;
        LCDSPI_rxBufferOverflow = 0u;
    #endif /* (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(LCDSPI_INTERNAL_TX_SW_BUFFER_CONST)
        LCDSPI_txBufferHead = 0u;
        LCDSPI_txBufferTail = 0u;
    #endif /* (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: LCDSPI_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void LCDSPI_SpiPostEnable(void)
{
#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (LCDSPI_CHECK_SPI_MASTER)
    {
    #if (LCDSPI_CTS_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_CTS_SCLK_HSIOM_REG, LCDSPI_CTS_SCLK_HSIOM_MASK,
                                       LCDSPI_CTS_SCLK_HSIOM_POS, LCDSPI_CTS_SCLK_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_CTS_SCLK_PIN) */

    #if (LCDSPI_RTS_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_RTS_SS0_HSIOM_REG, LCDSPI_RTS_SS0_HSIOM_MASK,
                                       LCDSPI_RTS_SS0_HSIOM_POS, LCDSPI_RTS_SS0_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_RTS_SS0_PIN) */

    #if (LCDSPI_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS1_HSIOM_REG, LCDSPI_SS1_HSIOM_MASK,
                                       LCDSPI_SS1_HSIOM_POS, LCDSPI_SS1_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_SS1_PIN) */

    #if (LCDSPI_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS2_HSIOM_REG, LCDSPI_SS2_HSIOM_MASK,
                                       LCDSPI_SS2_HSIOM_POS, LCDSPI_SS2_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_SS2_PIN) */

    #if (LCDSPI_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS3_HSIOM_REG, LCDSPI_SS3_HSIOM_MASK,
                                       LCDSPI_SS3_HSIOM_POS, LCDSPI_SS3_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_SS3_PIN) */
    }

#else

    #if (LCDSPI_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SCLK_M_HSIOM_REG, LCDSPI_SCLK_M_HSIOM_MASK,
                                       LCDSPI_SCLK_M_HSIOM_POS, LCDSPI_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_MISO_SDA_TX_PIN_PIN) */

    #if (LCDSPI_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS0_M_HSIOM_REG, LCDSPI_SS0_M_HSIOM_MASK,
                                       LCDSPI_SS0_M_HSIOM_POS, LCDSPI_SS0_M_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_SPI_MASTER_SS0_PIN) */

    #if (LCDSPI_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS1_M_HSIOM_REG, LCDSPI_SS1_M_HSIOM_MASK,
                                       LCDSPI_SS1_M_HSIOM_POS, LCDSPI_SS1_M_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_SPI_MASTER_SS1_PIN) */

    #if (LCDSPI_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS2_M_HSIOM_REG, LCDSPI_SS2_M_HSIOM_MASK,
                                       LCDSPI_SS2_M_HSIOM_POS, LCDSPI_SS2_M_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_SPI_MASTER_SS2_PIN) */

    #if (LCDSPI_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS3_M_HSIOM_REG, LCDSPI_SS3_M_HSIOM_MASK,
                                       LCDSPI_SS3_M_HSIOM_POS, LCDSPI_SS3_M_HSIOM_SEL_SPI);
    #endif /* (LCDSPI_SPI_MASTER_SS3_PIN) */

#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    LCDSPI_SetTxInterruptMode(LCDSPI_IntrTxMask);
}


/*******************************************************************************
* Function Name: LCDSPI_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void LCDSPI_SpiStop(void)
{
#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (LCDSPI_CHECK_SPI_MASTER)
    {
    #if (LCDSPI_CTS_SCLK_PIN)
        /* Set output pin state after block is disabled */
        LCDSPI_uart_cts_spi_sclk_Write(LCDSPI_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_CTS_SCLK_HSIOM_REG, LCDSPI_CTS_SCLK_HSIOM_MASK,
                                       LCDSPI_CTS_SCLK_HSIOM_POS, LCDSPI_CTS_SCLK_HSIOM_SEL_GPIO);
    #endif /* (LCDSPI_uart_cts_spi_sclk_PIN) */

    #if (LCDSPI_RTS_SS0_PIN)
        /* Set output pin state after block is disabled */
        LCDSPI_uart_rts_spi_ss0_Write(LCDSPI_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_RTS_SS0_HSIOM_REG, LCDSPI_RTS_SS0_HSIOM_MASK,
                                       LCDSPI_RTS_SS0_HSIOM_POS, LCDSPI_RTS_SS0_HSIOM_SEL_GPIO);
    #endif /* (LCDSPI_uart_rts_spi_ss0_PIN) */

    #if (LCDSPI_SS1_PIN)
        /* Set output pin state after block is disabled */
        LCDSPI_spi_ss1_Write(LCDSPI_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS1_HSIOM_REG, LCDSPI_SS1_HSIOM_MASK,
                                       LCDSPI_SS1_HSIOM_POS, LCDSPI_SS1_HSIOM_SEL_GPIO);
    #endif /* (LCDSPI_SS1_PIN) */

    #if (LCDSPI_SS2_PIN)
        /* Set output pin state after block is disabled */
        LCDSPI_spi_ss2_Write(LCDSPI_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS2_HSIOM_REG, LCDSPI_SS2_HSIOM_MASK,
                                       LCDSPI_SS2_HSIOM_POS, LCDSPI_SS2_HSIOM_SEL_GPIO);
    #endif /* (LCDSPI_SS2_PIN) */

    #if (LCDSPI_SS3_PIN)
        /* Set output pin state after block is disabled */
        LCDSPI_spi_ss3_Write(LCDSPI_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS3_HSIOM_REG, LCDSPI_SS3_HSIOM_MASK,
                                       LCDSPI_SS3_HSIOM_POS, LCDSPI_SS3_HSIOM_SEL_GPIO);
    #endif /* (LCDSPI_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        LCDSPI_IntrTxMask = LO16(LCDSPI_GetTxInterruptMode() & LCDSPI_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        LCDSPI_IntrTxMask = LO16(LCDSPI_GetTxInterruptMode() & LCDSPI_INTR_SPIS_TX_RESTORE);
    }

#else

#if (LCDSPI_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    LCDSPI_sclk_m_Write(LCDSPI_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    LCDSPI_SET_HSIOM_SEL(LCDSPI_SCLK_M_HSIOM_REG, LCDSPI_SCLK_M_HSIOM_MASK,
                                   LCDSPI_SCLK_M_HSIOM_POS, LCDSPI_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (LCDSPI_MISO_SDA_TX_PIN_PIN) */

#if (LCDSPI_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    LCDSPI_ss0_m_Write(LCDSPI_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    LCDSPI_SET_HSIOM_SEL(LCDSPI_SS0_M_HSIOM_REG, LCDSPI_SS0_M_HSIOM_MASK,
                                   LCDSPI_SS0_M_HSIOM_POS, LCDSPI_SS0_M_HSIOM_SEL_GPIO);
#endif /* (LCDSPI_SPI_MASTER_SS0_PIN) */

#if (LCDSPI_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    LCDSPI_ss1_m_Write(LCDSPI_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    LCDSPI_SET_HSIOM_SEL(LCDSPI_SS1_M_HSIOM_REG, LCDSPI_SS1_M_HSIOM_MASK,
                                   LCDSPI_SS1_M_HSIOM_POS, LCDSPI_SS1_M_HSIOM_SEL_GPIO);
#endif /* (LCDSPI_SPI_MASTER_SS1_PIN) */

#if (LCDSPI_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    LCDSPI_ss2_m_Write(LCDSPI_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    LCDSPI_SET_HSIOM_SEL(LCDSPI_SS2_M_HSIOM_REG, LCDSPI_SS2_M_HSIOM_MASK,
                                   LCDSPI_SS2_M_HSIOM_POS, LCDSPI_SS2_M_HSIOM_SEL_GPIO);
#endif /* (LCDSPI_SPI_MASTER_SS2_PIN) */

#if (LCDSPI_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    LCDSPI_ss3_m_Write(LCDSPI_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    LCDSPI_SET_HSIOM_SEL(LCDSPI_SS3_M_HSIOM_REG, LCDSPI_SS3_M_HSIOM_MASK,
                                   LCDSPI_SS3_M_HSIOM_POS, LCDSPI_SS3_M_HSIOM_SEL_GPIO);
#endif /* (LCDSPI_SPI_MASTER_SS3_PIN) */

    #if (LCDSPI_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        LCDSPI_IntrTxMask = LO16(LCDSPI_GetTxInterruptMode() & LCDSPI_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        LCDSPI_IntrTxMask = LO16(LCDSPI_GetTxInterruptMode() & LCDSPI_INTR_SPIS_TX_RESTORE);
    #endif /* (LCDSPI_SPI_MASTER_CONST) */

#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (LCDSPI_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: LCDSPI_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - LCDSPI_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - LCDSPI_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - LCDSPI_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - LCDSPI_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void LCDSPI_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = LCDSPI_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~LCDSPI_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  LCDSPI_GET_SPI_CTRL_SS(slaveSelect);

        LCDSPI_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (LCDSPI_SPI_MASTER_CONST) */


#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: LCDSPI_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - LCDSPI_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - LCDSPI_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - LCDSPI_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - LCDSPI_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - LCDSPI_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - LCDSPI_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void LCDSPI_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = LCDSPI_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            LCDSPI_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            LCDSPI_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */


#if(LCDSPI_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: LCDSPI_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void LCDSPI_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        LCDSPI_ClearSpiExtClkInterruptSource(LCDSPI_INTR_SPI_EC_WAKE_UP);
        LCDSPI_SetSpiExtClkInterruptMode(LCDSPI_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: LCDSPI_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void LCDSPI_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        LCDSPI_SetSpiExtClkInterruptMode(LCDSPI_NO_INTR_SOURCES);
    }
#endif /* (LCDSPI_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */

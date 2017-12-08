/***************************************************************************//**
* \file LCD_SPI_SPI.c
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

#include "LCD_SPI_PVT.h"
#include "LCD_SPI_SPI_UART_PVT.h"

#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const LCD_SPI_SPI_INIT_STRUCT LCD_SPI_configSpi =
    {
        LCD_SPI_SPI_MODE,
        LCD_SPI_SPI_SUB_MODE,
        LCD_SPI_SPI_CLOCK_MODE,
        LCD_SPI_SPI_OVS_FACTOR,
        LCD_SPI_SPI_MEDIAN_FILTER_ENABLE,
        LCD_SPI_SPI_LATE_MISO_SAMPLE_ENABLE,
        LCD_SPI_SPI_WAKE_ENABLE,
        LCD_SPI_SPI_RX_DATA_BITS_NUM,
        LCD_SPI_SPI_TX_DATA_BITS_NUM,
        LCD_SPI_SPI_BITS_ORDER,
        LCD_SPI_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) LCD_SPI_SCB_IRQ_INTERNAL,
        LCD_SPI_SPI_INTR_RX_MASK,
        LCD_SPI_SPI_RX_TRIGGER_LEVEL,
        LCD_SPI_SPI_INTR_TX_MASK,
        LCD_SPI_SPI_TX_TRIGGER_LEVEL,
        (uint8) LCD_SPI_SPI_BYTE_MODE_ENABLE,
        (uint8) LCD_SPI_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) LCD_SPI_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: LCD_SPI_SpiInit
    ****************************************************************************//**
    *
    *  Configures the LCD_SPI for SPI operation.
    *
    *  This function is intended specifically to be used when the LCD_SPI 
    *  configuration is set to “Unconfigured LCD_SPI” in the customizer. 
    *  After initializing the LCD_SPI in SPI mode using this function, 
    *  the component can be enabled using the LCD_SPI_Start() or 
    * LCD_SPI_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void LCD_SPI_SpiInit(const LCD_SPI_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            LCD_SPI_SetPins(LCD_SPI_SCB_MODE_SPI, config->mode, LCD_SPI_DUMMY_PARAM);

            /* Store internal configuration */
            LCD_SPI_scbMode       = (uint8) LCD_SPI_SCB_MODE_SPI;
            LCD_SPI_scbEnableWake = (uint8) config->enableWake;
            LCD_SPI_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            LCD_SPI_rxBuffer      =         config->rxBuffer;
            LCD_SPI_rxDataBits    = (uint8) config->rxDataBits;
            LCD_SPI_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            LCD_SPI_txBuffer      =         config->txBuffer;
            LCD_SPI_txDataBits    = (uint8) config->txDataBits;
            LCD_SPI_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            LCD_SPI_CTRL_REG     = LCD_SPI_GET_CTRL_OVS(config->oversample)           |
                                            LCD_SPI_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            LCD_SPI_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            LCD_SPI_CTRL_SPI;

            LCD_SPI_SPI_CTRL_REG = LCD_SPI_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            LCD_SPI_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          LCD_SPI_SPI_MODE_TI_PRECEDES_MASK) |
                                            LCD_SPI_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            LCD_SPI_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            LCD_SPI_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            LCD_SPI_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            LCD_SPI_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            LCD_SPI_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            LCD_SPI_RX_CTRL_REG     =  LCD_SPI_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                LCD_SPI_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                LCD_SPI_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                LCD_SPI_SPI_RX_CTRL;

            LCD_SPI_RX_FIFO_CTRL_REG = LCD_SPI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            LCD_SPI_TX_CTRL_REG      = LCD_SPI_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                LCD_SPI_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                LCD_SPI_SPI_TX_CTRL;

            LCD_SPI_TX_FIFO_CTRL_REG = LCD_SPI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (LCD_SPI_ISR_NUMBER);
            CyIntSetPriority(LCD_SPI_ISR_NUMBER, LCD_SPI_ISR_PRIORITY);
            (void) CyIntSetVector(LCD_SPI_ISR_NUMBER, &LCD_SPI_SPI_UART_ISR);

            /* Configure interrupt sources */
            LCD_SPI_INTR_I2C_EC_MASK_REG = LCD_SPI_NO_INTR_SOURCES;
            LCD_SPI_INTR_SPI_EC_MASK_REG = LCD_SPI_NO_INTR_SOURCES;
            LCD_SPI_INTR_SLAVE_MASK_REG  = LCD_SPI_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            LCD_SPI_INTR_MASTER_MASK_REG = LCD_SPI_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            LCD_SPI_INTR_RX_MASK_REG     = LCD_SPI_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            LCD_SPI_INTR_TX_MASK_REG     = LCD_SPI_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            LCD_SPI_IntrTxMask = LO16(LCD_SPI_INTR_TX_MASK_REG);

            /* Set active SS0 */
            LCD_SPI_SpiSetActiveSlaveSelect(LCD_SPI_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            LCD_SPI_rxBufferHead     = 0u;
            LCD_SPI_rxBufferTail     = 0u;
            LCD_SPI_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            LCD_SPI_txBufferHead = 0u;
            LCD_SPI_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: LCD_SPI_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void LCD_SPI_SpiInit(void)
    {
        /* Configure SPI interface */
        LCD_SPI_CTRL_REG     = LCD_SPI_SPI_DEFAULT_CTRL;
        LCD_SPI_SPI_CTRL_REG = LCD_SPI_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        LCD_SPI_RX_CTRL_REG      = LCD_SPI_SPI_DEFAULT_RX_CTRL;
        LCD_SPI_RX_FIFO_CTRL_REG = LCD_SPI_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        LCD_SPI_TX_CTRL_REG      = LCD_SPI_SPI_DEFAULT_TX_CTRL;
        LCD_SPI_TX_FIFO_CTRL_REG = LCD_SPI_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(LCD_SPI_SCB_IRQ_INTERNAL)
            CyIntDisable    (LCD_SPI_ISR_NUMBER);
            CyIntSetPriority(LCD_SPI_ISR_NUMBER, LCD_SPI_ISR_PRIORITY);
            (void) CyIntSetVector(LCD_SPI_ISR_NUMBER, &LCD_SPI_SPI_UART_ISR);
    #endif /* (LCD_SPI_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        LCD_SPI_INTR_I2C_EC_MASK_REG = LCD_SPI_SPI_DEFAULT_INTR_I2C_EC_MASK;
        LCD_SPI_INTR_SPI_EC_MASK_REG = LCD_SPI_SPI_DEFAULT_INTR_SPI_EC_MASK;
        LCD_SPI_INTR_SLAVE_MASK_REG  = LCD_SPI_SPI_DEFAULT_INTR_SLAVE_MASK;
        LCD_SPI_INTR_MASTER_MASK_REG = LCD_SPI_SPI_DEFAULT_INTR_MASTER_MASK;
        LCD_SPI_INTR_RX_MASK_REG     = LCD_SPI_SPI_DEFAULT_INTR_RX_MASK;
        LCD_SPI_INTR_TX_MASK_REG     = LCD_SPI_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        LCD_SPI_IntrTxMask = LO16(LCD_SPI_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (LCD_SPI_SPI_MASTER_CONST)
        LCD_SPI_SpiSetActiveSlaveSelect(LCD_SPI_SPI_SLAVE_SELECT0);
    #endif /* (LCD_SPI_SPI_MASTER_CONST) */

    #if(LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST)
        LCD_SPI_rxBufferHead     = 0u;
        LCD_SPI_rxBufferTail     = 0u;
        LCD_SPI_rxBufferOverflow = 0u;
    #endif /* (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST)
        LCD_SPI_txBufferHead = 0u;
        LCD_SPI_txBufferTail = 0u;
    #endif /* (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: LCD_SPI_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void LCD_SPI_SpiPostEnable(void)
{
#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (LCD_SPI_CHECK_SPI_MASTER)
    {
    #if (LCD_SPI_CTS_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_CTS_SCLK_HSIOM_REG, LCD_SPI_CTS_SCLK_HSIOM_MASK,
                                       LCD_SPI_CTS_SCLK_HSIOM_POS, LCD_SPI_CTS_SCLK_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_CTS_SCLK_PIN) */

    #if (LCD_SPI_RTS_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_RTS_SS0_HSIOM_REG, LCD_SPI_RTS_SS0_HSIOM_MASK,
                                       LCD_SPI_RTS_SS0_HSIOM_POS, LCD_SPI_RTS_SS0_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_RTS_SS0_PIN) */

    #if (LCD_SPI_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS1_HSIOM_REG, LCD_SPI_SS1_HSIOM_MASK,
                                       LCD_SPI_SS1_HSIOM_POS, LCD_SPI_SS1_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_SS1_PIN) */

    #if (LCD_SPI_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS2_HSIOM_REG, LCD_SPI_SS2_HSIOM_MASK,
                                       LCD_SPI_SS2_HSIOM_POS, LCD_SPI_SS2_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_SS2_PIN) */

    #if (LCD_SPI_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS3_HSIOM_REG, LCD_SPI_SS3_HSIOM_MASK,
                                       LCD_SPI_SS3_HSIOM_POS, LCD_SPI_SS3_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_SS3_PIN) */
    }

#else

    #if (LCD_SPI_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SCLK_M_HSIOM_REG, LCD_SPI_SCLK_M_HSIOM_MASK,
                                       LCD_SPI_SCLK_M_HSIOM_POS, LCD_SPI_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_MISO_SDA_TX_PIN_PIN) */

    #if (LCD_SPI_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS0_M_HSIOM_REG, LCD_SPI_SS0_M_HSIOM_MASK,
                                       LCD_SPI_SS0_M_HSIOM_POS, LCD_SPI_SS0_M_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_SPI_MASTER_SS0_PIN) */

    #if (LCD_SPI_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS1_M_HSIOM_REG, LCD_SPI_SS1_M_HSIOM_MASK,
                                       LCD_SPI_SS1_M_HSIOM_POS, LCD_SPI_SS1_M_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_SPI_MASTER_SS1_PIN) */

    #if (LCD_SPI_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS2_M_HSIOM_REG, LCD_SPI_SS2_M_HSIOM_MASK,
                                       LCD_SPI_SS2_M_HSIOM_POS, LCD_SPI_SS2_M_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_SPI_MASTER_SS2_PIN) */

    #if (LCD_SPI_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS3_M_HSIOM_REG, LCD_SPI_SS3_M_HSIOM_MASK,
                                       LCD_SPI_SS3_M_HSIOM_POS, LCD_SPI_SS3_M_HSIOM_SEL_SPI);
    #endif /* (LCD_SPI_SPI_MASTER_SS3_PIN) */

#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    LCD_SPI_SetTxInterruptMode(LCD_SPI_IntrTxMask);
}


/*******************************************************************************
* Function Name: LCD_SPI_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void LCD_SPI_SpiStop(void)
{
#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (LCD_SPI_CHECK_SPI_MASTER)
    {
    #if (LCD_SPI_CTS_SCLK_PIN)
        /* Set output pin state after block is disabled */
        LCD_SPI_uart_cts_spi_sclk_Write(LCD_SPI_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_CTS_SCLK_HSIOM_REG, LCD_SPI_CTS_SCLK_HSIOM_MASK,
                                       LCD_SPI_CTS_SCLK_HSIOM_POS, LCD_SPI_CTS_SCLK_HSIOM_SEL_GPIO);
    #endif /* (LCD_SPI_uart_cts_spi_sclk_PIN) */

    #if (LCD_SPI_RTS_SS0_PIN)
        /* Set output pin state after block is disabled */
        LCD_SPI_uart_rts_spi_ss0_Write(LCD_SPI_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_RTS_SS0_HSIOM_REG, LCD_SPI_RTS_SS0_HSIOM_MASK,
                                       LCD_SPI_RTS_SS0_HSIOM_POS, LCD_SPI_RTS_SS0_HSIOM_SEL_GPIO);
    #endif /* (LCD_SPI_uart_rts_spi_ss0_PIN) */

    #if (LCD_SPI_SS1_PIN)
        /* Set output pin state after block is disabled */
        LCD_SPI_spi_ss1_Write(LCD_SPI_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS1_HSIOM_REG, LCD_SPI_SS1_HSIOM_MASK,
                                       LCD_SPI_SS1_HSIOM_POS, LCD_SPI_SS1_HSIOM_SEL_GPIO);
    #endif /* (LCD_SPI_SS1_PIN) */

    #if (LCD_SPI_SS2_PIN)
        /* Set output pin state after block is disabled */
        LCD_SPI_spi_ss2_Write(LCD_SPI_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS2_HSIOM_REG, LCD_SPI_SS2_HSIOM_MASK,
                                       LCD_SPI_SS2_HSIOM_POS, LCD_SPI_SS2_HSIOM_SEL_GPIO);
    #endif /* (LCD_SPI_SS2_PIN) */

    #if (LCD_SPI_SS3_PIN)
        /* Set output pin state after block is disabled */
        LCD_SPI_spi_ss3_Write(LCD_SPI_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS3_HSIOM_REG, LCD_SPI_SS3_HSIOM_MASK,
                                       LCD_SPI_SS3_HSIOM_POS, LCD_SPI_SS3_HSIOM_SEL_GPIO);
    #endif /* (LCD_SPI_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        LCD_SPI_IntrTxMask = LO16(LCD_SPI_GetTxInterruptMode() & LCD_SPI_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        LCD_SPI_IntrTxMask = LO16(LCD_SPI_GetTxInterruptMode() & LCD_SPI_INTR_SPIS_TX_RESTORE);
    }

#else

#if (LCD_SPI_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    LCD_SPI_sclk_m_Write(LCD_SPI_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SCLK_M_HSIOM_REG, LCD_SPI_SCLK_M_HSIOM_MASK,
                                   LCD_SPI_SCLK_M_HSIOM_POS, LCD_SPI_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (LCD_SPI_MISO_SDA_TX_PIN_PIN) */

#if (LCD_SPI_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    LCD_SPI_ss0_m_Write(LCD_SPI_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS0_M_HSIOM_REG, LCD_SPI_SS0_M_HSIOM_MASK,
                                   LCD_SPI_SS0_M_HSIOM_POS, LCD_SPI_SS0_M_HSIOM_SEL_GPIO);
#endif /* (LCD_SPI_SPI_MASTER_SS0_PIN) */

#if (LCD_SPI_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    LCD_SPI_ss1_m_Write(LCD_SPI_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS1_M_HSIOM_REG, LCD_SPI_SS1_M_HSIOM_MASK,
                                   LCD_SPI_SS1_M_HSIOM_POS, LCD_SPI_SS1_M_HSIOM_SEL_GPIO);
#endif /* (LCD_SPI_SPI_MASTER_SS1_PIN) */

#if (LCD_SPI_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    LCD_SPI_ss2_m_Write(LCD_SPI_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS2_M_HSIOM_REG, LCD_SPI_SS2_M_HSIOM_MASK,
                                   LCD_SPI_SS2_M_HSIOM_POS, LCD_SPI_SS2_M_HSIOM_SEL_GPIO);
#endif /* (LCD_SPI_SPI_MASTER_SS2_PIN) */

#if (LCD_SPI_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    LCD_SPI_ss3_m_Write(LCD_SPI_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    LCD_SPI_SET_HSIOM_SEL(LCD_SPI_SS3_M_HSIOM_REG, LCD_SPI_SS3_M_HSIOM_MASK,
                                   LCD_SPI_SS3_M_HSIOM_POS, LCD_SPI_SS3_M_HSIOM_SEL_GPIO);
#endif /* (LCD_SPI_SPI_MASTER_SS3_PIN) */

    #if (LCD_SPI_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        LCD_SPI_IntrTxMask = LO16(LCD_SPI_GetTxInterruptMode() & LCD_SPI_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        LCD_SPI_IntrTxMask = LO16(LCD_SPI_GetTxInterruptMode() & LCD_SPI_INTR_SPIS_TX_RESTORE);
    #endif /* (LCD_SPI_SPI_MASTER_CONST) */

#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (LCD_SPI_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: LCD_SPI_SetActiveSlaveSelect
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
    *   - LCD_SPI_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - LCD_SPI_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - LCD_SPI_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - LCD_SPI_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void LCD_SPI_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = LCD_SPI_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~LCD_SPI_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  LCD_SPI_GET_SPI_CTRL_SS(slaveSelect);

        LCD_SPI_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (LCD_SPI_SPI_MASTER_CONST) */


#if !(LCD_SPI_CY_SCBIP_V0 || LCD_SPI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: LCD_SPI_SpiSetSlaveSelectPolarity
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
    *   - LCD_SPI_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - LCD_SPI_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - LCD_SPI_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - LCD_SPI_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - LCD_SPI_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - LCD_SPI_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void LCD_SPI_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = LCD_SPI_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            LCD_SPI_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            LCD_SPI_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(LCD_SPI_CY_SCBIP_V0 || LCD_SPI_CY_SCBIP_V1) */


#if(LCD_SPI_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: LCD_SPI_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void LCD_SPI_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        LCD_SPI_ClearSpiExtClkInterruptSource(LCD_SPI_INTR_SPI_EC_WAKE_UP);
        LCD_SPI_SetSpiExtClkInterruptMode(LCD_SPI_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void LCD_SPI_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        LCD_SPI_SetSpiExtClkInterruptMode(LCD_SPI_NO_INTR_SOURCES);
    }
#endif /* (LCD_SPI_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */

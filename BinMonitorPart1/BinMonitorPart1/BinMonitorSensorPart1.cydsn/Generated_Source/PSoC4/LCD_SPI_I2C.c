/***************************************************************************//**
* \file LCD_SPI_I2C.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_SPI_PVT.h"
#include "LCD_SPI_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 LCD_SPI_state;  /* Current state of I2C FSM */

#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const LCD_SPI_I2C_INIT_STRUCT LCD_SPI_configI2C =
    {
        LCD_SPI_I2C_MODE,
        LCD_SPI_I2C_OVS_FACTOR_LOW,
        LCD_SPI_I2C_OVS_FACTOR_HIGH,
        LCD_SPI_I2C_MEDIAN_FILTER_ENABLE,
        LCD_SPI_I2C_SLAVE_ADDRESS,
        LCD_SPI_I2C_SLAVE_ADDRESS_MASK,
        LCD_SPI_I2C_ACCEPT_ADDRESS,
        LCD_SPI_I2C_WAKE_ENABLE,
        LCD_SPI_I2C_BYTE_MODE_ENABLE,
        LCD_SPI_I2C_DATA_RATE,
        LCD_SPI_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: LCD_SPI_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the LCD_SPI for I2C operation.
    *
    *  This function is intended specifically to be used when the LCD_SPI 
    *  configuration is set to “Unconfigured LCD_SPI” in the customizer. 
    *  After initializing the LCD_SPI in I2C mode using this function, 
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
    void LCD_SPI_I2CInit(const LCD_SPI_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            LCD_SPI_SetPins(LCD_SPI_SCB_MODE_I2C, LCD_SPI_DUMMY_PARAM,
                                     LCD_SPI_DUMMY_PARAM);

            /* Store internal configuration */
            LCD_SPI_scbMode       = (uint8) LCD_SPI_SCB_MODE_I2C;
            LCD_SPI_scbEnableWake = (uint8) config->enableWake;
            LCD_SPI_scbEnableIntr = (uint8) LCD_SPI_SCB_IRQ_INTERNAL;

            LCD_SPI_mode          = (uint8) config->mode;
            LCD_SPI_acceptAddr    = (uint8) config->acceptAddr;

        #if (LCD_SPI_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            LCD_SPI_SET_I2C_CFG_SDA_FILT_TRIM(LCD_SPI_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (LCD_SPI_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((LCD_SPI_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= LCD_SPI_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (LCD_SPI_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                LCD_SPI_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = LCD_SPI_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                LCD_SPI_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = LCD_SPI_DIGITAL_FILTER_ENABLE;
            }

        #if (!LCD_SPI_CY_SCBIP_V0)
            locEnableWake = (LCD_SPI_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!LCD_SPI_CY_SCBIP_V0) */

            /* Configure I2C interface */
            LCD_SPI_CTRL_REG     = LCD_SPI_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            LCD_SPI_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            LCD_SPI_GET_CTRL_EC_AM_MODE (locEnableWake);

            LCD_SPI_I2C_CTRL_REG = LCD_SPI_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    LCD_SPI_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    LCD_SPI_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    LCD_SPI_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            LCD_SPI_RX_CTRL_REG      = LCD_SPI_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                LCD_SPI_I2C_RX_CTRL;
            LCD_SPI_RX_FIFO_CTRL_REG = LCD_SPI_CLEAR_REG;

            /* Set default address and mask */
            LCD_SPI_RX_MATCH_REG    = ((LCD_SPI_I2C_SLAVE) ?
                                                (LCD_SPI_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 LCD_SPI_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (LCD_SPI_CLEAR_REG));


            /* Configure TX direction */
            LCD_SPI_TX_CTRL_REG      = LCD_SPI_I2C_TX_CTRL;
            LCD_SPI_TX_FIFO_CTRL_REG = LCD_SPI_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (LCD_SPI_ISR_NUMBER);
            CyIntSetPriority(LCD_SPI_ISR_NUMBER, LCD_SPI_ISR_PRIORITY);
            (void) CyIntSetVector(LCD_SPI_ISR_NUMBER, &LCD_SPI_I2C_ISR);

            /* Configure interrupt sources */
        #if(!LCD_SPI_CY_SCBIP_V1)
            LCD_SPI_INTR_SPI_EC_MASK_REG = LCD_SPI_NO_INTR_SOURCES;
        #endif /* (!LCD_SPI_CY_SCBIP_V1) */

            LCD_SPI_INTR_I2C_EC_MASK_REG = LCD_SPI_NO_INTR_SOURCES;
            LCD_SPI_INTR_RX_MASK_REG     = LCD_SPI_NO_INTR_SOURCES;
            LCD_SPI_INTR_TX_MASK_REG     = LCD_SPI_NO_INTR_SOURCES;

            LCD_SPI_INTR_SLAVE_MASK_REG  = ((LCD_SPI_I2C_SLAVE) ?
                            (LCD_SPI_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             LCD_SPI_I2C_INTR_SLAVE_MASK) : (LCD_SPI_CLEAR_REG));

            LCD_SPI_INTR_MASTER_MASK_REG = ((LCD_SPI_I2C_MASTER) ?
                                                     (LCD_SPI_I2C_INTR_MASTER_MASK) :
                                                     (LCD_SPI_CLEAR_REG));

            /* Configure global variables */
            LCD_SPI_state = LCD_SPI_I2C_FSM_IDLE;

            /* Internal slave variables */
            LCD_SPI_slStatus        = 0u;
            LCD_SPI_slRdBufIndex    = 0u;
            LCD_SPI_slWrBufIndex    = 0u;
            LCD_SPI_slOverFlowCount = 0u;

            /* Internal master variables */
            LCD_SPI_mstrStatus     = 0u;
            LCD_SPI_mstrRdBufIndex = 0u;
            LCD_SPI_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: LCD_SPI_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void LCD_SPI_I2CInit(void)
    {
    #if(LCD_SPI_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        LCD_SPI_SET_I2C_CFG_SDA_FILT_TRIM(LCD_SPI_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (LCD_SPI_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        LCD_SPI_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        LCD_SPI_CTRL_REG     = LCD_SPI_I2C_DEFAULT_CTRL;
        LCD_SPI_I2C_CTRL_REG = LCD_SPI_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        LCD_SPI_RX_CTRL_REG      = LCD_SPI_I2C_DEFAULT_RX_CTRL;
        LCD_SPI_RX_FIFO_CTRL_REG = LCD_SPI_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        LCD_SPI_RX_MATCH_REG     = LCD_SPI_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        LCD_SPI_TX_CTRL_REG      = LCD_SPI_I2C_DEFAULT_TX_CTRL;
        LCD_SPI_TX_FIFO_CTRL_REG = LCD_SPI_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (LCD_SPI_ISR_NUMBER);
        CyIntSetPriority(LCD_SPI_ISR_NUMBER, LCD_SPI_ISR_PRIORITY);
    #if(!LCD_SPI_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(LCD_SPI_ISR_NUMBER, &LCD_SPI_I2C_ISR);
    #endif /* (LCD_SPI_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!LCD_SPI_CY_SCBIP_V1)
        LCD_SPI_INTR_SPI_EC_MASK_REG = LCD_SPI_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!LCD_SPI_CY_SCBIP_V1) */

        LCD_SPI_INTR_I2C_EC_MASK_REG = LCD_SPI_I2C_DEFAULT_INTR_I2C_EC_MASK;
        LCD_SPI_INTR_SLAVE_MASK_REG  = LCD_SPI_I2C_DEFAULT_INTR_SLAVE_MASK;
        LCD_SPI_INTR_MASTER_MASK_REG = LCD_SPI_I2C_DEFAULT_INTR_MASTER_MASK;
        LCD_SPI_INTR_RX_MASK_REG     = LCD_SPI_I2C_DEFAULT_INTR_RX_MASK;
        LCD_SPI_INTR_TX_MASK_REG     = LCD_SPI_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        LCD_SPI_state = LCD_SPI_I2C_FSM_IDLE;

    #if(LCD_SPI_I2C_SLAVE)
        /* Internal slave variable */
        LCD_SPI_slStatus        = 0u;
        LCD_SPI_slRdBufIndex    = 0u;
        LCD_SPI_slWrBufIndex    = 0u;
        LCD_SPI_slOverFlowCount = 0u;
    #endif /* (LCD_SPI_I2C_SLAVE) */

    #if(LCD_SPI_I2C_MASTER)
    /* Internal master variable */
        LCD_SPI_mstrStatus     = 0u;
        LCD_SPI_mstrRdBufIndex = 0u;
        LCD_SPI_mstrWrBufIndex = 0u;
    #endif /* (LCD_SPI_I2C_MASTER) */
    }
#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: LCD_SPI_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void LCD_SPI_I2CStop(void)
{
    LCD_SPI_state = LCD_SPI_I2C_FSM_IDLE;
}


#if(LCD_SPI_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: LCD_SPI_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables LCD_SPI_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void LCD_SPI_I2CSaveConfig(void)
    {
    #if (!LCD_SPI_CY_SCBIP_V0)
        #if (LCD_SPI_I2C_MULTI_MASTER_SLAVE_CONST && LCD_SPI_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (LCD_SPI_CTRL_REG & LCD_SPI_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                LCD_SPI_Stop();
                LCD_SPI_CTRL_REG |= LCD_SPI_CTRL_EC_AM_MODE;
                LCD_SPI_Enable();
            }
        #endif /* (LCD_SPI_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (LCD_SPI_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            LCD_SPI_SCBCLK_Stop();
        #endif /* (LCD_SPI_SCB_CLK_INTERNAL) */
    #endif /* (!LCD_SPI_CY_SCBIP_V0) */

        LCD_SPI_SetI2CExtClkInterruptMode(LCD_SPI_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables LCD_SPI_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void LCD_SPI_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        LCD_SPI_SetI2CExtClkInterruptMode(LCD_SPI_NO_INTR_SOURCES);

    #if (!LCD_SPI_CY_SCBIP_V0)
        #if (LCD_SPI_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            LCD_SPI_SCBCLK_Start();
        #endif /* (LCD_SPI_SCB_CLK_INTERNAL) */
    #endif /* (!LCD_SPI_CY_SCBIP_V0) */
    }
#endif /* (LCD_SPI_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */

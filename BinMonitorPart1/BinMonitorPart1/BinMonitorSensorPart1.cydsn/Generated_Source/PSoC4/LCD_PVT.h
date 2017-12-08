/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_LCD_H)
#define CY_SCB_PVT_LCD_H

#include "LCD.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define LCD_SetI2CExtClkInterruptMode(interruptMask) LCD_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define LCD_ClearI2CExtClkInterruptSource(interruptMask) LCD_CLEAR_INTR_I2C_EC(interruptMask)
#define LCD_GetI2CExtClkInterruptSource()                (LCD_INTR_I2C_EC_REG)
#define LCD_GetI2CExtClkInterruptMode()                  (LCD_INTR_I2C_EC_MASK_REG)
#define LCD_GetI2CExtClkInterruptSourceMasked()          (LCD_INTR_I2C_EC_MASKED_REG)

#if (!LCD_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define LCD_SetSpiExtClkInterruptMode(interruptMask) \
                                                                LCD_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define LCD_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                LCD_CLEAR_INTR_SPI_EC(interruptMask)
    #define LCD_GetExtSpiClkInterruptSource()                 (LCD_INTR_SPI_EC_REG)
    #define LCD_GetExtSpiClkInterruptMode()                   (LCD_INTR_SPI_EC_MASK_REG)
    #define LCD_GetExtSpiClkInterruptSourceMasked()           (LCD_INTR_SPI_EC_MASKED_REG)
#endif /* (!LCD_CY_SCBIP_V1) */

#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void LCD_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (LCD_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_LCD_CUSTOM_INTR_HANDLER)
    extern cyisraddress LCD_customIntrHandler;
#endif /* !defined (CY_REMOVE_LCD_CUSTOM_INTR_HANDLER) */
#endif /* (LCD_SCB_IRQ_INTERNAL) */

extern LCD_BACKUP_STRUCT LCD_backup;

#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 LCD_scbMode;
    extern uint8 LCD_scbEnableWake;
    extern uint8 LCD_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 LCD_mode;
    extern uint8 LCD_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * LCD_rxBuffer;
    extern uint8   LCD_rxDataBits;
    extern uint32  LCD_rxBufferSize;

    extern volatile uint8 * LCD_txBuffer;
    extern uint8   LCD_txDataBits;
    extern uint32  LCD_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 LCD_numberOfAddr;
    extern uint8 LCD_subAddrSize;
#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (LCD_SCB_MODE_I2C_CONST_CFG || \
        LCD_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 LCD_IntrTxMask;
#endif /* (! (LCD_SCB_MODE_I2C_CONST_CFG || \
              LCD_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define LCD_SCB_MODE_I2C_RUNTM_CFG     (LCD_SCB_MODE_I2C      == LCD_scbMode)
    #define LCD_SCB_MODE_SPI_RUNTM_CFG     (LCD_SCB_MODE_SPI      == LCD_scbMode)
    #define LCD_SCB_MODE_UART_RUNTM_CFG    (LCD_SCB_MODE_UART     == LCD_scbMode)
    #define LCD_SCB_MODE_EZI2C_RUNTM_CFG   (LCD_SCB_MODE_EZI2C    == LCD_scbMode)
    #define LCD_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (LCD_SCB_MODE_UNCONFIG == LCD_scbMode)

    /* Defines wakeup enable */
    #define LCD_SCB_WAKE_ENABLE_CHECK       (0u != LCD_scbEnableWake)
#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!LCD_CY_SCBIP_V1)
    #define LCD_SCB_PINS_NUMBER    (7u)
#else
    #define LCD_SCB_PINS_NUMBER    (2u)
#endif /* (!LCD_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_LCD_H) */


/* [] END OF FILE */

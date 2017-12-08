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

#if !defined(CY_SCB_PVT_LCD_SPI_H)
#define CY_SCB_PVT_LCD_SPI_H

#include "LCD_SPI.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define LCD_SPI_SetI2CExtClkInterruptMode(interruptMask) LCD_SPI_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define LCD_SPI_ClearI2CExtClkInterruptSource(interruptMask) LCD_SPI_CLEAR_INTR_I2C_EC(interruptMask)
#define LCD_SPI_GetI2CExtClkInterruptSource()                (LCD_SPI_INTR_I2C_EC_REG)
#define LCD_SPI_GetI2CExtClkInterruptMode()                  (LCD_SPI_INTR_I2C_EC_MASK_REG)
#define LCD_SPI_GetI2CExtClkInterruptSourceMasked()          (LCD_SPI_INTR_I2C_EC_MASKED_REG)

#if (!LCD_SPI_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define LCD_SPI_SetSpiExtClkInterruptMode(interruptMask) \
                                                                LCD_SPI_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define LCD_SPI_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                LCD_SPI_CLEAR_INTR_SPI_EC(interruptMask)
    #define LCD_SPI_GetExtSpiClkInterruptSource()                 (LCD_SPI_INTR_SPI_EC_REG)
    #define LCD_SPI_GetExtSpiClkInterruptMode()                   (LCD_SPI_INTR_SPI_EC_MASK_REG)
    #define LCD_SPI_GetExtSpiClkInterruptSourceMasked()           (LCD_SPI_INTR_SPI_EC_MASKED_REG)
#endif /* (!LCD_SPI_CY_SCBIP_V1) */

#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void LCD_SPI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (LCD_SPI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_LCD_SPI_CUSTOM_INTR_HANDLER)
    extern cyisraddress LCD_SPI_customIntrHandler;
#endif /* !defined (CY_REMOVE_LCD_SPI_CUSTOM_INTR_HANDLER) */
#endif /* (LCD_SPI_SCB_IRQ_INTERNAL) */

extern LCD_SPI_BACKUP_STRUCT LCD_SPI_backup;

#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 LCD_SPI_scbMode;
    extern uint8 LCD_SPI_scbEnableWake;
    extern uint8 LCD_SPI_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 LCD_SPI_mode;
    extern uint8 LCD_SPI_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * LCD_SPI_rxBuffer;
    extern uint8   LCD_SPI_rxDataBits;
    extern uint32  LCD_SPI_rxBufferSize;

    extern volatile uint8 * LCD_SPI_txBuffer;
    extern uint8   LCD_SPI_txDataBits;
    extern uint32  LCD_SPI_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 LCD_SPI_numberOfAddr;
    extern uint8 LCD_SPI_subAddrSize;
#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (LCD_SPI_SCB_MODE_I2C_CONST_CFG || \
        LCD_SPI_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 LCD_SPI_IntrTxMask;
#endif /* (! (LCD_SPI_SCB_MODE_I2C_CONST_CFG || \
              LCD_SPI_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define LCD_SPI_SCB_MODE_I2C_RUNTM_CFG     (LCD_SPI_SCB_MODE_I2C      == LCD_SPI_scbMode)
    #define LCD_SPI_SCB_MODE_SPI_RUNTM_CFG     (LCD_SPI_SCB_MODE_SPI      == LCD_SPI_scbMode)
    #define LCD_SPI_SCB_MODE_UART_RUNTM_CFG    (LCD_SPI_SCB_MODE_UART     == LCD_SPI_scbMode)
    #define LCD_SPI_SCB_MODE_EZI2C_RUNTM_CFG   (LCD_SPI_SCB_MODE_EZI2C    == LCD_SPI_scbMode)
    #define LCD_SPI_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (LCD_SPI_SCB_MODE_UNCONFIG == LCD_SPI_scbMode)

    /* Defines wakeup enable */
    #define LCD_SPI_SCB_WAKE_ENABLE_CHECK       (0u != LCD_SPI_scbEnableWake)
#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!LCD_SPI_CY_SCBIP_V1)
    #define LCD_SPI_SCB_PINS_NUMBER    (7u)
#else
    #define LCD_SPI_SCB_PINS_NUMBER    (2u)
#endif /* (!LCD_SPI_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_LCD_SPI_H) */


/* [] END OF FILE */

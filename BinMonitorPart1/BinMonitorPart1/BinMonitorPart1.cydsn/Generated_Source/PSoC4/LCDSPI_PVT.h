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

#if !defined(CY_SCB_PVT_LCDSPI_H)
#define CY_SCB_PVT_LCDSPI_H

#include "LCDSPI.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define LCDSPI_SetI2CExtClkInterruptMode(interruptMask) LCDSPI_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define LCDSPI_ClearI2CExtClkInterruptSource(interruptMask) LCDSPI_CLEAR_INTR_I2C_EC(interruptMask)
#define LCDSPI_GetI2CExtClkInterruptSource()                (LCDSPI_INTR_I2C_EC_REG)
#define LCDSPI_GetI2CExtClkInterruptMode()                  (LCDSPI_INTR_I2C_EC_MASK_REG)
#define LCDSPI_GetI2CExtClkInterruptSourceMasked()          (LCDSPI_INTR_I2C_EC_MASKED_REG)

#if (!LCDSPI_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define LCDSPI_SetSpiExtClkInterruptMode(interruptMask) \
                                                                LCDSPI_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define LCDSPI_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                LCDSPI_CLEAR_INTR_SPI_EC(interruptMask)
    #define LCDSPI_GetExtSpiClkInterruptSource()                 (LCDSPI_INTR_SPI_EC_REG)
    #define LCDSPI_GetExtSpiClkInterruptMode()                   (LCDSPI_INTR_SPI_EC_MASK_REG)
    #define LCDSPI_GetExtSpiClkInterruptSourceMasked()           (LCDSPI_INTR_SPI_EC_MASKED_REG)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void LCDSPI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (LCDSPI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_LCDSPI_CUSTOM_INTR_HANDLER)
    extern cyisraddress LCDSPI_customIntrHandler;
#endif /* !defined (CY_REMOVE_LCDSPI_CUSTOM_INTR_HANDLER) */
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */

extern LCDSPI_BACKUP_STRUCT LCDSPI_backup;

#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 LCDSPI_scbMode;
    extern uint8 LCDSPI_scbEnableWake;
    extern uint8 LCDSPI_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 LCDSPI_mode;
    extern uint8 LCDSPI_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * LCDSPI_rxBuffer;
    extern uint8   LCDSPI_rxDataBits;
    extern uint32  LCDSPI_rxBufferSize;

    extern volatile uint8 * LCDSPI_txBuffer;
    extern uint8   LCDSPI_txDataBits;
    extern uint32  LCDSPI_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 LCDSPI_numberOfAddr;
    extern uint8 LCDSPI_subAddrSize;
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (LCDSPI_SCB_MODE_I2C_CONST_CFG || \
        LCDSPI_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 LCDSPI_IntrTxMask;
#endif /* (! (LCDSPI_SCB_MODE_I2C_CONST_CFG || \
              LCDSPI_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define LCDSPI_SCB_MODE_I2C_RUNTM_CFG     (LCDSPI_SCB_MODE_I2C      == LCDSPI_scbMode)
    #define LCDSPI_SCB_MODE_SPI_RUNTM_CFG     (LCDSPI_SCB_MODE_SPI      == LCDSPI_scbMode)
    #define LCDSPI_SCB_MODE_UART_RUNTM_CFG    (LCDSPI_SCB_MODE_UART     == LCDSPI_scbMode)
    #define LCDSPI_SCB_MODE_EZI2C_RUNTM_CFG   (LCDSPI_SCB_MODE_EZI2C    == LCDSPI_scbMode)
    #define LCDSPI_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (LCDSPI_SCB_MODE_UNCONFIG == LCDSPI_scbMode)

    /* Defines wakeup enable */
    #define LCDSPI_SCB_WAKE_ENABLE_CHECK       (0u != LCDSPI_scbEnableWake)
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_SCB_PINS_NUMBER    (7u)
#else
    #define LCDSPI_SCB_PINS_NUMBER    (2u)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_LCDSPI_H) */


/* [] END OF FILE */

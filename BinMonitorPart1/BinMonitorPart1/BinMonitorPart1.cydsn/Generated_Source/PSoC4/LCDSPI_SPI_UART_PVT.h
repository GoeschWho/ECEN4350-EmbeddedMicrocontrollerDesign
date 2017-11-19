/***************************************************************************//**
* \file LCDSPI_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_LCDSPI_H)
#define CY_SCB_SPI_UART_PVT_LCDSPI_H

#include "LCDSPI_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  LCDSPI_rxBufferHead;
    extern volatile uint32  LCDSPI_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   LCDSPI_rxBufferOverflow;
    /** @} globals */
#endif /* (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST) */

#if (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  LCDSPI_txBufferHead;
    extern volatile uint32  LCDSPI_txBufferTail;
#endif /* (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST) */

#if (LCDSPI_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 LCDSPI_rxBufferInternal[LCDSPI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (LCDSPI_INTERNAL_RX_SW_BUFFER) */

#if (LCDSPI_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 LCDSPI_txBufferInternal[LCDSPI_TX_BUFFER_SIZE];
#endif /* (LCDSPI_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void LCDSPI_SpiPostEnable(void);
void LCDSPI_SpiStop(void);

#if (LCDSPI_SCB_MODE_SPI_CONST_CFG)
    void LCDSPI_SpiInit(void);
#endif /* (LCDSPI_SCB_MODE_SPI_CONST_CFG) */

#if (LCDSPI_SPI_WAKE_ENABLE_CONST)
    void LCDSPI_SpiSaveConfig(void);
    void LCDSPI_SpiRestoreConfig(void);
#endif /* (LCDSPI_SPI_WAKE_ENABLE_CONST) */

void LCDSPI_UartPostEnable(void);
void LCDSPI_UartStop(void);

#if (LCDSPI_SCB_MODE_UART_CONST_CFG)
    void LCDSPI_UartInit(void);
#endif /* (LCDSPI_SCB_MODE_UART_CONST_CFG) */

#if (LCDSPI_UART_WAKE_ENABLE_CONST)
    void LCDSPI_UartSaveConfig(void);
    void LCDSPI_UartRestoreConfig(void);
#endif /* (LCDSPI_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in LCDSPI_SetPins() */
#define LCDSPI_UART_RX_PIN_ENABLE    (LCDSPI_UART_RX)
#define LCDSPI_UART_TX_PIN_ENABLE    (LCDSPI_UART_TX)

/* UART RTS and CTS position to be used in  LCDSPI_SetPins() */
#define LCDSPI_UART_RTS_PIN_ENABLE    (0x10u)
#define LCDSPI_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define LCDSPI_SpiUartEnableIntRx(intSourceMask)  LCDSPI_SetRxInterruptMode(intSourceMask)
#define LCDSPI_SpiUartEnableIntTx(intSourceMask)  LCDSPI_SetTxInterruptMode(intSourceMask)
uint32  LCDSPI_SpiUartDisableIntRx(void);
uint32  LCDSPI_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_LCDSPI_H) */


/* [] END OF FILE */

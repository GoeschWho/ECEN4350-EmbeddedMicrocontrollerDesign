/***************************************************************************//**
* \file LCD_SPI_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_LCD_SPI_H)
#define CY_SCB_SPI_UART_PVT_LCD_SPI_H

#include "LCD_SPI_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  LCD_SPI_rxBufferHead;
    extern volatile uint32  LCD_SPI_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   LCD_SPI_rxBufferOverflow;
    /** @} globals */
#endif /* (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

#if (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  LCD_SPI_txBufferHead;
    extern volatile uint32  LCD_SPI_txBufferTail;
#endif /* (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

#if (LCD_SPI_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 LCD_SPI_rxBufferInternal[LCD_SPI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (LCD_SPI_INTERNAL_RX_SW_BUFFER) */

#if (LCD_SPI_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 LCD_SPI_txBufferInternal[LCD_SPI_TX_BUFFER_SIZE];
#endif /* (LCD_SPI_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void LCD_SPI_SpiPostEnable(void);
void LCD_SPI_SpiStop(void);

#if (LCD_SPI_SCB_MODE_SPI_CONST_CFG)
    void LCD_SPI_SpiInit(void);
#endif /* (LCD_SPI_SCB_MODE_SPI_CONST_CFG) */

#if (LCD_SPI_SPI_WAKE_ENABLE_CONST)
    void LCD_SPI_SpiSaveConfig(void);
    void LCD_SPI_SpiRestoreConfig(void);
#endif /* (LCD_SPI_SPI_WAKE_ENABLE_CONST) */

void LCD_SPI_UartPostEnable(void);
void LCD_SPI_UartStop(void);

#if (LCD_SPI_SCB_MODE_UART_CONST_CFG)
    void LCD_SPI_UartInit(void);
#endif /* (LCD_SPI_SCB_MODE_UART_CONST_CFG) */

#if (LCD_SPI_UART_WAKE_ENABLE_CONST)
    void LCD_SPI_UartSaveConfig(void);
    void LCD_SPI_UartRestoreConfig(void);
#endif /* (LCD_SPI_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in LCD_SPI_SetPins() */
#define LCD_SPI_UART_RX_PIN_ENABLE    (LCD_SPI_UART_RX)
#define LCD_SPI_UART_TX_PIN_ENABLE    (LCD_SPI_UART_TX)

/* UART RTS and CTS position to be used in  LCD_SPI_SetPins() */
#define LCD_SPI_UART_RTS_PIN_ENABLE    (0x10u)
#define LCD_SPI_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define LCD_SPI_SpiUartEnableIntRx(intSourceMask)  LCD_SPI_SetRxInterruptMode(intSourceMask)
#define LCD_SPI_SpiUartEnableIntTx(intSourceMask)  LCD_SPI_SetTxInterruptMode(intSourceMask)
uint32  LCD_SPI_SpiUartDisableIntRx(void);
uint32  LCD_SPI_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_LCD_SPI_H) */


/* [] END OF FILE */

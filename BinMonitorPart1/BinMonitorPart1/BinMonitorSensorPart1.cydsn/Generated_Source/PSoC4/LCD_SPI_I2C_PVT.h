/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_LCD_SPI_H)
#define CY_SCB_I2C_PVT_LCD_SPI_H

#include "LCD_SPI_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 LCD_SPI_state; /* Current state of I2C FSM */

#if(LCD_SPI_I2C_SLAVE_CONST)
    extern volatile uint8 LCD_SPI_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * LCD_SPI_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  LCD_SPI_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  LCD_SPI_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * LCD_SPI_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  LCD_SPI_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  LCD_SPI_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  LCD_SPI_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   LCD_SPI_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (LCD_SPI_I2C_SLAVE_CONST) */

#if(LCD_SPI_I2C_MASTER_CONST)
    extern volatile uint16 LCD_SPI_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  LCD_SPI_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * LCD_SPI_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  LCD_SPI_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  LCD_SPI_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * LCD_SPI_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  LCD_SPI_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  LCD_SPI_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  LCD_SPI_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (LCD_SPI_I2C_MASTER_CONST) */

#if (LCD_SPI_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*LCD_SPI_customAddressHandler) (void);
#endif /* (LCD_SPI_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(LCD_SPI_SCB_MODE_I2C_CONST_CFG)
    void LCD_SPI_I2CInit(void);
#endif /* (LCD_SPI_SCB_MODE_I2C_CONST_CFG) */

void LCD_SPI_I2CStop(void);
void LCD_SPI_I2CSaveConfig(void);
void LCD_SPI_I2CRestoreConfig(void);

#if(LCD_SPI_I2C_MASTER_CONST)
    void LCD_SPI_I2CReStartGeneration(void);
#endif /* (LCD_SPI_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_LCD_SPI_H) */


/* [] END OF FILE */

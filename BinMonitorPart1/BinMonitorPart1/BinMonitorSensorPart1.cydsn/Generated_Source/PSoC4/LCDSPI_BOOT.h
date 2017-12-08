/***************************************************************************//**
* \file LCDSPI_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_LCDSPI_H)
#define CY_SCB_BOOT_LCDSPI_H

#include "LCDSPI_PVT.h"

#if (LCDSPI_SCB_MODE_I2C_INC)
    #include "LCDSPI_I2C.h"
#endif /* (LCDSPI_SCB_MODE_I2C_INC) */

#if (LCDSPI_SCB_MODE_EZI2C_INC)
    #include "LCDSPI_EZI2C.h"
#endif /* (LCDSPI_SCB_MODE_EZI2C_INC) */

#if (LCDSPI_SCB_MODE_SPI_INC || LCDSPI_SCB_MODE_UART_INC)
    #include "LCDSPI_SPI_UART.h"
#endif /* (LCDSPI_SCB_MODE_SPI_INC || LCDSPI_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define LCDSPI_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCDSPI) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (LCDSPI_SCB_MODE_I2C_INC)
    #define LCDSPI_I2C_BTLDR_COMM_ENABLED     (LCDSPI_BTLDR_COMM_ENABLED && \
                                                            (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             LCDSPI_I2C_SLAVE_CONST))
#else
     #define LCDSPI_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (LCDSPI_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (LCDSPI_SCB_MODE_EZI2C_INC)
    #define LCDSPI_EZI2C_BTLDR_COMM_ENABLED   (LCDSPI_BTLDR_COMM_ENABLED && \
                                                         LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define LCDSPI_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (LCDSPI_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (LCDSPI_SCB_MODE_SPI_INC)
    #define LCDSPI_SPI_BTLDR_COMM_ENABLED     (LCDSPI_BTLDR_COMM_ENABLED && \
                                                            (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             LCDSPI_SPI_SLAVE_CONST))
#else
        #define LCDSPI_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (LCDSPI_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (LCDSPI_SCB_MODE_UART_INC)
       #define LCDSPI_UART_BTLDR_COMM_ENABLED    (LCDSPI_BTLDR_COMM_ENABLED && \
                                                            (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (LCDSPI_UART_RX_DIRECTION && \
                                                              LCDSPI_UART_TX_DIRECTION)))
#else
     #define LCDSPI_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (LCDSPI_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define LCDSPI_BTLDR_COMM_MODE_ENABLED    (LCDSPI_I2C_BTLDR_COMM_ENABLED   || \
                                                     LCDSPI_SPI_BTLDR_COMM_ENABLED   || \
                                                     LCDSPI_EZI2C_BTLDR_COMM_ENABLED || \
                                                     LCDSPI_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void LCDSPI_I2CCyBtldrCommStart(void);
    void LCDSPI_I2CCyBtldrCommStop (void);
    void LCDSPI_I2CCyBtldrCommReset(void);
    cystatus LCDSPI_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCDSPI_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (LCDSPI_SCB_MODE_I2C_CONST_CFG)
        #define LCDSPI_CyBtldrCommStart   LCDSPI_I2CCyBtldrCommStart
        #define LCDSPI_CyBtldrCommStop    LCDSPI_I2CCyBtldrCommStop
        #define LCDSPI_CyBtldrCommReset   LCDSPI_I2CCyBtldrCommReset
        #define LCDSPI_CyBtldrCommRead    LCDSPI_I2CCyBtldrCommRead
        #define LCDSPI_CyBtldrCommWrite   LCDSPI_I2CCyBtldrCommWrite
    #endif /* (LCDSPI_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void LCDSPI_EzI2CCyBtldrCommStart(void);
    void LCDSPI_EzI2CCyBtldrCommStop (void);
    void LCDSPI_EzI2CCyBtldrCommReset(void);
    cystatus LCDSPI_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCDSPI_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (LCDSPI_SCB_MODE_EZI2C_CONST_CFG)
        #define LCDSPI_CyBtldrCommStart   LCDSPI_EzI2CCyBtldrCommStart
        #define LCDSPI_CyBtldrCommStop    LCDSPI_EzI2CCyBtldrCommStop
        #define LCDSPI_CyBtldrCommReset   LCDSPI_EzI2CCyBtldrCommReset
        #define LCDSPI_CyBtldrCommRead    LCDSPI_EzI2CCyBtldrCommRead
        #define LCDSPI_CyBtldrCommWrite   LCDSPI_EzI2CCyBtldrCommWrite
    #endif /* (LCDSPI_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void LCDSPI_SpiCyBtldrCommStart(void);
    void LCDSPI_SpiCyBtldrCommStop (void);
    void LCDSPI_SpiCyBtldrCommReset(void);
    cystatus LCDSPI_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCDSPI_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (LCDSPI_SCB_MODE_SPI_CONST_CFG)
        #define LCDSPI_CyBtldrCommStart   LCDSPI_SpiCyBtldrCommStart
        #define LCDSPI_CyBtldrCommStop    LCDSPI_SpiCyBtldrCommStop
        #define LCDSPI_CyBtldrCommReset   LCDSPI_SpiCyBtldrCommReset
        #define LCDSPI_CyBtldrCommRead    LCDSPI_SpiCyBtldrCommRead
        #define LCDSPI_CyBtldrCommWrite   LCDSPI_SpiCyBtldrCommWrite
    #endif /* (LCDSPI_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void LCDSPI_UartCyBtldrCommStart(void);
    void LCDSPI_UartCyBtldrCommStop (void);
    void LCDSPI_UartCyBtldrCommReset(void);
    cystatus LCDSPI_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCDSPI_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (LCDSPI_SCB_MODE_UART_CONST_CFG)
        #define LCDSPI_CyBtldrCommStart   LCDSPI_UartCyBtldrCommStart
        #define LCDSPI_CyBtldrCommStop    LCDSPI_UartCyBtldrCommStop
        #define LCDSPI_CyBtldrCommReset   LCDSPI_UartCyBtldrCommReset
        #define LCDSPI_CyBtldrCommRead    LCDSPI_UartCyBtldrCommRead
        #define LCDSPI_CyBtldrCommWrite   LCDSPI_UartCyBtldrCommWrite
    #endif /* (LCDSPI_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_BTLDR_COMM_ENABLED)
    #if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void LCDSPI_CyBtldrCommStart(void);
        void LCDSPI_CyBtldrCommStop (void);
        void LCDSPI_CyBtldrCommReset(void);
        cystatus LCDSPI_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus LCDSPI_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCDSPI)
        #define CyBtldrCommStart    LCDSPI_CyBtldrCommStart
        #define CyBtldrCommStop     LCDSPI_CyBtldrCommStop
        #define CyBtldrCommReset    LCDSPI_CyBtldrCommReset
        #define CyBtldrCommWrite    LCDSPI_CyBtldrCommWrite
        #define CyBtldrCommRead     LCDSPI_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCDSPI) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCDSPI_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define LCDSPI_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define LCDSPI_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define LCDSPI_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define LCDSPI_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef LCDSPI_SPI_BYTE_TO_BYTE
    #define LCDSPI_SPI_BYTE_TO_BYTE   (16u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef LCDSPI_UART_BYTE_TO_BYTE
    #define LCDSPI_UART_BYTE_TO_BYTE  (2500u)
#endif /* LCDSPI_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_LCDSPI_H) */


/* [] END OF FILE */

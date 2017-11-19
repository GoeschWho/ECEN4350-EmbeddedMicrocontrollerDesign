/***************************************************************************//**
* \file LCDSPI_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_LCDSPI_H)
#define CY_SCB_PINS_LCDSPI_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define LCDSPI_REMOVE_RX_WAKE_SDA_MOSI_PIN  (1u)
#define LCDSPI_REMOVE_RX_SDA_MOSI_PIN      (1u)
#define LCDSPI_REMOVE_TX_SCL_MISO_PIN      (1u)
#define LCDSPI_REMOVE_CTS_SCLK_PIN      (1u)
#define LCDSPI_REMOVE_RTS_SS0_PIN      (1u)
#define LCDSPI_REMOVE_SS1_PIN                 (1u)
#define LCDSPI_REMOVE_SS2_PIN                 (1u)
#define LCDSPI_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define LCDSPI_REMOVE_I2C_PINS                (1u)
#define LCDSPI_REMOVE_SPI_MASTER_PINS         (0u)
#define LCDSPI_REMOVE_SPI_MASTER_SCLK_PIN     (0u)
#define LCDSPI_REMOVE_SPI_MASTER_MOSI_PIN     (0u)
#define LCDSPI_REMOVE_SPI_MASTER_MISO_PIN     (0u)
#define LCDSPI_REMOVE_SPI_MASTER_SS0_PIN      (0u)
#define LCDSPI_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define LCDSPI_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define LCDSPI_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define LCDSPI_REMOVE_SPI_SLAVE_PINS          (1u)
#define LCDSPI_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define LCDSPI_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define LCDSPI_REMOVE_UART_TX_PIN             (1u)
#define LCDSPI_REMOVE_UART_RX_TX_PIN          (1u)
#define LCDSPI_REMOVE_UART_RX_PIN             (1u)
#define LCDSPI_REMOVE_UART_RX_WAKE_PIN        (1u)
#define LCDSPI_REMOVE_UART_RTS_PIN            (1u)
#define LCDSPI_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define LCDSPI_RX_WAKE_SDA_MOSI_PIN (0u == LCDSPI_REMOVE_RX_WAKE_SDA_MOSI_PIN)
#define LCDSPI_RX_SDA_MOSI_PIN     (0u == LCDSPI_REMOVE_RX_SDA_MOSI_PIN)
#define LCDSPI_TX_SCL_MISO_PIN     (0u == LCDSPI_REMOVE_TX_SCL_MISO_PIN)
#define LCDSPI_CTS_SCLK_PIN     (0u == LCDSPI_REMOVE_CTS_SCLK_PIN)
#define LCDSPI_RTS_SS0_PIN     (0u == LCDSPI_REMOVE_RTS_SS0_PIN)
#define LCDSPI_SS1_PIN                (0u == LCDSPI_REMOVE_SS1_PIN)
#define LCDSPI_SS2_PIN                (0u == LCDSPI_REMOVE_SS2_PIN)
#define LCDSPI_SS3_PIN                (0u == LCDSPI_REMOVE_SS3_PIN)

/* Mode defined pins */
#define LCDSPI_I2C_PINS               (0u == LCDSPI_REMOVE_I2C_PINS)
#define LCDSPI_SPI_MASTER_PINS        (0u == LCDSPI_REMOVE_SPI_MASTER_PINS)
#define LCDSPI_SPI_MASTER_SCLK_PIN    (0u == LCDSPI_REMOVE_SPI_MASTER_SCLK_PIN)
#define LCDSPI_SPI_MASTER_MOSI_PIN    (0u == LCDSPI_REMOVE_SPI_MASTER_MOSI_PIN)
#define LCDSPI_SPI_MASTER_MISO_PIN    (0u == LCDSPI_REMOVE_SPI_MASTER_MISO_PIN)
#define LCDSPI_SPI_MASTER_SS0_PIN     (0u == LCDSPI_REMOVE_SPI_MASTER_SS0_PIN)
#define LCDSPI_SPI_MASTER_SS1_PIN     (0u == LCDSPI_REMOVE_SPI_MASTER_SS1_PIN)
#define LCDSPI_SPI_MASTER_SS2_PIN     (0u == LCDSPI_REMOVE_SPI_MASTER_SS2_PIN)
#define LCDSPI_SPI_MASTER_SS3_PIN     (0u == LCDSPI_REMOVE_SPI_MASTER_SS3_PIN)
#define LCDSPI_SPI_SLAVE_PINS         (0u == LCDSPI_REMOVE_SPI_SLAVE_PINS)
#define LCDSPI_SPI_SLAVE_MOSI_PIN     (0u == LCDSPI_REMOVE_SPI_SLAVE_MOSI_PIN)
#define LCDSPI_SPI_SLAVE_MISO_PIN     (0u == LCDSPI_REMOVE_SPI_SLAVE_MISO_PIN)
#define LCDSPI_UART_TX_PIN            (0u == LCDSPI_REMOVE_UART_TX_PIN)
#define LCDSPI_UART_RX_TX_PIN         (0u == LCDSPI_REMOVE_UART_RX_TX_PIN)
#define LCDSPI_UART_RX_PIN            (0u == LCDSPI_REMOVE_UART_RX_PIN)
#define LCDSPI_UART_RX_WAKE_PIN       (0u == LCDSPI_REMOVE_UART_RX_WAKE_PIN)
#define LCDSPI_UART_RTS_PIN           (0u == LCDSPI_REMOVE_UART_RTS_PIN)
#define LCDSPI_UART_CTS_PIN           (0u == LCDSPI_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
    #include "LCDSPI_uart_rx_wake_i2c_sda_spi_mosi.h"
#endif /* (LCDSPI_RX_SDA_MOSI) */

#if (LCDSPI_RX_SDA_MOSI_PIN)
    #include "LCDSPI_uart_rx_i2c_sda_spi_mosi.h"
#endif /* (LCDSPI_RX_SDA_MOSI) */

#if (LCDSPI_TX_SCL_MISO_PIN)
    #include "LCDSPI_uart_tx_i2c_scl_spi_miso.h"
#endif /* (LCDSPI_TX_SCL_MISO) */

#if (LCDSPI_CTS_SCLK_PIN)
    #include "LCDSPI_uart_cts_spi_sclk.h"
#endif /* (LCDSPI_CTS_SCLK) */

#if (LCDSPI_RTS_SS0_PIN)
    #include "LCDSPI_uart_rts_spi_ss0.h"
#endif /* (LCDSPI_RTS_SS0_PIN) */

#if (LCDSPI_SS1_PIN)
    #include "LCDSPI_spi_ss1.h"
#endif /* (LCDSPI_SS1_PIN) */

#if (LCDSPI_SS2_PIN)
    #include "LCDSPI_spi_ss2.h"
#endif /* (LCDSPI_SS2_PIN) */

#if (LCDSPI_SS3_PIN)
    #include "LCDSPI_spi_ss3.h"
#endif /* (LCDSPI_SS3_PIN) */

#if (LCDSPI_I2C_PINS)
    #include "LCDSPI_scl.h"
    #include "LCDSPI_sda.h"
#endif /* (LCDSPI_I2C_PINS) */

#if (LCDSPI_SPI_MASTER_PINS)
#if (LCDSPI_SPI_MASTER_SCLK_PIN)
    #include "LCDSPI_sclk_m.h"
#endif /* (LCDSPI_SPI_MASTER_SCLK_PIN) */

#if (LCDSPI_SPI_MASTER_MOSI_PIN)
    #include "LCDSPI_mosi_m.h"
#endif /* (LCDSPI_SPI_MASTER_MOSI_PIN) */

#if (LCDSPI_SPI_MASTER_MISO_PIN)
    #include "LCDSPI_miso_m.h"
#endif /*(LCDSPI_SPI_MASTER_MISO_PIN) */
#endif /* (LCDSPI_SPI_MASTER_PINS) */

#if (LCDSPI_SPI_SLAVE_PINS)
    #include "LCDSPI_sclk_s.h"
    #include "LCDSPI_ss_s.h"

#if (LCDSPI_SPI_SLAVE_MOSI_PIN)
    #include "LCDSPI_mosi_s.h"
#endif /* (LCDSPI_SPI_SLAVE_MOSI_PIN) */

#if (LCDSPI_SPI_SLAVE_MISO_PIN)
    #include "LCDSPI_miso_s.h"
#endif /*(LCDSPI_SPI_SLAVE_MISO_PIN) */
#endif /* (LCDSPI_SPI_SLAVE_PINS) */

#if (LCDSPI_SPI_MASTER_SS0_PIN)
    #include "LCDSPI_ss0_m.h"
#endif /* (LCDSPI_SPI_MASTER_SS0_PIN) */

#if (LCDSPI_SPI_MASTER_SS1_PIN)
    #include "LCDSPI_ss1_m.h"
#endif /* (LCDSPI_SPI_MASTER_SS1_PIN) */

#if (LCDSPI_SPI_MASTER_SS2_PIN)
    #include "LCDSPI_ss2_m.h"
#endif /* (LCDSPI_SPI_MASTER_SS2_PIN) */

#if (LCDSPI_SPI_MASTER_SS3_PIN)
    #include "LCDSPI_ss3_m.h"
#endif /* (LCDSPI_SPI_MASTER_SS3_PIN) */

#if (LCDSPI_UART_TX_PIN)
    #include "LCDSPI_tx.h"
#endif /* (LCDSPI_UART_TX_PIN) */

#if (LCDSPI_UART_RX_TX_PIN)
    #include "LCDSPI_rx_tx.h"
#endif /* (LCDSPI_UART_RX_TX_PIN) */

#if (LCDSPI_UART_RX_PIN)
    #include "LCDSPI_rx.h"
#endif /* (LCDSPI_UART_RX_PIN) */

#if (LCDSPI_UART_RX_WAKE_PIN)
    #include "LCDSPI_rx_wake.h"
#endif /* (LCDSPI_UART_RX_WAKE_PIN) */

#if (LCDSPI_UART_RTS_PIN)
    #include "LCDSPI_rts.h"
#endif /* (LCDSPI_UART_RTS_PIN) */

#if (LCDSPI_UART_CTS_PIN)
    #include "LCDSPI_cts.h"
#endif /* (LCDSPI_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (LCDSPI_RX_SDA_MOSI_PIN)
    #define LCDSPI_RX_SDA_MOSI_HSIOM_REG   (*(reg32 *) LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    #define LCDSPI_RX_SDA_MOSI_HSIOM_PTR   ( (reg32 *) LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    
    #define LCDSPI_RX_SDA_MOSI_HSIOM_MASK      (LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define LCDSPI_RX_SDA_MOSI_HSIOM_POS       (LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define LCDSPI_RX_SDA_MOSI_HSIOM_SEL_GPIO  (LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define LCDSPI_RX_SDA_MOSI_HSIOM_SEL_I2C   (LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define LCDSPI_RX_SDA_MOSI_HSIOM_SEL_SPI   (LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define LCDSPI_RX_SDA_MOSI_HSIOM_SEL_UART  (LCDSPI_uart_rx_i2c_sda_spi_mosi__0__HSIOM_UART)
    
#elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG   (*(reg32 *) LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_PTR   ( (reg32 *) LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_MASK      (LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_POS       (LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_SEL_GPIO  (LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_SEL_I2C   (LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_SEL_SPI   (LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_SEL_UART  (LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_UART)    
   
    #define LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_REG (*(reg32 *) LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_PTR ( (reg32 *) LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS  (LCDSPI_uart_rx_wake_i2c_sda_spi_mosi__SHIFT)
    #define LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK ((uint32) LCDSPI_INTCFG_TYPE_MASK << \
                                                                           LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins LCDSPI_RX_SDA_MOSI_PIN or LCDSPI_RX_WAKE_SDA_MOSI_PIN present.*/
#endif /* (LCDSPI_RX_SDA_MOSI_PIN) */

#if (LCDSPI_TX_SCL_MISO_PIN)
    #define LCDSPI_TX_SCL_MISO_HSIOM_REG   (*(reg32 *) LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    #define LCDSPI_TX_SCL_MISO_HSIOM_PTR   ( (reg32 *) LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    
    #define LCDSPI_TX_SCL_MISO_HSIOM_MASK      (LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM_MASK)
    #define LCDSPI_TX_SCL_MISO_HSIOM_POS       (LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM_SHIFT)
    #define LCDSPI_TX_SCL_MISO_HSIOM_SEL_GPIO  (LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM_GPIO)
    #define LCDSPI_TX_SCL_MISO_HSIOM_SEL_I2C   (LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM_I2C)
    #define LCDSPI_TX_SCL_MISO_HSIOM_SEL_SPI   (LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM_SPI)
    #define LCDSPI_TX_SCL_MISO_HSIOM_SEL_UART  (LCDSPI_uart_tx_i2c_scl_spi_miso__0__HSIOM_UART)
#endif /* (LCDSPI_TX_SCL_MISO_PIN) */

#if (LCDSPI_CTS_SCLK_PIN)
    #define LCDSPI_CTS_SCLK_HSIOM_REG   (*(reg32 *) LCDSPI_uart_cts_spi_sclk__0__HSIOM)
    #define LCDSPI_CTS_SCLK_HSIOM_PTR   ( (reg32 *) LCDSPI_uart_cts_spi_sclk__0__HSIOM)
    
    #define LCDSPI_CTS_SCLK_HSIOM_MASK      (LCDSPI_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define LCDSPI_CTS_SCLK_HSIOM_POS       (LCDSPI_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define LCDSPI_CTS_SCLK_HSIOM_SEL_GPIO  (LCDSPI_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define LCDSPI_CTS_SCLK_HSIOM_SEL_I2C   (LCDSPI_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define LCDSPI_CTS_SCLK_HSIOM_SEL_SPI   (LCDSPI_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define LCDSPI_CTS_SCLK_HSIOM_SEL_UART  (LCDSPI_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (LCDSPI_CTS_SCLK_PIN) */

#if (LCDSPI_RTS_SS0_PIN)
    #define LCDSPI_RTS_SS0_HSIOM_REG   (*(reg32 *) LCDSPI_uart_rts_spi_ss0__0__HSIOM)
    #define LCDSPI_RTS_SS0_HSIOM_PTR   ( (reg32 *) LCDSPI_uart_rts_spi_ss0__0__HSIOM)
    
    #define LCDSPI_RTS_SS0_HSIOM_MASK      (LCDSPI_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define LCDSPI_RTS_SS0_HSIOM_POS       (LCDSPI_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define LCDSPI_RTS_SS0_HSIOM_SEL_GPIO  (LCDSPI_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define LCDSPI_RTS_SS0_HSIOM_SEL_I2C   (LCDSPI_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define LCDSPI_RTS_SS0_HSIOM_SEL_SPI   (LCDSPI_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_RTS_SS0_HSIOM_SEL_UART  (LCDSPI_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */
#endif /* (LCDSPI_RTS_SS0_PIN) */

#if (LCDSPI_SS1_PIN)
    #define LCDSPI_SS1_HSIOM_REG  (*(reg32 *) LCDSPI_spi_ss1__0__HSIOM)
    #define LCDSPI_SS1_HSIOM_PTR  ( (reg32 *) LCDSPI_spi_ss1__0__HSIOM)
    
    #define LCDSPI_SS1_HSIOM_MASK     (LCDSPI_spi_ss1__0__HSIOM_MASK)
    #define LCDSPI_SS1_HSIOM_POS      (LCDSPI_spi_ss1__0__HSIOM_SHIFT)
    #define LCDSPI_SS1_HSIOM_SEL_GPIO (LCDSPI_spi_ss1__0__HSIOM_GPIO)
    #define LCDSPI_SS1_HSIOM_SEL_I2C  (LCDSPI_spi_ss1__0__HSIOM_I2C)
    #define LCDSPI_SS1_HSIOM_SEL_SPI  (LCDSPI_spi_ss1__0__HSIOM_SPI)
#endif /* (LCDSPI_SS1_PIN) */

#if (LCDSPI_SS2_PIN)
    #define LCDSPI_SS2_HSIOM_REG     (*(reg32 *) LCDSPI_spi_ss2__0__HSIOM)
    #define LCDSPI_SS2_HSIOM_PTR     ( (reg32 *) LCDSPI_spi_ss2__0__HSIOM)
    
    #define LCDSPI_SS2_HSIOM_MASK     (LCDSPI_spi_ss2__0__HSIOM_MASK)
    #define LCDSPI_SS2_HSIOM_POS      (LCDSPI_spi_ss2__0__HSIOM_SHIFT)
    #define LCDSPI_SS2_HSIOM_SEL_GPIO (LCDSPI_spi_ss2__0__HSIOM_GPIO)
    #define LCDSPI_SS2_HSIOM_SEL_I2C  (LCDSPI_spi_ss2__0__HSIOM_I2C)
    #define LCDSPI_SS2_HSIOM_SEL_SPI  (LCDSPI_spi_ss2__0__HSIOM_SPI)
#endif /* (LCDSPI_SS2_PIN) */

#if (LCDSPI_SS3_PIN)
    #define LCDSPI_SS3_HSIOM_REG     (*(reg32 *) LCDSPI_spi_ss3__0__HSIOM)
    #define LCDSPI_SS3_HSIOM_PTR     ( (reg32 *) LCDSPI_spi_ss3__0__HSIOM)
    
    #define LCDSPI_SS3_HSIOM_MASK     (LCDSPI_spi_ss3__0__HSIOM_MASK)
    #define LCDSPI_SS3_HSIOM_POS      (LCDSPI_spi_ss3__0__HSIOM_SHIFT)
    #define LCDSPI_SS3_HSIOM_SEL_GPIO (LCDSPI_spi_ss3__0__HSIOM_GPIO)
    #define LCDSPI_SS3_HSIOM_SEL_I2C  (LCDSPI_spi_ss3__0__HSIOM_I2C)
    #define LCDSPI_SS3_HSIOM_SEL_SPI  (LCDSPI_spi_ss3__0__HSIOM_SPI)
#endif /* (LCDSPI_SS3_PIN) */

#if (LCDSPI_I2C_PINS)
    #define LCDSPI_SCL_HSIOM_REG  (*(reg32 *) LCDSPI_scl__0__HSIOM)
    #define LCDSPI_SCL_HSIOM_PTR  ( (reg32 *) LCDSPI_scl__0__HSIOM)
    
    #define LCDSPI_SCL_HSIOM_MASK     (LCDSPI_scl__0__HSIOM_MASK)
    #define LCDSPI_SCL_HSIOM_POS      (LCDSPI_scl__0__HSIOM_SHIFT)
    #define LCDSPI_SCL_HSIOM_SEL_GPIO (LCDSPI_sda__0__HSIOM_GPIO)
    #define LCDSPI_SCL_HSIOM_SEL_I2C  (LCDSPI_sda__0__HSIOM_I2C)
    
    #define LCDSPI_SDA_HSIOM_REG  (*(reg32 *) LCDSPI_sda__0__HSIOM)
    #define LCDSPI_SDA_HSIOM_PTR  ( (reg32 *) LCDSPI_sda__0__HSIOM)
    
    #define LCDSPI_SDA_HSIOM_MASK     (LCDSPI_sda__0__HSIOM_MASK)
    #define LCDSPI_SDA_HSIOM_POS      (LCDSPI_sda__0__HSIOM_SHIFT)
    #define LCDSPI_SDA_HSIOM_SEL_GPIO (LCDSPI_sda__0__HSIOM_GPIO)
    #define LCDSPI_SDA_HSIOM_SEL_I2C  (LCDSPI_sda__0__HSIOM_I2C)
#endif /* (LCDSPI_I2C_PINS) */

#if (LCDSPI_SPI_SLAVE_PINS)
    #define LCDSPI_SCLK_S_HSIOM_REG   (*(reg32 *) LCDSPI_sclk_s__0__HSIOM)
    #define LCDSPI_SCLK_S_HSIOM_PTR   ( (reg32 *) LCDSPI_sclk_s__0__HSIOM)
    
    #define LCDSPI_SCLK_S_HSIOM_MASK      (LCDSPI_sclk_s__0__HSIOM_MASK)
    #define LCDSPI_SCLK_S_HSIOM_POS       (LCDSPI_sclk_s__0__HSIOM_SHIFT)
    #define LCDSPI_SCLK_S_HSIOM_SEL_GPIO  (LCDSPI_sclk_s__0__HSIOM_GPIO)
    #define LCDSPI_SCLK_S_HSIOM_SEL_SPI   (LCDSPI_sclk_s__0__HSIOM_SPI)
    
    #define LCDSPI_SS0_S_HSIOM_REG    (*(reg32 *) LCDSPI_ss0_s__0__HSIOM)
    #define LCDSPI_SS0_S_HSIOM_PTR    ( (reg32 *) LCDSPI_ss0_s__0__HSIOM)
    
    #define LCDSPI_SS0_S_HSIOM_MASK       (LCDSPI_ss0_s__0__HSIOM_MASK)
    #define LCDSPI_SS0_S_HSIOM_POS        (LCDSPI_ss0_s__0__HSIOM_SHIFT)
    #define LCDSPI_SS0_S_HSIOM_SEL_GPIO   (LCDSPI_ss0_s__0__HSIOM_GPIO)  
    #define LCDSPI_SS0_S_HSIOM_SEL_SPI    (LCDSPI_ss0_s__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_SLAVE_PINS) */

#if (LCDSPI_SPI_SLAVE_MOSI_PIN)
    #define LCDSPI_MOSI_S_HSIOM_REG   (*(reg32 *) LCDSPI_mosi_s__0__HSIOM)
    #define LCDSPI_MOSI_S_HSIOM_PTR   ( (reg32 *) LCDSPI_mosi_s__0__HSIOM)
    
    #define LCDSPI_MOSI_S_HSIOM_MASK      (LCDSPI_mosi_s__0__HSIOM_MASK)
    #define LCDSPI_MOSI_S_HSIOM_POS       (LCDSPI_mosi_s__0__HSIOM_SHIFT)
    #define LCDSPI_MOSI_S_HSIOM_SEL_GPIO  (LCDSPI_mosi_s__0__HSIOM_GPIO)
    #define LCDSPI_MOSI_S_HSIOM_SEL_SPI   (LCDSPI_mosi_s__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_SLAVE_MOSI_PIN) */

#if (LCDSPI_SPI_SLAVE_MISO_PIN)
    #define LCDSPI_MISO_S_HSIOM_REG   (*(reg32 *) LCDSPI_miso_s__0__HSIOM)
    #define LCDSPI_MISO_S_HSIOM_PTR   ( (reg32 *) LCDSPI_miso_s__0__HSIOM)
    
    #define LCDSPI_MISO_S_HSIOM_MASK      (LCDSPI_miso_s__0__HSIOM_MASK)
    #define LCDSPI_MISO_S_HSIOM_POS       (LCDSPI_miso_s__0__HSIOM_SHIFT)
    #define LCDSPI_MISO_S_HSIOM_SEL_GPIO  (LCDSPI_miso_s__0__HSIOM_GPIO)
    #define LCDSPI_MISO_S_HSIOM_SEL_SPI   (LCDSPI_miso_s__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_SLAVE_MISO_PIN) */

#if (LCDSPI_SPI_MASTER_MISO_PIN)
    #define LCDSPI_MISO_M_HSIOM_REG   (*(reg32 *) LCDSPI_miso_m__0__HSIOM)
    #define LCDSPI_MISO_M_HSIOM_PTR   ( (reg32 *) LCDSPI_miso_m__0__HSIOM)
    
    #define LCDSPI_MISO_M_HSIOM_MASK      (LCDSPI_miso_m__0__HSIOM_MASK)
    #define LCDSPI_MISO_M_HSIOM_POS       (LCDSPI_miso_m__0__HSIOM_SHIFT)
    #define LCDSPI_MISO_M_HSIOM_SEL_GPIO  (LCDSPI_miso_m__0__HSIOM_GPIO)
    #define LCDSPI_MISO_M_HSIOM_SEL_SPI   (LCDSPI_miso_m__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_MASTER_MISO_PIN) */

#if (LCDSPI_SPI_MASTER_MOSI_PIN)
    #define LCDSPI_MOSI_M_HSIOM_REG   (*(reg32 *) LCDSPI_mosi_m__0__HSIOM)
    #define LCDSPI_MOSI_M_HSIOM_PTR   ( (reg32 *) LCDSPI_mosi_m__0__HSIOM)
    
    #define LCDSPI_MOSI_M_HSIOM_MASK      (LCDSPI_mosi_m__0__HSIOM_MASK)
    #define LCDSPI_MOSI_M_HSIOM_POS       (LCDSPI_mosi_m__0__HSIOM_SHIFT)
    #define LCDSPI_MOSI_M_HSIOM_SEL_GPIO  (LCDSPI_mosi_m__0__HSIOM_GPIO)
    #define LCDSPI_MOSI_M_HSIOM_SEL_SPI   (LCDSPI_mosi_m__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_MASTER_MOSI_PIN) */

#if (LCDSPI_SPI_MASTER_SCLK_PIN)
    #define LCDSPI_SCLK_M_HSIOM_REG   (*(reg32 *) LCDSPI_sclk_m__0__HSIOM)
    #define LCDSPI_SCLK_M_HSIOM_PTR   ( (reg32 *) LCDSPI_sclk_m__0__HSIOM)
    
    #define LCDSPI_SCLK_M_HSIOM_MASK      (LCDSPI_sclk_m__0__HSIOM_MASK)
    #define LCDSPI_SCLK_M_HSIOM_POS       (LCDSPI_sclk_m__0__HSIOM_SHIFT)
    #define LCDSPI_SCLK_M_HSIOM_SEL_GPIO  (LCDSPI_sclk_m__0__HSIOM_GPIO)
    #define LCDSPI_SCLK_M_HSIOM_SEL_SPI   (LCDSPI_sclk_m__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_MASTER_SCLK_PIN) */

#if (LCDSPI_SPI_MASTER_SS0_PIN)
    #define LCDSPI_SS0_M_HSIOM_REG    (*(reg32 *) LCDSPI_ss0_m__0__HSIOM)
    #define LCDSPI_SS0_M_HSIOM_PTR    ( (reg32 *) LCDSPI_ss0_m__0__HSIOM)
    
    #define LCDSPI_SS0_M_HSIOM_MASK       (LCDSPI_ss0_m__0__HSIOM_MASK)
    #define LCDSPI_SS0_M_HSIOM_POS        (LCDSPI_ss0_m__0__HSIOM_SHIFT)
    #define LCDSPI_SS0_M_HSIOM_SEL_GPIO   (LCDSPI_ss0_m__0__HSIOM_GPIO)
    #define LCDSPI_SS0_M_HSIOM_SEL_SPI    (LCDSPI_ss0_m__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_MASTER_SS0_PIN) */

#if (LCDSPI_SPI_MASTER_SS1_PIN)
    #define LCDSPI_SS1_M_HSIOM_REG    (*(reg32 *) LCDSPI_ss1_m__0__HSIOM)
    #define LCDSPI_SS1_M_HSIOM_PTR    ( (reg32 *) LCDSPI_ss1_m__0__HSIOM)
    
    #define LCDSPI_SS1_M_HSIOM_MASK       (LCDSPI_ss1_m__0__HSIOM_MASK)
    #define LCDSPI_SS1_M_HSIOM_POS        (LCDSPI_ss1_m__0__HSIOM_SHIFT)
    #define LCDSPI_SS1_M_HSIOM_SEL_GPIO   (LCDSPI_ss1_m__0__HSIOM_GPIO)
    #define LCDSPI_SS1_M_HSIOM_SEL_SPI    (LCDSPI_ss1_m__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_MASTER_SS1_PIN) */

#if (LCDSPI_SPI_MASTER_SS2_PIN)
    #define LCDSPI_SS2_M_HSIOM_REG    (*(reg32 *) LCDSPI_ss2_m__0__HSIOM)
    #define LCDSPI_SS2_M_HSIOM_PTR    ( (reg32 *) LCDSPI_ss2_m__0__HSIOM)
    
    #define LCDSPI_SS2_M_HSIOM_MASK       (LCDSPI_ss2_m__0__HSIOM_MASK)
    #define LCDSPI_SS2_M_HSIOM_POS        (LCDSPI_ss2_m__0__HSIOM_SHIFT)
    #define LCDSPI_SS2_M_HSIOM_SEL_GPIO   (LCDSPI_ss2_m__0__HSIOM_GPIO)
    #define LCDSPI_SS2_M_HSIOM_SEL_SPI    (LCDSPI_ss2_m__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_MASTER_SS2_PIN) */

#if (LCDSPI_SPI_MASTER_SS3_PIN)
    #define LCDSPI_SS3_M_HSIOM_REG    (*(reg32 *) LCDSPI_ss3_m__0__HSIOM)
    #define LCDSPI_SS3_M_HSIOM_PTR    ( (reg32 *) LCDSPI_ss3_m__0__HSIOM)
    
    #define LCDSPI_SS3_M_HSIOM_MASK      (LCDSPI_ss3_m__0__HSIOM_MASK)
    #define LCDSPI_SS3_M_HSIOM_POS       (LCDSPI_ss3_m__0__HSIOM_SHIFT)
    #define LCDSPI_SS3_M_HSIOM_SEL_GPIO  (LCDSPI_ss3_m__0__HSIOM_GPIO)
    #define LCDSPI_SS3_M_HSIOM_SEL_SPI   (LCDSPI_ss3_m__0__HSIOM_SPI)
#endif /* (LCDSPI_SPI_MASTER_SS3_PIN) */

#if (LCDSPI_UART_RX_PIN)
    #define LCDSPI_RX_HSIOM_REG   (*(reg32 *) LCDSPI_rx__0__HSIOM)
    #define LCDSPI_RX_HSIOM_PTR   ( (reg32 *) LCDSPI_rx__0__HSIOM)
    
    #define LCDSPI_RX_HSIOM_MASK      (LCDSPI_rx__0__HSIOM_MASK)
    #define LCDSPI_RX_HSIOM_POS       (LCDSPI_rx__0__HSIOM_SHIFT)
    #define LCDSPI_RX_HSIOM_SEL_GPIO  (LCDSPI_rx__0__HSIOM_GPIO)
    #define LCDSPI_RX_HSIOM_SEL_UART  (LCDSPI_rx__0__HSIOM_UART)
#endif /* (LCDSPI_UART_RX_PIN) */

#if (LCDSPI_UART_RX_WAKE_PIN)
    #define LCDSPI_RX_WAKE_HSIOM_REG   (*(reg32 *) LCDSPI_rx_wake__0__HSIOM)
    #define LCDSPI_RX_WAKE_HSIOM_PTR   ( (reg32 *) LCDSPI_rx_wake__0__HSIOM)
    
    #define LCDSPI_RX_WAKE_HSIOM_MASK      (LCDSPI_rx_wake__0__HSIOM_MASK)
    #define LCDSPI_RX_WAKE_HSIOM_POS       (LCDSPI_rx_wake__0__HSIOM_SHIFT)
    #define LCDSPI_RX_WAKE_HSIOM_SEL_GPIO  (LCDSPI_rx_wake__0__HSIOM_GPIO)
    #define LCDSPI_RX_WAKE_HSIOM_SEL_UART  (LCDSPI_rx_wake__0__HSIOM_UART)
#endif /* (LCDSPI_UART_WAKE_RX_PIN) */

#if (LCDSPI_UART_CTS_PIN)
    #define LCDSPI_CTS_HSIOM_REG   (*(reg32 *) LCDSPI_cts__0__HSIOM)
    #define LCDSPI_CTS_HSIOM_PTR   ( (reg32 *) LCDSPI_cts__0__HSIOM)
    
    #define LCDSPI_CTS_HSIOM_MASK      (LCDSPI_cts__0__HSIOM_MASK)
    #define LCDSPI_CTS_HSIOM_POS       (LCDSPI_cts__0__HSIOM_SHIFT)
    #define LCDSPI_CTS_HSIOM_SEL_GPIO  (LCDSPI_cts__0__HSIOM_GPIO)
    #define LCDSPI_CTS_HSIOM_SEL_UART  (LCDSPI_cts__0__HSIOM_UART)
#endif /* (LCDSPI_UART_CTS_PIN) */

#if (LCDSPI_UART_TX_PIN)
    #define LCDSPI_TX_HSIOM_REG   (*(reg32 *) LCDSPI_tx__0__HSIOM)
    #define LCDSPI_TX_HSIOM_PTR   ( (reg32 *) LCDSPI_tx__0__HSIOM)
    
    #define LCDSPI_TX_HSIOM_MASK      (LCDSPI_tx__0__HSIOM_MASK)
    #define LCDSPI_TX_HSIOM_POS       (LCDSPI_tx__0__HSIOM_SHIFT)
    #define LCDSPI_TX_HSIOM_SEL_GPIO  (LCDSPI_tx__0__HSIOM_GPIO)
    #define LCDSPI_TX_HSIOM_SEL_UART  (LCDSPI_tx__0__HSIOM_UART)
#endif /* (LCDSPI_UART_TX_PIN) */

#if (LCDSPI_UART_RX_TX_PIN)
    #define LCDSPI_RX_TX_HSIOM_REG   (*(reg32 *) LCDSPI_rx_tx__0__HSIOM)
    #define LCDSPI_RX_TX_HSIOM_PTR   ( (reg32 *) LCDSPI_rx_tx__0__HSIOM)
    
    #define LCDSPI_RX_TX_HSIOM_MASK      (LCDSPI_rx_tx__0__HSIOM_MASK)
    #define LCDSPI_RX_TX_HSIOM_POS       (LCDSPI_rx_tx__0__HSIOM_SHIFT)
    #define LCDSPI_RX_TX_HSIOM_SEL_GPIO  (LCDSPI_rx_tx__0__HSIOM_GPIO)
    #define LCDSPI_RX_TX_HSIOM_SEL_UART  (LCDSPI_rx_tx__0__HSIOM_UART)
#endif /* (LCDSPI_UART_RX_TX_PIN) */

#if (LCDSPI_UART_RTS_PIN)
    #define LCDSPI_RTS_HSIOM_REG      (*(reg32 *) LCDSPI_rts__0__HSIOM)
    #define LCDSPI_RTS_HSIOM_PTR      ( (reg32 *) LCDSPI_rts__0__HSIOM)
    
    #define LCDSPI_RTS_HSIOM_MASK     (LCDSPI_rts__0__HSIOM_MASK)
    #define LCDSPI_RTS_HSIOM_POS      (LCDSPI_rts__0__HSIOM_SHIFT)    
    #define LCDSPI_RTS_HSIOM_SEL_GPIO (LCDSPI_rts__0__HSIOM_GPIO)
    #define LCDSPI_RTS_HSIOM_SEL_UART (LCDSPI_rts__0__HSIOM_UART)    
#endif /* (LCDSPI_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define LCDSPI_HSIOM_DEF_SEL      (0x00u)
#define LCDSPI_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for LCDSPI_CY_SCBIP_V0 
* and LCDSPI_CY_SCBIP_V1. It is not recommended to use them for 
* LCDSPI_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define LCDSPI_HSIOM_UART_SEL     (0x09u)
#define LCDSPI_HSIOM_I2C_SEL      (0x0Eu)
#define LCDSPI_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX   (0u)
#define LCDSPI_RX_SDA_MOSI_PIN_INDEX       (0u)
#define LCDSPI_TX_SCL_MISO_PIN_INDEX       (1u)
#define LCDSPI_CTS_SCLK_PIN_INDEX       (2u)
#define LCDSPI_RTS_SS0_PIN_INDEX       (3u)
#define LCDSPI_SS1_PIN_INDEX                  (4u)
#define LCDSPI_SS2_PIN_INDEX                  (5u)
#define LCDSPI_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define LCDSPI_RX_WAKE_SDA_MOSI_PIN_MASK ((uint32) 0x01u << LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX)
#define LCDSPI_RX_SDA_MOSI_PIN_MASK     ((uint32) 0x01u << LCDSPI_RX_SDA_MOSI_PIN_INDEX)
#define LCDSPI_TX_SCL_MISO_PIN_MASK     ((uint32) 0x01u << LCDSPI_TX_SCL_MISO_PIN_INDEX)
#define LCDSPI_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << LCDSPI_CTS_SCLK_PIN_INDEX)
#define LCDSPI_RTS_SS0_PIN_MASK     ((uint32) 0x01u << LCDSPI_RTS_SS0_PIN_INDEX)
#define LCDSPI_SS1_PIN_MASK                ((uint32) 0x01u << LCDSPI_SS1_PIN_INDEX)
#define LCDSPI_SS2_PIN_MASK                ((uint32) 0x01u << LCDSPI_SS2_PIN_INDEX)
#define LCDSPI_SS3_PIN_MASK                ((uint32) 0x01u << LCDSPI_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define LCDSPI_INTCFG_TYPE_MASK           (0x03u)
#define LCDSPI_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define LCDSPI_PIN_DM_ALG_HIZ  (0u)
#define LCDSPI_PIN_DM_DIG_HIZ  (1u)
#define LCDSPI_PIN_DM_OD_LO    (4u)
#define LCDSPI_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define LCDSPI_DM_MASK    (0x7u)
#define LCDSPI_DM_SIZE    (3u)
#define LCDSPI_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) LCDSPI_DM_MASK << (LCDSPI_DM_SIZE * (pos)))) >> \
                                                              (LCDSPI_DM_SIZE * (pos)) )

#if (LCDSPI_TX_SCL_MISO_PIN)
    #define LCDSPI_CHECK_TX_SCL_MISO_PIN_USED \
                (LCDSPI_PIN_DM_ALG_HIZ != \
                    LCDSPI_GET_P4_PIN_DM(LCDSPI_uart_tx_i2c_scl_spi_miso_PC, \
                                                   LCDSPI_uart_tx_i2c_scl_spi_miso_SHIFT))
#endif /* (LCDSPI_TX_SCL_MISO_PIN) */

#if (LCDSPI_RTS_SS0_PIN)
    #define LCDSPI_CHECK_RTS_SS0_PIN_USED \
                (LCDSPI_PIN_DM_ALG_HIZ != \
                    LCDSPI_GET_P4_PIN_DM(LCDSPI_uart_rts_spi_ss0_PC, \
                                                   LCDSPI_uart_rts_spi_ss0_SHIFT))
#endif /* (LCDSPI_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define LCDSPI_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define LCDSPI_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define LCDSPI_SET_HSIOM_SEL(reg, mask, pos, sel) LCDSPI_SET_REGISTER_BITS(reg, mask, pos, sel)
#define LCDSPI_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        LCDSPI_SET_REGISTER_BITS(reg, mask, pos, intType)
#define LCDSPI_SET_INP_DIS(reg, mask, val) LCDSPI_SET_REGISTER_BIT(reg, mask, val)

/* LCDSPI_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  LCDSPI_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (LCDSPI_CY_SCBIP_V0)
#if (LCDSPI_I2C_PINS)
    #define LCDSPI_SET_I2C_SCL_DR(val) LCDSPI_scl_Write(val)

    #define LCDSPI_SET_I2C_SCL_HSIOM_SEL(sel) \
                          LCDSPI_SET_HSIOM_SEL(LCDSPI_SCL_HSIOM_REG,  \
                                                         LCDSPI_SCL_HSIOM_MASK, \
                                                         LCDSPI_SCL_HSIOM_POS,  \
                                                         (sel))
    #define LCDSPI_WAIT_SCL_SET_HIGH  (0u == LCDSPI_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
    #define LCDSPI_SET_I2C_SCL_DR(val) \
                            LCDSPI_uart_rx_wake_i2c_sda_spi_mosi_Write(val)

    #define LCDSPI_SET_I2C_SCL_HSIOM_SEL(sel) \
                    LCDSPI_SET_HSIOM_SEL(LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG,  \
                                                   LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_MASK, \
                                                   LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define LCDSPI_WAIT_SCL_SET_HIGH  (0u == LCDSPI_uart_rx_wake_i2c_sda_spi_mosi_Read())

#elif (LCDSPI_RX_SDA_MOSI_PIN)
    #define LCDSPI_SET_I2C_SCL_DR(val) \
                            LCDSPI_uart_rx_i2c_sda_spi_mosi_Write(val)


    #define LCDSPI_SET_I2C_SCL_HSIOM_SEL(sel) \
                            LCDSPI_SET_HSIOM_SEL(LCDSPI_RX_SDA_MOSI_HSIOM_REG,  \
                                                           LCDSPI_RX_SDA_MOSI_HSIOM_MASK, \
                                                           LCDSPI_RX_SDA_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define LCDSPI_WAIT_SCL_SET_HIGH  (0u == LCDSPI_uart_rx_i2c_sda_spi_mosi_Read())

#else
    #define LCDSPI_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define LCDSPI_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define LCDSPI_WAIT_SCL_SET_HIGH  (0u)
#endif /* (LCDSPI_I2C_PINS) */

/* SCB I2C: sda signal */
#if (LCDSPI_I2C_PINS)
    #define LCDSPI_WAIT_SDA_SET_HIGH  (0u == LCDSPI_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (LCDSPI_TX_SCL_MISO_PIN)
    #define LCDSPI_WAIT_SDA_SET_HIGH  (0u == LCDSPI_uart_tx_i2c_scl_spi_miso_Read())
#else
    #define LCDSPI_WAIT_SDA_SET_HIGH  (0u)
#endif /* (LCDSPI_MOSI_SCL_RX_PIN) */
#endif /* (LCDSPI_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (LCDSPI_RX_SDA_MOSI_PIN)
    #define LCDSPI_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
    #define LCDSPI_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) LCDSPI_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(LCDSPI_UART_RX_WAKE_PIN)
    #define LCDSPI_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) LCDSPI_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (LCDSPI_RX_SDA_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define LCDSPI_REMOVE_MOSI_SCL_RX_WAKE_PIN    LCDSPI_REMOVE_RX_WAKE_SDA_MOSI_PIN
#define LCDSPI_REMOVE_MOSI_SCL_RX_PIN         LCDSPI_REMOVE_RX_SDA_MOSI_PIN
#define LCDSPI_REMOVE_MISO_SDA_TX_PIN         LCDSPI_REMOVE_TX_SCL_MISO_PIN
#ifndef LCDSPI_REMOVE_SCLK_PIN
#define LCDSPI_REMOVE_SCLK_PIN                LCDSPI_REMOVE_CTS_SCLK_PIN
#endif /* LCDSPI_REMOVE_SCLK_PIN */
#ifndef LCDSPI_REMOVE_SS0_PIN
#define LCDSPI_REMOVE_SS0_PIN                 LCDSPI_REMOVE_RTS_SS0_PIN
#endif /* LCDSPI_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define LCDSPI_MOSI_SCL_RX_WAKE_PIN   LCDSPI_RX_WAKE_SDA_MOSI_PIN
#define LCDSPI_MOSI_SCL_RX_PIN        LCDSPI_RX_SDA_MOSI_PIN
#define LCDSPI_MISO_SDA_TX_PIN        LCDSPI_TX_SCL_MISO_PIN
#ifndef LCDSPI_SCLK_PIN
#define LCDSPI_SCLK_PIN               LCDSPI_CTS_SCLK_PIN
#endif /* LCDSPI_SCLK_PIN */
#ifndef LCDSPI_SS0_PIN
#define LCDSPI_SS0_PIN                LCDSPI_RTS_SS0_PIN
#endif /* LCDSPI_SS0_PIN */

#if (LCDSPI_MOSI_SCL_RX_WAKE_PIN)
    #define LCDSPI_MOSI_SCL_RX_WAKE_HSIOM_REG     LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define LCDSPI_MOSI_SCL_RX_WAKE_HSIOM_PTR     LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define LCDSPI_MOSI_SCL_RX_WAKE_HSIOM_MASK    LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define LCDSPI_MOSI_SCL_RX_WAKE_HSIOM_POS     LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define LCDSPI_MOSI_SCL_RX_WAKE_INTCFG_REG    LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define LCDSPI_MOSI_SCL_RX_WAKE_INTCFG_PTR    LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define LCDSPI_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define LCDSPI_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG
#endif /* (LCDSPI_RX_WAKE_SDA_MOSI_PIN) */

#if (LCDSPI_MOSI_SCL_RX_PIN)
    #define LCDSPI_MOSI_SCL_RX_HSIOM_REG      LCDSPI_RX_SDA_MOSI_HSIOM_REG
    #define LCDSPI_MOSI_SCL_RX_HSIOM_PTR      LCDSPI_RX_SDA_MOSI_HSIOM_PTR
    #define LCDSPI_MOSI_SCL_RX_HSIOM_MASK     LCDSPI_RX_SDA_MOSI_HSIOM_MASK
    #define LCDSPI_MOSI_SCL_RX_HSIOM_POS      LCDSPI_RX_SDA_MOSI_HSIOM_POS
#endif /* (LCDSPI_MOSI_SCL_RX_PIN) */

#if (LCDSPI_MISO_SDA_TX_PIN)
    #define LCDSPI_MISO_SDA_TX_HSIOM_REG      LCDSPI_TX_SCL_MISO_HSIOM_REG
    #define LCDSPI_MISO_SDA_TX_HSIOM_PTR      LCDSPI_TX_SCL_MISO_HSIOM_REG
    #define LCDSPI_MISO_SDA_TX_HSIOM_MASK     LCDSPI_TX_SCL_MISO_HSIOM_REG
    #define LCDSPI_MISO_SDA_TX_HSIOM_POS      LCDSPI_TX_SCL_MISO_HSIOM_REG
#endif /* (LCDSPI_MISO_SDA_TX_PIN_PIN) */

#if (LCDSPI_SCLK_PIN)
    #ifndef LCDSPI_SCLK_HSIOM_REG
    #define LCDSPI_SCLK_HSIOM_REG     LCDSPI_CTS_SCLK_HSIOM_REG
    #define LCDSPI_SCLK_HSIOM_PTR     LCDSPI_CTS_SCLK_HSIOM_PTR
    #define LCDSPI_SCLK_HSIOM_MASK    LCDSPI_CTS_SCLK_HSIOM_MASK
    #define LCDSPI_SCLK_HSIOM_POS     LCDSPI_CTS_SCLK_HSIOM_POS
    #endif /* LCDSPI_SCLK_HSIOM_REG */
#endif /* (LCDSPI_SCLK_PIN) */

#if (LCDSPI_SS0_PIN)
    #ifndef LCDSPI_SS0_HSIOM_REG
    #define LCDSPI_SS0_HSIOM_REG      LCDSPI_RTS_SS0_HSIOM_REG
    #define LCDSPI_SS0_HSIOM_PTR      LCDSPI_RTS_SS0_HSIOM_PTR
    #define LCDSPI_SS0_HSIOM_MASK     LCDSPI_RTS_SS0_HSIOM_MASK
    #define LCDSPI_SS0_HSIOM_POS      LCDSPI_RTS_SS0_HSIOM_POS
    #endif /* LCDSPI_SS0_HSIOM_REG */
#endif /* (LCDSPI_SS0_PIN) */

#define LCDSPI_MOSI_SCL_RX_WAKE_PIN_INDEX LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX
#define LCDSPI_MOSI_SCL_RX_PIN_INDEX      LCDSPI_RX_SDA_MOSI_PIN_INDEX
#define LCDSPI_MISO_SDA_TX_PIN_INDEX      LCDSPI_TX_SCL_MISO_PIN_INDEX
#ifndef LCDSPI_SCLK_PIN_INDEX
#define LCDSPI_SCLK_PIN_INDEX             LCDSPI_CTS_SCLK_PIN_INDEX
#endif /* LCDSPI_SCLK_PIN_INDEX */
#ifndef LCDSPI_SS0_PIN_INDEX
#define LCDSPI_SS0_PIN_INDEX              LCDSPI_RTS_SS0_PIN_INDEX
#endif /* LCDSPI_SS0_PIN_INDEX */

#define LCDSPI_MOSI_SCL_RX_WAKE_PIN_MASK LCDSPI_RX_WAKE_SDA_MOSI_PIN_MASK
#define LCDSPI_MOSI_SCL_RX_PIN_MASK      LCDSPI_RX_SDA_MOSI_PIN_MASK
#define LCDSPI_MISO_SDA_TX_PIN_MASK      LCDSPI_TX_SCL_MISO_PIN_MASK
#ifndef LCDSPI_SCLK_PIN_MASK
#define LCDSPI_SCLK_PIN_MASK             LCDSPI_CTS_SCLK_PIN_MASK
#endif /* LCDSPI_SCLK_PIN_MASK */
#ifndef LCDSPI_SS0_PIN_MASK
#define LCDSPI_SS0_PIN_MASK              LCDSPI_RTS_SS0_PIN_MASK
#endif /* LCDSPI_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_LCDSPI_H) */


/* [] END OF FILE */

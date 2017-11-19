/*******************************************************************************
* File Name: LCD_SPI.h
* Version 2.50
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Master Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_LCD_SPI_H)
#define CY_SPIM_LCD_SPI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component SPI_Master_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define LCD_SPI_INTERNAL_CLOCK             (1u)

#if(0u != LCD_SPI_INTERNAL_CLOCK)
    #include "LCD_SPI_IntClock.h"
#endif /* (0u != LCD_SPI_INTERNAL_CLOCK) */

#define LCD_SPI_MODE                       (1u)
#define LCD_SPI_DATA_WIDTH                 (8u)
#define LCD_SPI_MODE_USE_ZERO              (1u)
#define LCD_SPI_BIDIRECTIONAL_MODE         (0u)

/* Internal interrupt handling */
#define LCD_SPI_TX_BUFFER_SIZE             (8u)
#define LCD_SPI_RX_BUFFER_SIZE             (8u)
#define LCD_SPI_INTERNAL_TX_INT_ENABLED    (1u)
#define LCD_SPI_INTERNAL_RX_INT_ENABLED    (1u)

#define LCD_SPI_SINGLE_REG_SIZE            (8u)
#define LCD_SPI_USE_SECOND_DATAPATH        (LCD_SPI_DATA_WIDTH > LCD_SPI_SINGLE_REG_SIZE)

#define LCD_SPI_FIFO_SIZE                  (4u)
#define LCD_SPI_TX_SOFTWARE_BUF_ENABLED    ((0u != LCD_SPI_INTERNAL_TX_INT_ENABLED) && \
                                                     (LCD_SPI_TX_BUFFER_SIZE > LCD_SPI_FIFO_SIZE))

#define LCD_SPI_RX_SOFTWARE_BUF_ENABLED    ((0u != LCD_SPI_INTERNAL_RX_INT_ENABLED) && \
                                                     (LCD_SPI_RX_BUFFER_SIZE > LCD_SPI_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
} LCD_SPI_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  LCD_SPI_Init(void)                           ;
void  LCD_SPI_Enable(void)                         ;
void  LCD_SPI_Start(void)                          ;
void  LCD_SPI_Stop(void)                           ;

void  LCD_SPI_EnableTxInt(void)                    ;
void  LCD_SPI_EnableRxInt(void)                    ;
void  LCD_SPI_DisableTxInt(void)                   ;
void  LCD_SPI_DisableRxInt(void)                   ;

void  LCD_SPI_Sleep(void)                          ;
void  LCD_SPI_Wakeup(void)                         ;
void  LCD_SPI_SaveConfig(void)                     ;
void  LCD_SPI_RestoreConfig(void)                  ;

void  LCD_SPI_SetTxInterruptMode(uint8 intSrc)     ;
void  LCD_SPI_SetRxInterruptMode(uint8 intSrc)     ;
uint8 LCD_SPI_ReadTxStatus(void)                   ;
uint8 LCD_SPI_ReadRxStatus(void)                   ;
void  LCD_SPI_WriteTxData(uint8 txData)  \
                                                            ;
uint8 LCD_SPI_ReadRxData(void) \
                                                            ;
uint8 LCD_SPI_GetRxBufferSize(void)                ;
uint8 LCD_SPI_GetTxBufferSize(void)                ;
void  LCD_SPI_ClearRxBuffer(void)                  ;
void  LCD_SPI_ClearTxBuffer(void)                  ;
void  LCD_SPI_ClearFIFO(void)                              ;
void  LCD_SPI_PutArray(const uint8 buffer[], uint8 byteCount) \
                                                            ;

#if(0u != LCD_SPI_BIDIRECTIONAL_MODE)
    void  LCD_SPI_TxEnable(void)                   ;
    void  LCD_SPI_TxDisable(void)                  ;
#endif /* (0u != LCD_SPI_BIDIRECTIONAL_MODE) */

CY_ISR_PROTO(LCD_SPI_TX_ISR);
CY_ISR_PROTO(LCD_SPI_RX_ISR);


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 LCD_SPI_initVar;


/***************************************
*           API Constants
***************************************/

#define LCD_SPI_TX_ISR_NUMBER     ((uint8) (LCD_SPI_TxInternalInterrupt__INTC_NUMBER))
#define LCD_SPI_RX_ISR_NUMBER     ((uint8) (LCD_SPI_RxInternalInterrupt__INTC_NUMBER))

#define LCD_SPI_TX_ISR_PRIORITY   ((uint8) (LCD_SPI_TxInternalInterrupt__INTC_PRIOR_NUM))
#define LCD_SPI_RX_ISR_PRIORITY   ((uint8) (LCD_SPI_RxInternalInterrupt__INTC_PRIOR_NUM))


/***************************************
*    Initial Parameter Constants
***************************************/

#define LCD_SPI_INT_ON_SPI_DONE    ((uint8) (0u   << LCD_SPI_STS_SPI_DONE_SHIFT))
#define LCD_SPI_INT_ON_TX_EMPTY    ((uint8) (0u   << LCD_SPI_STS_TX_FIFO_EMPTY_SHIFT))
#define LCD_SPI_INT_ON_TX_NOT_FULL ((uint8) (1u << \
                                                                           LCD_SPI_STS_TX_FIFO_NOT_FULL_SHIFT))
#define LCD_SPI_INT_ON_BYTE_COMP   ((uint8) (0u  << LCD_SPI_STS_BYTE_COMPLETE_SHIFT))
#define LCD_SPI_INT_ON_SPI_IDLE    ((uint8) (0u   << LCD_SPI_STS_SPI_IDLE_SHIFT))

/* Disable TX_NOT_FULL if software buffer is used */
#define LCD_SPI_INT_ON_TX_NOT_FULL_DEF ((LCD_SPI_TX_SOFTWARE_BUF_ENABLED) ? \
                                                                        (0u) : (LCD_SPI_INT_ON_TX_NOT_FULL))

/* TX interrupt mask */
#define LCD_SPI_TX_INIT_INTERRUPTS_MASK    (LCD_SPI_INT_ON_SPI_DONE  | \
                                                     LCD_SPI_INT_ON_TX_EMPTY  | \
                                                     LCD_SPI_INT_ON_TX_NOT_FULL_DEF | \
                                                     LCD_SPI_INT_ON_BYTE_COMP | \
                                                     LCD_SPI_INT_ON_SPI_IDLE)

#define LCD_SPI_INT_ON_RX_FULL         ((uint8) (0u << \
                                                                          LCD_SPI_STS_RX_FIFO_FULL_SHIFT))
#define LCD_SPI_INT_ON_RX_NOT_EMPTY    ((uint8) (1u << \
                                                                          LCD_SPI_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define LCD_SPI_INT_ON_RX_OVER         ((uint8) (0u << \
                                                                          LCD_SPI_STS_RX_FIFO_OVERRUN_SHIFT))

/* RX interrupt mask */
#define LCD_SPI_RX_INIT_INTERRUPTS_MASK    (LCD_SPI_INT_ON_RX_FULL      | \
                                                     LCD_SPI_INT_ON_RX_NOT_EMPTY | \
                                                     LCD_SPI_INT_ON_RX_OVER)
/* Nubmer of bits to receive/transmit */
#define LCD_SPI_BITCTR_INIT            (((uint8) (LCD_SPI_DATA_WIDTH << 1u)) - 1u)


/***************************************
*             Registers
***************************************/
#if(CY_PSOC3 || CY_PSOC5)
    #define LCD_SPI_TXDATA_REG (* (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F0_REG)
    #define LCD_SPI_TXDATA_PTR (  (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F0_REG)
    #define LCD_SPI_RXDATA_REG (* (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F1_REG)
    #define LCD_SPI_RXDATA_PTR (  (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F1_REG)
#else   /* PSOC4 */
    #if(LCD_SPI_USE_SECOND_DATAPATH)
        #define LCD_SPI_TXDATA_REG (* (reg16 *) \
                                          LCD_SPI_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define LCD_SPI_TXDATA_PTR (  (reg16 *) \
                                          LCD_SPI_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define LCD_SPI_RXDATA_REG (* (reg16 *) \
                                          LCD_SPI_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
        #define LCD_SPI_RXDATA_PTR (  (reg16 *) \
                                          LCD_SPI_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
    #else
        #define LCD_SPI_TXDATA_REG (* (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F0_REG)
        #define LCD_SPI_TXDATA_PTR (  (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F0_REG)
        #define LCD_SPI_RXDATA_REG (* (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F1_REG)
        #define LCD_SPI_RXDATA_PTR (  (reg8 *) \
                                                LCD_SPI_BSPIM_sR8_Dp_u0__F1_REG)
    #endif /* (LCD_SPI_USE_SECOND_DATAPATH) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define LCD_SPI_AUX_CONTROL_DP0_REG (* (reg8 *) \
                                        LCD_SPI_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)
#define LCD_SPI_AUX_CONTROL_DP0_PTR (  (reg8 *) \
                                        LCD_SPI_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(LCD_SPI_USE_SECOND_DATAPATH)
    #define LCD_SPI_AUX_CONTROL_DP1_REG  (* (reg8 *) \
                                        LCD_SPI_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define LCD_SPI_AUX_CONTROL_DP1_PTR  (  (reg8 *) \
                                        LCD_SPI_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
#endif /* (LCD_SPI_USE_SECOND_DATAPATH) */

#define LCD_SPI_COUNTER_PERIOD_REG     (* (reg8 *) LCD_SPI_BSPIM_BitCounter__PERIOD_REG)
#define LCD_SPI_COUNTER_PERIOD_PTR     (  (reg8 *) LCD_SPI_BSPIM_BitCounter__PERIOD_REG)
#define LCD_SPI_COUNTER_CONTROL_REG    (* (reg8 *) LCD_SPI_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)
#define LCD_SPI_COUNTER_CONTROL_PTR    (  (reg8 *) LCD_SPI_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)

#define LCD_SPI_TX_STATUS_REG          (* (reg8 *) LCD_SPI_BSPIM_TxStsReg__STATUS_REG)
#define LCD_SPI_TX_STATUS_PTR          (  (reg8 *) LCD_SPI_BSPIM_TxStsReg__STATUS_REG)
#define LCD_SPI_RX_STATUS_REG          (* (reg8 *) LCD_SPI_BSPIM_RxStsReg__STATUS_REG)
#define LCD_SPI_RX_STATUS_PTR          (  (reg8 *) LCD_SPI_BSPIM_RxStsReg__STATUS_REG)

#define LCD_SPI_CONTROL_REG            (* (reg8 *) \
                                      LCD_SPI_BSPIM_BidirMode_CtrlReg__CONTROL_REG)
#define LCD_SPI_CONTROL_PTR            (  (reg8 *) \
                                      LCD_SPI_BSPIM_BidirMode_CtrlReg__CONTROL_REG)

#define LCD_SPI_TX_STATUS_MASK_REG     (* (reg8 *) LCD_SPI_BSPIM_TxStsReg__MASK_REG)
#define LCD_SPI_TX_STATUS_MASK_PTR     (  (reg8 *) LCD_SPI_BSPIM_TxStsReg__MASK_REG)
#define LCD_SPI_RX_STATUS_MASK_REG     (* (reg8 *) LCD_SPI_BSPIM_RxStsReg__MASK_REG)
#define LCD_SPI_RX_STATUS_MASK_PTR     (  (reg8 *) LCD_SPI_BSPIM_RxStsReg__MASK_REG)

#define LCD_SPI_TX_STATUS_ACTL_REG     (* (reg8 *) LCD_SPI_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define LCD_SPI_TX_STATUS_ACTL_PTR     (  (reg8 *) LCD_SPI_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define LCD_SPI_RX_STATUS_ACTL_REG     (* (reg8 *) LCD_SPI_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)
#define LCD_SPI_RX_STATUS_ACTL_PTR     (  (reg8 *) LCD_SPI_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)

#if(LCD_SPI_USE_SECOND_DATAPATH)
    #define LCD_SPI_AUX_CONTROLDP1     (LCD_SPI_AUX_CONTROL_DP1_REG)
#endif /* (LCD_SPI_USE_SECOND_DATAPATH) */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define LCD_SPI_STS_SPI_DONE_SHIFT             (0x00u)
#define LCD_SPI_STS_TX_FIFO_EMPTY_SHIFT        (0x01u)
#define LCD_SPI_STS_TX_FIFO_NOT_FULL_SHIFT     (0x02u)
#define LCD_SPI_STS_BYTE_COMPLETE_SHIFT        (0x03u)
#define LCD_SPI_STS_SPI_IDLE_SHIFT             (0x04u)
#define LCD_SPI_STS_RX_FIFO_FULL_SHIFT         (0x04u)
#define LCD_SPI_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x05u)
#define LCD_SPI_STS_RX_FIFO_OVERRUN_SHIFT      (0x06u)

#define LCD_SPI_STS_SPI_DONE           ((uint8) (0x01u << LCD_SPI_STS_SPI_DONE_SHIFT))
#define LCD_SPI_STS_TX_FIFO_EMPTY      ((uint8) (0x01u << LCD_SPI_STS_TX_FIFO_EMPTY_SHIFT))
#define LCD_SPI_STS_TX_FIFO_NOT_FULL   ((uint8) (0x01u << LCD_SPI_STS_TX_FIFO_NOT_FULL_SHIFT))
#define LCD_SPI_STS_BYTE_COMPLETE      ((uint8) (0x01u << LCD_SPI_STS_BYTE_COMPLETE_SHIFT))
#define LCD_SPI_STS_SPI_IDLE           ((uint8) (0x01u << LCD_SPI_STS_SPI_IDLE_SHIFT))
#define LCD_SPI_STS_RX_FIFO_FULL       ((uint8) (0x01u << LCD_SPI_STS_RX_FIFO_FULL_SHIFT))
#define LCD_SPI_STS_RX_FIFO_NOT_EMPTY  ((uint8) (0x01u << LCD_SPI_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define LCD_SPI_STS_RX_FIFO_OVERRUN    ((uint8) (0x01u << LCD_SPI_STS_RX_FIFO_OVERRUN_SHIFT))

/* TX and RX masks for clear on read bits */
#define LCD_SPI_TX_STS_CLR_ON_RD_BYTES_MASK    (0x09u)
#define LCD_SPI_RX_STS_CLR_ON_RD_BYTES_MASK    (0x40u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define LCD_SPI_INT_ENABLE     (0x10u) /* Enable interrupt from statusi */
#define LCD_SPI_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define LCD_SPI_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define LCD_SPI_FIFO_CLR       (LCD_SPI_TX_FIFO_CLR | LCD_SPI_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define LCD_SPI_CNTR_ENABLE    (0x20u) /* Enable CNT7 */

/* Bi-Directional mode control bit */
#define LCD_SPI_CTRL_TX_SIGNAL_EN  (0x01u)

/* Datapath Auxillary Control Register definitions */
#define LCD_SPI_AUX_CTRL_FIFO0_CLR         (0x01u)
#define LCD_SPI_AUX_CTRL_FIFO1_CLR         (0x02u)
#define LCD_SPI_AUX_CTRL_FIFO0_LVL         (0x04u)
#define LCD_SPI_AUX_CTRL_FIFO1_LVL         (0x08u)
#define LCD_SPI_STATUS_ACTL_INT_EN_MASK    (0x10u)

/* Component disabled */
#define LCD_SPI_DISABLED   (0u)


/***************************************
*       Macros
***************************************/

/* Returns true if componentn enabled */
#define LCD_SPI_IS_ENABLED (0u != (LCD_SPI_TX_STATUS_ACTL_REG & LCD_SPI_INT_ENABLE))

/* Retuns TX status register */
#define LCD_SPI_GET_STATUS_TX(swTxSts) ( (uint8)(LCD_SPI_TX_STATUS_REG | \
                                                          ((swTxSts) & LCD_SPI_TX_STS_CLR_ON_RD_BYTES_MASK)) )
/* Retuns RX status register */
#define LCD_SPI_GET_STATUS_RX(swRxSts) ( (uint8)(LCD_SPI_RX_STATUS_REG | \
                                                          ((swRxSts) & LCD_SPI_RX_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define LCD_SPI_WriteByte   LCD_SPI_WriteTxData
#define LCD_SPI_ReadByte    LCD_SPI_ReadRxData
void  LCD_SPI_SetInterruptMode(uint8 intSrc)       ;
uint8 LCD_SPI_ReadStatus(void)                     ;
void  LCD_SPI_EnableInt(void)                      ;
void  LCD_SPI_DisableInt(void)                     ;

#define LCD_SPI_TXDATA                 (LCD_SPI_TXDATA_REG)
#define LCD_SPI_RXDATA                 (LCD_SPI_RXDATA_REG)
#define LCD_SPI_AUX_CONTROLDP0         (LCD_SPI_AUX_CONTROL_DP0_REG)
#define LCD_SPI_TXBUFFERREAD           (LCD_SPI_txBufferRead)
#define LCD_SPI_TXBUFFERWRITE          (LCD_SPI_txBufferWrite)
#define LCD_SPI_RXBUFFERREAD           (LCD_SPI_rxBufferRead)
#define LCD_SPI_RXBUFFERWRITE          (LCD_SPI_rxBufferWrite)

#define LCD_SPI_COUNTER_PERIOD         (LCD_SPI_COUNTER_PERIOD_REG)
#define LCD_SPI_COUNTER_CONTROL        (LCD_SPI_COUNTER_CONTROL_REG)
#define LCD_SPI_STATUS                 (LCD_SPI_TX_STATUS_REG)
#define LCD_SPI_CONTROL                (LCD_SPI_CONTROL_REG)
#define LCD_SPI_STATUS_MASK            (LCD_SPI_TX_STATUS_MASK_REG)
#define LCD_SPI_STATUS_ACTL            (LCD_SPI_TX_STATUS_ACTL_REG)

#define LCD_SPI_INIT_INTERRUPTS_MASK  (LCD_SPI_INT_ON_SPI_DONE     | \
                                                LCD_SPI_INT_ON_TX_EMPTY     | \
                                                LCD_SPI_INT_ON_TX_NOT_FULL_DEF  | \
                                                LCD_SPI_INT_ON_RX_FULL      | \
                                                LCD_SPI_INT_ON_RX_NOT_EMPTY | \
                                                LCD_SPI_INT_ON_RX_OVER      | \
                                                LCD_SPI_INT_ON_BYTE_COMP)
                                                
#define LCD_SPI_DataWidth                  (LCD_SPI_DATA_WIDTH)
#define LCD_SPI_InternalClockUsed          (LCD_SPI_INTERNAL_CLOCK)
#define LCD_SPI_InternalTxInterruptEnabled (LCD_SPI_INTERNAL_TX_INT_ENABLED)
#define LCD_SPI_InternalRxInterruptEnabled (LCD_SPI_INTERNAL_RX_INT_ENABLED)
#define LCD_SPI_ModeUseZero                (LCD_SPI_MODE_USE_ZERO)
#define LCD_SPI_BidirectionalMode          (LCD_SPI_BIDIRECTIONAL_MODE)
#define LCD_SPI_Mode                       (LCD_SPI_MODE)
#define LCD_SPI_DATAWIDHT                  (LCD_SPI_DATA_WIDTH)
#define LCD_SPI_InternalInterruptEnabled   (0u)

#define LCD_SPI_TXBUFFERSIZE   (LCD_SPI_TX_BUFFER_SIZE)
#define LCD_SPI_RXBUFFERSIZE   (LCD_SPI_RX_BUFFER_SIZE)

#define LCD_SPI_TXBUFFER       LCD_SPI_txBuffer
#define LCD_SPI_RXBUFFER       LCD_SPI_rxBuffer

#endif /* (CY_SPIM_LCD_SPI_H) */


/* [] END OF FILE */

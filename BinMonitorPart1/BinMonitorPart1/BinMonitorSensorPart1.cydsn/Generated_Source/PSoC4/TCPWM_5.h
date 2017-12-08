/*******************************************************************************
* File Name: TCPWM_5.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the TCPWM_5
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_TCPWM_5_H)
#define CY_TCPWM_TCPWM_5_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} TCPWM_5_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TCPWM_5_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TCPWM_5_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TCPWM_5_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TCPWM_5_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define TCPWM_5_QUAD_ENCODING_MODES            (0lu)
#define TCPWM_5_QUAD_AUTO_START                (0lu)

/* Signal modes */
#define TCPWM_5_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TCPWM_5_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TCPWM_5_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TCPWM_5_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TCPWM_5_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TCPWM_5_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TCPWM_5_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TCPWM_5_TC_RUN_MODE                    (0lu)
#define TCPWM_5_TC_COUNTER_MODE                (0lu)
#define TCPWM_5_TC_COMP_CAP_MODE               (2lu)
#define TCPWM_5_TC_PRESCALER                   (0lu)

/* Signal modes */
#define TCPWM_5_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TCPWM_5_TC_COUNT_SIGNAL_MODE           (3lu)
#define TCPWM_5_TC_START_SIGNAL_MODE           (0lu)
#define TCPWM_5_TC_STOP_SIGNAL_MODE            (0lu)
#define TCPWM_5_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TCPWM_5_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TCPWM_5_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define TCPWM_5_TC_START_SIGNAL_PRESENT        (0lu)
#define TCPWM_5_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TCPWM_5_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TCPWM_5_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define TCPWM_5_PWM_KILL_EVENT                 (0lu)
#define TCPWM_5_PWM_STOP_EVENT                 (0lu)
#define TCPWM_5_PWM_MODE                       (4lu)
#define TCPWM_5_PWM_OUT_N_INVERT               (1lu)
#define TCPWM_5_PWM_OUT_INVERT                 (0lu)
#define TCPWM_5_PWM_ALIGN                      (0lu)
#define TCPWM_5_PWM_RUN_MODE                   (0lu)
#define TCPWM_5_PWM_DEAD_TIME_CYCLE            (0lu)
#define TCPWM_5_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TCPWM_5_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TCPWM_5_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TCPWM_5_PWM_START_SIGNAL_MODE          (0lu)
#define TCPWM_5_PWM_STOP_SIGNAL_MODE           (0lu)
#define TCPWM_5_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TCPWM_5_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TCPWM_5_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TCPWM_5_PWM_START_SIGNAL_PRESENT       (0lu)
#define TCPWM_5_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TCPWM_5_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TCPWM_5_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TCPWM_5_TC_PERIOD_VALUE                (32lu)
#define TCPWM_5_TC_COMPARE_VALUE               (31lu)
#define TCPWM_5_TC_COMPARE_BUF_VALUE           (65535lu)
#define TCPWM_5_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TCPWM_5_PWM_PERIOD_VALUE               (3lu)
#define TCPWM_5_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TCPWM_5_PWM_PERIOD_SWAP                (0lu)
#define TCPWM_5_PWM_COMPARE_VALUE              (2lu)
#define TCPWM_5_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TCPWM_5_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TCPWM_5__LEFT 0
#define TCPWM_5__RIGHT 1
#define TCPWM_5__CENTER 2
#define TCPWM_5__ASYMMETRIC 3

#define TCPWM_5__X1 0
#define TCPWM_5__X2 1
#define TCPWM_5__X4 2

#define TCPWM_5__PWM 4
#define TCPWM_5__PWM_DT 5
#define TCPWM_5__PWM_PR 6

#define TCPWM_5__INVERSE 1
#define TCPWM_5__DIRECT 0

#define TCPWM_5__CAPTURE 2
#define TCPWM_5__COMPARE 0

#define TCPWM_5__TRIG_LEVEL 3
#define TCPWM_5__TRIG_RISING 0
#define TCPWM_5__TRIG_FALLING 1
#define TCPWM_5__TRIG_BOTH 2

#define TCPWM_5__INTR_MASK_TC 1
#define TCPWM_5__INTR_MASK_CC_MATCH 2
#define TCPWM_5__INTR_MASK_NONE 0
#define TCPWM_5__INTR_MASK_TC_CC 3

#define TCPWM_5__UNCONFIG 8
#define TCPWM_5__TIMER 1
#define TCPWM_5__QUAD 3
#define TCPWM_5__PWM_SEL 7

#define TCPWM_5__COUNT_UP 0
#define TCPWM_5__COUNT_DOWN 1
#define TCPWM_5__COUNT_UPDOWN0 2
#define TCPWM_5__COUNT_UPDOWN1 3


/* Prescaler */
#define TCPWM_5_PRESCALE_DIVBY1                ((uint32)(0u << TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_PRESCALE_DIVBY2                ((uint32)(1u << TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_PRESCALE_DIVBY4                ((uint32)(2u << TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_PRESCALE_DIVBY8                ((uint32)(3u << TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_PRESCALE_DIVBY16               ((uint32)(4u << TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_PRESCALE_DIVBY32               ((uint32)(5u << TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_PRESCALE_DIVBY64               ((uint32)(6u << TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_PRESCALE_DIVBY128              ((uint32)(7u << TCPWM_5_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TCPWM_5_MODE_TIMER_COMPARE             ((uint32)(TCPWM_5__COMPARE         <<  \
                                                                  TCPWM_5_MODE_SHIFT))
#define TCPWM_5_MODE_TIMER_CAPTURE             ((uint32)(TCPWM_5__CAPTURE         <<  \
                                                                  TCPWM_5_MODE_SHIFT))
#define TCPWM_5_MODE_QUAD                      ((uint32)(TCPWM_5__QUAD            <<  \
                                                                  TCPWM_5_MODE_SHIFT))
#define TCPWM_5_MODE_PWM                       ((uint32)(TCPWM_5__PWM             <<  \
                                                                  TCPWM_5_MODE_SHIFT))
#define TCPWM_5_MODE_PWM_DT                    ((uint32)(TCPWM_5__PWM_DT          <<  \
                                                                  TCPWM_5_MODE_SHIFT))
#define TCPWM_5_MODE_PWM_PR                    ((uint32)(TCPWM_5__PWM_PR          <<  \
                                                                  TCPWM_5_MODE_SHIFT))

/* Quad Modes */
#define TCPWM_5_MODE_X1                        ((uint32)(TCPWM_5__X1              <<  \
                                                                  TCPWM_5_QUAD_MODE_SHIFT))
#define TCPWM_5_MODE_X2                        ((uint32)(TCPWM_5__X2              <<  \
                                                                  TCPWM_5_QUAD_MODE_SHIFT))
#define TCPWM_5_MODE_X4                        ((uint32)(TCPWM_5__X4              <<  \
                                                                  TCPWM_5_QUAD_MODE_SHIFT))

/* Counter modes */
#define TCPWM_5_COUNT_UP                       ((uint32)(TCPWM_5__COUNT_UP        <<  \
                                                                  TCPWM_5_UPDOWN_SHIFT))
#define TCPWM_5_COUNT_DOWN                     ((uint32)(TCPWM_5__COUNT_DOWN      <<  \
                                                                  TCPWM_5_UPDOWN_SHIFT))
#define TCPWM_5_COUNT_UPDOWN0                  ((uint32)(TCPWM_5__COUNT_UPDOWN0   <<  \
                                                                  TCPWM_5_UPDOWN_SHIFT))
#define TCPWM_5_COUNT_UPDOWN1                  ((uint32)(TCPWM_5__COUNT_UPDOWN1   <<  \
                                                                  TCPWM_5_UPDOWN_SHIFT))

/* PWM output invert */
#define TCPWM_5_INVERT_LINE                    ((uint32)(TCPWM_5__INVERSE         <<  \
                                                                  TCPWM_5_INV_OUT_SHIFT))
#define TCPWM_5_INVERT_LINE_N                  ((uint32)(TCPWM_5__INVERSE         <<  \
                                                                  TCPWM_5_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TCPWM_5_TRIG_RISING                    ((uint32)TCPWM_5__TRIG_RISING)
#define TCPWM_5_TRIG_FALLING                   ((uint32)TCPWM_5__TRIG_FALLING)
#define TCPWM_5_TRIG_BOTH                      ((uint32)TCPWM_5__TRIG_BOTH)
#define TCPWM_5_TRIG_LEVEL                     ((uint32)TCPWM_5__TRIG_LEVEL)

/* Interrupt mask */
#define TCPWM_5_INTR_MASK_TC                   ((uint32)TCPWM_5__INTR_MASK_TC)
#define TCPWM_5_INTR_MASK_CC_MATCH             ((uint32)TCPWM_5__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TCPWM_5_CC_MATCH_SET                   (0x00u)
#define TCPWM_5_CC_MATCH_CLEAR                 (0x01u)
#define TCPWM_5_CC_MATCH_INVERT                (0x02u)
#define TCPWM_5_CC_MATCH_NO_CHANGE             (0x03u)
#define TCPWM_5_OVERLOW_SET                    (0x00u)
#define TCPWM_5_OVERLOW_CLEAR                  (0x04u)
#define TCPWM_5_OVERLOW_INVERT                 (0x08u)
#define TCPWM_5_OVERLOW_NO_CHANGE              (0x0Cu)
#define TCPWM_5_UNDERFLOW_SET                  (0x00u)
#define TCPWM_5_UNDERFLOW_CLEAR                (0x10u)
#define TCPWM_5_UNDERFLOW_INVERT               (0x20u)
#define TCPWM_5_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TCPWM_5_PWM_MODE_LEFT                  (TCPWM_5_CC_MATCH_CLEAR        |   \
                                                         TCPWM_5_OVERLOW_SET           |   \
                                                         TCPWM_5_UNDERFLOW_NO_CHANGE)
#define TCPWM_5_PWM_MODE_RIGHT                 (TCPWM_5_CC_MATCH_SET          |   \
                                                         TCPWM_5_OVERLOW_NO_CHANGE     |   \
                                                         TCPWM_5_UNDERFLOW_CLEAR)
#define TCPWM_5_PWM_MODE_ASYM                  (TCPWM_5_CC_MATCH_INVERT       |   \
                                                         TCPWM_5_OVERLOW_SET           |   \
                                                         TCPWM_5_UNDERFLOW_CLEAR)

#if (TCPWM_5_CY_TCPWM_V2)
    #if(TCPWM_5_CY_TCPWM_4000)
        #define TCPWM_5_PWM_MODE_CENTER                (TCPWM_5_CC_MATCH_INVERT       |   \
                                                                 TCPWM_5_OVERLOW_NO_CHANGE     |   \
                                                                 TCPWM_5_UNDERFLOW_CLEAR)
    #else
        #define TCPWM_5_PWM_MODE_CENTER                (TCPWM_5_CC_MATCH_INVERT       |   \
                                                                 TCPWM_5_OVERLOW_SET           |   \
                                                                 TCPWM_5_UNDERFLOW_CLEAR)
    #endif /* (TCPWM_5_CY_TCPWM_4000) */
#else
    #define TCPWM_5_PWM_MODE_CENTER                (TCPWM_5_CC_MATCH_INVERT       |   \
                                                             TCPWM_5_OVERLOW_NO_CHANGE     |   \
                                                             TCPWM_5_UNDERFLOW_CLEAR)
#endif /* (TCPWM_5_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TCPWM_5_CMD_CAPTURE                    (0u)
#define TCPWM_5_CMD_RELOAD                     (8u)
#define TCPWM_5_CMD_STOP                       (16u)
#define TCPWM_5_CMD_START                      (24u)

/* Status */
#define TCPWM_5_STATUS_DOWN                    (1u)
#define TCPWM_5_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TCPWM_5_Init(void);
void   TCPWM_5_Enable(void);
void   TCPWM_5_Start(void);
void   TCPWM_5_Stop(void);

void   TCPWM_5_SetMode(uint32 mode);
void   TCPWM_5_SetCounterMode(uint32 counterMode);
void   TCPWM_5_SetPWMMode(uint32 modeMask);
void   TCPWM_5_SetQDMode(uint32 qdMode);

void   TCPWM_5_SetPrescaler(uint32 prescaler);
void   TCPWM_5_TriggerCommand(uint32 mask, uint32 command);
void   TCPWM_5_SetOneShot(uint32 oneShotEnable);
uint32 TCPWM_5_ReadStatus(void);

void   TCPWM_5_SetPWMSyncKill(uint32 syncKillEnable);
void   TCPWM_5_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TCPWM_5_SetPWMDeadTime(uint32 deadTime);
void   TCPWM_5_SetPWMInvert(uint32 mask);

void   TCPWM_5_SetInterruptMode(uint32 interruptMask);
uint32 TCPWM_5_GetInterruptSourceMasked(void);
uint32 TCPWM_5_GetInterruptSource(void);
void   TCPWM_5_ClearInterrupt(uint32 interruptMask);
void   TCPWM_5_SetInterrupt(uint32 interruptMask);

void   TCPWM_5_WriteCounter(uint32 count);
uint32 TCPWM_5_ReadCounter(void);

uint32 TCPWM_5_ReadCapture(void);
uint32 TCPWM_5_ReadCaptureBuf(void);

void   TCPWM_5_WritePeriod(uint32 period);
uint32 TCPWM_5_ReadPeriod(void);
void   TCPWM_5_WritePeriodBuf(uint32 periodBuf);
uint32 TCPWM_5_ReadPeriodBuf(void);

void   TCPWM_5_WriteCompare(uint32 compare);
uint32 TCPWM_5_ReadCompare(void);
void   TCPWM_5_WriteCompareBuf(uint32 compareBuf);
uint32 TCPWM_5_ReadCompareBuf(void);

void   TCPWM_5_SetPeriodSwap(uint32 swapEnable);
void   TCPWM_5_SetCompareSwap(uint32 swapEnable);

void   TCPWM_5_SetCaptureMode(uint32 triggerMode);
void   TCPWM_5_SetReloadMode(uint32 triggerMode);
void   TCPWM_5_SetStartMode(uint32 triggerMode);
void   TCPWM_5_SetStopMode(uint32 triggerMode);
void   TCPWM_5_SetCountMode(uint32 triggerMode);

void   TCPWM_5_SaveConfig(void);
void   TCPWM_5_RestoreConfig(void);
void   TCPWM_5_Sleep(void);
void   TCPWM_5_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TCPWM_5_BLOCK_CONTROL_REG              (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TCPWM_5_BLOCK_CONTROL_PTR              ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TCPWM_5_COMMAND_REG                    (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TCPWM_5_COMMAND_PTR                    ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TCPWM_5_INTRRUPT_CAUSE_REG             (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TCPWM_5_INTRRUPT_CAUSE_PTR             ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TCPWM_5_CONTROL_REG                    (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__CTRL )
#define TCPWM_5_CONTROL_PTR                    ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__CTRL )
#define TCPWM_5_STATUS_REG                     (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__STATUS )
#define TCPWM_5_STATUS_PTR                     ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__STATUS )
#define TCPWM_5_COUNTER_REG                    (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__COUNTER )
#define TCPWM_5_COUNTER_PTR                    ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__COUNTER )
#define TCPWM_5_COMP_CAP_REG                   (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__CC )
#define TCPWM_5_COMP_CAP_PTR                   ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__CC )
#define TCPWM_5_COMP_CAP_BUF_REG               (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__CC_BUFF )
#define TCPWM_5_COMP_CAP_BUF_PTR               ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__CC_BUFF )
#define TCPWM_5_PERIOD_REG                     (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__PERIOD )
#define TCPWM_5_PERIOD_PTR                     ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__PERIOD )
#define TCPWM_5_PERIOD_BUF_REG                 (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TCPWM_5_PERIOD_BUF_PTR                 ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TCPWM_5_TRIG_CONTROL0_REG              (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TCPWM_5_TRIG_CONTROL0_PTR              ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TCPWM_5_TRIG_CONTROL1_REG              (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TCPWM_5_TRIG_CONTROL1_PTR              ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TCPWM_5_TRIG_CONTROL2_REG              (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TCPWM_5_TRIG_CONTROL2_PTR              ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TCPWM_5_INTERRUPT_REQ_REG              (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR )
#define TCPWM_5_INTERRUPT_REQ_PTR              ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR )
#define TCPWM_5_INTERRUPT_SET_REG              (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR_SET )
#define TCPWM_5_INTERRUPT_SET_PTR              ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR_SET )
#define TCPWM_5_INTERRUPT_MASK_REG             (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR_MASK )
#define TCPWM_5_INTERRUPT_MASK_PTR             ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR_MASK )
#define TCPWM_5_INTERRUPT_MASKED_REG           (*(reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TCPWM_5_INTERRUPT_MASKED_PTR           ( (reg32 *) TCPWM_5_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TCPWM_5_MASK                           ((uint32)TCPWM_5_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TCPWM_5_RELOAD_CC_SHIFT                (0u)
#define TCPWM_5_RELOAD_PERIOD_SHIFT            (1u)
#define TCPWM_5_PWM_SYNC_KILL_SHIFT            (2u)
#define TCPWM_5_PWM_STOP_KILL_SHIFT            (3u)
#define TCPWM_5_PRESCALER_SHIFT                (8u)
#define TCPWM_5_UPDOWN_SHIFT                   (16u)
#define TCPWM_5_ONESHOT_SHIFT                  (18u)
#define TCPWM_5_QUAD_MODE_SHIFT                (20u)
#define TCPWM_5_INV_OUT_SHIFT                  (20u)
#define TCPWM_5_INV_COMPL_OUT_SHIFT            (21u)
#define TCPWM_5_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TCPWM_5_RELOAD_CC_MASK                 ((uint32)(TCPWM_5_1BIT_MASK        <<  \
                                                                            TCPWM_5_RELOAD_CC_SHIFT))
#define TCPWM_5_RELOAD_PERIOD_MASK             ((uint32)(TCPWM_5_1BIT_MASK        <<  \
                                                                            TCPWM_5_RELOAD_PERIOD_SHIFT))
#define TCPWM_5_PWM_SYNC_KILL_MASK             ((uint32)(TCPWM_5_1BIT_MASK        <<  \
                                                                            TCPWM_5_PWM_SYNC_KILL_SHIFT))
#define TCPWM_5_PWM_STOP_KILL_MASK             ((uint32)(TCPWM_5_1BIT_MASK        <<  \
                                                                            TCPWM_5_PWM_STOP_KILL_SHIFT))
#define TCPWM_5_PRESCALER_MASK                 ((uint32)(TCPWM_5_8BIT_MASK        <<  \
                                                                            TCPWM_5_PRESCALER_SHIFT))
#define TCPWM_5_UPDOWN_MASK                    ((uint32)(TCPWM_5_2BIT_MASK        <<  \
                                                                            TCPWM_5_UPDOWN_SHIFT))
#define TCPWM_5_ONESHOT_MASK                   ((uint32)(TCPWM_5_1BIT_MASK        <<  \
                                                                            TCPWM_5_ONESHOT_SHIFT))
#define TCPWM_5_QUAD_MODE_MASK                 ((uint32)(TCPWM_5_3BIT_MASK        <<  \
                                                                            TCPWM_5_QUAD_MODE_SHIFT))
#define TCPWM_5_INV_OUT_MASK                   ((uint32)(TCPWM_5_2BIT_MASK        <<  \
                                                                            TCPWM_5_INV_OUT_SHIFT))
#define TCPWM_5_MODE_MASK                      ((uint32)(TCPWM_5_3BIT_MASK        <<  \
                                                                            TCPWM_5_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TCPWM_5_CAPTURE_SHIFT                  (0u)
#define TCPWM_5_COUNT_SHIFT                    (2u)
#define TCPWM_5_RELOAD_SHIFT                   (4u)
#define TCPWM_5_STOP_SHIFT                     (6u)
#define TCPWM_5_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TCPWM_5_CAPTURE_MASK                   ((uint32)(TCPWM_5_2BIT_MASK        <<  \
                                                                  TCPWM_5_CAPTURE_SHIFT))
#define TCPWM_5_COUNT_MASK                     ((uint32)(TCPWM_5_2BIT_MASK        <<  \
                                                                  TCPWM_5_COUNT_SHIFT))
#define TCPWM_5_RELOAD_MASK                    ((uint32)(TCPWM_5_2BIT_MASK        <<  \
                                                                  TCPWM_5_RELOAD_SHIFT))
#define TCPWM_5_STOP_MASK                      ((uint32)(TCPWM_5_2BIT_MASK        <<  \
                                                                  TCPWM_5_STOP_SHIFT))
#define TCPWM_5_START_MASK                     ((uint32)(TCPWM_5_2BIT_MASK        <<  \
                                                                  TCPWM_5_START_SHIFT))

/* MASK */
#define TCPWM_5_1BIT_MASK                      ((uint32)0x01u)
#define TCPWM_5_2BIT_MASK                      ((uint32)0x03u)
#define TCPWM_5_3BIT_MASK                      ((uint32)0x07u)
#define TCPWM_5_6BIT_MASK                      ((uint32)0x3Fu)
#define TCPWM_5_8BIT_MASK                      ((uint32)0xFFu)
#define TCPWM_5_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TCPWM_5_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TCPWM_5_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TCPWM_5_QUAD_ENCODING_MODES     << TCPWM_5_QUAD_MODE_SHIFT))       |\
         ((uint32)(TCPWM_5_CONFIG                  << TCPWM_5_MODE_SHIFT)))

#define TCPWM_5_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TCPWM_5_PWM_STOP_EVENT          << TCPWM_5_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TCPWM_5_PWM_OUT_INVERT          << TCPWM_5_INV_OUT_SHIFT))         |\
         ((uint32)(TCPWM_5_PWM_OUT_N_INVERT        << TCPWM_5_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TCPWM_5_PWM_MODE                << TCPWM_5_MODE_SHIFT)))

#define TCPWM_5_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TCPWM_5_PWM_RUN_MODE         << TCPWM_5_ONESHOT_SHIFT))
            
#define TCPWM_5_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TCPWM_5_PWM_ALIGN            << TCPWM_5_UPDOWN_SHIFT))

#define TCPWM_5_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TCPWM_5_PWM_KILL_EVENT      << TCPWM_5_PWM_SYNC_KILL_SHIFT))

#define TCPWM_5_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TCPWM_5_PWM_DEAD_TIME_CYCLE  << TCPWM_5_PRESCALER_SHIFT))

#define TCPWM_5_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TCPWM_5_PWM_PRESCALER        << TCPWM_5_PRESCALER_SHIFT))

#define TCPWM_5_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TCPWM_5_TC_PRESCALER            << TCPWM_5_PRESCALER_SHIFT))       |\
         ((uint32)(TCPWM_5_TC_COUNTER_MODE         << TCPWM_5_UPDOWN_SHIFT))          |\
         ((uint32)(TCPWM_5_TC_RUN_MODE             << TCPWM_5_ONESHOT_SHIFT))         |\
         ((uint32)(TCPWM_5_TC_COMP_CAP_MODE        << TCPWM_5_MODE_SHIFT)))
        
#define TCPWM_5_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TCPWM_5_QUAD_PHIA_SIGNAL_MODE   << TCPWM_5_COUNT_SHIFT))           |\
         ((uint32)(TCPWM_5_QUAD_INDEX_SIGNAL_MODE  << TCPWM_5_RELOAD_SHIFT))          |\
         ((uint32)(TCPWM_5_QUAD_STOP_SIGNAL_MODE   << TCPWM_5_STOP_SHIFT))            |\
         ((uint32)(TCPWM_5_QUAD_PHIB_SIGNAL_MODE   << TCPWM_5_START_SHIFT)))

#define TCPWM_5_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TCPWM_5_PWM_SWITCH_SIGNAL_MODE  << TCPWM_5_CAPTURE_SHIFT))         |\
         ((uint32)(TCPWM_5_PWM_COUNT_SIGNAL_MODE   << TCPWM_5_COUNT_SHIFT))           |\
         ((uint32)(TCPWM_5_PWM_RELOAD_SIGNAL_MODE  << TCPWM_5_RELOAD_SHIFT))          |\
         ((uint32)(TCPWM_5_PWM_STOP_SIGNAL_MODE    << TCPWM_5_STOP_SHIFT))            |\
         ((uint32)(TCPWM_5_PWM_START_SIGNAL_MODE   << TCPWM_5_START_SHIFT)))

#define TCPWM_5_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TCPWM_5_TC_CAPTURE_SIGNAL_MODE  << TCPWM_5_CAPTURE_SHIFT))         |\
         ((uint32)(TCPWM_5_TC_COUNT_SIGNAL_MODE    << TCPWM_5_COUNT_SHIFT))           |\
         ((uint32)(TCPWM_5_TC_RELOAD_SIGNAL_MODE   << TCPWM_5_RELOAD_SHIFT))          |\
         ((uint32)(TCPWM_5_TC_STOP_SIGNAL_MODE     << TCPWM_5_STOP_SHIFT))            |\
         ((uint32)(TCPWM_5_TC_START_SIGNAL_MODE    << TCPWM_5_START_SHIFT)))
        
#define TCPWM_5_TIMER_UPDOWN_CNT_USED                                                          \
                ((TCPWM_5__COUNT_UPDOWN0 == TCPWM_5_TC_COUNTER_MODE)                  ||\
                 (TCPWM_5__COUNT_UPDOWN1 == TCPWM_5_TC_COUNTER_MODE))

#define TCPWM_5_PWM_UPDOWN_CNT_USED                                                            \
                ((TCPWM_5__CENTER == TCPWM_5_PWM_ALIGN)                               ||\
                 (TCPWM_5__ASYMMETRIC == TCPWM_5_PWM_ALIGN))               
        
#define TCPWM_5_PWM_PR_INIT_VALUE              (1u)
#define TCPWM_5_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TCPWM_5_H */

/* [] END OF FILE */

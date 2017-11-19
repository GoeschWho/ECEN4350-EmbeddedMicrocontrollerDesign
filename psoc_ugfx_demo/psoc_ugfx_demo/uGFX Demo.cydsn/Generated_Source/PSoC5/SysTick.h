/*******************************************************************************
* File Name: SysTick.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SysTick_H)
#define CY_CLOCK_SysTick_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SysTick_Start(void) ;
void SysTick_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SysTick_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SysTick_StandbyPower(uint8 state) ;
void SysTick_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SysTick_GetDividerRegister(void) ;
void SysTick_SetModeRegister(uint8 modeBitMask) ;
void SysTick_ClearModeRegister(uint8 modeBitMask) ;
uint8 SysTick_GetModeRegister(void) ;
void SysTick_SetSourceRegister(uint8 clkSource) ;
uint8 SysTick_GetSourceRegister(void) ;
#if defined(SysTick__CFG3)
void SysTick_SetPhaseRegister(uint8 clkPhase) ;
uint8 SysTick_GetPhaseRegister(void) ;
#endif /* defined(SysTick__CFG3) */

#define SysTick_Enable()                       SysTick_Start()
#define SysTick_Disable()                      SysTick_Stop()
#define SysTick_SetDivider(clkDivider)         SysTick_SetDividerRegister(clkDivider, 1u)
#define SysTick_SetDividerValue(clkDivider)    SysTick_SetDividerRegister((clkDivider) - 1u, 1u)
#define SysTick_SetMode(clkMode)               SysTick_SetModeRegister(clkMode)
#define SysTick_SetSource(clkSource)           SysTick_SetSourceRegister(clkSource)
#if defined(SysTick__CFG3)
#define SysTick_SetPhase(clkPhase)             SysTick_SetPhaseRegister(clkPhase)
#define SysTick_SetPhaseValue(clkPhase)        SysTick_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(SysTick__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SysTick_CLKEN              (* (reg8 *) SysTick__PM_ACT_CFG)
#define SysTick_CLKEN_PTR          ((reg8 *) SysTick__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SysTick_CLKSTBY            (* (reg8 *) SysTick__PM_STBY_CFG)
#define SysTick_CLKSTBY_PTR        ((reg8 *) SysTick__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SysTick_DIV_LSB            (* (reg8 *) SysTick__CFG0)
#define SysTick_DIV_LSB_PTR        ((reg8 *) SysTick__CFG0)
#define SysTick_DIV_PTR            ((reg16 *) SysTick__CFG0)

/* Clock MSB divider configuration register. */
#define SysTick_DIV_MSB            (* (reg8 *) SysTick__CFG1)
#define SysTick_DIV_MSB_PTR        ((reg8 *) SysTick__CFG1)

/* Mode and source configuration register */
#define SysTick_MOD_SRC            (* (reg8 *) SysTick__CFG2)
#define SysTick_MOD_SRC_PTR        ((reg8 *) SysTick__CFG2)

#if defined(SysTick__CFG3)
/* Analog clock phase configuration register */
#define SysTick_PHASE              (* (reg8 *) SysTick__CFG3)
#define SysTick_PHASE_PTR          ((reg8 *) SysTick__CFG3)
#endif /* defined(SysTick__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SysTick_CLKEN_MASK         SysTick__PM_ACT_MSK
#define SysTick_CLKSTBY_MASK       SysTick__PM_STBY_MSK

/* CFG2 field masks */
#define SysTick_SRC_SEL_MSK        SysTick__CFG2_SRC_SEL_MASK
#define SysTick_MODE_MASK          (~(SysTick_SRC_SEL_MSK))

#if defined(SysTick__CFG3)
/* CFG3 phase mask */
#define SysTick_PHASE_MASK         SysTick__CFG3_PHASE_DLY_MASK
#endif /* defined(SysTick__CFG3) */

#endif /* CY_CLOCK_SysTick_H */


/* [] END OF FILE */

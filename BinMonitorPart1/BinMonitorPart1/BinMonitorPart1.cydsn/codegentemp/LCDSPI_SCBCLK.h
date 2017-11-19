/*******************************************************************************
* File Name: LCDSPI_SCBCLK.h
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

#if !defined(CY_CLOCK_LCDSPI_SCBCLK_H)
#define CY_CLOCK_LCDSPI_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void LCDSPI_SCBCLK_StartEx(uint32 alignClkDiv);
#define LCDSPI_SCBCLK_Start() \
    LCDSPI_SCBCLK_StartEx(LCDSPI_SCBCLK__PA_DIV_ID)

#else

void LCDSPI_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void LCDSPI_SCBCLK_Stop(void);

void LCDSPI_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 LCDSPI_SCBCLK_GetDividerRegister(void);
uint8  LCDSPI_SCBCLK_GetFractionalDividerRegister(void);

#define LCDSPI_SCBCLK_Enable()                         LCDSPI_SCBCLK_Start()
#define LCDSPI_SCBCLK_Disable()                        LCDSPI_SCBCLK_Stop()
#define LCDSPI_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    LCDSPI_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define LCDSPI_SCBCLK_SetDivider(clkDivider)           LCDSPI_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define LCDSPI_SCBCLK_SetDividerValue(clkDivider)      LCDSPI_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define LCDSPI_SCBCLK_DIV_ID     LCDSPI_SCBCLK__DIV_ID

#define LCDSPI_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define LCDSPI_SCBCLK_CTRL_REG   (*(reg32 *)LCDSPI_SCBCLK__CTRL_REGISTER)
#define LCDSPI_SCBCLK_DIV_REG    (*(reg32 *)LCDSPI_SCBCLK__DIV_REGISTER)

#define LCDSPI_SCBCLK_CMD_DIV_SHIFT          (0u)
#define LCDSPI_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define LCDSPI_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define LCDSPI_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define LCDSPI_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << LCDSPI_SCBCLK_CMD_DISABLE_SHIFT))
#define LCDSPI_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << LCDSPI_SCBCLK_CMD_ENABLE_SHIFT))

#define LCDSPI_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define LCDSPI_SCBCLK_DIV_FRAC_SHIFT (3u)
#define LCDSPI_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define LCDSPI_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define LCDSPI_SCBCLK_DIV_REG        (*(reg32 *)LCDSPI_SCBCLK__REGISTER)
#define LCDSPI_SCBCLK_ENABLE_REG     LCDSPI_SCBCLK_DIV_REG
#define LCDSPI_SCBCLK_DIV_FRAC_MASK  LCDSPI_SCBCLK__FRAC_MASK
#define LCDSPI_SCBCLK_DIV_FRAC_SHIFT (16u)
#define LCDSPI_SCBCLK_DIV_INT_MASK   LCDSPI_SCBCLK__DIVIDER_MASK
#define LCDSPI_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_LCDSPI_SCBCLK_H) */

/* [] END OF FILE */

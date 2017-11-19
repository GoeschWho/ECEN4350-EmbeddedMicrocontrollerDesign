/*******************************************************************************
* File Name: LCDSPI_ss0_m.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LCDSPI_ss0_m_ALIASES_H) /* Pins LCDSPI_ss0_m_ALIASES_H */
#define CY_PINS_LCDSPI_ss0_m_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LCDSPI_ss0_m_0			(LCDSPI_ss0_m__0__PC)
#define LCDSPI_ss0_m_0_PS		(LCDSPI_ss0_m__0__PS)
#define LCDSPI_ss0_m_0_PC		(LCDSPI_ss0_m__0__PC)
#define LCDSPI_ss0_m_0_DR		(LCDSPI_ss0_m__0__DR)
#define LCDSPI_ss0_m_0_SHIFT	(LCDSPI_ss0_m__0__SHIFT)
#define LCDSPI_ss0_m_0_INTR	((uint16)((uint16)0x0003u << (LCDSPI_ss0_m__0__SHIFT*2u)))

#define LCDSPI_ss0_m_INTR_ALL	 ((uint16)(LCDSPI_ss0_m_0_INTR))


#endif /* End Pins LCDSPI_ss0_m_ALIASES_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: rst0_m.h  
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

#if !defined(CY_PINS_rst0_m_ALIASES_H) /* Pins rst0_m_ALIASES_H */
#define CY_PINS_rst0_m_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define rst0_m_0			(rst0_m__0__PC)
#define rst0_m_0_PS		(rst0_m__0__PS)
#define rst0_m_0_PC		(rst0_m__0__PC)
#define rst0_m_0_DR		(rst0_m__0__DR)
#define rst0_m_0_SHIFT	(rst0_m__0__SHIFT)
#define rst0_m_0_INTR	((uint16)((uint16)0x0003u << (rst0_m__0__SHIFT*2u)))

#define rst0_m_INTR_ALL	 ((uint16)(rst0_m_0_INTR))


#endif /* End Pins rst0_m_ALIASES_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: TCPWM_5_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

#include "TCPWM_5.h"

static TCPWM_5_BACKUP_STRUCT TCPWM_5_backup;


/*******************************************************************************
* Function Name: TCPWM_5_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TCPWM_5_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TCPWM_5_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TCPWM_5_Sleep(void)
{
    if(0u != (TCPWM_5_BLOCK_CONTROL_REG & TCPWM_5_MASK))
    {
        TCPWM_5_backup.enableState = 1u;
    }
    else
    {
        TCPWM_5_backup.enableState = 0u;
    }

    TCPWM_5_Stop();
    TCPWM_5_SaveConfig();
}


/*******************************************************************************
* Function Name: TCPWM_5_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TCPWM_5_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TCPWM_5_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TCPWM_5_Wakeup(void)
{
    TCPWM_5_RestoreConfig();

    if(0u != TCPWM_5_backup.enableState)
    {
        TCPWM_5_Enable();
    }
}


/* [] END OF FILE */

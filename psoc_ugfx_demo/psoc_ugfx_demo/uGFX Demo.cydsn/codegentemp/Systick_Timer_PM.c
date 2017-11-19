/*******************************************************************************
* File Name: Systick_Timer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Systick_Timer.h"

static Systick_Timer_backupStruct Systick_Timer_backup;


/*******************************************************************************
* Function Name: Systick_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Systick_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Systick_Timer_SaveConfig(void) 
{
    #if (!Systick_Timer_UsingFixedFunction)
        Systick_Timer_backup.TimerUdb = Systick_Timer_ReadCounter();
        Systick_Timer_backup.InterruptMaskValue = Systick_Timer_STATUS_MASK;
        #if (Systick_Timer_UsingHWCaptureCounter)
            Systick_Timer_backup.TimerCaptureCounter = Systick_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Systick_Timer_UDB_CONTROL_REG_REMOVED)
            Systick_Timer_backup.TimerControlRegister = Systick_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Systick_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Systick_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Systick_Timer_RestoreConfig(void) 
{   
    #if (!Systick_Timer_UsingFixedFunction)

        Systick_Timer_WriteCounter(Systick_Timer_backup.TimerUdb);
        Systick_Timer_STATUS_MASK =Systick_Timer_backup.InterruptMaskValue;
        #if (Systick_Timer_UsingHWCaptureCounter)
            Systick_Timer_SetCaptureCount(Systick_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Systick_Timer_UDB_CONTROL_REG_REMOVED)
            Systick_Timer_WriteControlRegister(Systick_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Systick_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Systick_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Systick_Timer_Sleep(void) 
{
    #if(!Systick_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Systick_Timer_CTRL_ENABLE == (Systick_Timer_CONTROL & Systick_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Systick_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Systick_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Systick_Timer_Stop();
    Systick_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Systick_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Systick_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Systick_Timer_Wakeup(void) 
{
    Systick_Timer_RestoreConfig();
    #if(!Systick_Timer_UDB_CONTROL_REG_REMOVED)
        if(Systick_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Systick_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

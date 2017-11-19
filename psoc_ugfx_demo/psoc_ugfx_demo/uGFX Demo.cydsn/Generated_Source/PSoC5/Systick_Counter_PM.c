/*******************************************************************************
* File Name: Systick_Counter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Systick_Counter.h"

static Systick_Counter_backupStruct Systick_Counter_backup;


/*******************************************************************************
* Function Name: Systick_Counter_SaveConfig
********************************************************************************
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
*  Systick_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Systick_Counter_SaveConfig(void) 
{
    #if (!Systick_Counter_UsingFixedFunction)

        Systick_Counter_backup.CounterUdb = Systick_Counter_ReadCounter();

        #if(!Systick_Counter_ControlRegRemoved)
            Systick_Counter_backup.CounterControlRegister = Systick_Counter_ReadControlRegister();
        #endif /* (!Systick_Counter_ControlRegRemoved) */

    #endif /* (!Systick_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Systick_Counter_RestoreConfig
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
*  Systick_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Systick_Counter_RestoreConfig(void) 
{      
    #if (!Systick_Counter_UsingFixedFunction)

       Systick_Counter_WriteCounter(Systick_Counter_backup.CounterUdb);

        #if(!Systick_Counter_ControlRegRemoved)
            Systick_Counter_WriteControlRegister(Systick_Counter_backup.CounterControlRegister);
        #endif /* (!Systick_Counter_ControlRegRemoved) */

    #endif /* (!Systick_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Systick_Counter_Sleep
********************************************************************************
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
*  Systick_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Systick_Counter_Sleep(void) 
{
    #if(!Systick_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Systick_Counter_CTRL_ENABLE == (Systick_Counter_CONTROL & Systick_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Systick_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Systick_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Systick_Counter_backup.CounterEnableState = 1u;
        if(Systick_Counter_backup.CounterEnableState != 0u)
        {
            Systick_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Systick_Counter_ControlRegRemoved) */
    
    Systick_Counter_Stop();
    Systick_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Systick_Counter_Wakeup
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
*  Systick_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Systick_Counter_Wakeup(void) 
{
    Systick_Counter_RestoreConfig();
    #if(!Systick_Counter_ControlRegRemoved)
        if(Systick_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Systick_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Systick_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */

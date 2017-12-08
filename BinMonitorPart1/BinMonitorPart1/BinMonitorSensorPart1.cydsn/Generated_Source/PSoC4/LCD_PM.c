/***************************************************************************//**
* \file LCD_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
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

#include "LCD.h"
#include "LCD_PVT.h"

#if(LCD_SCB_MODE_I2C_INC)
    #include "LCD_I2C_PVT.h"
#endif /* (LCD_SCB_MODE_I2C_INC) */

#if(LCD_SCB_MODE_EZI2C_INC)
    #include "LCD_EZI2C_PVT.h"
#endif /* (LCD_SCB_MODE_EZI2C_INC) */

#if(LCD_SCB_MODE_SPI_INC || LCD_SCB_MODE_UART_INC)
    #include "LCD_SPI_UART_PVT.h"
#endif /* (LCD_SCB_MODE_SPI_INC || LCD_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG || \
   (LCD_SCB_MODE_I2C_CONST_CFG   && (!LCD_I2C_WAKE_ENABLE_CONST))   || \
   (LCD_SCB_MODE_EZI2C_CONST_CFG && (!LCD_EZI2C_WAKE_ENABLE_CONST)) || \
   (LCD_SCB_MODE_SPI_CONST_CFG   && (!LCD_SPI_WAKE_ENABLE_CONST))   || \
   (LCD_SCB_MODE_UART_CONST_CFG  && (!LCD_UART_WAKE_ENABLE_CONST)))

    LCD_BACKUP_STRUCT LCD_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: LCD_Sleep
****************************************************************************//**
*
*  Prepares the LCD component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the LCD_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void LCD_Sleep(void)
{
#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LCD_SCB_WAKE_ENABLE_CHECK)
    {
        if(LCD_SCB_MODE_I2C_RUNTM_CFG)
        {
            LCD_I2CSaveConfig();
        }
        else if(LCD_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LCD_EzI2CSaveConfig();
        }
    #if(!LCD_CY_SCBIP_V1)
        else if(LCD_SCB_MODE_SPI_RUNTM_CFG)
        {
            LCD_SpiSaveConfig();
        }
        else if(LCD_SCB_MODE_UART_RUNTM_CFG)
        {
            LCD_UartSaveConfig();
        }
    #endif /* (!LCD_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        LCD_backup.enableState = (uint8) LCD_GET_CTRL_ENABLED;

        if(0u != LCD_backup.enableState)
        {
            LCD_Stop();
        }
    }

#else

    #if (LCD_SCB_MODE_I2C_CONST_CFG && LCD_I2C_WAKE_ENABLE_CONST)
        LCD_I2CSaveConfig();

    #elif (LCD_SCB_MODE_EZI2C_CONST_CFG && LCD_EZI2C_WAKE_ENABLE_CONST)
        LCD_EzI2CSaveConfig();

    #elif (LCD_SCB_MODE_SPI_CONST_CFG && LCD_SPI_WAKE_ENABLE_CONST)
        LCD_SpiSaveConfig();

    #elif (LCD_SCB_MODE_UART_CONST_CFG && LCD_UART_WAKE_ENABLE_CONST)
        LCD_UartSaveConfig();

    #else

        LCD_backup.enableState = (uint8) LCD_GET_CTRL_ENABLED;

        if(0u != LCD_backup.enableState)
        {
            LCD_Stop();
        }

    #endif /* defined (LCD_SCB_MODE_I2C_CONST_CFG) && (LCD_I2C_WAKE_ENABLE_CONST) */

#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LCD_Wakeup
****************************************************************************//**
*
*  Prepares the LCD component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the LCD_Wakeup() function without first calling the 
*   LCD_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void LCD_Wakeup(void)
{
#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LCD_SCB_WAKE_ENABLE_CHECK)
    {
        if(LCD_SCB_MODE_I2C_RUNTM_CFG)
        {
            LCD_I2CRestoreConfig();
        }
        else if(LCD_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LCD_EzI2CRestoreConfig();
        }
    #if(!LCD_CY_SCBIP_V1)
        else if(LCD_SCB_MODE_SPI_RUNTM_CFG)
        {
            LCD_SpiRestoreConfig();
        }
        else if(LCD_SCB_MODE_UART_RUNTM_CFG)
        {
            LCD_UartRestoreConfig();
        }
    #endif /* (!LCD_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != LCD_backup.enableState)
        {
            LCD_Enable();
        }
    }

#else

    #if (LCD_SCB_MODE_I2C_CONST_CFG  && LCD_I2C_WAKE_ENABLE_CONST)
        LCD_I2CRestoreConfig();

    #elif (LCD_SCB_MODE_EZI2C_CONST_CFG && LCD_EZI2C_WAKE_ENABLE_CONST)
        LCD_EzI2CRestoreConfig();

    #elif (LCD_SCB_MODE_SPI_CONST_CFG && LCD_SPI_WAKE_ENABLE_CONST)
        LCD_SpiRestoreConfig();

    #elif (LCD_SCB_MODE_UART_CONST_CFG && LCD_UART_WAKE_ENABLE_CONST)
        LCD_UartRestoreConfig();

    #else

        if(0u != LCD_backup.enableState)
        {
            LCD_Enable();
        }

    #endif /* (LCD_I2C_WAKE_ENABLE_CONST) */

#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

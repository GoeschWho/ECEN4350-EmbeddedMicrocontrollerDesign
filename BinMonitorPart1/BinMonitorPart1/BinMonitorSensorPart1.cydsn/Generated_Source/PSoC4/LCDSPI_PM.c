/***************************************************************************//**
* \file LCDSPI_PM.c
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

#include "LCDSPI.h"
#include "LCDSPI_PVT.h"

#if(LCDSPI_SCB_MODE_I2C_INC)
    #include "LCDSPI_I2C_PVT.h"
#endif /* (LCDSPI_SCB_MODE_I2C_INC) */

#if(LCDSPI_SCB_MODE_EZI2C_INC)
    #include "LCDSPI_EZI2C_PVT.h"
#endif /* (LCDSPI_SCB_MODE_EZI2C_INC) */

#if(LCDSPI_SCB_MODE_SPI_INC || LCDSPI_SCB_MODE_UART_INC)
    #include "LCDSPI_SPI_UART_PVT.h"
#endif /* (LCDSPI_SCB_MODE_SPI_INC || LCDSPI_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
   (LCDSPI_SCB_MODE_I2C_CONST_CFG   && (!LCDSPI_I2C_WAKE_ENABLE_CONST))   || \
   (LCDSPI_SCB_MODE_EZI2C_CONST_CFG && (!LCDSPI_EZI2C_WAKE_ENABLE_CONST)) || \
   (LCDSPI_SCB_MODE_SPI_CONST_CFG   && (!LCDSPI_SPI_WAKE_ENABLE_CONST))   || \
   (LCDSPI_SCB_MODE_UART_CONST_CFG  && (!LCDSPI_UART_WAKE_ENABLE_CONST)))

    LCDSPI_BACKUP_STRUCT LCDSPI_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: LCDSPI_Sleep
****************************************************************************//**
*
*  Prepares the LCDSPI component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the LCDSPI_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void LCDSPI_Sleep(void)
{
#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LCDSPI_SCB_WAKE_ENABLE_CHECK)
    {
        if(LCDSPI_SCB_MODE_I2C_RUNTM_CFG)
        {
            LCDSPI_I2CSaveConfig();
        }
        else if(LCDSPI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LCDSPI_EzI2CSaveConfig();
        }
    #if(!LCDSPI_CY_SCBIP_V1)
        else if(LCDSPI_SCB_MODE_SPI_RUNTM_CFG)
        {
            LCDSPI_SpiSaveConfig();
        }
        else if(LCDSPI_SCB_MODE_UART_RUNTM_CFG)
        {
            LCDSPI_UartSaveConfig();
        }
    #endif /* (!LCDSPI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        LCDSPI_backup.enableState = (uint8) LCDSPI_GET_CTRL_ENABLED;

        if(0u != LCDSPI_backup.enableState)
        {
            LCDSPI_Stop();
        }
    }

#else

    #if (LCDSPI_SCB_MODE_I2C_CONST_CFG && LCDSPI_I2C_WAKE_ENABLE_CONST)
        LCDSPI_I2CSaveConfig();

    #elif (LCDSPI_SCB_MODE_EZI2C_CONST_CFG && LCDSPI_EZI2C_WAKE_ENABLE_CONST)
        LCDSPI_EzI2CSaveConfig();

    #elif (LCDSPI_SCB_MODE_SPI_CONST_CFG && LCDSPI_SPI_WAKE_ENABLE_CONST)
        LCDSPI_SpiSaveConfig();

    #elif (LCDSPI_SCB_MODE_UART_CONST_CFG && LCDSPI_UART_WAKE_ENABLE_CONST)
        LCDSPI_UartSaveConfig();

    #else

        LCDSPI_backup.enableState = (uint8) LCDSPI_GET_CTRL_ENABLED;

        if(0u != LCDSPI_backup.enableState)
        {
            LCDSPI_Stop();
        }

    #endif /* defined (LCDSPI_SCB_MODE_I2C_CONST_CFG) && (LCDSPI_I2C_WAKE_ENABLE_CONST) */

#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LCDSPI_Wakeup
****************************************************************************//**
*
*  Prepares the LCDSPI component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the LCDSPI_Wakeup() function without first calling the 
*   LCDSPI_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void LCDSPI_Wakeup(void)
{
#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LCDSPI_SCB_WAKE_ENABLE_CHECK)
    {
        if(LCDSPI_SCB_MODE_I2C_RUNTM_CFG)
        {
            LCDSPI_I2CRestoreConfig();
        }
        else if(LCDSPI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LCDSPI_EzI2CRestoreConfig();
        }
    #if(!LCDSPI_CY_SCBIP_V1)
        else if(LCDSPI_SCB_MODE_SPI_RUNTM_CFG)
        {
            LCDSPI_SpiRestoreConfig();
        }
        else if(LCDSPI_SCB_MODE_UART_RUNTM_CFG)
        {
            LCDSPI_UartRestoreConfig();
        }
    #endif /* (!LCDSPI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != LCDSPI_backup.enableState)
        {
            LCDSPI_Enable();
        }
    }

#else

    #if (LCDSPI_SCB_MODE_I2C_CONST_CFG  && LCDSPI_I2C_WAKE_ENABLE_CONST)
        LCDSPI_I2CRestoreConfig();

    #elif (LCDSPI_SCB_MODE_EZI2C_CONST_CFG && LCDSPI_EZI2C_WAKE_ENABLE_CONST)
        LCDSPI_EzI2CRestoreConfig();

    #elif (LCDSPI_SCB_MODE_SPI_CONST_CFG && LCDSPI_SPI_WAKE_ENABLE_CONST)
        LCDSPI_SpiRestoreConfig();

    #elif (LCDSPI_SCB_MODE_UART_CONST_CFG && LCDSPI_UART_WAKE_ENABLE_CONST)
        LCDSPI_UartRestoreConfig();

    #else

        if(0u != LCDSPI_backup.enableState)
        {
            LCDSPI_Enable();
        }

    #endif /* (LCDSPI_I2C_WAKE_ENABLE_CONST) */

#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

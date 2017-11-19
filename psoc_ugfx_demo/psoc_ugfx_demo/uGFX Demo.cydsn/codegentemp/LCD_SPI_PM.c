/*******************************************************************************
* File Name: LCD_SPI_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_SPI_PVT.h"

static LCD_SPI_BACKUP_STRUCT LCD_SPI_backup =
{
    LCD_SPI_DISABLED,
    LCD_SPI_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: LCD_SPI_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_SPI_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: LCD_SPI_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_SPI_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: LCD_SPI_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_SPI_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_SPI_Sleep(void) 
{
    /* Save components enable state */
    LCD_SPI_backup.enableState = ((uint8) LCD_SPI_IS_ENABLED);

    LCD_SPI_Stop();
}


/*******************************************************************************
* Function Name: LCD_SPI_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_SPI_backup - used when non-retention registers are restored.
*  LCD_SPI_txBufferWrite - modified every function call - resets to
*  zero.
*  LCD_SPI_txBufferRead - modified every function call - resets to
*  zero.
*  LCD_SPI_rxBufferWrite - modified every function call - resets to
*  zero.
*  LCD_SPI_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_SPI_Wakeup(void) 
{
    #if(LCD_SPI_RX_SOFTWARE_BUF_ENABLED)
        LCD_SPI_rxBufferFull  = 0u;
        LCD_SPI_rxBufferRead  = 0u;
        LCD_SPI_rxBufferWrite = 0u;
    #endif /* (LCD_SPI_RX_SOFTWARE_BUF_ENABLED) */

    #if(LCD_SPI_TX_SOFTWARE_BUF_ENABLED)
        LCD_SPI_txBufferFull  = 0u;
        LCD_SPI_txBufferRead  = 0u;
        LCD_SPI_txBufferWrite = 0u;
    #endif /* (LCD_SPI_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    LCD_SPI_ClearFIFO();

    /* Restore components block enable state */
    if(0u != LCD_SPI_backup.enableState)
    {
        LCD_SPI_Enable();
    }
}


/* [] END OF FILE */

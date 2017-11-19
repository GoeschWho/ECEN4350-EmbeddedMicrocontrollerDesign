/*******************************************************************************
* File Name: LCD_SPI_INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_SPI_PVT.h"


/* User code required at start of ISR */
/* `#START LCD_SPI_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: LCD_SPI_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  LCD_SPI_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  LCD_SPI_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  LCD_SPI_txBuffer[LCD_SPI_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(LCD_SPI_TX_ISR)
{
    #if(LCD_SPI_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (LCD_SPI_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef LCD_SPI_TX_ISR_ENTRY_CALLBACK
        LCD_SPI_TX_ISR_EntryCallback();
    #endif /* LCD_SPI_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START LCD_SPI_TX_ISR_START` */

    /* `#END` */
    
    #if(LCD_SPI_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(LCD_SPI_txBufferRead != LCD_SPI_txBufferWrite)
        {
            tmpStatus = LCD_SPI_GET_STATUS_TX(LCD_SPI_swStatusTx);
            LCD_SPI_swStatusTx = tmpStatus;

            if(0u != (LCD_SPI_swStatusTx & LCD_SPI_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == LCD_SPI_txBufferFull)
                {
                   LCD_SPI_txBufferRead++;

                    if(LCD_SPI_txBufferRead >= LCD_SPI_TX_BUFFER_SIZE)
                    {
                        LCD_SPI_txBufferRead = 0u;
                    }
                }
                else
                {
                    LCD_SPI_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(LCD_SPI_TXDATA_PTR, 
                                             LCD_SPI_txBuffer[LCD_SPI_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(LCD_SPI_txBufferRead == LCD_SPI_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            LCD_SPI_TX_STATUS_MASK_REG &= ((uint8) ~LCD_SPI_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (LCD_SPI_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START LCD_SPI_TX_ISR_END` */

    /* `#END` */
    
    #ifdef LCD_SPI_TX_ISR_EXIT_CALLBACK
        LCD_SPI_TX_ISR_ExitCallback();
    #endif /* LCD_SPI_TX_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: LCD_SPI_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  LCD_SPI_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  LCD_SPI_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  LCD_SPI_rxBuffer[LCD_SPI_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(LCD_SPI_RX_ISR)
{
    #if(LCD_SPI_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (LCD_SPI_RX_SOFTWARE_BUF_ENABLED) */

    #ifdef LCD_SPI_RX_ISR_ENTRY_CALLBACK
        LCD_SPI_RX_ISR_EntryCallback();
    #endif /* LCD_SPI_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START LCD_SPI_RX_ISR_START` */

    /* `#END` */
    
    #if(LCD_SPI_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = LCD_SPI_GET_STATUS_RX(LCD_SPI_swStatusRx);
        LCD_SPI_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (LCD_SPI_swStatusRx & LCD_SPI_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG8(LCD_SPI_RXDATA_PTR);

            /* Set next pointer. */
            LCD_SPI_rxBufferWrite++;
            if(LCD_SPI_rxBufferWrite >= LCD_SPI_RX_BUFFER_SIZE)
            {
                LCD_SPI_rxBufferWrite = 0u;
            }

            if(LCD_SPI_rxBufferWrite == LCD_SPI_rxBufferRead)
            {
                LCD_SPI_rxBufferRead++;
                if(LCD_SPI_rxBufferRead >= LCD_SPI_RX_BUFFER_SIZE)
                {
                    LCD_SPI_rxBufferRead = 0u;
                }

                LCD_SPI_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            LCD_SPI_rxBuffer[LCD_SPI_rxBufferWrite] = rxData;

            tmpStatus = LCD_SPI_GET_STATUS_RX(LCD_SPI_swStatusRx);
            LCD_SPI_swStatusRx = tmpStatus;
        }

    #endif /* (LCD_SPI_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START LCD_SPI_RX_ISR_END` */

    /* `#END` */
    
    #ifdef LCD_SPI_RX_ISR_EXIT_CALLBACK
        LCD_SPI_RX_ISR_ExitCallback();
    #endif /* LCD_SPI_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */

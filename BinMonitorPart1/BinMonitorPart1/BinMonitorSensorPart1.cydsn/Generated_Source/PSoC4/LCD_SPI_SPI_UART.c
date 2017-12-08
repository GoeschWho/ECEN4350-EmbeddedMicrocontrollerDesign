/***************************************************************************//**
* \file LCD_SPI_SPI_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_SPI_PVT.h"
#include "LCD_SPI_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 LCD_SPI_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 LCD_SPI_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  LCD_SPI_rxBufferOverflow;
    /** \} globals */
#endif /* (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

#if(LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 LCD_SPI_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 LCD_SPI_txBufferTail;
#endif /* (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

#if(LCD_SPI_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 LCD_SPI_rxBufferInternal[LCD_SPI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (LCD_SPI_INTERNAL_RX_SW_BUFFER) */

#if(LCD_SPI_INTERNAL_TX_SW_BUFFER)
    volatile uint8 LCD_SPI_txBufferInternal[LCD_SPI_TX_BUFFER_SIZE];
#endif /* (LCD_SPI_INTERNAL_TX_SW_BUFFER) */


#if(LCD_SPI_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: LCD_SPI_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  LCD_SPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  LCD_SPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 LCD_SPI_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (LCD_SPI_CHECK_RX_SW_BUFFER)
        {
            if (LCD_SPI_rxBufferHead != LCD_SPI_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (LCD_SPI_rxBufferTail + 1u);

                if (LCD_SPI_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = LCD_SPI_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                LCD_SPI_rxBufferTail = locTail;

                #if (LCD_SPI_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (LCD_SPI_INTR_RX_MASK_REG & LCD_SPI_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        LCD_SPI_INTR_RX_MASK_REG |= LCD_SPI_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = LCD_SPI_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  LCD_SPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  LCD_SPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 LCD_SPI_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (LCD_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (LCD_SPI_CHECK_RX_SW_BUFFER)
        {
            locHead = LCD_SPI_rxBufferHead;

            if(locHead >= LCD_SPI_rxBufferTail)
            {
                size = (locHead - LCD_SPI_rxBufferTail);
            }
            else
            {
                size = (locHead + (LCD_SPI_INTERNAL_RX_BUFFER_SIZE - LCD_SPI_rxBufferTail));
            }
        }
        #else
        {
            size = LCD_SPI_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  LCD_SPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  LCD_SPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void LCD_SPI_SpiUartClearRxBuffer(void)
    {
        #if (LCD_SPI_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            LCD_SPI_DisableInt();

            /* Flush RX software buffer */
            LCD_SPI_rxBufferHead = LCD_SPI_rxBufferTail;
            LCD_SPI_rxBufferOverflow = 0u;

            LCD_SPI_CLEAR_RX_FIFO;
            LCD_SPI_ClearRxInterruptSource(LCD_SPI_INTR_RX_ALL);

            #if (LCD_SPI_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                LCD_SPI_INTR_RX_MASK_REG |= LCD_SPI_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            LCD_SPI_EnableInt();
        }
        #else
        {
            LCD_SPI_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (LCD_SPI_RX_DIRECTION) */


#if(LCD_SPI_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: LCD_SPI_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  LCD_SPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCD_SPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void LCD_SPI_SpiUartWriteTxData(uint32 txData)
    {
    #if (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (LCD_SPI_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((LCD_SPI_txBufferHead == LCD_SPI_txBufferTail) &&
                (LCD_SPI_SPI_UART_FIFO_SIZE != LCD_SPI_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                LCD_SPI_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (LCD_SPI_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (LCD_SPI_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == LCD_SPI_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                LCD_SPI_ClearTxInterruptSource(LCD_SPI_INTR_TX_NOT_FULL);

                LCD_SPI_PutWordInTxBuffer(locHead, txData);

                LCD_SPI_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (LCD_SPI_INTR_TX_MASK_REG & LCD_SPI_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    LCD_SPI_INTR_TX_MASK_REG |= (uint32) LCD_SPI_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (LCD_SPI_SPI_UART_FIFO_SIZE == LCD_SPI_GET_TX_FIFO_ENTRIES)
            {
            }

            LCD_SPI_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  LCD_SPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCD_SPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void LCD_SPI_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            LCD_SPI_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  LCD_SPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCD_SPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 LCD_SPI_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (LCD_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (LCD_SPI_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = LCD_SPI_txBufferTail;

            if (LCD_SPI_txBufferHead >= locTail)
            {
                size = (LCD_SPI_txBufferHead - locTail);
            }
            else
            {
                size = (LCD_SPI_txBufferHead + (LCD_SPI_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = LCD_SPI_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  LCD_SPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCD_SPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void LCD_SPI_SpiUartClearTxBuffer(void)
    {
        #if (LCD_SPI_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            LCD_SPI_DisableInt();

            /* Flush TX software buffer */
            LCD_SPI_txBufferHead = LCD_SPI_txBufferTail;

            LCD_SPI_INTR_TX_MASK_REG &= (uint32) ~LCD_SPI_INTR_TX_NOT_FULL;
            LCD_SPI_CLEAR_TX_FIFO;
            LCD_SPI_ClearTxInterruptSource(LCD_SPI_INTR_TX_ALL);

            /* Release lock */
            LCD_SPI_EnableInt();
        }
        #else
        {
            LCD_SPI_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (LCD_SPI_TX_DIRECTION) */


/*******************************************************************************
* Function Name: LCD_SPI_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 LCD_SPI_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = LCD_SPI_GetRxInterruptMode();

    LCD_SPI_SetRxInterruptMode(LCD_SPI_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: LCD_SPI_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 LCD_SPI_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = LCD_SPI_GetTxInterruptMode();

    LCD_SPI_SetTxInterruptMode(LCD_SPI_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: LCD_SPI_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void LCD_SPI_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (LCD_SPI_ONE_BYTE_WIDTH == LCD_SPI_rxDataBits)
        {
            LCD_SPI_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            LCD_SPI_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            LCD_SPI_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 LCD_SPI_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (LCD_SPI_ONE_BYTE_WIDTH == LCD_SPI_rxDataBits)
        {
            value = LCD_SPI_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) LCD_SPI_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)LCD_SPI_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void LCD_SPI_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (LCD_SPI_ONE_BYTE_WIDTH == LCD_SPI_txDataBits)
        {
            LCD_SPI_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            LCD_SPI_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            LCD_SPI_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: LCD_SPI_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 LCD_SPI_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (LCD_SPI_ONE_BYTE_WIDTH == LCD_SPI_txDataBits)
        {
            value = (uint32) LCD_SPI_txBuffer[idx];
        }
        else
        {
            value  = (uint32) LCD_SPI_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) LCD_SPI_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (LCD_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */

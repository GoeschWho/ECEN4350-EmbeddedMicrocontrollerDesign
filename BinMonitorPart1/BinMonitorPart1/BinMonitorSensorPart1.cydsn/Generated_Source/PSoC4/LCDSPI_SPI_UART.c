/***************************************************************************//**
* \file LCDSPI_SPI_UART.c
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

#include "LCDSPI_PVT.h"
#include "LCDSPI_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(LCDSPI_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 LCDSPI_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 LCDSPI_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  LCDSPI_rxBufferOverflow;
    /** \} globals */
#endif /* (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST) */

#if(LCDSPI_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 LCDSPI_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 LCDSPI_txBufferTail;
#endif /* (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST) */

#if(LCDSPI_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 LCDSPI_rxBufferInternal[LCDSPI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (LCDSPI_INTERNAL_RX_SW_BUFFER) */

#if(LCDSPI_INTERNAL_TX_SW_BUFFER)
    volatile uint8 LCDSPI_txBufferInternal[LCDSPI_TX_BUFFER_SIZE];
#endif /* (LCDSPI_INTERNAL_TX_SW_BUFFER) */


#if(LCDSPI_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: LCDSPI_SpiUartReadRxData
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
    *  LCDSPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  LCDSPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 LCDSPI_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (LCDSPI_CHECK_RX_SW_BUFFER)
        {
            if (LCDSPI_rxBufferHead != LCDSPI_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (LCDSPI_rxBufferTail + 1u);

                if (LCDSPI_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = LCDSPI_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                LCDSPI_rxBufferTail = locTail;

                #if (LCDSPI_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (LCDSPI_INTR_RX_MASK_REG & LCDSPI_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        LCDSPI_INTR_RX_MASK_REG |= LCDSPI_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = LCDSPI_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: LCDSPI_SpiUartGetRxBufferSize
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
    *  LCDSPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  LCDSPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 LCDSPI_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (LCDSPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (LCDSPI_CHECK_RX_SW_BUFFER)
        {
            locHead = LCDSPI_rxBufferHead;

            if(locHead >= LCDSPI_rxBufferTail)
            {
                size = (locHead - LCDSPI_rxBufferTail);
            }
            else
            {
                size = (locHead + (LCDSPI_INTERNAL_RX_BUFFER_SIZE - LCDSPI_rxBufferTail));
            }
        }
        #else
        {
            size = LCDSPI_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: LCDSPI_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  LCDSPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  LCDSPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void LCDSPI_SpiUartClearRxBuffer(void)
    {
        #if (LCDSPI_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            LCDSPI_DisableInt();

            /* Flush RX software buffer */
            LCDSPI_rxBufferHead = LCDSPI_rxBufferTail;
            LCDSPI_rxBufferOverflow = 0u;

            LCDSPI_CLEAR_RX_FIFO;
            LCDSPI_ClearRxInterruptSource(LCDSPI_INTR_RX_ALL);

            #if (LCDSPI_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                LCDSPI_INTR_RX_MASK_REG |= LCDSPI_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            LCDSPI_EnableInt();
        }
        #else
        {
            LCDSPI_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (LCDSPI_RX_DIRECTION) */


#if(LCDSPI_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: LCDSPI_SpiUartWriteTxData
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
    *  LCDSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCDSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void LCDSPI_SpiUartWriteTxData(uint32 txData)
    {
    #if (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (LCDSPI_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((LCDSPI_txBufferHead == LCDSPI_txBufferTail) &&
                (LCDSPI_SPI_UART_FIFO_SIZE != LCDSPI_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                LCDSPI_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (LCDSPI_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (LCDSPI_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == LCDSPI_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                LCDSPI_ClearTxInterruptSource(LCDSPI_INTR_TX_NOT_FULL);

                LCDSPI_PutWordInTxBuffer(locHead, txData);

                LCDSPI_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (LCDSPI_INTR_TX_MASK_REG & LCDSPI_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    LCDSPI_INTR_TX_MASK_REG |= (uint32) LCDSPI_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (LCDSPI_SPI_UART_FIFO_SIZE == LCDSPI_GET_TX_FIFO_ENTRIES)
            {
            }

            LCDSPI_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: LCDSPI_SpiUartPutArray
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
    *  LCDSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCDSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void LCDSPI_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            LCDSPI_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: LCDSPI_SpiUartGetTxBufferSize
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
    *  LCDSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCDSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 LCDSPI_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (LCDSPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (LCDSPI_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = LCDSPI_txBufferTail;

            if (LCDSPI_txBufferHead >= locTail)
            {
                size = (LCDSPI_txBufferHead - locTail);
            }
            else
            {
                size = (LCDSPI_txBufferHead + (LCDSPI_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = LCDSPI_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: LCDSPI_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  LCDSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  LCDSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void LCDSPI_SpiUartClearTxBuffer(void)
    {
        #if (LCDSPI_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            LCDSPI_DisableInt();

            /* Flush TX software buffer */
            LCDSPI_txBufferHead = LCDSPI_txBufferTail;

            LCDSPI_INTR_TX_MASK_REG &= (uint32) ~LCDSPI_INTR_TX_NOT_FULL;
            LCDSPI_CLEAR_TX_FIFO;
            LCDSPI_ClearTxInterruptSource(LCDSPI_INTR_TX_ALL);

            /* Release lock */
            LCDSPI_EnableInt();
        }
        #else
        {
            LCDSPI_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (LCDSPI_TX_DIRECTION) */


/*******************************************************************************
* Function Name: LCDSPI_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 LCDSPI_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = LCDSPI_GetRxInterruptMode();

    LCDSPI_SetRxInterruptMode(LCDSPI_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: LCDSPI_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 LCDSPI_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = LCDSPI_GetTxInterruptMode();

    LCDSPI_SetTxInterruptMode(LCDSPI_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: LCDSPI_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void LCDSPI_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (LCDSPI_ONE_BYTE_WIDTH == LCDSPI_rxDataBits)
        {
            LCDSPI_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            LCDSPI_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            LCDSPI_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: LCDSPI_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 LCDSPI_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (LCDSPI_ONE_BYTE_WIDTH == LCDSPI_rxDataBits)
        {
            value = LCDSPI_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) LCDSPI_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)LCDSPI_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: LCDSPI_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void LCDSPI_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (LCDSPI_ONE_BYTE_WIDTH == LCDSPI_txDataBits)
        {
            LCDSPI_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            LCDSPI_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            LCDSPI_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: LCDSPI_GetWordFromTxBuffer
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
    uint32 LCDSPI_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (LCDSPI_ONE_BYTE_WIDTH == LCDSPI_txDataBits)
        {
            value = (uint32) LCDSPI_txBuffer[idx];
        }
        else
        {
            value  = (uint32) LCDSPI_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) LCDSPI_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */

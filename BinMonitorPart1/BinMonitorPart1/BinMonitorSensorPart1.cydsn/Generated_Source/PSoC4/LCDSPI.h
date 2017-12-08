/***************************************************************************//**
* \file LCDSPI.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the SCB Component.
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

#if !defined(CY_SCB_LCDSPI_H)
#define CY_SCB_LCDSPI_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

/* SCB IP block v0 is available in PSoC 4100/PSoC 4200 */
#define LCDSPI_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
/* SCB IP block v1 is available in PSoC 4000 */
#define LCDSPI_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
/* SCB IP block v2 is available in all other devices */
#define LCDSPI_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

/** Component version major.minor */
#define LCDSPI_COMP_VERSION_MAJOR    (4)
#define LCDSPI_COMP_VERSION_MINOR    (0)
    
#define LCDSPI_SCB_MODE           (2u)

/* SCB modes enum */
#define LCDSPI_SCB_MODE_I2C       (0x01u)
#define LCDSPI_SCB_MODE_SPI       (0x02u)
#define LCDSPI_SCB_MODE_UART      (0x04u)
#define LCDSPI_SCB_MODE_EZI2C     (0x08u)
#define LCDSPI_SCB_MODE_UNCONFIG  (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define LCDSPI_SCB_MODE_I2C_CONST_CFG       (LCDSPI_SCB_MODE_I2C       == LCDSPI_SCB_MODE)
#define LCDSPI_SCB_MODE_SPI_CONST_CFG       (LCDSPI_SCB_MODE_SPI       == LCDSPI_SCB_MODE)
#define LCDSPI_SCB_MODE_UART_CONST_CFG      (LCDSPI_SCB_MODE_UART      == LCDSPI_SCB_MODE)
#define LCDSPI_SCB_MODE_EZI2C_CONST_CFG     (LCDSPI_SCB_MODE_EZI2C     == LCDSPI_SCB_MODE)
#define LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG  (LCDSPI_SCB_MODE_UNCONFIG  == LCDSPI_SCB_MODE)

/* Condition compilation for includes */
#define LCDSPI_SCB_MODE_I2C_INC      (0u !=(LCDSPI_SCB_MODE_I2C   & LCDSPI_SCB_MODE))
#define LCDSPI_SCB_MODE_EZI2C_INC    (0u !=(LCDSPI_SCB_MODE_EZI2C & LCDSPI_SCB_MODE))
#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_SCB_MODE_SPI_INC  (0u !=(LCDSPI_SCB_MODE_SPI   & LCDSPI_SCB_MODE))
    #define LCDSPI_SCB_MODE_UART_INC (0u !=(LCDSPI_SCB_MODE_UART  & LCDSPI_SCB_MODE))
#else
    #define LCDSPI_SCB_MODE_SPI_INC  (0u)
    #define LCDSPI_SCB_MODE_UART_INC (0u)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

/* Interrupts remove options */
#define LCDSPI_REMOVE_SCB_IRQ             (1u)
#define LCDSPI_SCB_IRQ_INTERNAL           (0u == LCDSPI_REMOVE_SCB_IRQ)

#define LCDSPI_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define LCDSPI_UART_RX_WAKEUP_IRQ         (0u == LCDSPI_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define LCDSPI_SCB_INTR_MODE_NONE     (0u)
#define LCDSPI_SCB_INTR_MODE_INTERNAL (1u)
#define LCDSPI_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define LCDSPI_REMOVE_SCB_CLK     (0u)
#define LCDSPI_SCB_CLK_INTERNAL   (0u == LCDSPI_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "LCDSPI_PINS.h"

#if (LCDSPI_SCB_CLK_INTERNAL)
    #include "LCDSPI_SCBCLK.h"
#endif /* (LCDSPI_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} LCDSPI_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_general
* @{
*/

/* Start and Stop APIs */
void LCDSPI_Init(void);
void LCDSPI_Enable(void);
void LCDSPI_Start(void);
void LCDSPI_Stop(void);

/** @} general */

/**
* \addtogroup group_power
* @{
*/
/* Sleep and Wakeup APis */
void LCDSPI_Sleep(void);
void LCDSPI_Wakeup(void);
/** @} power */ 

/**
* \addtogroup group_interrupt
* @{
*/
#if (LCDSPI_SCB_IRQ_INTERNAL)
    /* Custom interrupt handler */
    void LCDSPI_SetCustomInterruptHandler(void (*func)(void));
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */
/** @} interrupt */

/* Interface to internal interrupt component */
#if (LCDSPI_SCB_IRQ_INTERNAL)
    /**
    * \addtogroup group_interrupt
    * @{
    */    
    /*******************************************************************************
    * Function Name: LCDSPI_EnableInt
    ****************************************************************************//**
    *
    *  When using an Internal interrupt, this enables the interrupt in the NVIC. 
    *  When using an external interrupt the API for the interrupt component must 
    *  be used to enable the interrupt.
    *
    *******************************************************************************/
    #define LCDSPI_EnableInt()    CyIntEnable(LCDSPI_ISR_NUMBER)
    
    
    /*******************************************************************************
    * Function Name: LCDSPI_DisableInt
    ****************************************************************************//**
    *
    *  When using an Internal interrupt, this disables the interrupt in the NVIC. 
    *  When using an external interrupt the API for the interrupt component must 
    *  be used to disable the interrupt.
    *
    *******************************************************************************/    
    #define LCDSPI_DisableInt()   CyIntDisable(LCDSPI_ISR_NUMBER)
    /** @} interrupt */

    /*******************************************************************************
    * Function Name: LCDSPI_ClearPendingInt
    ****************************************************************************//**
    *
    *  This function clears the interrupt pending status in the NVIC. 
    *
    *******************************************************************************/
    #define LCDSPI_ClearPendingInt()  CyIntClearPending(LCDSPI_ISR_NUMBER)
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */

#if (LCDSPI_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: LCDSPI_RxWakeEnableInt
    ****************************************************************************//**
    *
    *  This function enables the interrupt (RX_WAKE) pending status in the NVIC. 
    *
    *******************************************************************************/    
    #define LCDSPI_RxWakeEnableInt()  CyIntEnable(LCDSPI_RX_WAKE_ISR_NUMBER)
    

    /*******************************************************************************
    * Function Name: LCDSPI_RxWakeDisableInt
    ****************************************************************************//**
    *
    *  This function disables the interrupt (RX_WAKE) pending status in the NVIC.  
    *
    *******************************************************************************/
    #define LCDSPI_RxWakeDisableInt() CyIntDisable(LCDSPI_RX_WAKE_ISR_NUMBER)
    
    
    /*******************************************************************************
    * Function Name: LCDSPI_RxWakeClearPendingInt
    ****************************************************************************//**
    *
    *  This function clears the interrupt (RX_WAKE) pending status in the NVIC. 
    *
    *******************************************************************************/    
    #define LCDSPI_RxWakeClearPendingInt()  CyIntClearPending(LCDSPI_RX_WAKE_ISR_NUMBER)
#endif /* (LCDSPI_UART_RX_WAKEUP_IRQ) */

/**
* \addtogroup group_interrupt
* @{
*/
/* Get interrupt cause */
/*******************************************************************************
* Function Name: LCDSPI_GetInterruptCause
****************************************************************************//**
*
*  Returns a mask of bits showing the source of the current triggered interrupt. 
*  This is useful for modes of operation where an interrupt can be generated by 
*  conditions in multiple interrupt source registers.
*
*  \return
*   Mask with the OR of the following conditions that have been triggered.
*    - LCDSPI_INTR_CAUSE_MASTER - Interrupt from Master
*    - LCDSPI_INTR_CAUSE_SLAVE - Interrupt from Slave
*    - LCDSPI_INTR_CAUSE_TX - Interrupt from TX
*    - LCDSPI_INTR_CAUSE_RX - Interrupt from RX
*
*******************************************************************************/
#define LCDSPI_GetInterruptCause()    (LCDSPI_INTR_CAUSE_REG)


/* APIs to service INTR_RX register */
/*******************************************************************************
* Function Name: LCDSPI_GetRxInterruptSource
****************************************************************************//**
*
*  Returns RX interrupt request register. This register contains current status 
*  of RX interrupt sources.
*
*  \return
*   Current status of RX interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCDSPI_INTR_RX_FIFO_LEVEL - The number of data elements in the 
      RX FIFO is greater than the value of RX FIFO level.
*   - LCDSPI_INTR_RX_NOT_EMPTY - Receiver FIFO is not empty.
*   - LCDSPI_INTR_RX_FULL - Receiver FIFO is full.
*   - LCDSPI_INTR_RX_OVERFLOW - Attempt to write to a full 
*     receiver FIFO.
*   - LCDSPI_INTR_RX_UNDERFLOW - Attempt to read from an empty 
*     receiver FIFO.
*   - LCDSPI_INTR_RX_FRAME_ERROR - UART framing error detected.
*   - LCDSPI_INTR_RX_PARITY_ERROR - UART parity error detected.
*
*******************************************************************************/
#define LCDSPI_GetRxInterruptSource() (LCDSPI_INTR_RX_REG)


/*******************************************************************************
* Function Name: LCDSPI_SetRxInterruptMode
****************************************************************************//**
*
*  Writes RX interrupt mask register. This register configures which bits from 
*  RX interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: RX interrupt sources to be enabled (refer to 
*   LCDSPI_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define LCDSPI_SetRxInterruptMode(interruptMask)     LCDSPI_WRITE_INTR_RX_MASK(interruptMask)


/*******************************************************************************
* Function Name: LCDSPI_GetRxInterruptMode
****************************************************************************//**
*
*  Returns RX interrupt mask register This register specifies which bits from 
*  RX interrupt request register will trigger an interrupt event.
*
*  \return 
*   RX interrupt sources to be enabled (refer to 
*   LCDSPI_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define LCDSPI_GetRxInterruptMode()   (LCDSPI_INTR_RX_MASK_REG)


/*******************************************************************************
* Function Name: LCDSPI_GetRxInterruptSourceMasked
****************************************************************************//**
*
*  Returns RX interrupt masked request register. This register contains logical
*  AND of corresponding bits from RX interrupt request and mask registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled RX interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled RX interrupt sources (refer to 
*   LCDSPI_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define LCDSPI_GetRxInterruptSourceMasked()   (LCDSPI_INTR_RX_MASKED_REG)


/*******************************************************************************
* Function Name: LCDSPI_ClearRxInterruptSource
****************************************************************************//**
*
*  Clears RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to be cleared (refer to 
*   LCDSPI_GetRxInterruptSource() function for bit fields values).
*
*  \sideeffects 
*   The side effects are listed in the table below for each 
*   affected interrupt source. Refer to section RX FIFO interrupt sources for 
*   detailed description.
*   - LCDSPI_INTR_RX_FIFO_LEVEL Interrupt source is not cleared when 
*     the receiver FIFO has more entries than level.
*   - LCDSPI_INTR_RX_NOT_EMPTY Interrupt source is not cleared when
*     receiver FIFO is not empty.
*   - LCDSPI_INTR_RX_FULL Interrupt source is not cleared when 
*      receiver FIFO is full.
*
*******************************************************************************/
#define LCDSPI_ClearRxInterruptSource(interruptMask)  LCDSPI_CLEAR_INTR_RX(interruptMask)


/*******************************************************************************
* Function Name: LCDSPI_SetRxInterrupt
****************************************************************************//**
*
*  Sets RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to set in the RX interrupt request 
*   register (refer to LCDSPI_GetRxInterruptSource() function for bit 
*   fields values).
*
*******************************************************************************/
#define LCDSPI_SetRxInterrupt(interruptMask)  LCDSPI_SET_INTR_RX(interruptMask)

void LCDSPI_SetRxFifoLevel(uint32 level);


/* APIs to service INTR_TX register */
/*******************************************************************************
* Function Name: LCDSPI_GetTxInterruptSource
****************************************************************************//**
*
*  Returns TX interrupt request register. This register contains current status 
*  of TX interrupt sources.
* 
*  \return 
*   Current status of TX interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCDSPI_INTR_TX_FIFO_LEVEL - The number of data elements in the 
*     TX FIFO is less than the value of TX FIFO level.
*   - LCDSPI_INTR_TX_NOT_FULL - Transmitter FIFO is not full.
*   - LCDSPI_INTR_TX_EMPTY - Transmitter FIFO is empty.
*   - LCDSPI_INTR_TX_OVERFLOW - Attempt to write to a full 
*     transmitter FIFO.
*   - LCDSPI_INTR_TX_UNDERFLOW - Attempt to read from an empty 
*     transmitter FIFO.
*   - LCDSPI_INTR_TX_UART_NACK - UART received a NACK in SmartCard 
*   mode.
*   - LCDSPI_INTR_TX_UART_DONE - UART transfer is complete. 
*     All data elements from the TX FIFO are sent.
*   - LCDSPI_INTR_TX_UART_ARB_LOST - Value on the TX line of the UART
*     does not match the value on the RX line.
*
*******************************************************************************/
#define LCDSPI_GetTxInterruptSource() (LCDSPI_INTR_TX_REG)


/*******************************************************************************
* Function Name: LCDSPI_SetTxInterruptMode
****************************************************************************//**
*
*  Writes TX interrupt mask register. This register configures which bits from 
*  TX interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: TX interrupt sources to be enabled (refer to 
*   LCDSPI_GetTxInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCDSPI_SetTxInterruptMode(interruptMask)  LCDSPI_WRITE_INTR_TX_MASK(interruptMask)


/*******************************************************************************
* Function Name: LCDSPI_GetTxInterruptMode
****************************************************************************//**
*
*  Returns TX interrupt mask register This register specifies which bits from 
*  TX interrupt request register will trigger an interrupt event.
*
*  \return 
*   Enabled TX interrupt sources (refer to 
*   LCDSPI_GetTxInterruptSource() function for bit field values).
*   
*******************************************************************************/
#define LCDSPI_GetTxInterruptMode()   (LCDSPI_INTR_TX_MASK_REG)


/*******************************************************************************
* Function Name: LCDSPI_GetTxInterruptSourceMasked
****************************************************************************//**
*
*  Returns TX interrupt masked request register. This register contains logical
*  AND of corresponding bits from TX interrupt request and mask registers.
*  This function is intended to be used in the interrupt service routine to identify 
*  which of enabled TX interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled TX interrupt sources (refer to 
*   LCDSPI_GetTxInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCDSPI_GetTxInterruptSourceMasked()   (LCDSPI_INTR_TX_MASKED_REG)


/*******************************************************************************
* Function Name: LCDSPI_ClearTxInterruptSource
****************************************************************************//**
*
*  Clears TX interrupt sources in the interrupt request register.
*
*  \param interruptMask: TX interrupt sources to be cleared (refer to 
*   LCDSPI_GetTxInterruptSource() function for bit field values).
*
*  \sideeffects 
*   The side effects are listed in the table below for each affected interrupt 
*   source. Refer to section TX FIFO interrupt sources for detailed description.
*   - LCDSPI_INTR_TX_FIFO_LEVEL - Interrupt source is not cleared when 
*     transmitter FIFO has less entries than level.
*   - LCDSPI_INTR_TX_NOT_FULL - Interrupt source is not cleared when
*     transmitter FIFO has empty entries.
*   - LCDSPI_INTR_TX_EMPTY - Interrupt source is not cleared when 
*     transmitter FIFO is empty.
*   - LCDSPI_INTR_TX_UNDERFLOW - Interrupt source is not cleared when 
*     transmitter FIFO is empty and I2C mode with clock stretching is selected. 
*     Put data into the transmitter FIFO before clearing it. This behavior only 
*     applicable for PSoC 4100/PSoC 4200 devices.
*
*******************************************************************************/
#define LCDSPI_ClearTxInterruptSource(interruptMask)  LCDSPI_CLEAR_INTR_TX(interruptMask)


/*******************************************************************************
* Function Name: LCDSPI_SetTxInterrupt
****************************************************************************//**
*
*  Sets RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to set in the RX interrupt request 
*   register (refer to LCDSPI_GetRxInterruptSource() function for bit 
*   fields values).
*
*******************************************************************************/
#define LCDSPI_SetTxInterrupt(interruptMask)  LCDSPI_SET_INTR_TX(interruptMask)

void LCDSPI_SetTxFifoLevel(uint32 level);


/* APIs to service INTR_MASTER register */
/*******************************************************************************
* Function Name: LCDSPI_GetMasterInterruptSource
****************************************************************************//**
*
*  Returns Master interrupt request register. This register contains current 
*  status of Master interrupt sources.
*
*  \return 
*   Current status of Master interrupt sources. 
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCDSPI_INTR_MASTER_SPI_DONE - SPI master transfer is complete.
*     Refer to Interrupt sources section for detailed description.
*   - LCDSPI_INTR_MASTER_I2C_ARB_LOST - I2C master lost arbitration.
*   - LCDSPI_INTR_MASTER_I2C_NACK - I2C master received negative 
*    acknowledgement (NAK).
*   - LCDSPI_INTR_MASTER_I2C_ACK - I2C master received acknowledgement.
*   - LCDSPI_INTR_MASTER_I2C_STOP - I2C master generated STOP.
*   - LCDSPI_INTR_MASTER_I2C_BUS_ERROR - I2C master bus error 
*     (detection of unexpected START or STOP condition).
*
*******************************************************************************/
#define LCDSPI_GetMasterInterruptSource() (LCDSPI_INTR_MASTER_REG)

/*******************************************************************************
* Function Name: LCDSPI_SetMasterInterruptMode
****************************************************************************//**
*
*  Writes Master interrupt mask register. This register configures which bits 
*  from Master interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: Master interrupt sources to be enabled (refer to 
*   LCDSPI_GetMasterInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCDSPI_SetMasterInterruptMode(interruptMask)  LCDSPI_WRITE_INTR_MASTER_MASK(interruptMask)

/*******************************************************************************
* Function Name: LCDSPI_GetMasterInterruptMode
****************************************************************************//**
*
*  Returns Master interrupt mask register This register specifies which bits 
*  from Master interrupt request register will trigger an interrupt event.
*
*  \return 
*   Enabled Master interrupt sources (refer to 
*   LCDSPI_GetMasterInterruptSource() function for return values).
*
*******************************************************************************/
#define LCDSPI_GetMasterInterruptMode()   (LCDSPI_INTR_MASTER_MASK_REG)

/*******************************************************************************
* Function Name: LCDSPI_GetMasterInterruptSourceMasked
****************************************************************************//**
*
*  Returns Master interrupt masked request register. This register contains 
*  logical AND of corresponding bits from Master interrupt request and mask 
*  registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled Master interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled Master interrupt sources (refer to 
*   LCDSPI_GetMasterInterruptSource() function for return values).
*
*******************************************************************************/
#define LCDSPI_GetMasterInterruptSourceMasked()   (LCDSPI_INTR_MASTER_MASKED_REG)

/*******************************************************************************
* Function Name: LCDSPI_ClearMasterInterruptSource
****************************************************************************//**
*
*  Clears Master interrupt sources in the interrupt request register.
*
*  \param interruptMask: Master interrupt sources to be cleared (refer to 
*   LCDSPI_GetMasterInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCDSPI_ClearMasterInterruptSource(interruptMask)  LCDSPI_CLEAR_INTR_MASTER(interruptMask)

/*******************************************************************************
* Function Name: LCDSPI_SetMasterInterrupt
****************************************************************************//**
*
*  Sets Master interrupt sources in the interrupt request register.
*
*  \param interruptMask: Master interrupt sources to set in the Master interrupt
*   request register (refer to LCDSPI_GetMasterInterruptSource() 
*   function for bit field values).
*
*******************************************************************************/
#define LCDSPI_SetMasterInterrupt(interruptMask)  LCDSPI_SET_INTR_MASTER(interruptMask)


/* APIs to service INTR_SLAVE register */
/*******************************************************************************
* Function Name: LCDSPI_GetSlaveInterruptSource
****************************************************************************//**
*
*  Returns Slave interrupt request register. This register contains current 
*  status of Slave interrupt sources.
*
*  \return 
*   Current status of Slave interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCDSPI_INTR_SLAVE_I2C_ARB_LOST - I2C slave lost arbitration: 
*     the value driven on the SDA line is not the same as the value observed 
*     on the SDA line.
*   - LCDSPI_INTR_SLAVE_I2C_NACK - I2C slave received negative 
*     acknowledgement (NAK).
*   - LCDSPI_INTR_SLAVE_I2C_ACK - I2C slave received 
*     acknowledgement (ACK).
*   - LCDSPI_INTR_SLAVE_I2C_WRITE_STOP - Stop or Repeated Start 
*     event for write transfer intended for this slave (address matching 
*     is performed).
*   - LCDSPI_INTR_SLAVE_I2C_STOP - Stop or Repeated Start event 
*     for (read or write) transfer intended for this slave (address matching 
*     is performed).
*   - LCDSPI_INTR_SLAVE_I2C_START - I2C slave received Start 
*     condition.
*   - LCDSPI_INTR_SLAVE_I2C_ADDR_MATCH - I2C slave received matching 
*     address.
*   - LCDSPI_INTR_SLAVE_I2C_GENERAL - I2C Slave received general 
*     call address.
*   - LCDSPI_INTR_SLAVE_I2C_BUS_ERROR - I2C slave bus error (detection 
*      of unexpected Start or Stop condition).
*   - LCDSPI_INTR_SLAVE_SPI_BUS_ERROR - SPI slave select line is 
*      deselected at an expected time while the SPI transfer.
*
*******************************************************************************/
#define LCDSPI_GetSlaveInterruptSource()  (LCDSPI_INTR_SLAVE_REG)

/*******************************************************************************
* Function Name: LCDSPI_SetSlaveInterruptMode
****************************************************************************//**
*
*  Writes Slave interrupt mask register. 
*  This register configures which bits from Slave interrupt request register 
*  will trigger an interrupt event.
*
*  \param interruptMask: Slave interrupt sources to be enabled (refer to 
*   LCDSPI_GetSlaveInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCDSPI_SetSlaveInterruptMode(interruptMask)   LCDSPI_WRITE_INTR_SLAVE_MASK(interruptMask)

/*******************************************************************************
* Function Name: LCDSPI_GetSlaveInterruptMode
****************************************************************************//**
*
*  Returns Slave interrupt mask register.
*  This register specifies which bits from Slave interrupt request register 
*  will trigger an interrupt event.
*
*  \return 
*   Enabled Slave interrupt sources(refer to 
*   LCDSPI_GetSlaveInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCDSPI_GetSlaveInterruptMode()    (LCDSPI_INTR_SLAVE_MASK_REG)

/*******************************************************************************
* Function Name: LCDSPI_GetSlaveInterruptSourceMasked
****************************************************************************//**
*
*  Returns Slave interrupt masked request register. This register contains 
*  logical AND of corresponding bits from Slave interrupt request and mask 
*  registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled Slave interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled Slave interrupt sources (refer to 
*   LCDSPI_GetSlaveInterruptSource() function for return values).
*
*******************************************************************************/
#define LCDSPI_GetSlaveInterruptSourceMasked()    (LCDSPI_INTR_SLAVE_MASKED_REG)

/*******************************************************************************
* Function Name: LCDSPI_ClearSlaveInterruptSource
****************************************************************************//**
*
*  Clears Slave interrupt sources in the interrupt request register.
*
*  \param interruptMask: Slave interrupt sources to be cleared (refer to 
*   LCDSPI_GetSlaveInterruptSource() function for return values).
*
*******************************************************************************/
#define LCDSPI_ClearSlaveInterruptSource(interruptMask)   LCDSPI_CLEAR_INTR_SLAVE(interruptMask)

/*******************************************************************************
* Function Name: LCDSPI_SetSlaveInterrupt
****************************************************************************//**
*
*  Sets Slave interrupt sources in the interrupt request register.
*
*  \param interruptMask: Slave interrupt sources to set in the Slave interrupt 
*   request register (refer to LCDSPI_GetSlaveInterruptSource() 
*   function for return values).
*
*******************************************************************************/
#define LCDSPI_SetSlaveInterrupt(interruptMask)   LCDSPI_SET_INTR_SLAVE(interruptMask)

/** @} interrupt */ 


/***************************************
*     Vars with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/

/** LCDSPI_initVar indicates whether the LCDSPI 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the LCDSPI_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  LCDSPI_Init() function can be called before the 
*  LCDSPI_Start() or LCDSPI_Enable() function.
*/
extern uint8 LCDSPI_initVar;
/** @} globals */

/***************************************
*              Registers
***************************************/

#define LCDSPI_CTRL_REG               (*(reg32 *) LCDSPI_SCB__CTRL)
#define LCDSPI_CTRL_PTR               ( (reg32 *) LCDSPI_SCB__CTRL)

#define LCDSPI_STATUS_REG             (*(reg32 *) LCDSPI_SCB__STATUS)
#define LCDSPI_STATUS_PTR             ( (reg32 *) LCDSPI_SCB__STATUS)

#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_SPI_CTRL_REG           (*(reg32 *) LCDSPI_SCB__SPI_CTRL)
    #define LCDSPI_SPI_CTRL_PTR           ( (reg32 *) LCDSPI_SCB__SPI_CTRL)

    #define LCDSPI_SPI_STATUS_REG         (*(reg32 *) LCDSPI_SCB__SPI_STATUS)
    #define LCDSPI_SPI_STATUS_PTR         ( (reg32 *) LCDSPI_SCB__SPI_STATUS)

    #define LCDSPI_UART_CTRL_REG          (*(reg32 *) LCDSPI_SCB__UART_CTRL)
    #define LCDSPI_UART_CTRL_PTR          ( (reg32 *) LCDSPI_SCB__UART_CTRL)

    #define LCDSPI_UART_TX_CTRL_REG       (*(reg32 *) LCDSPI_SCB__UART_TX_CTRL)
    #define LCDSPI_UART_TX_CTRL_PTR       ( (reg32 *) LCDSPI_SCB__UART_TX_CTRL)

    #define LCDSPI_UART_RX_CTRL_REG       (*(reg32 *) LCDSPI_SCB__UART_RX_CTRL)
    #define LCDSPI_UART_RX_CTRL_PTR       ( (reg32 *) LCDSPI_SCB__UART_RX_CTRL)

    #define LCDSPI_UART_RX_STATUS_REG     (*(reg32 *) LCDSPI_SCB__UART_RX_STATUS)
    #define LCDSPI_UART_RX_STATUS_PTR     ( (reg32 *) LCDSPI_SCB__UART_RX_STATUS)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_UART_FLOW_CTRL_REG     (*(reg32 *) LCDSPI_SCB__UART_FLOW_CTRL)
    #define LCDSPI_UART_FLOW_CTRL_PTR     ( (reg32 *) LCDSPI_SCB__UART_FLOW_CTRL)
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_I2C_CTRL_REG           (*(reg32 *) LCDSPI_SCB__I2C_CTRL)
#define LCDSPI_I2C_CTRL_PTR           ( (reg32 *) LCDSPI_SCB__I2C_CTRL)

#define LCDSPI_I2C_STATUS_REG         (*(reg32 *) LCDSPI_SCB__I2C_STATUS)
#define LCDSPI_I2C_STATUS_PTR         ( (reg32 *) LCDSPI_SCB__I2C_STATUS)

#define LCDSPI_I2C_MASTER_CMD_REG     (*(reg32 *) LCDSPI_SCB__I2C_M_CMD)
#define LCDSPI_I2C_MASTER_CMD_PTR     ( (reg32 *) LCDSPI_SCB__I2C_M_CMD)

#define LCDSPI_I2C_SLAVE_CMD_REG      (*(reg32 *) LCDSPI_SCB__I2C_S_CMD)
#define LCDSPI_I2C_SLAVE_CMD_PTR      ( (reg32 *) LCDSPI_SCB__I2C_S_CMD)

#define LCDSPI_I2C_CFG_REG            (*(reg32 *) LCDSPI_SCB__I2C_CFG)
#define LCDSPI_I2C_CFG_PTR            ( (reg32 *) LCDSPI_SCB__I2C_CFG)

#define LCDSPI_TX_CTRL_REG            (*(reg32 *) LCDSPI_SCB__TX_CTRL)
#define LCDSPI_TX_CTRL_PTR            ( (reg32 *) LCDSPI_SCB__TX_CTRL)

#define LCDSPI_TX_FIFO_CTRL_REG       (*(reg32 *) LCDSPI_SCB__TX_FIFO_CTRL)
#define LCDSPI_TX_FIFO_CTRL_PTR       ( (reg32 *) LCDSPI_SCB__TX_FIFO_CTRL)

#define LCDSPI_TX_FIFO_STATUS_REG     (*(reg32 *) LCDSPI_SCB__TX_FIFO_STATUS)
#define LCDSPI_TX_FIFO_STATUS_PTR     ( (reg32 *) LCDSPI_SCB__TX_FIFO_STATUS)

#define LCDSPI_TX_FIFO_WR_REG         (*(reg32 *) LCDSPI_SCB__TX_FIFO_WR)
#define LCDSPI_TX_FIFO_WR_PTR         ( (reg32 *) LCDSPI_SCB__TX_FIFO_WR)

#define LCDSPI_RX_CTRL_REG            (*(reg32 *) LCDSPI_SCB__RX_CTRL)
#define LCDSPI_RX_CTRL_PTR            ( (reg32 *) LCDSPI_SCB__RX_CTRL)

#define LCDSPI_RX_FIFO_CTRL_REG       (*(reg32 *) LCDSPI_SCB__RX_FIFO_CTRL)
#define LCDSPI_RX_FIFO_CTRL_PTR       ( (reg32 *) LCDSPI_SCB__RX_FIFO_CTRL)

#define LCDSPI_RX_FIFO_STATUS_REG     (*(reg32 *) LCDSPI_SCB__RX_FIFO_STATUS)
#define LCDSPI_RX_FIFO_STATUS_PTR     ( (reg32 *) LCDSPI_SCB__RX_FIFO_STATUS)

#define LCDSPI_RX_MATCH_REG           (*(reg32 *) LCDSPI_SCB__RX_MATCH)
#define LCDSPI_RX_MATCH_PTR           ( (reg32 *) LCDSPI_SCB__RX_MATCH)

#define LCDSPI_RX_FIFO_RD_REG         (*(reg32 *) LCDSPI_SCB__RX_FIFO_RD)
#define LCDSPI_RX_FIFO_RD_PTR         ( (reg32 *) LCDSPI_SCB__RX_FIFO_RD)

#define LCDSPI_RX_FIFO_RD_SILENT_REG  (*(reg32 *) LCDSPI_SCB__RX_FIFO_RD_SILENT)
#define LCDSPI_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) LCDSPI_SCB__RX_FIFO_RD_SILENT)

#ifdef LCDSPI_SCB__EZ_DATA0
    #define LCDSPI_EZBUF_DATA0_REG    (*(reg32 *) LCDSPI_SCB__EZ_DATA0)
    #define LCDSPI_EZBUF_DATA0_PTR    ( (reg32 *) LCDSPI_SCB__EZ_DATA0)
#else
    #define LCDSPI_EZBUF_DATA0_REG    (*(reg32 *) LCDSPI_SCB__EZ_DATA00)
    #define LCDSPI_EZBUF_DATA0_PTR    ( (reg32 *) LCDSPI_SCB__EZ_DATA00)
#endif /* LCDSPI_SCB__EZ_DATA00 */

#define LCDSPI_INTR_CAUSE_REG         (*(reg32 *) LCDSPI_SCB__INTR_CAUSE)
#define LCDSPI_INTR_CAUSE_PTR         ( (reg32 *) LCDSPI_SCB__INTR_CAUSE)

#define LCDSPI_INTR_I2C_EC_REG        (*(reg32 *) LCDSPI_SCB__INTR_I2C_EC)
#define LCDSPI_INTR_I2C_EC_PTR        ( (reg32 *) LCDSPI_SCB__INTR_I2C_EC)

#define LCDSPI_INTR_I2C_EC_MASK_REG   (*(reg32 *) LCDSPI_SCB__INTR_I2C_EC_MASK)
#define LCDSPI_INTR_I2C_EC_MASK_PTR   ( (reg32 *) LCDSPI_SCB__INTR_I2C_EC_MASK)

#define LCDSPI_INTR_I2C_EC_MASKED_REG (*(reg32 *) LCDSPI_SCB__INTR_I2C_EC_MASKED)
#define LCDSPI_INTR_I2C_EC_MASKED_PTR ( (reg32 *) LCDSPI_SCB__INTR_I2C_EC_MASKED)

#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_INTR_SPI_EC_REG        (*(reg32 *) LCDSPI_SCB__INTR_SPI_EC)
    #define LCDSPI_INTR_SPI_EC_PTR        ( (reg32 *) LCDSPI_SCB__INTR_SPI_EC)

    #define LCDSPI_INTR_SPI_EC_MASK_REG   (*(reg32 *) LCDSPI_SCB__INTR_SPI_EC_MASK)
    #define LCDSPI_INTR_SPI_EC_MASK_PTR   ( (reg32 *) LCDSPI_SCB__INTR_SPI_EC_MASK)

    #define LCDSPI_INTR_SPI_EC_MASKED_REG (*(reg32 *) LCDSPI_SCB__INTR_SPI_EC_MASKED)
    #define LCDSPI_INTR_SPI_EC_MASKED_PTR ( (reg32 *) LCDSPI_SCB__INTR_SPI_EC_MASKED)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_INTR_MASTER_REG        (*(reg32 *) LCDSPI_SCB__INTR_M)
#define LCDSPI_INTR_MASTER_PTR        ( (reg32 *) LCDSPI_SCB__INTR_M)

#define LCDSPI_INTR_MASTER_SET_REG    (*(reg32 *) LCDSPI_SCB__INTR_M_SET)
#define LCDSPI_INTR_MASTER_SET_PTR    ( (reg32 *) LCDSPI_SCB__INTR_M_SET)

#define LCDSPI_INTR_MASTER_MASK_REG   (*(reg32 *) LCDSPI_SCB__INTR_M_MASK)
#define LCDSPI_INTR_MASTER_MASK_PTR   ( (reg32 *) LCDSPI_SCB__INTR_M_MASK)

#define LCDSPI_INTR_MASTER_MASKED_REG (*(reg32 *) LCDSPI_SCB__INTR_M_MASKED)
#define LCDSPI_INTR_MASTER_MASKED_PTR ( (reg32 *) LCDSPI_SCB__INTR_M_MASKED)

#define LCDSPI_INTR_SLAVE_REG         (*(reg32 *) LCDSPI_SCB__INTR_S)
#define LCDSPI_INTR_SLAVE_PTR         ( (reg32 *) LCDSPI_SCB__INTR_S)

#define LCDSPI_INTR_SLAVE_SET_REG     (*(reg32 *) LCDSPI_SCB__INTR_S_SET)
#define LCDSPI_INTR_SLAVE_SET_PTR     ( (reg32 *) LCDSPI_SCB__INTR_S_SET)

#define LCDSPI_INTR_SLAVE_MASK_REG    (*(reg32 *) LCDSPI_SCB__INTR_S_MASK)
#define LCDSPI_INTR_SLAVE_MASK_PTR    ( (reg32 *) LCDSPI_SCB__INTR_S_MASK)

#define LCDSPI_INTR_SLAVE_MASKED_REG  (*(reg32 *) LCDSPI_SCB__INTR_S_MASKED)
#define LCDSPI_INTR_SLAVE_MASKED_PTR  ( (reg32 *) LCDSPI_SCB__INTR_S_MASKED)

#define LCDSPI_INTR_TX_REG            (*(reg32 *) LCDSPI_SCB__INTR_TX)
#define LCDSPI_INTR_TX_PTR            ( (reg32 *) LCDSPI_SCB__INTR_TX)

#define LCDSPI_INTR_TX_SET_REG        (*(reg32 *) LCDSPI_SCB__INTR_TX_SET)
#define LCDSPI_INTR_TX_SET_PTR        ( (reg32 *) LCDSPI_SCB__INTR_TX_SET)

#define LCDSPI_INTR_TX_MASK_REG       (*(reg32 *) LCDSPI_SCB__INTR_TX_MASK)
#define LCDSPI_INTR_TX_MASK_PTR       ( (reg32 *) LCDSPI_SCB__INTR_TX_MASK)

#define LCDSPI_INTR_TX_MASKED_REG     (*(reg32 *) LCDSPI_SCB__INTR_TX_MASKED)
#define LCDSPI_INTR_TX_MASKED_PTR     ( (reg32 *) LCDSPI_SCB__INTR_TX_MASKED)

#define LCDSPI_INTR_RX_REG            (*(reg32 *) LCDSPI_SCB__INTR_RX)
#define LCDSPI_INTR_RX_PTR            ( (reg32 *) LCDSPI_SCB__INTR_RX)

#define LCDSPI_INTR_RX_SET_REG        (*(reg32 *) LCDSPI_SCB__INTR_RX_SET)
#define LCDSPI_INTR_RX_SET_PTR        ( (reg32 *) LCDSPI_SCB__INTR_RX_SET)

#define LCDSPI_INTR_RX_MASK_REG       (*(reg32 *) LCDSPI_SCB__INTR_RX_MASK)
#define LCDSPI_INTR_RX_MASK_PTR       ( (reg32 *) LCDSPI_SCB__INTR_RX_MASK)

#define LCDSPI_INTR_RX_MASKED_REG     (*(reg32 *) LCDSPI_SCB__INTR_RX_MASKED)
#define LCDSPI_INTR_RX_MASKED_PTR     ( (reg32 *) LCDSPI_SCB__INTR_RX_MASKED)

/* Defines get from SCB IP parameters. */
#define LCDSPI_FIFO_SIZE      (8u)  /* TX or RX FIFO size. */
#define LCDSPI_EZ_DATA_NR     (32u)  /* Number of words in EZ memory. */ 
#define LCDSPI_ONE_BYTE_WIDTH (8u)            /* Number of bits in one byte. */
#define LCDSPI_FF_DATA_NR_LOG2_MASK       (0x0Fu)      /* Number of bits to represent a FIFO address. */
#define LCDSPI_FF_DATA_NR_LOG2_PLUS1_MASK (0x1Fu) /* Number of bits to represent #bytes in FIFO. */


/***************************************
*        Registers Constants
***************************************/

#if (LCDSPI_SCB_IRQ_INTERNAL)
    #define LCDSPI_ISR_NUMBER     ((uint8) LCDSPI_SCB_IRQ__INTC_NUMBER)
    #define LCDSPI_ISR_PRIORITY   ((uint8) LCDSPI_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */

#if (LCDSPI_UART_RX_WAKEUP_IRQ)
    #define LCDSPI_RX_WAKE_ISR_NUMBER     ((uint8) LCDSPI_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define LCDSPI_RX_WAKE_ISR_PRIORITY   ((uint8) LCDSPI_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (LCDSPI_UART_RX_WAKEUP_IRQ) */

/* LCDSPI_CTRL_REG */
#define LCDSPI_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define LCDSPI_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define LCDSPI_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define LCDSPI_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */
#define LCDSPI_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define LCDSPI_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define LCDSPI_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define LCDSPI_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define LCDSPI_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define LCDSPI_CTRL_EC_AM_MODE        ((uint32) 0x01u << LCDSPI_CTRL_EC_AM_MODE_POS)
#define LCDSPI_CTRL_EC_OP_MODE        ((uint32) 0x01u << LCDSPI_CTRL_EC_OP_MODE_POS)
#define LCDSPI_CTRL_EZBUF_MODE        ((uint32) 0x01u << LCDSPI_CTRL_EZBUF_MODE_POS)
#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_CTRL_BYTE_MODE ((uint32) 0x01u << LCDSPI_CTRL_BYTE_MODE_POS)
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */
#define LCDSPI_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << LCDSPI_CTRL_ADDR_ACCEPT_POS)
#define LCDSPI_CTRL_BLOCK             ((uint32) 0x01u << LCDSPI_CTRL_BLOCK_POS)
#define LCDSPI_CTRL_MODE_MASK         ((uint32) 0x03u << LCDSPI_CTRL_MODE_POS)
#define LCDSPI_CTRL_MODE_I2C          ((uint32) 0x00u)
#define LCDSPI_CTRL_MODE_SPI          ((uint32) 0x01u << LCDSPI_CTRL_MODE_POS)
#define LCDSPI_CTRL_MODE_UART         ((uint32) 0x02u << LCDSPI_CTRL_MODE_POS)
#define LCDSPI_CTRL_ENABLED           ((uint32) 0x01u << LCDSPI_CTRL_ENABLED_POS)

/* LCDSPI_STATUS_REG */
#define LCDSPI_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define LCDSPI_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* LCDSPI_SPI_CTRL_REG  */
#define LCDSPI_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define LCDSPI_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define LCDSPI_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define LCDSPI_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define LCDSPI_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define LCDSPI_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define LCDSPI_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define LCDSPI_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define LCDSPI_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */
#define LCDSPI_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define LCDSPI_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define LCDSPI_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define LCDSPI_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define LCDSPI_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define LCDSPI_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << LCDSPI_SPI_CTRL_SELECT_PRECEDE_POS)
#define LCDSPI_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << LCDSPI_SPI_CTRL_CPHA_POS)
#define LCDSPI_SPI_CTRL_CPHA                  ((uint32) 0x01u << LCDSPI_SPI_CTRL_CPHA_POS)
#define LCDSPI_SPI_CTRL_CPOL                  ((uint32) 0x01u << LCDSPI_SPI_CTRL_CPOL_POS)
#define LCDSPI_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    LCDSPI_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << LCDSPI_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define LCDSPI_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << LCDSPI_SPI_CTRL_SSEL0_POLARITY_POS)
    #define LCDSPI_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << LCDSPI_SPI_CTRL_SSEL1_POLARITY_POS)
    #define LCDSPI_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << LCDSPI_SPI_CTRL_SSEL2_POLARITY_POS)
    #define LCDSPI_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << LCDSPI_SPI_CTRL_SSEL3_POLARITY_POS)
    #define LCDSPI_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << LCDSPI_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << LCDSPI_SPI_CTRL_LOOPBACK_POS)
#define LCDSPI_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << LCDSPI_SPI_CTRL_MODE_POS)
#define LCDSPI_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define LCDSPI_SPI_CTRL_MODE_TI               ((uint32) 0x01u << LCDSPI_CTRL_MODE_POS)
#define LCDSPI_SPI_CTRL_MODE_NS               ((uint32) 0x02u << LCDSPI_CTRL_MODE_POS)
#define LCDSPI_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << LCDSPI_SPI_CTRL_SLAVE_SELECT_POS)
#define LCDSPI_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define LCDSPI_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << LCDSPI_SPI_CTRL_SLAVE_SELECT_POS)
#define LCDSPI_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << LCDSPI_SPI_CTRL_SLAVE_SELECT_POS)
#define LCDSPI_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << LCDSPI_SPI_CTRL_SLAVE_SELECT_POS)
#define LCDSPI_SPI_CTRL_MASTER                ((uint32) 0x01u << LCDSPI_SPI_CTRL_MASTER_MODE_POS)
#define LCDSPI_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* LCDSPI_SPI_STATUS_REG  */
#define LCDSPI_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define LCDSPI_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define LCDSPI_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define LCDSPI_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << LCDSPI_I2C_STATUS_EZBUF_ADDR_POS)

/* LCDSPI_UART_CTRL */
#define LCDSPI_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define LCDSPI_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define LCDSPI_UART_CTRL_LOOPBACK             ((uint32) 0x01u << LCDSPI_UART_CTRL_LOOPBACK_POS)
#define LCDSPI_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define LCDSPI_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << LCDSPI_UART_CTRL_MODE_POS)
#define LCDSPI_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << LCDSPI_UART_CTRL_MODE_POS)
#define LCDSPI_UART_CTRL_MODE_MASK            ((uint32) 0x03u << LCDSPI_UART_CTRL_MODE_POS)

/* LCDSPI_UART_TX_CTRL */
#define LCDSPI_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define LCDSPI_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define LCDSPI_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define LCDSPI_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define LCDSPI_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define LCDSPI_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define LCDSPI_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define LCDSPI_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define LCDSPI_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    LCDSPI_UART_TX_CTRL_PARITY_POS)
#define LCDSPI_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    LCDSPI_UART_TX_CTRL_PARITY_ENABLED_POS)
#define LCDSPI_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    LCDSPI_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* LCDSPI_UART_RX_CTRL */
#define LCDSPI_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define LCDSPI_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define LCDSPI_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define LCDSPI_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define LCDSPI_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define LCDSPI_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define LCDSPI_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define LCDSPI_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define LCDSPI_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define LCDSPI_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define LCDSPI_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define LCDSPI_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define LCDSPI_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define LCDSPI_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define LCDSPI_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    LCDSPI_UART_RX_CTRL_PARITY_POS)
#define LCDSPI_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    LCDSPI_UART_RX_CTRL_PARITY_ENABLED_POS)
#define LCDSPI_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    LCDSPI_UART_RX_CTRL_POLARITY_POS)
#define LCDSPI_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   LCDSPI_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define LCDSPI_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    LCDSPI_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define LCDSPI_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    LCDSPI_UART_RX_CTRL_MP_MODE_POS)
#define LCDSPI_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    LCDSPI_UART_RX_CTRL_LIN_MODE_POS)
#define LCDSPI_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    LCDSPI_UART_RX_CTRL_SKIP_START_POS)
#define LCDSPI_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    LCDSPI_UART_RX_CTRL_BREAK_WIDTH_POS)
/* LCDSPI_UART_RX_STATUS_REG */
#define LCDSPI_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define LCDSPI_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    /* LCDSPI_UART_FLOW_CTRL_REG */
    #define LCDSPI_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define LCDSPI_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define LCDSPI_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define LCDSPI_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define LCDSPI_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) LCDSPI_FF_DATA_NR_LOG2_MASK)
    #define LCDSPI_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       LCDSPI_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define LCDSPI_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       LCDSPI_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define LCDSPI_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       LCDSPI_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

/* LCDSPI_I2C_CTRL */
#define LCDSPI_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define LCDSPI_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define LCDSPI_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define LCDSPI_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define LCDSPI_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define LCDSPI_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define LCDSPI_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define LCDSPI_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define LCDSPI_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define LCDSPI_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define LCDSPI_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define LCDSPI_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define LCDSPI_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                LCDSPI_I2C_CTRL_LOW_PHASE_OVS_POS)
#define LCDSPI_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_M_READY_DATA_ACK_POS)
#define LCDSPI_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define LCDSPI_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define LCDSPI_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define LCDSPI_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_S_READY_DATA_ACK_POS)
#define LCDSPI_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define LCDSPI_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_LOOPBACK_POS)
#define LCDSPI_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_SLAVE_MODE_POS)
#define LCDSPI_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CTRL_MASTER_MODE_POS)
#define LCDSPI_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                LCDSPI_I2C_CTRL_SLAVE_MODE_POS)

/* LCDSPI_I2C_STATUS_REG  */
#define LCDSPI_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define LCDSPI_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define LCDSPI_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define LCDSPI_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define LCDSPI_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define LCDSPI_I2C_STATUS_S_READ          ((uint32) 0x01u << LCDSPI_I2C_STATUS_S_READ_POS)
#define LCDSPI_I2C_STATUS_M_READ          ((uint32) 0x01u << LCDSPI_I2C_STATUS_M_READ_POS)
#define LCDSPI_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << LCDSPI_I2C_STATUS_EZBUF_ADDR_POS)

/* LCDSPI_I2C_MASTER_CMD_REG */
#define LCDSPI_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define LCDSPI_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define LCDSPI_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define LCDSPI_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define LCDSPI_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define LCDSPI_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define LCDSPI_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   LCDSPI_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define LCDSPI_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   LCDSPI_I2C_MASTER_CMD_M_ACK_POS)
#define LCDSPI_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    LCDSPI_I2C_MASTER_CMD_M_NACK_POS)
#define LCDSPI_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    LCDSPI_I2C_MASTER_CMD_M_STOP_POS)

/* LCDSPI_I2C_SLAVE_CMD_REG  */
#define LCDSPI_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define LCDSPI_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define LCDSPI_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define LCDSPI_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << LCDSPI_I2C_SLAVE_CMD_S_NACK_POS)

#define LCDSPI_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define LCDSPI_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define LCDSPI_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define LCDSPI_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << LCDSPI_I2C_SLAVE_CMD_S_NACK_POS)

/* LCDSPI_I2C_CFG_REG */
#if (LCDSPI_CY_SCBIP_V0)
#define LCDSPI_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define LCDSPI_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define LCDSPI_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define LCDSPI_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define LCDSPI_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define LCDSPI_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define LCDSPI_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define LCDSPI_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define LCDSPI_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define LCDSPI_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                LCDSPI_I2C_CFG_SDA_FILT_TRIM_POS)
#define LCDSPI_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                LCDSPI_I2C_CFG_SCL_FILT_HYS_POS)
#define LCDSPI_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                LCDSPI_I2C_CFG_SCL_FILT_TRIM_POS)
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                LCDSPI_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                LCDSPI_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define LCDSPI_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CFG_SDA_FILT_HS_POS)
#define LCDSPI_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CFG_SDA_FILT_ENABLED_POS)
#define LCDSPI_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CFG_SCL_FILT_HS_POS)
#define LCDSPI_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CFG_SCL_FILT_ENABLED_POS)
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define LCDSPI_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                LCDSPI_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define LCDSPI_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define LCDSPI_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define LCDSPI_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define LCDSPI_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define LCDSPI_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define LCDSPI_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define LCDSPI_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define LCDSPI_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define LCDSPI_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define LCDSPI_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << LCDSPI_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define LCDSPI_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            LCDSPI_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define LCDSPI_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << LCDSPI_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define LCDSPI_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            LCDSPI_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define LCDSPI_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            LCDSPI_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define LCDSPI_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            LCDSPI_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define LCDSPI_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            LCDSPI_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (LCDSPI_CY_SCBIP_V0) */


/* LCDSPI_TX_CTRL_REG */
#define LCDSPI_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define LCDSPI_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define LCDSPI_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define LCDSPI_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define LCDSPI_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << LCDSPI_TX_CTRL_MSB_FIRST_POS)
#define LCDSPI_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define LCDSPI_TX_CTRL_ENABLED            ((uint32) 0x01u << LCDSPI_TX_CTRL_ENABLED_POS)

/* LCDSPI_TX_CTRL_FIFO_REG */
#define LCDSPI_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define LCDSPI_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define LCDSPI_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define LCDSPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) LCDSPI_FF_DATA_NR_LOG2_MASK)
#define LCDSPI_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << LCDSPI_TX_FIFO_CTRL_CLEAR_POS)
#define LCDSPI_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << LCDSPI_TX_FIFO_CTRL_FREEZE_POS)

/* LCDSPI_TX_FIFO_STATUS_REG */
#define LCDSPI_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define LCDSPI_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define LCDSPI_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define LCDSPI_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define LCDSPI_TX_FIFO_STATUS_USED_MASK   ((uint32) LCDSPI_FF_DATA_NR_LOG2_PLUS1_MASK)
#define LCDSPI_TX_FIFO_SR_VALID           ((uint32) 0x01u << LCDSPI_TX_FIFO_SR_VALID_POS)
#define LCDSPI_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) LCDSPI_FF_DATA_NR_LOG2_MASK << \
                                                                    LCDSPI_TX_FIFO_STATUS_RD_PTR_POS)
#define LCDSPI_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) LCDSPI_FF_DATA_NR_LOG2_MASK << \
                                                                    LCDSPI_TX_FIFO_STATUS_WR_PTR_POS)

/* LCDSPI_TX_FIFO_WR_REG */
#define LCDSPI_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define LCDSPI_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* LCDSPI_RX_CTRL_REG */
#define LCDSPI_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define LCDSPI_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define LCDSPI_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define LCDSPI_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define LCDSPI_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define LCDSPI_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << LCDSPI_RX_CTRL_MSB_FIRST_POS)
#define LCDSPI_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define LCDSPI_RX_CTRL_MEDIAN             ((uint32) 0x01u << LCDSPI_RX_CTRL_MEDIAN_POS)
#define LCDSPI_RX_CTRL_ENABLED            ((uint32) 0x01u << LCDSPI_RX_CTRL_ENABLED_POS)


/* LCDSPI_RX_FIFO_CTRL_REG */
#define LCDSPI_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define LCDSPI_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define LCDSPI_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define LCDSPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) LCDSPI_FF_DATA_NR_LOG2_MASK)
#define LCDSPI_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << LCDSPI_RX_FIFO_CTRL_CLEAR_POS)
#define LCDSPI_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << LCDSPI_RX_FIFO_CTRL_FREEZE_POS)

/* LCDSPI_RX_FIFO_STATUS_REG */
#define LCDSPI_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define LCDSPI_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define LCDSPI_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define LCDSPI_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define LCDSPI_RX_FIFO_STATUS_USED_MASK   ((uint32) LCDSPI_FF_DATA_NR_LOG2_PLUS1_MASK)
#define LCDSPI_RX_FIFO_SR_VALID           ((uint32) 0x01u << LCDSPI_RX_FIFO_SR_VALID_POS)
#define LCDSPI_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) LCDSPI_FF_DATA_NR_LOG2_MASK << \
                                                                    LCDSPI_RX_FIFO_STATUS_RD_PTR_POS)
#define LCDSPI_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) LCDSPI_FF_DATA_NR_LOG2_MASK << \
                                                                    LCDSPI_RX_FIFO_STATUS_WR_PTR_POS)

/* LCDSPI_RX_MATCH_REG */
#define LCDSPI_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define LCDSPI_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define LCDSPI_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define LCDSPI_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << LCDSPI_RX_MATCH_MASK_POS)

/* LCDSPI_RX_FIFO_WR_REG */
#define LCDSPI_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define LCDSPI_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* LCDSPI_RX_FIFO_RD_SILENT_REG */
#define LCDSPI_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define LCDSPI_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* LCDSPI_RX_FIFO_RD_SILENT_REG */
#define LCDSPI_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define LCDSPI_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* LCDSPI_EZBUF_DATA_REG */
#define LCDSPI_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define LCDSPI_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  LCDSPI_INTR_CAUSE_REG */
#define LCDSPI_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define LCDSPI_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define LCDSPI_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define LCDSPI_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define LCDSPI_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define LCDSPI_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define LCDSPI_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define LCDSPI_INTR_CAUSE_SLAVE       ((uint32) 0x01u << LCDSPI_INTR_CAUSE_SLAVE_POS)
#define LCDSPI_INTR_CAUSE_TX          ((uint32) 0x01u << LCDSPI_INTR_CAUSE_TX_POS)
#define LCDSPI_INTR_CAUSE_RX          ((uint32) 0x01u << LCDSPI_INTR_CAUSE_RX_POS)
#define LCDSPI_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << LCDSPI_INTR_CAUSE_I2C_EC_POS)
#define LCDSPI_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << LCDSPI_INTR_CAUSE_SPI_EC_POS)

/* LCDSPI_INTR_SPI_EC_REG, LCDSPI_INTR_SPI_EC_MASK_REG, LCDSPI_INTR_SPI_EC_MASKED_REG */
#define LCDSPI_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define LCDSPI_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define LCDSPI_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define LCDSPI_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define LCDSPI_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SPI_EC_EZBUF_STOP_POS)
#define LCDSPI_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* LCDSPI_INTR_I2C_EC, LCDSPI_INTR_I2C_EC_MASK, LCDSPI_INTR_I2C_EC_MASKED */
#define LCDSPI_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define LCDSPI_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define LCDSPI_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define LCDSPI_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define LCDSPI_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_I2C_EC_EZBUF_STOP_POS)
#define LCDSPI_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* LCDSPI_INTR_MASTER, LCDSPI_INTR_MASTER_SET,
   LCDSPI_INTR_MASTER_MASK, LCDSPI_INTR_MASTER_MASKED */
#define LCDSPI_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define LCDSPI_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define LCDSPI_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define LCDSPI_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define LCDSPI_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define LCDSPI_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define LCDSPI_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define LCDSPI_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << LCDSPI_INTR_MASTER_I2C_NACK_POS)
#define LCDSPI_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << LCDSPI_INTR_MASTER_I2C_ACK_POS)
#define LCDSPI_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << LCDSPI_INTR_MASTER_I2C_STOP_POS)
#define LCDSPI_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_MASTER_I2C_BUS_ERROR_POS)
#define LCDSPI_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << LCDSPI_INTR_MASTER_SPI_DONE_POS)

/*
* LCDSPI_INTR_SLAVE, LCDSPI_INTR_SLAVE_SET,
* LCDSPI_INTR_SLAVE_MASK, LCDSPI_INTR_SLAVE_MASKED
*/
#define LCDSPI_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define LCDSPI_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define LCDSPI_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define LCDSPI_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define LCDSPI_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define LCDSPI_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define LCDSPI_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define LCDSPI_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define LCDSPI_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define LCDSPI_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define LCDSPI_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define LCDSPI_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define LCDSPI_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define LCDSPI_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_NACK_POS)
#define LCDSPI_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_ACK_POS)
#define LCDSPI_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define LCDSPI_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_STOP_POS)
#define LCDSPI_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_START_POS)
#define LCDSPI_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define LCDSPI_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_GENERAL_POS)
#define LCDSPI_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define LCDSPI_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   LCDSPI_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define LCDSPI_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define LCDSPI_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    LCDSPI_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* LCDSPI_INTR_TX, LCDSPI_INTR_TX_SET,
* LCDSPI_INTR_TX_MASK, LCDSPI_INTR_TX_MASKED
*/
#define LCDSPI_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define LCDSPI_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define LCDSPI_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define LCDSPI_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define LCDSPI_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define LCDSPI_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define LCDSPI_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define LCDSPI_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define LCDSPI_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define LCDSPI_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define LCDSPI_INTR_TX_FIFO_LEVEL         (LCDSPI_INTR_TX_TRIGGER)
#define LCDSPI_INTR_TX_NOT_FULL           ((uint32) 0x01u << LCDSPI_INTR_TX_NOT_FULL_POS)
#define LCDSPI_INTR_TX_EMPTY              ((uint32) 0x01u << LCDSPI_INTR_TX_EMPTY_POS)
#define LCDSPI_INTR_TX_OVERFLOW           ((uint32) 0x01u << LCDSPI_INTR_TX_OVERFLOW_POS)
#define LCDSPI_INTR_TX_UNDERFLOW          ((uint32) 0x01u << LCDSPI_INTR_TX_UNDERFLOW_POS)
#define LCDSPI_INTR_TX_BLOCKED            ((uint32) 0x01u << LCDSPI_INTR_TX_BLOCKED_POS)
#define LCDSPI_INTR_TX_UART_NACK          ((uint32) 0x01u << LCDSPI_INTR_TX_UART_NACK_POS)
#define LCDSPI_INTR_TX_UART_DONE          ((uint32) 0x01u << LCDSPI_INTR_TX_UART_DONE_POS)
#define LCDSPI_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << LCDSPI_INTR_TX_UART_ARB_LOST_POS)

/*
* LCDSPI_INTR_RX, LCDSPI_INTR_RX_SET,
* LCDSPI_INTR_RX_MASK, LCDSPI_INTR_RX_MASKED
*/
#define LCDSPI_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define LCDSPI_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define LCDSPI_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define LCDSPI_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define LCDSPI_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define LCDSPI_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define LCDSPI_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define LCDSPI_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define LCDSPI_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define LCDSPI_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define LCDSPI_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define LCDSPI_INTR_RX_FIFO_LEVEL         (LCDSPI_INTR_RX_TRIGGER)
#define LCDSPI_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << LCDSPI_INTR_RX_NOT_EMPTY_POS)
#define LCDSPI_INTR_RX_FULL               ((uint32) 0x01u << LCDSPI_INTR_RX_FULL_POS)
#define LCDSPI_INTR_RX_OVERFLOW           ((uint32) 0x01u << LCDSPI_INTR_RX_OVERFLOW_POS)
#define LCDSPI_INTR_RX_UNDERFLOW          ((uint32) 0x01u << LCDSPI_INTR_RX_UNDERFLOW_POS)
#define LCDSPI_INTR_RX_BLOCKED            ((uint32) 0x01u << LCDSPI_INTR_RX_BLOCKED_POS)
#define LCDSPI_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << LCDSPI_INTR_RX_FRAME_ERROR_POS)
#define LCDSPI_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << LCDSPI_INTR_RX_PARITY_ERROR_POS)
#define LCDSPI_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << LCDSPI_INTR_RX_BAUD_DETECT_POS)
#define LCDSPI_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << LCDSPI_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define LCDSPI_INTR_I2C_EC_ALL    (LCDSPI_INTR_I2C_EC_WAKE_UP    | \
                                             LCDSPI_INTR_I2C_EC_EZBUF_STOP | \
                                             LCDSPI_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define LCDSPI_INTR_SPI_EC_ALL    (LCDSPI_INTR_SPI_EC_WAKE_UP    | \
                                             LCDSPI_INTR_SPI_EC_EZBUF_STOP | \
                                             LCDSPI_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define LCDSPI_INTR_MASTER_ALL    (LCDSPI_INTR_MASTER_I2C_ARB_LOST  | \
                                             LCDSPI_INTR_MASTER_I2C_NACK      | \
                                             LCDSPI_INTR_MASTER_I2C_ACK       | \
                                             LCDSPI_INTR_MASTER_I2C_STOP      | \
                                             LCDSPI_INTR_MASTER_I2C_BUS_ERROR | \
                                             LCDSPI_INTR_MASTER_SPI_DONE)

#define LCDSPI_INTR_SLAVE_ALL     (LCDSPI_INTR_SLAVE_I2C_ARB_LOST      | \
                                             LCDSPI_INTR_SLAVE_I2C_NACK          | \
                                             LCDSPI_INTR_SLAVE_I2C_ACK           | \
                                             LCDSPI_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             LCDSPI_INTR_SLAVE_I2C_STOP          | \
                                             LCDSPI_INTR_SLAVE_I2C_START         | \
                                             LCDSPI_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             LCDSPI_INTR_SLAVE_I2C_GENERAL       | \
                                             LCDSPI_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             LCDSPI_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             LCDSPI_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             LCDSPI_INTR_SLAVE_SPI_BUS_ERROR)

#define LCDSPI_INTR_TX_ALL        (LCDSPI_INTR_TX_TRIGGER   | \
                                             LCDSPI_INTR_TX_NOT_FULL  | \
                                             LCDSPI_INTR_TX_EMPTY     | \
                                             LCDSPI_INTR_TX_OVERFLOW  | \
                                             LCDSPI_INTR_TX_UNDERFLOW | \
                                             LCDSPI_INTR_TX_BLOCKED   | \
                                             LCDSPI_INTR_TX_UART_NACK | \
                                             LCDSPI_INTR_TX_UART_DONE | \
                                             LCDSPI_INTR_TX_UART_ARB_LOST)

#define LCDSPI_INTR_RX_ALL        (LCDSPI_INTR_RX_TRIGGER      | \
                                             LCDSPI_INTR_RX_NOT_EMPTY    | \
                                             LCDSPI_INTR_RX_FULL         | \
                                             LCDSPI_INTR_RX_OVERFLOW     | \
                                             LCDSPI_INTR_RX_UNDERFLOW    | \
                                             LCDSPI_INTR_RX_BLOCKED      | \
                                             LCDSPI_INTR_RX_FRAME_ERROR  | \
                                             LCDSPI_INTR_RX_PARITY_ERROR | \
                                             LCDSPI_INTR_RX_BAUD_DETECT  | \
                                             LCDSPI_INTR_RX_BREAK_DETECT)

/* I2C and EZI2C slave address defines */
#define LCDSPI_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define LCDSPI_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define LCDSPI_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define LCDSPI_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define LCDSPI_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define LCDSPI_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define LCDSPI_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define LCDSPI_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define LCDSPI_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define LCDSPI_CTRL_OVS_IRDA_OVS16        (LCDSPI_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
* Clear I2C command registers are because they are not impacted by re-enable.
*/
#define LCDSPI_SCB_SW_RESET   LCDSPI_I2CFwBlockReset()

/* TX FIFO macro */
#define LCDSPI_CLEAR_TX_FIFO \
                            do{        \
                                LCDSPI_TX_FIFO_CTRL_REG |= ((uint32)  LCDSPI_TX_FIFO_CTRL_CLEAR); \
                                LCDSPI_TX_FIFO_CTRL_REG &= ((uint32) ~LCDSPI_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define LCDSPI_GET_TX_FIFO_ENTRIES    (LCDSPI_TX_FIFO_STATUS_REG & \
                                                 LCDSPI_TX_FIFO_STATUS_USED_MASK)

#define LCDSPI_GET_TX_FIFO_SR_VALID   ((0u != (LCDSPI_TX_FIFO_STATUS_REG & \
                                                         LCDSPI_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define LCDSPI_CLEAR_RX_FIFO \
                            do{        \
                                LCDSPI_RX_FIFO_CTRL_REG |= ((uint32)  LCDSPI_RX_FIFO_CTRL_CLEAR); \
                                LCDSPI_RX_FIFO_CTRL_REG &= ((uint32) ~LCDSPI_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define LCDSPI_GET_RX_FIFO_ENTRIES    (LCDSPI_RX_FIFO_STATUS_REG & \
                                                    LCDSPI_RX_FIFO_STATUS_USED_MASK)

#define LCDSPI_GET_RX_FIFO_SR_VALID   ((0u != (LCDSPI_RX_FIFO_STATUS_REG & \
                                                         LCDSPI_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in LCDSPI_INTR_X_MASK_REG */
#define LCDSPI_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    LCDSPI_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    LCDSPI_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    LCDSPI_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    LCDSPI_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    LCDSPI_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    LCDSPI_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in LCDSPI_INTR_X_MASK_REG */
#define LCDSPI_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    LCDSPI_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    LCDSPI_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    LCDSPI_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    LCDSPI_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    LCDSPI_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    LCDSPI_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in LCDSPI_INTR_X_MASK_REG */
#define LCDSPI_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    LCDSPI_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    LCDSPI_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                LCDSPI_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define LCDSPI_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    LCDSPI_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define LCDSPI_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    LCDSPI_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define LCDSPI_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    LCDSPI_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in LCDSPI_INTR_X_SET_REG */
#define LCDSPI_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    LCDSPI_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    LCDSPI_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    LCDSPI_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    LCDSPI_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in LCDSPI_INTR_X_REG */
#define LCDSPI_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    LCDSPI_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    LCDSPI_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    LCDSPI_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    LCDSPI_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    LCDSPI_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define LCDSPI_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    LCDSPI_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in LCDSPI_INTR_CAUSE_REG */
#define LCDSPI_CHECK_CAUSE_INTR(sourceMask)    (0u != (LCDSPI_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define LCDSPI_CHECK_INTR_I2C_EC(sourceMask)  (0u != (LCDSPI_INTR_I2C_EC_REG & (sourceMask)))
#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_CHECK_INTR_SPI_EC(sourceMask)  (0u != (LCDSPI_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!LCDSPI_CY_SCBIP_V1) */
#define LCDSPI_CHECK_INTR_MASTER(sourceMask)  (0u != (LCDSPI_INTR_MASTER_REG & (sourceMask)))
#define LCDSPI_CHECK_INTR_SLAVE(sourceMask)   (0u != (LCDSPI_INTR_SLAVE_REG  & (sourceMask)))
#define LCDSPI_CHECK_INTR_TX(sourceMask)      (0u != (LCDSPI_INTR_TX_REG     & (sourceMask)))
#define LCDSPI_CHECK_INTR_RX(sourceMask)      (0u != (LCDSPI_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in LCDSPI_INTR_X_MASKED_REG */
#define LCDSPI_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (LCDSPI_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (LCDSPI_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!LCDSPI_CY_SCBIP_V1) */
#define LCDSPI_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (LCDSPI_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define LCDSPI_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (LCDSPI_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define LCDSPI_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (LCDSPI_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define LCDSPI_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (LCDSPI_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in LCDSPI_CTRL_REG: generally is used to check enable bit */
#define LCDSPI_GET_CTRL_ENABLED    (0u != (LCDSPI_CTRL_REG & LCDSPI_CTRL_ENABLED))

#define LCDSPI_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (LCDSPI_I2C_CTRL_REG & \
                                                                LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define LCDSPI_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                LCDSPI_I2C_CTRL_REG |= LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCDSPI_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                LCDSPI_I2C_CTRL_REG |= LCDSPI_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define LCDSPI_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                LCDSPI_I2C_CTRL_REG |= LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCDSPI_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                LCDSPI_I2C_CTRL_REG |= LCDSPI_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define LCDSPI_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                LCDSPI_I2C_CTRL_REG |= LCDSPI_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define LCDSPI_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                LCDSPI_I2C_CTRL_REG &= ~LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCDSPI_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                LCDSPI_I2C_CTRL_REG &= ~LCDSPI_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define LCDSPI_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                LCDSPI_I2C_CTRL_REG &= ~LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCDSPI_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                LCDSPI_I2C_CTRL_REG &= ~LCDSPI_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define LCDSPI_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                LCDSPI_I2C_CTRL_REG &= ~LCDSPI_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define LCDSPI_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                LCDSPI_I2C_CTRL_REG |= (LCDSPI_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define LCDSPI_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                LCDSPI_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(LCDSPI_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define LCDSPI_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                LCDSPI_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(LCDSPI_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    LCDSPI_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)
/* Disables auto data ACK/NACK bits */
#define LCDSPI_DISABLE_AUTO_DATA \
                do{                        \
                    LCDSPI_I2C_CTRL_REG &= ((uint32) ~(LCDSPI_I2C_CTRL_M_READY_DATA_ACK      |  \
                                                                 LCDSPI_I2C_CTRL_M_NOT_READY_DATA_NACK |  \
                                                                 LCDSPI_I2C_CTRL_S_READY_DATA_ACK      |  \
                                                                 LCDSPI_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                }while(0)

/* Master commands */
#define LCDSPI_I2C_MASTER_GENERATE_START \
                            do{                    \
                                LCDSPI_I2C_MASTER_CMD_REG = LCDSPI_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define LCDSPI_I2C_MASTER_CLEAR_START \
                            do{                 \
                                LCDSPI_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define LCDSPI_I2C_MASTER_GENERATE_RESTART LCDSPI_I2CReStartGeneration()

#define LCDSPI_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                LCDSPI_I2C_MASTER_CMD_REG =                                            \
                                    (LCDSPI_I2C_MASTER_CMD_M_STOP |                                    \
                                        (LCDSPI_CHECK_I2C_STATUS(LCDSPI_I2C_STATUS_M_READ) ? \
                                            (LCDSPI_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define LCDSPI_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                LCDSPI_I2C_MASTER_CMD_REG = LCDSPI_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define LCDSPI_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                LCDSPI_I2C_MASTER_CMD_REG = LCDSPI_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define LCDSPI_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                LCDSPI_I2C_SLAVE_CMD_REG = LCDSPI_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void LCDSPI_I2CSlaveNackGeneration(void);
    #define LCDSPI_I2C_SLAVE_GENERATE_NACK LCDSPI_I2CSlaveNackGeneration()

#else
    #define LCDSPI_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                LCDSPI_I2C_SLAVE_CMD_REG = LCDSPI_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                LCDSPI_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define LCDSPI_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    LCDSPI_I2C_SLAVE_ADDR_POS)) & \
                                                                        LCDSPI_I2C_SLAVE_ADDR_MASK)

#define LCDSPI_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> LCDSPI_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define LCDSPI_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define LCDSPI_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (LCDSPI_CY_SCBIP_V0)
    #define LCDSPI_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            LCDSPI_I2C_CFG_REG =                  \
                            ((LCDSPI_I2C_CFG_REG & (uint32) ~LCDSPI_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<LCDSPI_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (LCDSPI_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define LCDSPI_DIGITAL_FILTER_DISABLE    (0u)
#define LCDSPI_DIGITAL_FILTER_ENABLE     (1u)
#define LCDSPI_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (LCDSPI_CY_SCBIP_V0)
    /* LCDSPI_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define LCDSPI_I2C_CFG_FILT_MASK  (LCDSPI_I2C_CFG_SDA_FILT_ENABLED | \
                                                 LCDSPI_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* LCDSPI_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define LCDSPI_I2C_CFG_FILT_MASK  (LCDSPI_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 LCDSPI_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (LCDSPI_CY_SCBIP_V0) */

#define LCDSPI_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            LCDSPI_I2C_CFG_REG &= (uint32) ~LCDSPI_I2C_CFG_FILT_MASK; \
        }while(0)

#define LCDSPI_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            LCDSPI_I2C_CFG_REG |= (uint32)  LCDSPI_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define LCDSPI_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    LCDSPI_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        LCDSPI_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in LCDSPI_I2C_STATUS_REG */
#define LCDSPI_CHECK_I2C_STATUS(sourceMask)   (0u != (LCDSPI_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in LCDSPI_SPI_STATUS_REG */
#define LCDSPI_CHECK_SPI_STATUS(sourceMask)   (0u != (LCDSPI_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on LCDSPI_CTRL_BYTE_MODE bit */
#define LCDSPI_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * LCDSPI_FIFO_SIZE) : (LCDSPI_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* LCDSPI_CTRL */
#define LCDSPI_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & LCDSPI_CTRL_OVS_MASK)

#define LCDSPI_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (LCDSPI_CTRL_EC_OP_MODE)  : (0u))

#define LCDSPI_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (LCDSPI_CTRL_EC_AM_MODE)  : (0u))

#define LCDSPI_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (LCDSPI_CTRL_BLOCK)       : (0u))

#define LCDSPI_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (LCDSPI_CTRL_ADDR_ACCEPT) : (0u))

#if (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define LCDSPI_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (LCDSPI_CTRL_BYTE_MODE) : (0u))
#endif /* (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

/* LCDSPI_I2C_CTRL */
#define LCDSPI_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        LCDSPI_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define LCDSPI_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    LCDSPI_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    LCDSPI_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define LCDSPI_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (LCDSPI_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define LCDSPI_GET_I2C_CTRL_S_GENERAL_IGNORE(genCall) ((0u != (genCall)) ? \
                                                                    (LCDSPI_I2C_CTRL_S_GENERAL_IGNORE) : (0u))

#define LCDSPI_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << LCDSPI_I2C_CTRL_SLAVE_MODE_POS)

/* LCDSPI_SPI_CTRL */
#define LCDSPI_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (LCDSPI_SPI_CTRL_CONTINUOUS) : (0u))

#define LCDSPI_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (LCDSPI_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define LCDSPI_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        LCDSPI_SPI_CTRL_CPHA_POS) & \
                                                                        LCDSPI_SPI_CTRL_SCLK_MODE_MASK)

#define LCDSPI_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (LCDSPI_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define LCDSPI_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define LCDSPI_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (LCDSPI_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define LCDSPI_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     LCDSPI_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     LCDSPI_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << LCDSPI_SPI_CTRL_MODE_POS) & \
                                                                                 LCDSPI_SPI_CTRL_MODE_MASK)

#define LCDSPI_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      LCDSPI_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      LCDSPI_SPI_CTRL_SLAVE_SELECT_MASK)

#define LCDSPI_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (LCDSPI_SPI_CTRL_MASTER) : (0u))

/* LCDSPI_UART_CTRL */
#define LCDSPI_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            LCDSPI_UART_CTRL_MODE_POS) & \
                                                                            LCDSPI_UART_CTRL_MODE_MASK)

/* LCDSPI_UART_RX_CTRL */
#define LCDSPI_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        LCDSPI_UART_RX_CTRL_STOP_BITS_MASK)

#define LCDSPI_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (LCDSPI_UART_RX_CTRL_PARITY) : (0u))

#define LCDSPI_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (LCDSPI_UART_RX_CTRL_POLARITY) : (0u))

#define LCDSPI_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (LCDSPI_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define LCDSPI_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (LCDSPI_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define LCDSPI_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (LCDSPI_UART_RX_CTRL_MP_MODE) : (0u))

#define LCDSPI_GET_UART_RX_CTRL_BREAK_WIDTH(width)    (((uint32) ((uint32) (width) - 1u) << \
                                                                    LCDSPI_UART_RX_CTRL_BREAK_WIDTH_POS) & \
                                                                    LCDSPI_UART_RX_CTRL_BREAK_WIDTH_MASK)

/* LCDSPI_UART_TX_CTRL */
#define LCDSPI_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                LCDSPI_UART_RX_CTRL_STOP_BITS_MASK)

#define LCDSPI_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (LCDSPI_UART_TX_CTRL_PARITY) : (0u))

#define LCDSPI_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (LCDSPI_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* LCDSPI_UART_FLOW_CTRL */
#if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 LCDSPI_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define LCDSPI_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (LCDSPI_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define LCDSPI_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (LCDSPI_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define LCDSPI_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (LCDSPI_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

/* LCDSPI_RX_CTRL */
#define LCDSPI_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                LCDSPI_RX_CTRL_DATA_WIDTH_MASK)

#define LCDSPI_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (LCDSPI_RX_CTRL_MSB_FIRST) : (0u))

#define LCDSPI_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (LCDSPI_RX_CTRL_MEDIAN) : (0u))

/* LCDSPI_RX_MATCH */
#define LCDSPI_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & LCDSPI_RX_MATCH_ADDR_MASK)
#define LCDSPI_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            LCDSPI_RX_MATCH_MASK_POS) & \
                                                            LCDSPI_RX_MATCH_MASK_MASK)

/* LCDSPI_RX_FIFO_CTRL */
#define LCDSPI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    LCDSPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* LCDSPI_TX_CTRL */
#define LCDSPI_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                LCDSPI_TX_CTRL_DATA_WIDTH_MASK)

#define LCDSPI_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (LCDSPI_TX_CTRL_MSB_FIRST) : (0u))

/* LCDSPI_TX_FIFO_CTRL */
#define LCDSPI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    LCDSPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* LCDSPI_INTR_SLAVE_I2C_GENERAL */
#define LCDSPI_GET_INTR_SLAVE_I2C_GENERAL(genCall)  ((0u != (genCall)) ? \
                                                                (LCDSPI_INTR_SLAVE_I2C_GENERAL) : (0u))

/* Return true if master mode is enabled LCDSPI_SPI_CTRL_REG */
#define LCDSPI_CHECK_SPI_MASTER   (0u != (LCDSPI_SPI_CTRL_REG & LCDSPI_SPI_CTRL_MASTER))

/* Return inactive state of SPI SCLK line depends on CPOL */
#define LCDSPI_GET_SPI_SCLK_INACTIVE \
            ((0u == (LCDSPI_SPI_CTRL_REG & LCDSPI_SPI_CTRL_CPOL)) ? (0u) : (1u))

/* Get output pin inactive state */
#if (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
#define LCDSPI_GET_SPI_SS0_INACTIVE       (1u)
#define LCDSPI_GET_SPI_SS1_INACTIVE       (1u)
#define LCDSPI_GET_SPI_SS2_INACTIVE       (1u)
#define LCDSPI_GET_SPI_SS3_INACTIVE       (1u)
#define LCDSPI_GET_UART_RTS_INACTIVE      (1u)

#else
#define LCDSPI_GET_SPI_SS0_INACTIVE  \
        ((0u != (LCDSPI_SPI_CTRL_REG & LCDSPI_SPI_CTRL_SSEL0_POLARITY)) ? (0u) : (1u))

#define LCDSPI_GET_SPI_SS1_INACTIVE  \
        ((0u != (LCDSPI_SPI_CTRL_REG & LCDSPI_SPI_CTRL_SSEL1_POLARITY)) ? (0u) : (1u))

#define LCDSPI_GET_SPI_SS2_INACTIVE  \
        ((0u != (LCDSPI_SPI_CTRL_REG & LCDSPI_SPI_CTRL_SSEL2_POLARITY)) ? (0u) : (1u))

#define LCDSPI_GET_SPI_SS3_INACTIVE  \
        ((0u != (LCDSPI_SPI_CTRL_REG & LCDSPI_SPI_CTRL_SSEL3_POLARITY)) ? (0u) : (1u))

#define LCDSPI_GET_UART_RTS_INACTIVE \
        ((0u == (LCDSPI_UART_FLOW_CTRL_REG & LCDSPI_UART_FLOW_CTRL_RTS_POLARITY)) ? (0u) : (1u))

#endif /*(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */

/* Clear register constants for configuration and interrupt mask */
#define LCDSPI_CLEAR_REG          ((uint32) (0u))
#define LCDSPI_NO_INTR_SOURCES    ((uint32) (0u))
#define LCDSPI_DUMMY_PARAM        ((uint32) (0u))
#define LCDSPI_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define LCDSPI_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define LCDSPI_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define LCDSPI_CHECK_INTR_EC_I2C(sourceMask)  LCDSPI_CHECK_INTR_I2C_EC(sourceMask)
#if (!LCDSPI_CY_SCBIP_V1)
    #define LCDSPI_CHECK_INTR_EC_SPI(sourceMask)  LCDSPI_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#define LCDSPI_CY_SCBIP_V1_I2C_ONLY   (LCDSPI_CY_SCBIP_V1)
#define LCDSPI_EZBUFFER_SIZE          (LCDSPI_EZ_DATA_NR)

#define LCDSPI_EZBUF_DATA00_REG   LCDSPI_EZBUF_DATA0_REG
#define LCDSPI_EZBUF_DATA00_PTR   LCDSPI_EZBUF_DATA0_PTR

#endif /* (CY_SCB_LCDSPI_H) */


/* [] END OF FILE */

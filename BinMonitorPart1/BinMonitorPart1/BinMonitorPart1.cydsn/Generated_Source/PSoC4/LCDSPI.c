/***************************************************************************//**
* \file LCDSPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (LCDSPI_SCB_MODE_I2C_INC)
    #include "LCDSPI_I2C_PVT.h"
#endif /* (LCDSPI_SCB_MODE_I2C_INC) */

#if (LCDSPI_SCB_MODE_EZI2C_INC)
    #include "LCDSPI_EZI2C_PVT.h"
#endif /* (LCDSPI_SCB_MODE_EZI2C_INC) */

#if (LCDSPI_SCB_MODE_SPI_INC || LCDSPI_SCB_MODE_UART_INC)
    #include "LCDSPI_SPI_UART_PVT.h"
#endif /* (LCDSPI_SCB_MODE_SPI_INC || LCDSPI_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 LCDSPI_scbMode = LCDSPI_SCB_MODE_UNCONFIG;
    uint8 LCDSPI_scbEnableWake;
    uint8 LCDSPI_scbEnableIntr;

    /* I2C configuration variables */
    uint8 LCDSPI_mode;
    uint8 LCDSPI_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * LCDSPI_rxBuffer;
    uint8  LCDSPI_rxDataBits;
    uint32 LCDSPI_rxBufferSize;

    volatile uint8 * LCDSPI_txBuffer;
    uint8  LCDSPI_txDataBits;
    uint32 LCDSPI_txBufferSize;

    /* EZI2C configuration variables */
    uint8 LCDSPI_numberOfAddr;
    uint8 LCDSPI_subAddrSize;
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
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
uint8 LCDSPI_initVar = 0u;


#if (! (LCDSPI_SCB_MODE_I2C_CONST_CFG || \
        LCDSPI_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * LCDSPI_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent LCDSPI_Enable() call.
    */
    uint16 LCDSPI_IntrTxMask = 0u;
#endif /* (! (LCDSPI_SCB_MODE_I2C_CONST_CFG || \
              LCDSPI_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (LCDSPI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_LCDSPI_CUSTOM_INTR_HANDLER)
    void (*LCDSPI_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_LCDSPI_CUSTOM_INTR_HANDLER) */
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void LCDSPI_ScbEnableIntr(void);
static void LCDSPI_ScbModeStop(void);
static void LCDSPI_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: LCDSPI_Init
****************************************************************************//**
*
*  Initializes the LCDSPI component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  LCDSPI_I2CInit, LCDSPI_SpiInit, 
*  LCDSPI_UartInit or LCDSPI_EzI2CInit.
*
*******************************************************************************/
void LCDSPI_Init(void)
{
#if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    if (LCDSPI_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        LCDSPI_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (LCDSPI_SCB_MODE_I2C_CONST_CFG)
    LCDSPI_I2CInit();

#elif (LCDSPI_SCB_MODE_SPI_CONST_CFG)
    LCDSPI_SpiInit();

#elif (LCDSPI_SCB_MODE_UART_CONST_CFG)
    LCDSPI_UartInit();

#elif (LCDSPI_SCB_MODE_EZI2C_CONST_CFG)
    LCDSPI_EzI2CInit();

#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LCDSPI_Enable
****************************************************************************//**
*
*  Enables LCDSPI component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  LCDSPI_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The LCDSPI configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured LCDSPI”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void LCDSPI_Enable(void)
{
#if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!LCDSPI_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        LCDSPI_CTRL_REG |= LCDSPI_CTRL_ENABLED;

        LCDSPI_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        LCDSPI_ScbModePostEnable();
    }
#else
    LCDSPI_CTRL_REG |= LCDSPI_CTRL_ENABLED;

    LCDSPI_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    LCDSPI_ScbModePostEnable();
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LCDSPI_Start
****************************************************************************//**
*
*  Invokes LCDSPI_Init() and LCDSPI_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  LCDSPI_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void LCDSPI_Start(void)
{
    if (0u == LCDSPI_initVar)
    {
        LCDSPI_Init();
        LCDSPI_initVar = 1u; /* Component was initialized */
    }

    LCDSPI_Enable();
}


/*******************************************************************************
* Function Name: LCDSPI_Stop
****************************************************************************//**
*
*  Disables the LCDSPI component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function LCDSPI_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void LCDSPI_Stop(void)
{
#if (LCDSPI_SCB_IRQ_INTERNAL)
    LCDSPI_DisableInt();
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    LCDSPI_ScbModeStop();

    /* Disable SCB IP */
    LCDSPI_CTRL_REG &= (uint32) ~LCDSPI_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    LCDSPI_SetTxInterruptMode(LCDSPI_NO_INTR_SOURCES);

#if (LCDSPI_SCB_IRQ_INTERNAL)
    LCDSPI_ClearPendingInt();
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: LCDSPI_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void LCDSPI_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = LCDSPI_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~LCDSPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (LCDSPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    LCDSPI_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: LCDSPI_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void LCDSPI_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = LCDSPI_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~LCDSPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (LCDSPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    LCDSPI_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (LCDSPI_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: LCDSPI_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void LCDSPI_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_LCDSPI_CUSTOM_INTR_HANDLER)
        LCDSPI_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_LCDSPI_CUSTOM_INTR_HANDLER) */
    }
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: LCDSPI_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void LCDSPI_ScbEnableIntr(void)
{
#if (LCDSPI_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != LCDSPI_scbEnableIntr)
        {
            LCDSPI_EnableInt();
        }

    #else
        LCDSPI_EnableInt();

    #endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (LCDSPI_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: LCDSPI_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void LCDSPI_ScbModePostEnable(void)
{
#if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!LCDSPI_CY_SCBIP_V1)
    if (LCDSPI_SCB_MODE_SPI_RUNTM_CFG)
    {
        LCDSPI_SpiPostEnable();
    }
    else if (LCDSPI_SCB_MODE_UART_RUNTM_CFG)
    {
        LCDSPI_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!LCDSPI_CY_SCBIP_V1) */

#elif (LCDSPI_SCB_MODE_SPI_CONST_CFG)
    LCDSPI_SpiPostEnable();

#elif (LCDSPI_SCB_MODE_UART_CONST_CFG)
    LCDSPI_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LCDSPI_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void LCDSPI_ScbModeStop(void)
{
#if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    if (LCDSPI_SCB_MODE_I2C_RUNTM_CFG)
    {
        LCDSPI_I2CStop();
    }
    else if (LCDSPI_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        LCDSPI_EzI2CStop();
    }
#if (!LCDSPI_CY_SCBIP_V1)
    else if (LCDSPI_SCB_MODE_SPI_RUNTM_CFG)
    {
        LCDSPI_SpiStop();
    }
    else if (LCDSPI_SCB_MODE_UART_RUNTM_CFG)
    {
        LCDSPI_UartStop();
    }
#endif /* (!LCDSPI_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (LCDSPI_SCB_MODE_I2C_CONST_CFG)
    LCDSPI_I2CStop();

#elif (LCDSPI_SCB_MODE_EZI2C_CONST_CFG)
    LCDSPI_EzI2CStop();

#elif (LCDSPI_SCB_MODE_SPI_CONST_CFG)
    LCDSPI_SpiStop();

#elif (LCDSPI_SCB_MODE_UART_CONST_CFG)
    LCDSPI_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: LCDSPI_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void LCDSPI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[LCDSPI_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!LCDSPI_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!LCDSPI_CY_SCBIP_V1) */
        
        uint32 hsiomSel[LCDSPI_SCB_PINS_NUMBER] = 
        {
            LCDSPI_RX_SDA_MOSI_HSIOM_SEL_GPIO,
            LCDSPI_TX_SCL_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (LCDSPI_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (LCDSPI_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < LCDSPI_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = LCDSPI_PIN_DM_ALG_HIZ;
        }

        if ((LCDSPI_SCB_MODE_I2C   == mode) ||
            (LCDSPI_SCB_MODE_EZI2C == mode))
        {
        #if (LCDSPI_RX_SDA_MOSI_PIN)
            hsiomSel[LCDSPI_RX_SDA_MOSI_PIN_INDEX] = LCDSPI_RX_SDA_MOSI_HSIOM_SEL_I2C;
            pinsDm  [LCDSPI_RX_SDA_MOSI_PIN_INDEX] = LCDSPI_PIN_DM_OD_LO;
        #elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
            hsiomSel[LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX] = LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_SEL_I2C;
            pinsDm  [LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX] = LCDSPI_PIN_DM_OD_LO;
        #else
        #endif /* (LCDSPI_RX_SDA_MOSI_PIN) */
        
        #if (LCDSPI_TX_SCL_MISO_PIN)
            hsiomSel[LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_TX_SCL_MISO_HSIOM_SEL_I2C;
            pinsDm  [LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_PIN_DM_OD_LO;
        #endif /* (LCDSPI_TX_SCL_MISO_PIN) */
        }
    #if (!LCDSPI_CY_SCBIP_V1)
        else if (LCDSPI_SCB_MODE_SPI == mode)
        {
        #if (LCDSPI_RX_SDA_MOSI_PIN)
            hsiomSel[LCDSPI_RX_SDA_MOSI_PIN_INDEX] = LCDSPI_RX_SDA_MOSI_HSIOM_SEL_SPI;
        #elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
            hsiomSel[LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX] = LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (LCDSPI_RX_SDA_MOSI_PIN) */
        
        #if (LCDSPI_TX_SCL_MISO_PIN)
            hsiomSel[LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_TX_SCL_MISO_HSIOM_SEL_SPI;
        #endif /* (LCDSPI_TX_SCL_MISO_PIN) */
        
        #if (LCDSPI_CTS_SCLK_PIN)
            hsiomSel[LCDSPI_CTS_SCLK_PIN_INDEX] = LCDSPI_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (LCDSPI_CTS_SCLK_PIN) */

            if (LCDSPI_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[LCDSPI_RX_SDA_MOSI_PIN_INDEX] = LCDSPI_PIN_DM_DIG_HIZ;
                pinsDm[LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                pinsDm[LCDSPI_CTS_SCLK_PIN_INDEX] = LCDSPI_PIN_DM_DIG_HIZ;

            #if (LCDSPI_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[LCDSPI_RTS_SS0_PIN_INDEX] = LCDSPI_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [LCDSPI_RTS_SS0_PIN_INDEX] = LCDSPI_PIN_DM_DIG_HIZ;
            #endif /* (LCDSPI_RTS_SS0_PIN) */

            #if (LCDSPI_TX_SCL_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= LCDSPI_TX_SCL_MISO_PIN_MASK;
            #endif /* (LCDSPI_TX_SCL_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[LCDSPI_RX_SDA_MOSI_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                pinsDm[LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_PIN_DM_DIG_HIZ;
                pinsDm[LCDSPI_CTS_SCLK_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;

            #if (LCDSPI_RTS_SS0_PIN)
                hsiomSel [LCDSPI_RTS_SS0_PIN_INDEX] = LCDSPI_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [LCDSPI_RTS_SS0_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                pinsInBuf |= LCDSPI_RTS_SS0_PIN_MASK;
            #endif /* (LCDSPI_RTS_SS0_PIN) */

            #if (LCDSPI_SS1_PIN)
                hsiomSel [LCDSPI_SS1_PIN_INDEX] = LCDSPI_SS1_HSIOM_SEL_SPI;
                pinsDm   [LCDSPI_SS1_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                pinsInBuf |= LCDSPI_SS1_PIN_MASK;
            #endif /* (LCDSPI_SS1_PIN) */

            #if (LCDSPI_SS2_PIN)
                hsiomSel [LCDSPI_SS2_PIN_INDEX] = LCDSPI_SS2_HSIOM_SEL_SPI;
                pinsDm   [LCDSPI_SS2_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                pinsInBuf |= LCDSPI_SS2_PIN_MASK;
            #endif /* (LCDSPI_SS2_PIN) */

            #if (LCDSPI_SS3_PIN)
                hsiomSel [LCDSPI_SS3_PIN_INDEX] = LCDSPI_SS3_HSIOM_SEL_SPI;
                pinsDm   [LCDSPI_SS3_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                pinsInBuf |= LCDSPI_SS3_PIN_MASK;
            #endif /* (LCDSPI_SS3_PIN) */

                /* Disable input buffers */
            #if (LCDSPI_RX_SDA_MOSI_PIN)
                pinsInBuf |= LCDSPI_RX_SDA_MOSI_PIN_MASK;
            #elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
                pinsInBuf |= LCDSPI_RX_WAKE_SDA_MOSI_PIN_MASK;
            #else
            #endif /* (LCDSPI_RX_SDA_MOSI_PIN) */

            #if (LCDSPI_CTS_SCLK_PIN)
                pinsInBuf |= LCDSPI_CTS_SCLK_PIN_MASK;
            #endif /* (LCDSPI_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (LCDSPI_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (LCDSPI_TX_SCL_MISO_PIN)
                hsiomSel[LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_TX_SCL_MISO_HSIOM_SEL_UART;
                pinsDm  [LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_PIN_DM_OD_LO;
            #endif /* (LCDSPI_TX_SCL_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (LCDSPI_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (LCDSPI_RX_SDA_MOSI_PIN)
                    hsiomSel[LCDSPI_RX_SDA_MOSI_PIN_INDEX] = LCDSPI_RX_SDA_MOSI_HSIOM_SEL_UART;
                    pinsDm  [LCDSPI_RX_SDA_MOSI_PIN_INDEX] = LCDSPI_PIN_DM_DIG_HIZ;
                #elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
                    hsiomSel[LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX] = LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_SEL_UART;
                    pinsDm  [LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX] = LCDSPI_PIN_DM_DIG_HIZ;
                #else
                #endif /* (LCDSPI_RX_SDA_MOSI_PIN) */
                }

                if (0u != (LCDSPI_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (LCDSPI_TX_SCL_MISO_PIN)
                    hsiomSel[LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_TX_SCL_MISO_HSIOM_SEL_UART;
                    pinsDm  [LCDSPI_TX_SCL_MISO_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= LCDSPI_TX_SCL_MISO_PIN_MASK;
                #endif /* (LCDSPI_TX_SCL_MISO_PIN) */
                }

            #if !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
                if (LCDSPI_UART_MODE_STD == subMode)
                {
                    if (0u != (LCDSPI_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (LCDSPI_CTS_SCLK_PIN)
                        hsiomSel[LCDSPI_CTS_SCLK_PIN_INDEX] = LCDSPI_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [LCDSPI_CTS_SCLK_PIN_INDEX] = LCDSPI_PIN_DM_DIG_HIZ;
                    #endif /* (LCDSPI_CTS_SCLK_PIN) */
                    }

                    if (0u != (LCDSPI_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (LCDSPI_RTS_SS0_PIN)
                        hsiomSel[LCDSPI_RTS_SS0_PIN_INDEX] = LCDSPI_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [LCDSPI_RTS_SS0_PIN_INDEX] = LCDSPI_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= LCDSPI_RTS_SS0_PIN_MASK;
                    #endif /* (LCDSPI_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */
            }
        }
    #endif /* (!LCDSPI_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (LCDSPI_RX_SDA_MOSI_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_RX_SDA_MOSI_HSIOM_REG,
                                       LCDSPI_RX_SDA_MOSI_HSIOM_MASK,
                                       LCDSPI_RX_SDA_MOSI_HSIOM_POS,
                                        hsiomSel[LCDSPI_RX_SDA_MOSI_PIN_INDEX]);

        LCDSPI_uart_rx_i2c_sda_spi_mosi_SetDriveMode((uint8) pinsDm[LCDSPI_RX_SDA_MOSI_PIN_INDEX]);

        #if (!LCDSPI_CY_SCBIP_V1)
            LCDSPI_SET_INP_DIS(LCDSPI_uart_rx_i2c_sda_spi_mosi_INP_DIS,
                                         LCDSPI_uart_rx_i2c_sda_spi_mosi_MASK,
                                         (0u != (pinsInBuf & LCDSPI_RX_SDA_MOSI_PIN_MASK)));
        #endif /* (!LCDSPI_CY_SCBIP_V1) */
    
    #elif (LCDSPI_RX_WAKE_SDA_MOSI_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_REG,
                                       LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_MASK,
                                       LCDSPI_RX_WAKE_SDA_MOSI_HSIOM_POS,
                                       hsiomSel[LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX]);

        LCDSPI_uart_rx_wake_i2c_sda_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[LCDSPI_RX_WAKE_SDA_MOSI_PIN_INDEX]);

        LCDSPI_SET_INP_DIS(LCDSPI_uart_rx_wake_i2c_sda_spi_mosi_INP_DIS,
                                     LCDSPI_uart_rx_wake_i2c_sda_spi_mosi_MASK,
                                     (0u != (pinsInBuf & LCDSPI_RX_WAKE_SDA_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        LCDSPI_SET_INCFG_TYPE(LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_REG,
                                        LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK,
                                        LCDSPI_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS,
                                        LCDSPI_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (LCDSPI_RX_WAKE_SDA_MOSI_PIN) */

    #if (LCDSPI_TX_SCL_MISO_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_TX_SCL_MISO_HSIOM_REG,
                                       LCDSPI_TX_SCL_MISO_HSIOM_MASK,
                                       LCDSPI_TX_SCL_MISO_HSIOM_POS,
                                        hsiomSel[LCDSPI_TX_SCL_MISO_PIN_INDEX]);

        LCDSPI_uart_tx_i2c_scl_spi_miso_SetDriveMode((uint8) pinsDm[LCDSPI_TX_SCL_MISO_PIN_INDEX]);

    #if (!LCDSPI_CY_SCBIP_V1)
        LCDSPI_SET_INP_DIS(LCDSPI_uart_tx_i2c_scl_spi_miso_INP_DIS,
                                     LCDSPI_uart_tx_i2c_scl_spi_miso_MASK,
                                    (0u != (pinsInBuf & LCDSPI_TX_SCL_MISO_PIN_MASK)));
    #endif /* (!LCDSPI_CY_SCBIP_V1) */
    #endif /* (LCDSPI_RX_SDA_MOSI_PIN) */

    #if (LCDSPI_CTS_SCLK_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_CTS_SCLK_HSIOM_REG,
                                       LCDSPI_CTS_SCLK_HSIOM_MASK,
                                       LCDSPI_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[LCDSPI_CTS_SCLK_PIN_INDEX]);

        LCDSPI_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[LCDSPI_CTS_SCLK_PIN_INDEX]);

        LCDSPI_SET_INP_DIS(LCDSPI_uart_cts_spi_sclk_INP_DIS,
                                     LCDSPI_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & LCDSPI_CTS_SCLK_PIN_MASK)));
    #endif /* (LCDSPI_CTS_SCLK_PIN) */

    #if (LCDSPI_RTS_SS0_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_RTS_SS0_HSIOM_REG,
                                       LCDSPI_RTS_SS0_HSIOM_MASK,
                                       LCDSPI_RTS_SS0_HSIOM_POS,
                                       hsiomSel[LCDSPI_RTS_SS0_PIN_INDEX]);

        LCDSPI_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[LCDSPI_RTS_SS0_PIN_INDEX]);

        LCDSPI_SET_INP_DIS(LCDSPI_uart_rts_spi_ss0_INP_DIS,
                                     LCDSPI_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & LCDSPI_RTS_SS0_PIN_MASK)));
    #endif /* (LCDSPI_RTS_SS0_PIN) */

    #if (LCDSPI_SS1_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS1_HSIOM_REG,
                                       LCDSPI_SS1_HSIOM_MASK,
                                       LCDSPI_SS1_HSIOM_POS,
                                       hsiomSel[LCDSPI_SS1_PIN_INDEX]);

        LCDSPI_spi_ss1_SetDriveMode((uint8) pinsDm[LCDSPI_SS1_PIN_INDEX]);

        LCDSPI_SET_INP_DIS(LCDSPI_spi_ss1_INP_DIS,
                                     LCDSPI_spi_ss1_MASK,
                                     (0u != (pinsInBuf & LCDSPI_SS1_PIN_MASK)));
    #endif /* (LCDSPI_SS1_PIN) */

    #if (LCDSPI_SS2_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS2_HSIOM_REG,
                                       LCDSPI_SS2_HSIOM_MASK,
                                       LCDSPI_SS2_HSIOM_POS,
                                       hsiomSel[LCDSPI_SS2_PIN_INDEX]);

        LCDSPI_spi_ss2_SetDriveMode((uint8) pinsDm[LCDSPI_SS2_PIN_INDEX]);

        LCDSPI_SET_INP_DIS(LCDSPI_spi_ss2_INP_DIS,
                                     LCDSPI_spi_ss2_MASK,
                                     (0u != (pinsInBuf & LCDSPI_SS2_PIN_MASK)));
    #endif /* (LCDSPI_SS2_PIN) */

    #if (LCDSPI_SS3_PIN)
        LCDSPI_SET_HSIOM_SEL(LCDSPI_SS3_HSIOM_REG,
                                       LCDSPI_SS3_HSIOM_MASK,
                                       LCDSPI_SS3_HSIOM_POS,
                                       hsiomSel[LCDSPI_SS3_PIN_INDEX]);

        LCDSPI_spi_ss3_SetDriveMode((uint8) pinsDm[LCDSPI_SS3_PIN_INDEX]);

        LCDSPI_SET_INP_DIS(LCDSPI_spi_ss3_INP_DIS,
                                     LCDSPI_spi_ss3_MASK,
                                     (0u != (pinsInBuf & LCDSPI_SS3_PIN_MASK)));
    #endif /* (LCDSPI_SS3_PIN) */
    }

#endif /* (LCDSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: LCDSPI_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void LCDSPI_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (LCDSPI_CTRL_REG & LCDSPI_CTRL_EC_AM_MODE)) &&
            (0u == (LCDSPI_I2C_CTRL_REG & LCDSPI_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            LCDSPI_CTRL_REG &= ~LCDSPI_CTRL_EC_AM_MODE;
            LCDSPI_CTRL_REG |=  LCDSPI_CTRL_EC_AM_MODE;
        }

        LCDSPI_I2C_SLAVE_CMD_REG = LCDSPI_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (LCDSPI_CY_SCBIP_V0 || LCDSPI_CY_SCBIP_V1) */


/* [] END OF FILE */

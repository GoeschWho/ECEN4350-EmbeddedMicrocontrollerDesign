/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* Includes */
#include <project.h>
#include <gfx.h>

/* Function Delarations */
void StackEventHandler( uint32 eventCode, void *eventParam );
systemticks_t gfxSystemTicks(void);
systemticks_t gfxMillisecondsToTicks(delaytime_t ms);

/* define the test register to switch the PA/LNA hardware control pins */
#define CYREG_SRSS_TST_DDFT_CTRL 0x40030008

int main()
{
     CyGlobalIntEnable;   /* Enable global interrupts */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CySysTickStart();
    
    // Initialize the uGFX library
    gfxInit();
    
    // Change the display orientation
    //gdispSetOrientation(GDISP_ROTATE_LANDSCAPE);
    
    
    CyBle_Start( StackEventHandler );
    
    for(;;)
    {
        /* Place your application code here */
        gfxSleepMilliseconds(500);
        CyBle_ProcessEvents();
    }
}


void StackEventHandler( uint32 eventCode, void *eventParam )
{
    switch( eventCode )
    {
        /* Generic events */

        case CYBLE_EVT_STACK_ON:
            /* Configure the Link Layer to automatically switch PA
             * control pin P3[2] and LNA control pin P3[3] */
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_RF_CONFIG), 0x0331);
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_SRSS_TST_DDFT_CTRL), 0x80000302);
            /* CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST ); */
        break;
            
        /* Add additional events as required */    
            
        /* default catch-all case */

        default:
        break;    
    }
}    
            


systemticks_t gfxSystemTicks() {
    return CySysTickGetValue();
}

systemticks_t gfxMillisecondsToTicks(delaytime_t ms) {
    return ms;
}

/* [] END OF FILE */
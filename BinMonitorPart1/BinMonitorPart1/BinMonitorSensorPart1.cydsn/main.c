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
#include <project.h>

void StackEventHandler( uint32 eventCode, void *eventParam );
void UpdateTemperatureCharacteristic(uint8* tempData, uint8 len, uint16 attrHandle);

/* define the test register to switch the PA/LNA hardware control pins */
#define CYREG_SRSS_TST_DDFT_CTRL 0x40030008

uint8 number_read = 0;
uint8 number_write = 0;
uint8 number_notify = 0;
uint8 number_indicate = 0;
  
uint8 notification_enabled = 0;
uint8 indication_enabled = 0;

int main()
{
    //------ Declarations -------//
    CYBLE_API_RESULT_T apiResult;
    //---------------------------//
    
     CyGlobalIntEnable;   /* Enable global interrupts */    
    
    //------ BLE Setup ------//
    // Start
    apiResult = CyBle_Start(StackEventHandler);
    if(apiResult == 0x00u)
    {
//        LED_GREEN_Write(0u);
    }
    
    // Advertise
//    CyBle_ProcessEvents();
//    apiResult = CyBle_GappStartAdvertisement(0x00u);
//    if (apiResult == 0x00u) {
//        LED_GREEN_Write(0u);
//    }
  
    for(;;)
    {
        /* CyBle_ProcessEvents() allows BLE stack to process pending events */
        CyBle_ProcessEvents();
        
        LED_BLUE_Write(0u);  
        CyDelay(1000);
        //for(int i=0;i<1000;i++);
        LED_BLUE_Write(1u);
        //for(int i=0;i<1000;i++);
        CyDelay(1000);
        
    }
}


void StackEventHandler( uint32 eventCode, void *eventParam )
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    switch( eventCode )
    {
        /* Generic events */

        case CYBLE_EVT_STACK_ON:
            /* Configure the Link Layer to automatically switch PA
             * control pin P3[2] and LNA control pin P3[3] */
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_RF_CONFIG), 0x0331);
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_SRSS_TST_DDFT_CTRL), 0x80000302);
            CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
        break;
            
//        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
//            /* This event is generated at GAP disconnection. */
//            /* Restart advertisement */
//            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST); 
//        break;
//            
//        /* Add additional events as required */    
//            
//        case CYBLE_EVT_GATTS_WRITE_REQ:
//            /* Extract the Write data sent by Client */
//             wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
//            
//            /* If the attribute handle of the characteristic written to
//            * is equal to that of RGB_LED characteristic, then extract
//            * the RGB LED data */
//             if(CYBLE_TEMPERATURE_SERVICE_SERVICE_HANDLE == wrReqParam->handleValPair.attrHandle)
//             {
//                /* Update the GATT DB for RGB LED read characteristics*/
//                uint8 tempData = 99;
//                UpdateTemperatureCharacteristic(*tempData, sizeof(tempData), CYBLE_TEMPERATURE_SERVICE_SERVICE_HANDLE);
//             }
//            /* Send the response to the write request received. */
//            CyBle_GattsWriteRsp(cyBle_connHandle);
//        break;

            
        /* default catch-all case */

        default:
        break; 
    }

}        
/* [] END OF FILE */

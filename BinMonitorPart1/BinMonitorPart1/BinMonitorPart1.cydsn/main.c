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
#include <RA8875.h>

void StackEventHandler( uint32 eventCode, void *eventParam );

/* define the test register to switch the PA/LNA hardware control pins */
#define CYREG_SRSS_TST_DDFT_CTRL 0x40030008

int main()
{
    //------ Declarations -------//
    
    // LCD Strings
    char welcome1[] = "Megan Bird";
    char welcome2[] = "ECEN 4350";
    char welcome3[] = "Fall 2017";
    char ble[] = "BLE_Central";
    
    uint16_t x;
    uint16_t y;
    bool waiting = true;
    
    char BLE_START_ERROR[] = "BLE Start() Error";
    char STR_CYBLE_ERROR_OK[] = "BLE Advertise Successful";
    
    CYBLE_API_RESULT_T apiResult;
    //---------------------------//
    
     CyGlobalIntEnable;   /* Enable global interrupts */

    
    //------ LCD Setup ------//   
    
    rst0_m_Write(1u);
    
    begin(RA8875_800x480);
    displayOn(true);
    GPIOX(true);      // Enable TFT - display enable tied to GPIOX
    
    PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight  
    PWM1out(255);
    
    LCD_int_Write(1u);
    touchEnable(true);   
    
    //----- Color Demo -----//
    
    fillScreen(RA8875_WHITE);    
    CyDelay(500);
    fillScreen(RA8875_RED);
    CyDelay(500);
    fillScreen(RA8875_YELLOW);
    CyDelay(500);
    fillScreen(RA8875_GREEN);
    CyDelay(500);
    fillScreen(RA8875_BLUE);
    CyDelay(500);
    fillScreen(RA8875_CYAN);
    CyDelay(500);
    fillScreen(RA8875_MAGENTA);
    CyDelay(500);
    fillScreen(RA8875_BLACK);
    
    CyDelay(3000);
    
    // Try some GFX acceleration!
      drawCircle(100, 100, 50, RA8875_BLACK);
      fillCircle(100, 100, 49, RA8875_GREEN);
      
      fillRect(11, 11, 398, 198, RA8875_BLUE);
      drawRect(10, 10, 400, 200, RA8875_GREEN);
      drawPixel(10,10,RA8875_BLACK);
      drawPixel(11,11,RA8875_BLACK);
      drawLine(10, 10, 200, 100, RA8875_RED);
      drawTriangle(200, 15, 250, 100, 150, 125, RA8875_BLACK);
      fillTriangle(200, 16, 249, 99, 151, 124, RA8875_YELLOW);
      drawEllipse(300, 100, 100, 40, RA8875_BLACK);
      fillEllipse(300, 100, 98, 38, RA8875_GREEN);
      // Argument 5 (curvePart) is a 2-bit value to control each corner (select 0, 1, 2, or 3)
      drawCurve(50, 100, 80, 40, 2, RA8875_BLACK);  
      fillCurve(50, 100, 78, 38, 2, RA8875_WHITE);
        
    //--- Welcome Screen ---//
    CyDelay(10000);
    PWM1out(0);
    fillScreen(RA8875_WHITE);
    
    
    for (int i = 0; i < 256; i++) {
        PWM1out(i);
        CyDelay(5);
    }

    textMode();
    fillRect(75,85,370,100,RA8875_RED);
    textSetCursor(100, 100);
    textEnlarge(1);
    textTransparent(RA8875_WHITE);
    textWrite(welcome1,strlen(welcome1)); 
    
    textEnlarge(0);
    textSetCursor(100, 200);
    textTransparent(RA8875_BLACK);
    textWrite(welcome2,strlen(welcome2)); 
    textSetCursor(100, 250);
    textWrite(welcome3,strlen(welcome3)); 
    
    textSetCursor(100, 350);
    textTransparent(RA8875_BLUE);
    textWrite(ble,strlen(ble));    
    
    //CyDelay(1000);
    touchRead(&x, &y);
    CyDelay(10);
    while ( waiting )  {
        //if (LCD_int_Read() == 0u) {
            if ( touched() ) {
                LED_GREEN_Write(0u);
                touchRead(&x, &y);
                waiting = false;
            }
        //}
    }
    
    
    
    //----- Temp Screen -----//
    
    
    
    //------ BLE Setup ------//
    
    // Start
    apiResult = CyBle_Start(StackEventHandler);
    if(apiResult != 0x00u)
    {
        /* BLE stack initialization failed, check your configuration */
//        fillScreen(RA8875_RED);
//        textWrite(BLE_START_ERROR, strlen(BLE_START_ERROR));
    }
    
    // Advertise
    CyBle_ProcessEvents();
    apiResult = CyBle_GappStartAdvertisement(0x00u);
    if (apiResult == CYBLE_ERROR_OK) {
//        textWrite(STR_CYBLE_ERROR_OK, strlen(STR_CYBLE_ERROR_OK));
    }
    
  

    
    

    CyBle_Start( StackEventHandler );
    for(;;)
    {
        /* Place your application code here */
        LED_BLUE_Write(0u);  
        CyDelay(1000);
        //for(int i=0;i<1000;i++);
        LED_BLUE_Write(1u);
        //for(int i=0;i<1000;i++);
        CyDelay(1000);
        
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
            
/* [] END OF FILE */

#include <device.h>
#include "gfx.h"

int main()
{
    font_t font1, font2;
    coord_t swidth, sheight;
    gdispImage image;

    // Initialize the uGFX library
    gfxInit();
    
    // Change the display orientation
    gdispSetOrientation(GDISP_ROTATE_LANDSCAPE);
    
    // Some misc stuff
    swidth = gdispGetWidth();
    sheight = gdispGetHeight();

    // Prepare the resources
    font1 = gdispOpenFont("DejaVuSans16_aa");
    font2 = gdispOpenFont("DejaVuSans32_aa");
    gdispImageOpenFile(&image, "ugfx_150x50_white.bmp");
    
    // Write some text
    gdispFillStringBox(5, 5, swidth, 50, "Hello PSoC 5 LP!", font1, Black, White, justifyLeft);
    gdispFillStringBox(5, 55, swidth, 50, "Kerning: AVAVIPWA", font2, Black, White, justifyLeft);
    
    // Draw some image
    gdispImageDraw(&image, 5, 180, 150, 50, 0, 0);
    
    // Draw some random shapes
    gdispFillArea(180, 120, 40, 30, Red);
    gdispFillArea(210, 160, 90, 50, Lime);
    gdispDrawCircle(225, 155, 25, Green);
    
    // Get bored
    while (1) {
        gfxSleepMilliseconds(100);
    }

    return 0;
}

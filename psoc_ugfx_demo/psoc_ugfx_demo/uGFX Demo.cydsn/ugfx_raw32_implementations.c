#include <device.h>
#include "gfx.h"

void raw32Init(void)
{
    // Initialize the systick components
    Systick_Timer_Start();
    Systick_Counter_Start();
}

systemticks_t gfxSystemTicks(void)
{
    // We use a counter with a 1kHz clock source
	return Systick_Counter_ReadCounter();
}
 
systemticks_t gfxMillisecondsToTicks(delaytime_t ms)
{
    // We use a counter with a 1kHz clock source
	return ms;
}

/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

/*
 * This board file uses the SPIM block of the PSoC 5LP platform to
 * interface an ILI9341 display via SPI.
 * The SPIM block requires the following configuration:
 *    + Data bits = 8
 *    + CPHA = 0
 *    + CPOL = 0
 *    + Shift direction = MSB first
 *    + Enable high-speed mode = true
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H
    
#include <device.h>

static GFXINLINE void init_board(GDisplay* g)
{
    // We are not using multiple displays
    g->board = 0;

    // SPI
    LCD_SPI_Init();
    LCD_SPI_Enable(); 
    LCD_SPI_Start();
}

static GFXINLINE void post_init_board(GDisplay* g)
{
	(void)g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state)
{
	(void)g;
    
    if (state) {
        LCD_RST_Write(0);
    } else {
        LCD_RST_Write(1);
    }
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent)
{
	(void)g;
	(void)percent;
}

static GFXINLINE void acquire_bus(GDisplay* g)
{
	(void)g;
}

static GFXINLINE void release_bus(GDisplay* g)
{
	(void)g;
}

static GFXINLINE void write_index(GDisplay* g, uint16_t index)
{
	(void)g;
    
    LCD_DC_Write(0);
    LCD_SPI_WriteTxData(index);
}

static GFXINLINE void write_data(GDisplay* g, uint16_t data)
{
	(void)g;
    
    LCD_DC_Write(1);
    LCD_SPI_WriteTxData(data);
}

static GFXINLINE void setreadmode(GDisplay* g)
{
	(void)g;
}

static GFXINLINE void setwritemode(GDisplay* g)
{
	(void)g;
}

static GFXINLINE uint16_t read_data(GDisplay* g)
{
	(void)g;
    
	return LCD_SPI_ReadRxData();
}

#endif /* _GDISP_LLD_BOARD_H */

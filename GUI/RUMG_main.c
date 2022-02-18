#include "main.h"
#include "cmsis_os.h"
#include "stm32_adafruit_lcd.h"
#include "stm32_adafruit_ts.h"
#include "ili9488.h" //just for width and height
#include "fonts.h"

void DrawBase(void){
	//fill the background
	BSP_LCD_SetTextColor(MAIN_BGND);
	BSP_LCD_FillRect(0, 0, ILI9488_LCD_PIXEL_HEIGHT,  ILI9488_LCD_PIXEL_WIDTH);
	BSP_LCD_SetTextColor(WHITE_COLOR);
	//draw horizontal line
	BSP_LCD_DrawHLine((ILI9488_LCD_PIXEL_HEIGHT - 460)/2, ILI9488_LCD_PIXEL_WIDTH - 220, 460);
	BSP_LCD_DrawHLine((ILI9488_LCD_PIXEL_HEIGHT - 460)/2, ILI9488_LCD_PIXEL_WIDTH - 220 + 1, 460);
}


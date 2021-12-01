#include "main.h"
#include "cmsis_os.h"
#include "stm32_adafruit_lcd.h"
#include "stm32_adafruit_ts.h"
#include "ili9488.h" //just for width and height
#include "fonts.h"

TS_StateTypeDef TS_state;

uint8_t sst[5] = {'a', 'b', 'c', 'd', 'e'};

/*
		The main function
*/
void GUI(void){
	sst[4]++;
	BSP_LCD_DisplayStringAt(0, 0, sst, LEFT_MODE);	
  BSP_TS_GetState(&TS_state);
}

void InitGUI(void){
	BSP_LCD_Init();	
	BSP_TS_Init(ILI9488_LCD_PIXEL_WIDTH,  ILI9488_LCD_PIXEL_HEIGHT);
	BSP_LCD_SetTextColor(0x0000);
	//BSP_LCD_FillRect(0, 0, ILI9488_LCD_PIXEL_HEIGHT,  ILI9488_LCD_PIXEL_WIDTH);
	BSP_LCD_SetBackColor(0x0000);
	BSP_LCD_SetTextColor(0xffff);
	//BSP_LCD_SetFont(&Font24);	
	BSP_LCD_DisplayStringAt(0, 0, sst, LEFT_MODE);	
	DrawTheBase();
}


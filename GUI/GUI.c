#include "main.h"
#include "cmsis_os.h"
#include "stm32_adafruit_lcd.h"
#include "stm32_adafruit_ts.h"
#include "ili9488.h" //just for width and height
#include "fonts.h"

TS_StateTypeDef TS_state;

/*
		The main function
*/
void GUI(void){
  BSP_TS_GetState(&TS_state);
}

extern sFONT RuFont6;


void InitGUI(void){
	BSP_LCD_Init();	
	BSP_TS_Init(ILI9488_LCD_PIXEL_WIDTH,  ILI9488_LCD_PIXEL_HEIGHT);
	DrawTheBase();
}


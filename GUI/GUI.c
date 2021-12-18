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
	//sst[4]++;
	//BSP_LCD_DisplayStringAt(0, 0, sst, LEFT_MODE);	
  BSP_TS_GetState(&TS_state);
}

extern sFONT RuFont6;



void InitGUI(void){
	BSP_LCD_Init();	
	BSP_TS_Init(ILI9488_LCD_PIXEL_WIDTH,  ILI9488_LCD_PIXEL_HEIGHT);
	//BSP_LCD_SetTextColor(0x0000);
	//BSP_LCD_FillRect(0, 0, ILI9488_LCD_PIXEL_HEIGHT,  ILI9488_LCD_PIXEL_WIDTH);
	//BSP_LCD_SetBackColor(0x0000);
	//BSP_LCD_SetTextColor(0xffff);
	//BSP_LCD_SetFont(&Font24);	
	uint16_t byte = 0;
	uint8_t bit = 0;
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t column = 0;
	
	uint16_t param1 = 4;
	
	while(1){
		
	byte = 1135;
	bit = 0;
	x = 0;
	y = 0;
	column = 0;
	//for(uint16_t counter = 0; counter < 18176; counter++){
	for(uint16_t counter = 9000; counter < 18176; counter++){
			if((RuFont6.table[byte] & (0x80 >> bit)) > 0x00)
				BSP_LCD_DrawPixel(x, y, BLACK_COLOR);
			else
				BSP_LCD_DrawPixel(x, y, WHITE_COLOR);
			
			if(bit < 7) bit++; else{
				bit = 0;
				byte ++;
			}	
			
			if(x < (param1 + column * param1)) x++; else{
				x = column * param1;
				if(y < 320) y++; else{
					y = 0;
					column ++;
				}
			}
		}
	
		if(param1 < 20) param1++; else{
			param1 = 4;
		}
	}
	
	DrawTheBase();
}


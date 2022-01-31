#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "main.h"

#include "lcd.h"

/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"

extern LCD_DrawPropTypeDef DrawProp;

char str[6];

void DrawLog(void){
	FillBackground(MAIN_BGND);
	BSP_LCD_SetFont(&Font24);
	DrawProp.BackColor = MAIN_BGND;
	DrawProp.TextColor = WHITE_COLOR;
	//Print(UI_INDENT, UI_SPACE, "Password:", &Font24);
	Print(10, 10, "Erasing log", &Font24);
	EraseWholeLog();
	Print(10, 10, "Done        ", &Font24);
	Print(10, 10, "Writing", &Font24);
	
	str[0] = 0x20;
	str[1] = 0x30;
	str[2] = 0x30;
	str[3] = 0x30;
	str[4] = 0x30;
	str[5] = 0x00;
	for(uint16_t i = 0; i < 5; i++){
		LogStoreNext();
		str[4] = 0x30 + i % 10;
		str[3] = 0x30+ (i / 10) % 10;
		str[2] = 0x30+ (i / 100) % 10;
		str[1] = 0x30+ (i / 1000) % 10;
		Print(200, 10, str, &Font24);
	}
}

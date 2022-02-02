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
uint32_t my_min, my_max;
extern uint32_t log_memory_buf [LOG_ENTRY_SIZE];

void DrawLog(void){
	FillBackground(MAIN_BGND);
	BSP_LCD_SetFont(&Font24);
	DrawProp.BackColor = MAIN_BGND;
	DrawProp.TextColor = WHITE_COLOR;
	//Print(UI_INDENT, UI_SPACE, "Password:", &Font24);
	Print(10, 10, "Erasing log", &Font24);
	//EraseWholeLog();
	Print(10, 10, "Done        ", &Font24);
	Print(10, 10, "Erasing", &Font24);
	
	str[0] = 0x20;
	str[1] = 0x30;
	str[2] = 0x30;
	str[3] = 0x30;
	str[4] = 0x30;
	str[5] = 0x00;
	
	
	LOG_EraseWhole();
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + 0, 0x01020304);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + 4, 0x01020304);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + 8, 0x01020304);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + 12, 0x01020304);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + 16, 0x01020304);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + 20, 0x01020304);
	HAL_FLASH_Lock();
	LOG_ReadFlash(LOG_OFFSET, log_memory_buf, LOG_ENTRY_SIZE); 
	
	
	LOG_FindMinMaxNum(&my_min, &my_max);
	if(LOG_CheckIfEmpty()) Print(10, 10, "Empty   ", &Font24); else Print(10, 10, "Not empty", &Font24);
	/*HAL_FLASH_Unlock();
		for(uint32_t i = 0; i < (LOG_AREA_SIZE * PAGESIZE / 4); i++){
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + 4 * i, 0x01020304);		
			str[4] = 0x30 + i % 10;
			str[3] = 0x30+ (i / 10) % 10;
			str[2] = 0x30+ (i / 100) % 10;
			str[1] = 0x30+ (i / 1000) % 10;
		Print(200, 10, str, &Font24);
		}
	HAL_FLASH_Lock();*/
	LOG_FindMinMaxNum(&my_min, &my_max);
	if(LOG_CheckIfEmpty()) Print(10, 10, "Empty    ", &Font24); else Print(10, 10, "Not empty", &Font24);
	LOG_EraseWhole();
	LOG_FindMinMaxNum(&my_min, &my_max);
	if(LOG_CheckIfEmpty()) Print(10, 10, "Empty    ", &Font24); else Print(10, 10, "Not empty", &Font24);
}

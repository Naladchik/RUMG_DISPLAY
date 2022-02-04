#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "main.h"

#include "lcd.h"

/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"

extern LCD_DrawPropTypeDef DrawProp;

uint32_t my_min, my_max, my_addr;
uint8_t is_uniq;
extern uint32_t log_memory_buf [LOG_ENTRY_SIZE];

void DrawLog(void){
	FillBackground(MAIN_BGND);
	BSP_LCD_SetFont(&Font24);
	DrawProp.BackColor = MAIN_BGND;
	DrawProp.TextColor = WHITE_COLOR;
	Print(UI_INDENT, UI_SPACE, "Password:", &Font24);
}
	

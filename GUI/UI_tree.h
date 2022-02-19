#ifndef UI_TREE
#define UI_TREE
#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "UI_tree.h"
#include "main.h"

#include "lcd.h"
//#include "bmp.h"

/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"

#define WINDOW_MAIN																		0
#define WINDOW_MAIN_MENU												1
#define WINDOW_SETTINGS 													2
#define WINDOW_LOG																		3
#define WINDOW_PLOT    														  4
#define WINDOW_LOG_PASSWORD								5

#define UI_INDENT		160	
#define UI_SPACE		80
#define UI_INTERVAL 2 * Font24.Height
#define UI_T_WIDTH	200
#define UI_T_HEIGHT	40

#define UI_LEFT_GAS_X 							60
#define UI_RIGHT_GAS_X  					389
#define UI_GAS_Y												120
#define UI_GAS_HALF_WIDTH			50
#define UI_GAS_HIGHT								170

#define FLOW_REF_X 160
#define FLOW_REF_Y 170


void Print(uint16_t Xpos, uint16_t Ypos, char* str, sFONT *pFonts);
void DrawService(void);
void UI_logic(void);
void DoTouchScreen(void);

#endif

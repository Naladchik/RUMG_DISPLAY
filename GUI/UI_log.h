#ifndef UI_LOG
#define UI_LOG
#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "main.h"

#include "lcd.h"
//#include "bmp.h"

#define KEYPAD_Y						 50
#define BUTTON_W						 80
#define BUTTON_H						 66

/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"
void DrawLog(void);
uint8_t DrawLogPassword(void);
void LOG_Display(uint32_t addr);
void LOG_ReplaceHeader1(char* st);
void LOG_ReplaceHeader2(char* st);
void LOG_ReplaceHeader3(char* st);
void ConvertInteger32ToStr(char* str, const uint32_t integer);
void ConvertFloatToStr(char* str, const float value);
void LOG_Renew(void);
void DrawKeyPad(void);
uint8_t PasswordCheck(TS_TypeDef *touch);
#endif

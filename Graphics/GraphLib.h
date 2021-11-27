#ifndef GRAPH_LIB
#define GRAPH_LIB
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

void FillBackground(uint16_t color);
void DrawImage(const uint8_t *arr, uint16_t W, uint16_t H, uint16_t color, uint16_t X, uint16_t Y);
void DrawDigitB(uint16_t xx, uint16_t yy, uint8_t dig, uint16_t color);
void DrawCommaB(uint16_t xx, uint16_t yy, uint16_t color);
void DrawDigitS(uint16_t xx, uint16_t yy, uint8_t dig, uint16_t color);
void DrawDigitS_no_bgn(uint16_t xx, uint16_t yy, uint8_t dig, uint16_t color);
void DrawCommaS(uint16_t xx, uint16_t yy, uint16_t color);
void PrintNum(uint16_t Xpos, uint16_t Ypos, uint16_t num);
#endif

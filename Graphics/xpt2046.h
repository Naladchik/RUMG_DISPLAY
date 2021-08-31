#ifndef __XPT2046_H
#define __XPT2046_H
#include "stm32f1xx_hal.h"

#define T_X_OFFSET 	240
#define T_Y_OFFSET 	400
#define T_X_MAX 		3730
#define T_Y_MAX 		3730
#define T_X_COEFF   7.95 //(float)(T_X_MAX - T_X_OFFSET) / (float)DISPLAY_WIDTH;
#define T_Y_COEFF   12.0 //(float)(T_Y_MAX - T_Y_OFFSET) / (float)DISPLAY_HIGHT;

struct TouchStructType{ //Last unprocessed touch data
		uint16_t rawX;
		uint16_t rawY;
		uint16_t X;
		uint16_t Y;
		uint8_t Unprocessed:1;
};

void T_ReadTouch(struct TouchStructType* T_s);
#endif

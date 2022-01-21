#include "u8g.h"
#include "rus4x6.h"

/*Employs u8g library. Some source files was rudely edited.
The list of edits is below:
u8g_IIapi.c 420 commented
from 421 till the end is a new function
41 #include "stm32_adafruit_lcd.h"
*/

u8g_t ffont;

void RusFontTry(void){
	//u8g_SetVirtualScreenDimension(&ffont, 128, 64);
	//u8g_GetGlyph(&ffont, );
	u8g_SetFont(&ffont, u8g_font_7x13);
	u8g_DrawStr(&ffont, 20, 40, "Hello World.");
}

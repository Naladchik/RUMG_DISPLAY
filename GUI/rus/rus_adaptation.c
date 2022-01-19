#include "u8g.h"
#include "rus4x6.h"

u8g_t ffont;

void RusFontTry(void){

u8g_SetFont(&ffont, rus4x6);
u8g_DrawStr(&ffont, 20, 40, "Hello World.");

}

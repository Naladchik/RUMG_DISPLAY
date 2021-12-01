#include "main.h"
#include "cmsis_os.h"
#include "stm32_adafruit_lcd.h"
#include "stm32_adafruit_ts.h"
#include "ili9488.h" //just for width and height
#include "fonts.h"

void DrawTheBase(void){
	//fill the background
	BSP_LCD_SetTextColor(MAIN_BGND);
	BSP_LCD_FillRect(0, 0, ILI9488_LCD_PIXEL_HEIGHT,  ILI9488_LCD_PIXEL_WIDTH);
	BSP_LCD_SetTextColor(WHITE_COLOR);
	//draw horizontal line
	BSP_LCD_DrawHLine((ILI9488_LCD_PIXEL_HEIGHT - 460)/2, ILI9488_LCD_PIXEL_WIDTH - 220, 460);
	BSP_LCD_DrawHLine((ILI9488_LCD_PIXEL_HEIGHT - 460)/2, ILI9488_LCD_PIXEL_WIDTH - 220 + 1, 460);
	BSP_LCD_DrawBitmap();
	
	/*
	DrawImage(bal_stc, BAL_STC_W, BAL_STC_H, WHITE_COLOR, 5, 5);
	DrawImage(concentrator, CONCENTRATOR_W, CONCENTRATOR_H, WHITE_COLOR, 390, 58);
	DrawImage(davlenie, DAVLENIE_W, DAVLENIE_H, WHITE_COLOR, 5, 76);
	DrawImage(vyhodnoe, VYHODNOE_W, VYHODNOE_H, WHITE_COLOR, 201, 29);
	DrawImage(mpa3, MPA3_W, MPA3_H, WHITE_COLOR, 288, 79);
	DrawImage(mpa2, MPA2_W, MPA2_H, WHITE_COLOR, 442, 84);
	DrawImage(mpa1, MPA1_W, VYHODNOE_H, WHITE_COLOR, 58, 253);
	DrawImage(mpa1, MPA1_W, MPA1_H, WHITE_COLOR, 388, 253);
	DrawImage(l_min, L_MIN_W, L_MIN_H, WHITE_COLOR, FLOW_REF_X + 123, FLOW_REF_Y + 33);  
	DrawImage(lev_coll, LEV_COLL_W, LEV_COLL_H, WHITE_COLOR, 22, 269);
	DrawImage(prav_coll, PRAV_COLL_W, PRAV_COLL_H, WHITE_COLOR, 352, 269);
	DrawRoundScale(LEFT_ROUND_X, ROUNDS_Y, ROUND_RADIUS);
	DrawRoundScale(RIGHT_ROUND_X, ROUNDS_Y, ROUND_RADIUS);
	DrawAlarmSmall(2,260);
	DrawAlarmSmall(325,260);
	DrawImage(lora_signal_pict, LORA_SIGNAL_W, LORA_SIGNAL_H, WHITE_COLOR, 345, 5);*/
}


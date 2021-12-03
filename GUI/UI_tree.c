#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "main.h"
#include "lcd.h"
//#include "bmp.h"
/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"

//struct TouchStructType T_struct; //Last unprocessed touch data
extern TS_DrvTypeDef  *ts_drv;

TS_TypeDef ts;

uint8_t UI_item = MAIN_WIND;

extern LCD_DrawPropTypeDef DrawProp;
extern TypeAlarm Alarm;
extern uint8_t SilentTimer;

extern uint8_t SwitchGasRequest;
extern uint8_t ActiveGasRequested;

extern uint8_t ts_bz;


void Print(uint16_t Xpos, uint16_t Ypos, char* str, sFONT *pFonts){
	uint8_t  indx = 0;
	while((str[indx] != '\0') && indx < 20){
		BSP_LCD_DisplayChar(Xpos + pFonts->Width * indx, Ypos, str[indx]);
		indx++;		
	}
}

void DrawService(void){
	FillBackground(MAIN_BGND);
	BSP_LCD_SetFont(&Font24);
	DrawProp.BackColor = MAIN_BGND;
	DrawProp.TextColor = WHITE_COLOR;
	Print(UI_INDENT, UI_SPACE, "Settings", &Font24);
	Print(UI_INDENT, UI_SPACE + UI_INTERVAL, "  Log", &Font24);
	Print(UI_INDENT, UI_SPACE + 2 * UI_INTERVAL, "  Exit", &Font24);
}

void UI_logic(void){
		switch(UI_item){		
			case(MAIN_WIND): DrawMainWindow(); break;
			case(MAIN_MENU_WIND): break;
			case(SETTINGS_WIND):break;
			case(LOG_WIND):break;
			case(PLOT_WIND):DrawPlot(); break;
			default: break;
		}
		
		DoTouchScreen();
		
		if(ts.up){//touch processing
		switch(UI_item){
			case(MAIN_WIND):
			if((Alarm.ConcentratorMax)||(Alarm.CylindersEmpty)||(Alarm.LineMax)||(Alarm.LineMin))SilentTimer = ALRM_PAUSE;
			{	
			//menu
				if((ts.x >= 440) && (ts.y <= 50)){
					DrawService();
					UI_item = MAIN_MENU_WIND;
				}
				//gas left - right switching
				if((ts.y >= UI_GAS_Y) && (ts.y <= (UI_GAS_Y + UI_GAS_HIGHT))){
					if((ts.x >= UI_LEFT_GAS_X - UI_GAS_HALF_WIDTH) && (ts.x <= (UI_LEFT_GAS_X + UI_GAS_HALF_WIDTH))){
						SwitchGasRequest = 1;
						ActiveGasRequested = LEFT;
					}
					if((ts.x >= UI_RIGHT_GAS_X - UI_GAS_HALF_WIDTH) && (ts.x <= (UI_RIGHT_GAS_X + UI_GAS_HALF_WIDTH))){
						SwitchGasRequest = 1;
						ActiveGasRequested = RIGHT;
					}
				}
				//flow plot
				if(FLOW_SENSOR){
				if((ts.x >= FLOW_REF_X) && (ts.x <= FLOW_REF_X + 140)
					&& (ts.y >= FLOW_REF_Y) && (ts.y <= FLOW_REF_Y + 50)){
					UI_item = PLOT_WIND;
					FillBackground(WHITE_COLOR);
				}
			}
			}
				break;
			case(MAIN_MENU_WIND):
				if((ts.x >= UI_INDENT) && (ts.x <= (UI_INDENT + 200))){
					if((ts.y >= UI_SPACE) && (ts.y <= (UI_SPACE + UI_INTERVAL))){
						DrawSettings();
						UI_item = SETTINGS_WIND;
					}
					if((ts.y >= (UI_SPACE + UI_INTERVAL)) && (ts.y <= (UI_SPACE + 2 * UI_INTERVAL))){
						DrawLog();
						UI_item = LOG_WIND;
					}
					if((ts.y >= (UI_SPACE + 2 * UI_INTERVAL)) && (ts.y <= (UI_SPACE + 3 * UI_INTERVAL))){
						DrawTheBase();
						UI_item = MAIN_WIND;
					}
				}
				break;
			case(SETTINGS_WIND):
						DrawTheBase();
						UI_item = MAIN_WIND;
						break;
			case(LOG_WIND):
						DrawTheBase();
						UI_item = MAIN_WIND;
						break;
			case(PLOT_WIND):
						DrawTheBase();
						UI_item = MAIN_WIND;
						break;
			default: break;}			
			if(!(ts_drv->DetectTouch(0)) )ts.up = 0;			
		}
}


void DoTouchScreen(void){
		SPI2->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
		if(ts.up == 0){
			if(ts_drv->DetectTouch(0)){
				ts_drv->GetXY(0, &ts.x, &ts.y);
				if(ts.x > TS_X_MIN) ts.x -= TS_X_MIN; else ts.x = 0;
				ts.x = (uint16_t) ( ((float) ts.x) * (((float) DISPLAY_WIDTH) / ((float) (TS_X_MAX - TS_X_MIN))) );
				if(ts.y > TS_Y_MIN) ts.y -= TS_Y_MIN; else ts.y = 0;
				ts.y = (uint16_t) ( ((float) ts.y) * (((float) DISPLAY_HIGHT) / ((float) (TS_Y_MAX - TS_Y_MIN))) );
				ts_bz = 200;
				ts.up = 1;
			}
		}
		SPI2->CR1 &= ~(SPI_CR1_BR_2 | SPI_CR1_BR_1);
}

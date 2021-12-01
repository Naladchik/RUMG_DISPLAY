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
uint8_t UI_item = MAIN_WIND;

extern LCD_DrawPropTypeDef DrawProp;
extern TypeAlarm Alarm;
extern uint8_t SilentTimer;

//uint8_t SwitchGasRequest = 0;
//uint8_t ActiveGasRequested = LEFT;


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
		
		/*if(T_struct.Unprocessed){//touch processing
		switch(UI_item){		
			case(MAIN_WIND):
			if((Alarm.ConcentratorMax)||(Alarm.CylindersEmpty)||(Alarm.LineMax)||(Alarm.LineMin))SilentTimer = ALRM_PAUSE;
			{	
			//menu
				if((T_struct.X >= 440) && (T_struct.Y <= 50)){
					DrawService();
					UI_item = MAIN_MENU_WIND;
				}
				//gas left - right switching
				if((T_struct.Y >= UI_GAS_Y) && (T_struct.Y <= (UI_GAS_Y + UI_GAS_HIGHT))){
					if((T_struct.X >= UI_LEFT_GAS_X - UI_GAS_HALF_WIDTH) && (T_struct.X <= (UI_LEFT_GAS_X + UI_GAS_HALF_WIDTH))){
						SwitchGasRequest = 1;
						ActiveGasRequested = LEFT;
					}
					if((T_struct.X >= UI_RIGHT_GAS_X - UI_GAS_HALF_WIDTH) && (T_struct.X <= (UI_RIGHT_GAS_X + UI_GAS_HALF_WIDTH))){
						SwitchGasRequest = 1;
						ActiveGasRequested = RIGHT;
					}
				}
				//flow plot
				if((T_struct.X >= FLOW_REF_X) && (T_struct.X <= FLOW_REF_X + 140)
					&& (T_struct.Y >= FLOW_REF_Y) && (T_struct.Y <= FLOW_REF_Y + 50)){
					UI_item = PLOT_WIND;
					FillBackground(WHITE_COLOR);
				}
			}
				break;
			case(MAIN_MENU_WIND):
				if((T_struct.X >= UI_INDENT) && (T_struct.X <= (UI_INDENT + 200))){
					if((T_struct.Y >= UI_SPACE) && (T_struct.Y <= (UI_SPACE + UI_INTERVAL))){
						DrawSettings();
						UI_item = SETTINGS_WIND;
					}
					if((T_struct.Y >= (UI_SPACE + UI_INTERVAL)) && (T_struct.Y <= (UI_SPACE + 2 * UI_INTERVAL))){
						DrawLog();
						UI_item = LOG_WIND;
					}
					if((T_struct.Y >= (UI_SPACE + 2 * UI_INTERVAL)) && (T_struct.Y <= (UI_SPACE + 3 * UI_INTERVAL))){
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
			T_struct.Unprocessed = 0;			
		}
		T_Read_ifIRQ(&T_struct);*/
}

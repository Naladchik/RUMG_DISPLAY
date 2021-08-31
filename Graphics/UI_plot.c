#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "main.h"

#include "lcd.h"

/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"

extern LCD_DrawPropTypeDef DrawProp;
extern int16_t FlowArray[F_ARR_SIZE];
extern uint16_t flow_arr_index;
int16_t OldFlowArray[F_ARR_SIZE];
int16_t WorkFlowArray[F_ARR_SIZE];
uint16_t work_flow_arr_index;
uint16_t old_work_flow_arr_index;


void DrawPlot(void){	
	float scale;
	uint16_t previous_val, current_val;
	uint8_t difference = 0;
	//make snap shot
	for(uint16_t i = 0; i < F_ARR_SIZE; i++){
		WorkFlowArray[i] = FlowArray[i];
	}
	
	work_flow_arr_index = flow_arr_index;
	
	//calculate scale
	scale =  (float)DISPLAY_HIGHT / (float)(2000);
	
	//erase old graph
	/*for(uint16_t i = 0; i < F_ARR_SIZE; i++){
		if(i <= old_work_flow_arr_index){
			if(WorkFlowArray[work_flow_arr_index - i] != OldFlowArray[old_work_flow_arr_index - i])
				ili9488_WritePixel(i, DISPLAY_HIGHT - (uint16_t)((float)OldFlowArray[old_work_flow_arr_index - i] * scale), WHITE_COLOR);
		}
		else{
				if(WorkFlowArray[F_ARR_SIZE  + work_flow_arr_index - i] != OldFlowArray[F_ARR_SIZE  + old_work_flow_arr_index - i])
				ili9488_WritePixel(i, DISPLAY_HIGHT - (uint16_t)((float)OldFlowArray[F_ARR_SIZE + old_work_flow_arr_index - i] * scale), WHITE_COLOR);
		}
	}*/
	for(uint16_t i = 0; i < (F_ARR_SIZE - 1); i++){
		difference = 0;		
		if(old_work_flow_arr_index != work_flow_arr_index) difference = 1;
		//i point
		if(i <= old_work_flow_arr_index){
			//if(WorkFlowArray[work_flow_arr_index - i] != OldFlowArray[old_work_flow_arr_index - i]) difference = 1;
			previous_val = DISPLAY_HIGHT - (uint16_t)(float)OldFlowArray[old_work_flow_arr_index - i] * scale;
		}else{
			//if(WorkFlowArray[F_ARR_SIZE  + work_flow_arr_index - i] != OldFlowArray[F_ARR_SIZE  + old_work_flow_arr_index - i]) difference = 1;
			previous_val = DISPLAY_HIGHT - (uint16_t)(float)OldFlowArray[F_ARR_SIZE + old_work_flow_arr_index - i] * scale;
		}
		//i + 1 point
		if((i + 1) <= old_work_flow_arr_index){
			//if(WorkFlowArray[work_flow_arr_index - i - 1] != OldFlowArray[old_work_flow_arr_index - i - 1]) difference = 1;
			current_val = DISPLAY_HIGHT - (uint16_t)(float)OldFlowArray[old_work_flow_arr_index - i - 1] * scale;
		}else{
			//if(WorkFlowArray[F_ARR_SIZE  + work_flow_arr_index - i - 1] != OldFlowArray[F_ARR_SIZE  + old_work_flow_arr_index - i - 1]) difference = 1;
			current_val = DISPLAY_HIGHT - (uint16_t)(float)OldFlowArray[F_ARR_SIZE + old_work_flow_arr_index - i - 1] * scale;
		}
		
		if(difference){
			if(current_val > previous_val)
				ili9488_DrawVLine(WHITE_COLOR, i, previous_val, current_val - previous_val + 1);
			else
				ili9488_DrawVLine(WHITE_COLOR, i, current_val, previous_val - current_val + 1);
		}
	}
	
	//plot new graph
	/*for(uint16_t i = 0; i < F_ARR_SIZE; i++){
		if(i <= work_flow_arr_index)
			ili9488_WritePixel(i, DISPLAY_HIGHT - (uint16_t)((float)WorkFlowArray[work_flow_arr_index - i] * scale), BLACK_COLOR);
		else
			ili9488_WritePixel(i, DISPLAY_HIGHT - (uint16_t)((float)WorkFlowArray[F_ARR_SIZE + work_flow_arr_index - i] * scale), BLACK_COLOR);
	}*/
	
	for(uint16_t i = 0; i < (F_ARR_SIZE - 1); i++){
		if(i <= work_flow_arr_index)
			previous_val = DISPLAY_HIGHT - (uint16_t)(float)WorkFlowArray[work_flow_arr_index - i] * scale;
		else
			previous_val = DISPLAY_HIGHT - (uint16_t)(float)WorkFlowArray[F_ARR_SIZE + work_flow_arr_index - i] * scale;
		
		if((i + 1) <= work_flow_arr_index)
			current_val = DISPLAY_HIGHT - (uint16_t)(float)WorkFlowArray[work_flow_arr_index - i - 1] * scale;
		else
			current_val = DISPLAY_HIGHT - (uint16_t)(float)WorkFlowArray[F_ARR_SIZE + work_flow_arr_index - i - 1] * scale;
		if(current_val > previous_val)
			ili9488_DrawVLine(BLACK_COLOR, i, previous_val, current_val - previous_val + 1);
		else
			ili9488_DrawVLine(BLACK_COLOR, i, current_val, previous_val - current_val + 1);
	}
	
	//store the array
	for(uint16_t i = 0; i < F_ARR_SIZE; i++){
		OldFlowArray[i] = WorkFlowArray[i];
	}
	old_work_flow_arr_index = work_flow_arr_index;
}



#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "main.h"
#include "lcd.h"
#include "u8g.h"
#include "lcd.h"
#include "string.h"
#include "stm32_adafruit_lcd.h"

/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"
extern const u8g_fntpgm_uint8_t rus10x20[2863];
extern LCD_DrawPropTypeDef DrawProp;

TypeVolt PhValues_log;

uint32_t my_min, my_max, my_addr;
uint32_t LOG_current_num; //current number of log entry
uint8_t is_uniq;
extern uint32_t log_memory_buf [LOG_ENTRY_SIZE];

extern uint16_t rus_font_color;
extern int32_t EpochTime;

uint32_t read_buf [LOG_ENTRY_SIZE];

char string_buf[40];

const char no_logs[]  = {157, 181, 130, 32, 183, 176, 191, 184, 129, 181, 185 ,0}; //Нет записей (autogenerated by ru_str_converter.py script)
const char header1[] = {151, 176, 191, 184, 129, 140, 32, 189, 190, 188, 181, 128, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,165 ,0}; //Запись номер 0000000000.       Х (autogenerated by ru_str_converter.py script)
//const char header2[] = {156, 176, 186, 129, 184, 188, 176, 187, 140, 189, 139, 185, 32, 189, 190, 188, 181, 128, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46 ,0}; //Максимальный номер 0000000000. (autogenerated by ru_str_converter.py script)
//const char header3[] = {156, 184, 189, 184, 188, 176, 187, 140, 189, 139, 185, 32, 189, 190, 188, 181, 128, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46 ,0}; //Минимальный номер 0000000000. (autogenerated by ru_str_converter.py script)
const char alrm1[] = {145, 176, 130, 176, 128, 181, 143, 32, 128, 176, 183, 128, 143, 182, 181, 189, 176, 33 ,0}; //Батарея разряжена! (autogenerated by ru_str_converter.py script)
const char alrm2[] = {145, 176, 130, 176, 128, 181, 143, 32, 178, 32, 191, 190, 128, 143, 180, 186, 181, 46 ,0}; //Батарея в порядке. (autogenerated by ru_str_converter.py script)
const char alrm3[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 186, 190, 189, 134, 181, 189, 130, 128, 176, 130, 190, 128, 176, 47, 148, 140, 142, 176, 128, 176, 32, 191, 128, 181, 178, 139, 136, 181, 189, 190, 33 ,0}; //Давление концентратора/Дьюара превышено! (autogenerated by ru_str_converter.py script)
const char alrm4[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 186, 190, 189, 134, 181, 189, 130, 128, 176, 130, 190, 128, 176, 47, 148, 140, 142, 176, 128, 176, 32, 189, 181, 32, 191, 128, 181, 178, 139, 136, 181, 189, 190, 46 ,0}; //Давление концентратора/Дьюара не превышено. (autogenerated by ru_str_converter.py script)
const char alrm5[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 186, 190, 189, 134, 181, 189, 130, 128, 176, 130, 190, 128, 176, 47, 148, 140, 142, 176, 128, 176, 32, 189, 181, 180, 190, 129, 130, 176, 130, 190, 135, 189, 190, 33 ,0}; //Давление концентратора/Дьюара недостаточно! (autogenerated by ru_str_converter.py script)
const char alrm6[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 186, 190, 189, 134, 181, 189, 130, 128, 176, 130, 190, 128, 176, 47, 148, 140, 142, 176, 128, 176, 32, 178, 139, 136, 181, 32, 188, 184, 189, 184, 188, 131, 188, 176, 46 ,0}; //Давление концентратора/Дьюара выше минимума. (autogenerated by ru_str_converter.py script)
const char alrm7[] = {157, 131, 182, 189, 190, 32, 183, 176, 188, 181, 189, 184, 130, 140, 32, 177, 176, 187, 187, 190, 189, 139, 33 ,0}; //Нужно заменить баллоны! (autogenerated by ru_str_converter.py script)
const char alrm8[] = {147, 176, 183, 176, 32, 178, 32, 177, 176, 187, 187, 190, 189, 176, 133, 32, 181, 137, 181, 32, 180, 190, 129, 130, 176, 130, 190, 135, 189, 190, 46 ,0}; //Газа в баллонах ещё достаточно. (autogenerated by ru_str_converter.py script)
const char alrm9[] = {161, 184, 129, 130, 181, 188, 176, 32, 191, 181, 128, 181, 136, 187, 176, 32, 178, 32, 176, 178, 176, 128, 184, 185, 189, 139, 185, 32, 128, 181, 182, 184, 188, 33 ,0}; //Система перешла в аварийный режим! (autogenerated by ru_str_converter.py script)
const char alrm10[] = {161, 184, 129, 130, 181, 188, 176, 32, 178, 32, 136, 130, 176, 130, 189, 190, 188, 32, 128, 181, 182, 184, 188, 181, 46 ,0}; //Система в штатном режиме. (autogenerated by ru_str_converter.py script)
const char alrm11[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 32, 187, 184, 189, 184, 184, 32, 191, 128, 181, 178, 139, 136, 181, 189, 190, 33 ,0}; //Давление в линии превышено! (autogenerated by ru_str_converter.py script)
const char alrm12[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 32, 187, 184, 189, 184, 184, 32, 189, 181, 32, 191, 128, 181, 178, 139, 136, 181, 189, 190, 46 ,0}; //Давление в линии не превышено. (autogenerated by ru_str_converter.py script)
const char alrm13[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 32, 187, 184, 189, 184, 184, 32, 131, 191, 176, 187, 190, 32, 189, 184, 182, 181, 32, 191, 128, 181, 180, 181, 187, 176, 33 ,0}; //Давление в линии упало ниже предела! (autogenerated by ru_str_converter.py script)
const char alrm14[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 32, 187, 184, 189, 184, 184, 32, 178, 139, 136, 181, 32, 188, 184, 189, 184, 188, 131, 188, 176, 46 ,0}; //Давление в линии выше минимума. (autogenerated by ru_str_converter.py script)
const char alrm15[] = {173, 187, 181, 186, 130, 128, 184, 135, 181, 129, 186, 176, 143, 32, 129, 181, 130, 140, 32, 190, 130, 186, 187, 142, 135, 181, 189, 176, 33 ,0}; //Электрическая сеть отключена! (autogenerated by ru_str_converter.py script)
const char alrm16[] = {173, 187, 181, 186, 130, 128, 184, 135, 181, 129, 186, 176, 143, 32, 129, 181, 130, 140, 32, 191, 190, 180, 186, 187, 142, 135, 181, 189, 176, 46 ,0}; //Электрическая сеть подключена. (autogenerated by ru_str_converter.py script)
const char alrm17[] = {146, 186, 187, 142, 135, 181, 189, 184, 181, 32, 191, 190, 129, 187, 181, 32, 191, 190, 187, 189, 190, 179, 190, 32, 190, 130, 186, 187, 142, 135, 181, 189, 184, 143, 33 ,0}; //Включение после полного отключения! (autogenerated by ru_str_converter.py script)
const char stt1[] = {155, 181, 178, 139, 185, 32, 186, 187, 176, 191, 176, 189, 32, 190, 130, 186, 128, 139, 130, 44, 32, 191, 128, 176, 178, 139, 185, 32, 183, 176, 186, 128, 139, 130 , 46 ,0}; //Левый клапан открыт, правый закрыт. (autogenerated by ru_str_converter.py script)
const char stt2[] = {159, 128, 176, 178, 139, 185, 32, 186, 187, 176, 191, 176, 189, 32, 190, 130, 186, 128, 139, 130, 44, 32, 187, 181, 178, 139, 185, 32, 183, 176, 186, 128, 139, 130, 46 ,0}; //Правый клапан открыт, левый закрыт. (autogenerated by ru_str_converter.py script)
const char stt3[] = {158, 177, 176, 32, 186, 187, 176, 191, 176, 189, 176, 32, 183, 176, 186, 128, 139, 130, 139, 46 ,0}; //Оба клапана закрыты. (autogenerated by ru_str_converter.py script)
const char stt4[] = {158, 177, 176, 32, 186, 187, 176, 191, 176, 189, 176, 32, 176, 178, 176, 128, 184, 185, 189, 190, 32, 190, 130, 186, 128, 139, 130, 139, 33 ,0}; //Оба клапана аварийно открыты! (autogenerated by ru_str_converter.py script)
const char phv1[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 32, 187, 181, 178, 190, 188, 32, 191, 187, 181, 135, 181, 32, 48, 48, 48, 48, 48, 32, 177, 176, 128, 46 ,0}; //Давление в левом плече 00000 бар. (autogenerated by ru_str_converter.py script)
const char phv2[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 32, 191, 128, 176, 178, 190, 188, 32, 191, 187, 181, 135, 181, 32, 48, 48, 48, 48, 48, 32, 177, 176, 128, 46 ,0}; //Давление в правом плече 00000 бар. (autogenerated by ru_str_converter.py script)
const char phv3[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 32, 187, 184, 189, 184, 184, 32, 48, 48, 48, 48, 32, 177, 176, 128, 46 ,0}; //Давление в линии 0000 бар. (autogenerated by ru_str_converter.py script)
const char phv4[] = {148, 176, 178, 187, 181, 189, 184, 181, 32, 178, 189, 181, 136, 189, 181, 179, 190, 32, 184, 129, 130, 190, 135, 189, 184, 186, 176, 32, 48, 48, 48, 48, 32, 177, 176, 128, 46 ,0}; //Давление внешнего источника 0000 бар. (autogenerated by ru_str_converter.py script)
const char phv5[] = {157, 176, 191, 128, 143, 182, 181, 189, 184, 181, 32, 177, 187, 190, 186, 176, 32, 191, 184, 130, 176, 189, 184, 143, 32, 48, 48, 48, 48, 32, 146, 46 ,0}; //Напряжение блока питания 0000 В. (autogenerated by ru_str_converter.py script)
const char phv6[] = {157, 176, 191, 128, 143, 182, 181, 189, 184, 181, 32, 176, 186, 186, 131, 188, 131, 187, 143, 130, 190, 128, 176, 32, 48, 48, 48, 48, 32, 146, 46 ,0}; //Напряжение аккумулятора 0000 В. (autogenerated by ru_str_converter.py script)
	
	
u8g_t ffont;

void DrawLog(void){	
	u8g_SetFont(&ffont, rus10x20);
	rus_font_color = WHITE_COLOR;
	FillBackground(MAIN_BGND);
	uint32_t here_max, here_addr;
	if(LOG_FindMaxUnique(&here_max, &here_addr)){
		here_addr = LOG_FindEntry(LOG_current_num);
		LOG_Display(here_addr);
	}else{
		u8g_DrawStr(&ffont, 5, 15, no_logs);
	}	
}

uint8_t DrawLogPassword(void){
	FillBackground(MAIN_BGND);
	BSP_LCD_SetFont(&Font24);
	DrawProp.BackColor = MAIN_BGND;
	DrawProp.TextColor = WHITE_COLOR;
	Print(3, 3, "Password:", &Font24);
	return(0);
}

void LOG_Display(uint32_t addr){
	uint16_t n = 19; //line step in pixels
	uint16_t str_num = 1  ;
	LOG_ReadFlash(addr, read_buf, LOG_ENTRY_SIZE);
	
	strcpy(string_buf, header1);
	LOG_ReplaceHeader1(string_buf);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf);
	str_num++;
	
	/*strcpy(string_buf, header2);
	LOG_ReplaceHeader2(string_buf);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf);
	str_num++;
	
	strcpy(string_buf, header3);
	LOG_ReplaceHeader3(string_buf);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf);
	str_num++;*/
	
	/*verbose view
	if(read_buf[2] & 0x80000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 4 * n, alrm1); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 4 * n, alrm2);} //battery out
	if(read_buf[2] & 0x40000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 5 * n, alrm3); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 5 * n, alrm4);} //concentrator max
	if(read_buf[2] & 0x20000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 6 * n, alrm5); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 6 * n, alrm6);} //concentrator unsofficient
	if(read_buf[2] & 0x10000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 7 * n, alrm7); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 7 * n, alrm8);} //cylinders empty
	if(read_buf[2] & 0x08000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 8 * n, alrm9); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 8 * n, alrm10);} //emergency
	if(read_buf[2] & 0x04000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 9 * n, alrm11); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 9 * n, alrm12);} //line max
	if(read_buf[2] & 0x02000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 10 * n, alrm13); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 10 * n, alrm14);} //line min
	if(read_buf[2] & 0x01000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, 11 * n, alrm15); }else {rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, 11 * n, alrm16);} //power off */
	
	//optimized view
	if(read_buf[2] & 0x80000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm1); str_num++;} //battery out
	if(read_buf[2] & 0x40000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm3); str_num++;} //concentrator max
	if(read_buf[2] & 0x20000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm5); str_num++;} //concentrator unsofficient
	if(read_buf[2] & 0x10000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm7); str_num++;} //cylinders empty
	if(read_buf[2] & 0x08000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm9); str_num++;} //emergency
	if(read_buf[2] & 0x04000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm11); str_num++;} //line max
	if(read_buf[2] & 0x02000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm13); str_num++;} //line min
	if(read_buf[2] & 0x01000000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm15); str_num++;} //power off
	if(read_buf[2] & 0x00800000) {rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, alrm17); str_num++;} //initial power on after total off
	switch(read_buf[2] & 0x00600000){
		case(0x00400000): rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, stt1); str_num++; break;
		case(0x00200000): rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, stt2); str_num++; break;
		case(0x00000000): rus_font_color = WHITE_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, stt3); str_num++; break;
		case(0x00600000): rus_font_color = RED_COLOR; u8g_DrawStr(&ffont, 5, str_num * n, stt4); str_num++; break;
		default: break;
	}
	
	memcpy(&PhValues_log, &read_buf[3], sizeof(PhValues_log));
	rus_font_color = WHITE_COLOR;
	
	strcpy(string_buf, phv1);
	ConvertFloatToStr(string_buf + 23, PhValues_log.PressLeft);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf); str_num++;
	
	strcpy(string_buf, phv2);
	ConvertFloatToStr(string_buf + 24, PhValues_log.PressRight);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf); str_num++;
	
	strcpy(string_buf, phv3);
	ConvertFloatToStr(string_buf + 16, PhValues_log.PressLine);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf); str_num++;
	
	strcpy(string_buf, phv4);
	ConvertFloatToStr(string_buf + 27, PhValues_log.PressConc);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf); str_num++;
	
	strcpy(string_buf, phv5);
	ConvertFloatToStr(string_buf  + 24, PhValues_log.PSUVolt);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf); str_num++;
	
	strcpy(string_buf, phv6);
	ConvertFloatToStr(string_buf  + 23, PhValues_log.BatVolt);
	u8g_DrawStr(&ffont, 5, str_num * n, string_buf); str_num++;
	
	ConvertInteger32ToStr(string_buf, read_buf[1]);
	string_buf[10] = 0;
	u8g_DrawStr(&ffont, 5, 300, string_buf); 
}

/**
  * @brief   Replaces 000 to log entry order number
  * @param  
  * @retval
  */
void LOG_ReplaceHeader1(char* st){
	ConvertInteger32ToStr(st + 13, LOG_current_num);
}

/**
  * @brief  Replaces 000 to maximum log entry order number
  * @param  
  * @retval
  */
void LOG_ReplaceHeader2(char* st){
	uint32_t max_num, addr;
	if(LOG_FindMaxUnique(&max_num, &addr))	ConvertInteger32ToStr(st + 19, max_num);
}

/**
  * @brief  Replaces 000 to log entry quantity
  * @param  
  * @retval
  */
void LOG_ReplaceHeader3(char* st){
	uint32_t min_num, addr;
	if(LOG_FindMinUnique(&min_num, &addr))	ConvertInteger32ToStr(st + 18, min_num);
}

/**
  * @brief  Converts unsigned integer word (32-bit) to char* without (!) trailing zero. 10 digits total.
  * @param  
  * @retval
  */
void ConvertInteger32ToStr(char* str, const uint32_t integer){
	uint32_t divider = 1000000000;
	uint8_t leading_zeros = 1;
	for(uint8_t i = 0; i < 10; i++){
		if(((integer / divider) % 10) != 0) leading_zeros = 0;
		if(leading_zeros){
			str[ i ] = 0x20;
		} else{
			str[ i ] = 0x30 + (integer / divider) % 10;
		}
		divider /= 10;
	}	
}

/**
  * @brief  Converts float to char* without (!) trailing zero. 10 digits total.
  * @param  
  * @retval
  */
void ConvertFloatToStr(char* str, const float value){
	uint16_t integer = (uint16_t) (value * 10); 
	
	//five simbols in total
	if((integer/1000) % 10)  str[0] = 0x30 + (integer/1000) % 10; else str[0] = 0x20;
	if((integer/100) % 10)  str[1] = 0x30 + (integer/100) % 10; else str[1] = 0x20;
	str[2] = 0x30 + (integer/10) % 10; 
	str[3] = 0x2e;
	str[4] = 0x30 + integer % 10; 	
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint32_t  OldEpochTime;
uint32_t  ThisEpochTime;

void LOG_Renew(void){
	string_buf[10] = 0;
	rus_font_color = MAIN_BGND;
	ConvertInteger32ToStr(string_buf, OldEpochTime);
	u8g_DrawStr(&ffont, 300, 300, string_buf); 
	rus_font_color =WHITE_COLOR;
	ThisEpochTime = EpochTime;
	ConvertInteger32ToStr(string_buf, ThisEpochTime);
	u8g_DrawStr(&ffont, 300, 300, string_buf); 
	OldEpochTime = ThisEpochTime;
}

/**
  * @brief  
  * @param  
  * @retval
  */
void DrawKeyPad(void){
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2, KEYPAD_Y, BUTTON_W * 3, BUTTON_H * 4);
	BSP_LCD_SetTextColor(MAIN_BGND);
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	for(uint16_t i = 1; i <=3; i++){
		BSP_LCD_DrawHLine(DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2, KEYPAD_Y + BUTTON_H * i,  BUTTON_W * 3);
	}
	for(uint16_t i = 1; i <=4; i++){
		BSP_LCD_DrawVLine( DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2 + BUTTON_W * i, KEYPAD_Y,  BUTTON_H * 4);
	}
	BSP_LCD_SetFont(&Font24);
	for(uint16_t j = 0; j < 3; j++){
		for(uint16_t i = 1; i <=3; i++){
			BSP_LCD_DisplayChar(DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2 - BUTTON_W / 2 - Font24.Width / 2 + BUTTON_W * i, KEYPAD_Y + BUTTON_H / 2 - Font24.Height / 2+ BUTTON_H * j, 0x30 + i + j * 3);
		}
  }
	BSP_LCD_DisplayStringAt(DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2 - BUTTON_W / 2 - Font24.Width - Font24.Width / 2 + BUTTON_W , KEYPAD_Y + BUTTON_H / 2 - Font24.Height / 2+ BUTTON_H * 3, "Del", LEFT_MODE);
	BSP_LCD_DisplayChar(DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2 - BUTTON_W / 2 - Font24.Width / 2 + BUTTON_W * 2, KEYPAD_Y + BUTTON_H / 2 - Font24.Height / 2+ BUTTON_H * 3, 0x30);
	BSP_LCD_DisplayStringAt(DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2 - BUTTON_W / 2 - Font24.Width - Font24.Width / 2 + BUTTON_W * 3, KEYPAD_Y + BUTTON_H / 2 - Font24.Height / 2+ BUTTON_H * 3, "Ent", LEFT_MODE);
	
	BSP_LCD_SetTextColor(WHITE_COLOR);
	BSP_LCD_SetBackColor(MAIN_BGND);
	BSP_LCD_DisplayStringAt(460, 5, "X", LEFT_MODE);
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint8_t PasswordCheck(TS_TypeDef *touch, const uint8_t *pwd){
	//const uint8_t size = 6;
	const uint16_t keypad_x0 = DISPLAY_WIDTH / 2 - BUTTON_W * 3 / 2;
	const uint16_t keypad_y0 = KEYPAD_Y;
	//const static uint8_t password[PWD_SIZE + 1] = {'1', '2', '3', '4', '5', '6', 0x00};
	static uint8_t in_buf[PWD_SIZE + 2] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00};
	static uint8_t index = 0;
	uint8_t ret_val = 0;
	if(index > PWD_SIZE) index = PWD_SIZE;
	if((touch->x > keypad_x0) && (touch->x < keypad_x0 + BUTTON_W) && (touch->y > keypad_y0) && (touch->y < keypad_y0 + BUTTON_H)){
		in_buf[index] = '1';
		index++;
  }else if ((touch->x > keypad_x0 + BUTTON_W) && (touch->x < keypad_x0 + 2 * BUTTON_W) && (touch->y > keypad_y0) && (touch->y < keypad_y0 + BUTTON_H)){
		in_buf[index] = '2';
		index++;
  }else if ((touch->x > keypad_x0 + 2 * BUTTON_W) && (touch->x < keypad_x0 + 3 * BUTTON_W) && (touch->y > keypad_y0) && (touch->y < keypad_y0 + BUTTON_H)){
		in_buf[index] = '3';
		index++;
  }else if ((touch->x > keypad_x0) && (touch->x < keypad_x0 + BUTTON_W) && (touch->y > keypad_y0 + BUTTON_H) && (touch->y < keypad_y0 + 2 * BUTTON_H)){
		in_buf[index] = '4';
		index++;
	}else if ((touch->x > keypad_x0 + BUTTON_W) && (touch->x < keypad_x0 + 2 * BUTTON_W) && (touch->y > keypad_y0 + BUTTON_H) && (touch->y < keypad_y0 + 2 * BUTTON_H)){
		in_buf[index] = '5';
		index++;
	}else if ((touch->x > keypad_x0 + 2 * BUTTON_W) && (touch->x < keypad_x0 + 3 * BUTTON_W) && (touch->y > keypad_y0 + BUTTON_H) && (touch->y < keypad_y0 + 2 * BUTTON_H)){
		in_buf[index] = '6';
		index++;
	}else if ((touch->x > keypad_x0) && (touch->x < keypad_x0 + BUTTON_W) && (touch->y > keypad_y0 + 2 * BUTTON_H) && (touch->y < keypad_y0 + 3 * BUTTON_H)){
		in_buf[index] = '7';
		index++;
	}else if ((touch->x > keypad_x0 + BUTTON_W) && (touch->x < keypad_x0 + 2 * BUTTON_W) && (touch->y > keypad_y0 + 2 * BUTTON_H) && (touch->y < keypad_y0 + 3 * BUTTON_H)){
		in_buf[index] = '8';
		index++;
	}else if ((touch->x > keypad_x0 + 2 * BUTTON_W) && (touch->x < keypad_x0 + 3 * BUTTON_W) && (touch->y > keypad_y0 + 2 * BUTTON_H) && (touch->y < keypad_y0 + 3 * BUTTON_H)){
		in_buf[index] = '9';
		index++;
	}else if ((touch->x > keypad_x0 + BUTTON_W) && (touch->x < keypad_x0 + 2 * BUTTON_W) && (touch->y > keypad_y0 + 3 * BUTTON_H) && (touch->y < keypad_y0 + 4 * BUTTON_H)){
		in_buf[index] = '0';
		index++;
	}else if ((touch->x > keypad_x0) && (touch->x < keypad_x0 + BUTTON_W) && (touch->y > keypad_y0 + 3 * BUTTON_H) && (touch->y < keypad_y0 + 4 * BUTTON_H)){
		//Delete		
		if(index == PWD_SIZE) index = PWD_SIZE - 1; //this is done to make double decrement when all digitas were entered
	  in_buf[index] = 0x20;
		if(index > 0) index--;
	}else if ((touch->x > keypad_x0 + 2 * BUTTON_W) && (touch->x < keypad_x0 + 3 * BUTTON_W) && (touch->y > keypad_y0 + 3 * BUTTON_H) && (touch->y < keypad_y0 + 4 * BUTTON_H)){
		//Enter
		index = 0;
		uint8_t flag = 1;
		for(uint8_t i = 0; i <= PWD_SIZE; i++){
			if(in_buf[i] != pwd[i]) flag = 0;
		}
		if(flag) ret_val = 1;
		//zeroing
		for(uint8_t i = 0; i <= PWD_SIZE; i++){
			in_buf[i] = 0x20;
		}
	}else if((touch->x > 440) && (touch->y < 40)){
		//Exit
		//zeroing
		for(uint8_t i = 0; i <= PWD_SIZE; i++){
			in_buf[i] = 0x20;
		}
		ret_val = 2;
	}
	
	if(index > PWD_SIZE) index = PWD_SIZE;
	
	BSP_LCD_SetTextColor(WHITE_COLOR);
	BSP_LCD_SetBackColor(MAIN_BGND);
	in_buf[PWD_SIZE] = 0x00;
	BSP_LCD_DisplayStringAt( 200, 3, in_buf, LEFT_MODE);
	return(ret_val);
}



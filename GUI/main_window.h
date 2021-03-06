#ifndef MAIN_WINDOW
#define MAIN_WINDOW
#include "stm32f1xx_hal.h"
#include "logic.h"


//log scale parameters
#define A_ALFA 	(double)67.5
#define B_ALFA 	(double)180.0
#define A_PRESS (double)0.0363
#define B_PRESS (double)0.135

#define PRED_TIME_X				145
#define PRED_TIME_Y				250

#define ALFA_MIN 45
#define ALFA_MAX 315
#define DEG_RAD 0.0174533

#define LEFT_ROUND_X			68
#define RIGHT_ROUND_X			397
#define ROUNDS_Y				 	225
#define ROUND_RADIUS			42
#define HP_DIG_INTERVAL 	14
#define HP_REF_Y					ROUNDS_Y - 15


//touch screen 
typedef struct{
uint16_t x;
uint16_t y;
uint8_t up;
}TS_TypeDef;

#define TS_X_MIN 147
#define TS_X_MAX 3915
#define TS_Y_MIN 179
#define TS_Y_MAX 3859

void DrawFlowVal(uint16_t val, uint16_t color);
void DrawLinePress(float fval, uint16_t color);
void DrawConcPress(float fval, uint16_t color);
void DrawTheLine(uint16_t hight, uint16_t width);
void DrawRoundScale(uint16_t xx, uint16_t yy, uint16_t rr);
void DrawLeftPress(uint16_t val, uint16_t color);
void DrawRightPress(uint16_t val, uint16_t color);
void DrawConsumption(uint8_t A_G);
void DrawAlarmSmall(uint16_t X, uint16_t Y);
void EraseAlarmSmall(uint16_t X, uint16_t Y);
void DrawAlarmBig(uint16_t X, uint16_t Y);
void EraseAlarmBig(uint16_t X, uint16_t Y);
void DrawBattery(uint16_t percent, uint16_t xx, uint16_t yy);
void DrawMenuDots(uint16_t xx, uint16_t yy);
void DrawTheBase(void);
void DrawMainWindow(void);
void DrawErrorMessage(TypeAlarm* al);

#endif

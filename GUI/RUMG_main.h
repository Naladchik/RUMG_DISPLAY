#ifndef __RUMG_MAIN_H
#define __RUMG_MAIN_H
#include "main.h"

#define MAIN_BGND 	0x0844 // 4 6 51 -> 1 2 4 -> 00001 000010 00100
#define WHITE_COLOR	0xffff
#define BLACK_COLOR	0x0000
#define RED_COLOR 	0xf800
#define GREEN_COLOR 0x07e0
#define BLUE_COLOR 	0x001f
#define PG_COLOR		0xd7fa
#define GRAY_COLOR	0x7bef


//log scale parameters
#define A_ALFA 	(double)67.5
#define B_ALFA 	(double)180.0
#define A_PRESS (double)0.0363
#define B_PRESS (double)0.135


#define DISPLAY_MAX_X 479
#define DISPLAY_MAX_Y 319
#define DISPLAY_WIDTH 480
#define DISPLAY_HIGHT 320

#define MAIN_WIND					0
#define MAIN_MENU_WIND		1
#define SETTINGS_WIND			2
#define LOG_WIND					3
#define PLOT_WIND					4

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

void DrawTheBase(void);
#endif


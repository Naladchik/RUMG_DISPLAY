#include "stm32f1xx_hal.h"
#include "ili9488.h"
#include "lcd_io_spi.h"
#include "main_window.h"
#include "main.h"
#include <math.h>
#include "lcd.h"

extern uint16_t global_adc;
extern TypeDisplay DisplaySet;
extern uint8_t ActiveGas;

extern TypeVolt PhValues_output;

extern LCD_DrawPropTypeDef DrawProp;

extern uint16_t PredictedTime;
extern uint16_t OldPredictedTime;

extern struct TouchStructType T_struct;

#define BAL_STC_W 184
#define BAL_STC_H 19
const uint8_t bal_stc[BAL_STC_W * BAL_STC_H / 8] = {
// 'bal_stc_mono', 184x19px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x0f, 0x07, 0x80, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x8f, 0xc0, 0x07, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x3b, 0x8c, 0xe0, 0x07, 0x00, 0xf0, 0x7f, 0x1f, 0xc3, 0x87, 0x39, 0xce, 0x3c, 0x0f, 0x80, 0xe3, 
0xf8, 0xf0, 0xe6, 0x73, 0x9c, 0x60, 0xf8, 0x39, 0xcc, 0xe0, 0x07, 0x01, 0xf8, 0x7f, 0x1f, 0xc7, 
0xc7, 0x39, 0xce, 0x7e, 0x3f, 0x83, 0xfb, 0xf9, 0xf8, 0xe6, 0x73, 0x9c, 0xe3, 0xf8, 0x39, 0xdc, 
0xe0, 0x07, 0xc3, 0x9c, 0x67, 0x19, 0xce, 0xe7, 0x39, 0xce, 0xe7, 0x33, 0x83, 0xb8, 0xe3, 0x9c, 
0xe6, 0x73, 0x9c, 0xe7, 0x38, 0x39, 0xc0, 0xe0, 0x07, 0xf3, 0x9c, 0x67, 0x19, 0xce, 0x67, 0x39, 
0xce, 0xe7, 0x33, 0x83, 0x98, 0xe3, 0x9c, 0xe6, 0x73, 0x9d, 0xe7, 0x38, 0x39, 0xc1, 0xc0, 0x07, 
0x78, 0x1c, 0x67, 0x19, 0xce, 0x67, 0xf9, 0xfe, 0x07, 0x33, 0x83, 0x80, 0xe0, 0x1c, 0xfe, 0x73, 
0x9d, 0xe7, 0x38, 0x39, 0xc3, 0xc0, 0x07, 0x38, 0x7c, 0x67, 0x19, 0xce, 0x67, 0xf9, 0xfe, 0x1f, 
0x3f, 0x83, 0x80, 0xe0, 0x7c, 0xfe, 0x73, 0x9d, 0xe3, 0xf8, 0x39, 0xc3, 0x80, 0x07, 0x39, 0xdc, 
0x67, 0x19, 0xce, 0x67, 0xf9, 0xfe, 0x77, 0x1f, 0x83, 0x80, 0xe1, 0xdc, 0xe6, 0x73, 0x9f, 0x61, 
0xf8, 0x39, 0xc7, 0x80, 0x07, 0x3b, 0x9c, 0x67, 0x19, 0xce, 0x67, 0x39, 0xce, 0xe7, 0x33, 0x83, 
0x98, 0xe3, 0x9c, 0xe6, 0x73, 0x9e, 0x67, 0x38, 0x39, 0xc7, 0x00, 0x07, 0x3b, 0x9c, 0xe7, 0x39, 
0xce, 0x67, 0x39, 0xce, 0xe7, 0x33, 0x83, 0x98, 0xe3, 0x9c, 0xe6, 0x73, 0x9e, 0x67, 0x38, 0x39, 
0xce, 0x00, 0x07, 0xfb, 0xfc, 0xe7, 0x39, 0xce, 0xe7, 0x39, 0xce, 0xff, 0x33, 0x83, 0xf8, 0xe3, 
0xfc, 0xe6, 0x7f, 0xde, 0x67, 0x38, 0x3b, 0x8e, 0x00, 0x07, 0xf1, 0xfd, 0xe7, 0x79, 0xc7, 0xc7, 
0x39, 0xce, 0x7f, 0x73, 0x81, 0xf0, 0xe1, 0xfc, 0xe6, 0x7f, 0xdc, 0x67, 0x38, 0x1f, 0x9f, 0xe0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xc0, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00
};

#define CONCENTRATOR_W 72
#define CONCENTRATOR_H 14
const uint8_t concentrator[CONCENTRATOR_W * CONCENTRATOR_H / 8] = {// 'concentrator', 72x14px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x09, 0x39, 0x6d, 0x3c, 0xb7, 0x3d, 0xef, 0x7b, 0xc0, 0x09, 0x69, 0x6d, 
0x24, 0xb2, 0x2d, 0x26, 0x5b, 0x40, 0x0e, 0x69, 0xed, 0x3c, 0xf2, 0x2c, 0x66, 0x5b, 0x40, 0x0b, 
0x69, 0xed, 0x20, 0xf2, 0x2d, 0xa6, 0x5b, 0x40, 0x09, 0x69, 0x6d, 0x24, 0xb2, 0x2d, 0x26, 0x53, 
0x40, 0x09, 0x39, 0x6f, 0xbc, 0xb2, 0x3d, 0xe6, 0x73, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 
0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define DAVLENIE_W 88
#define DAVLENIE_H 24
const uint8_t davlenie[DAVLENIE_W * DAVLENIE_H / 8] = {// 'davlenie', 88x24px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xb8, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xb8, 0x7c, 0x7e, 0x1f, 0xc7, 0xe3, 0xb9, 
0xce, 0x3f, 0x00, 0x03, 0xb8, 0xfe, 0x7f, 0x1f, 0xcf, 0xf3, 0xb9, 0xce, 0x7f, 0x80, 0x07, 0xb8, 
0xce, 0x73, 0x1c, 0xce, 0x33, 0xb9, 0xce, 0x71, 0x80, 0x07, 0xb8, 0xce, 0x73, 0x1c, 0xce, 0x33, 
0xb9, 0xde, 0x71, 0x80, 0x07, 0x38, 0x0e, 0x7e, 0x1c, 0xcf, 0xf3, 0xf9, 0xde, 0x7f, 0x80, 0x07, 
0x38, 0x7e, 0x7e, 0x1c, 0xcf, 0xf3, 0xf9, 0xf6, 0x7f, 0x80, 0x07, 0x38, 0xee, 0x73, 0x1c, 0xce, 
0x03, 0xb9, 0xf6, 0x70, 0x00, 0x07, 0x38, 0xce, 0x73, 0x9c, 0xce, 0x33, 0xb9, 0xe6, 0x71, 0x80, 
0x0f, 0x3c, 0xce, 0x73, 0x9c, 0xce, 0x73, 0xb9, 0xe6, 0x73, 0x80, 0x0f, 0xfc, 0xfe, 0x7f, 0x3c, 
0xc7, 0xe3, 0xb9, 0xc6, 0x3f, 0x00, 0x0f, 0xfc, 0x7e, 0x7e, 0x38, 0xc3, 0xc3, 0xb9, 0xc6, 0x1e, 
0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define VYHODNOE_W 80
#define VYHODNOE_H 15
const uint8_t vyhodnoe[VYHODNOE_W * VYHODNOE_H / 8] = {// 'vyhodnoe', 80x15px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0xe3, 0x03, 0xb7, 0x3c, 0x1f, 0x9d, 0xcf, 0x8f, 0x80, 0x03, 0xf3, 
0x03, 0xb6, 0x7f, 0x1f, 0x9d, 0xdf, 0xdf, 0xc0, 0x03, 0x33, 0x03, 0xbe, 0x77, 0x1b, 0x9d, 0xdd, 
0xdd, 0xc0, 0x03, 0x33, 0x03, 0xbe, 0x77, 0x1b, 0x9d, 0xdd, 0xdd, 0xc0, 0x03, 0xe3, 0xf3, 0x9c, 
0x77, 0x3b, 0x9f, 0xdd, 0xdf, 0xc0, 0x03, 0xf3, 0xfb, 0x9c, 0x77, 0x3b, 0x9f, 0xdd, 0xdc, 0x00, 
0x03, 0x33, 0x3b, 0xbe, 0x77, 0x3b, 0x9d, 0xdd, 0xdd, 0xc0, 0x03, 0x33, 0x3b, 0xbe, 0x77, 0x73, 
0x9d, 0xdd, 0xdd, 0xc0, 0x03, 0xf3, 0xfb, 0xb6, 0x7f, 0x7f, 0xdd, 0xdf, 0xdf, 0xc0, 0x03, 0xf3, 
0xf3, 0xb7, 0x3e, 0x7f, 0xdd, 0xcf, 0x8f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define MPA3_W 40
#define MPA3_H 19
const uint8_t mpa3[MPA3_W * MPA3_H / 8] = {// 'MPa3', 40x19px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
0x3c, 0xfe, 0x00, 0x00, 0x0f, 0x3c, 0xfe, 0x00, 0x00, 0x0f, 0x3c, 0xfe, 0x38, 0x00, 0x0f, 0xfc, 
0xfe, 0x7c, 0x00, 0x0d, 0xec, 0xce, 0xee, 0x00, 0x0c, 0xcc, 0xce, 0xee, 0x00, 0x0c, 0xcc, 0xce, 
0x1e, 0x00, 0x0c, 0xcc, 0xce, 0x7e, 0x00, 0x0c, 0xcc, 0xce, 0xee, 0x00, 0x0c, 0xcc, 0xce, 0xee, 
0x00, 0x0c, 0xcc, 0xce, 0xee, 0x00, 0x0c, 0xcc, 0xce, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define MPA2_W 24
#define MPA2_H 13
const uint8_t mpa2[MPA2_W * MPA2_H / 8] = {// 'MPa2', 24x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0xbe, 0x00, 0x3b, 0xbe, 0x60, 0x3b, 0xb6, 0xb0, 0x35, 
0xb6, 0x90, 0x35, 0xb6, 0x70, 0x35, 0xb6, 0x90, 0x35, 0xb6, 0x90, 0x35, 0xb6, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define MPA1_W 16
#define MPA1_H 10
const uint8_t mpa1[MPA1_W * MPA1_H / 8] = {// 'MPa1', 16x10px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0xe4, 0x3e, 0xaa, 0x3e, 0xa6, 0x2a, 0xaa, 0x2a, 0xae, 
0x00, 0x00, 0x00, 0x00};

#define L_MIN_W 48
#define L_MIN_H 17
const uint8_t l_min[L_MIN_W * L_MIN_H / 8] = {// 'l_min', 48x17px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc3, 0x38, 0xe6, 0x73, 0x30, 0x1f, 0xc3, 
0x38, 0xe6, 0x73, 0x30, 0x1c, 0xc2, 0x3d, 0xe6, 0x73, 0x30, 0x1c, 0xc6, 0x3d, 0xe6, 0xf3, 0x30, 
0x1c, 0xc6, 0x3d, 0xe6, 0xf3, 0xf0, 0x1c, 0xc6, 0x37, 0x67, 0xb3, 0xf0, 0x1c, 0xc4, 0x37, 0x67, 
0x33, 0x30, 0x1c, 0xcc, 0x37, 0x67, 0x33, 0x30, 0x1c, 0xcc, 0x32, 0x67, 0x33, 0x30, 0x38, 0xc8, 
0x32, 0x66, 0x33, 0x30, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define LEV_COLL_W 96
#define LEV_COLL_H 14
const uint8_t lev_coll[LEV_COLL_W * LEV_COLL_H / 8] = {// 'lev_coll', 96x14px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x6c, 0xe7, 0xb1, 0xb6, 0x0d, 0x39, 0xe7, 0x9c, 0xd7, 0xbd, 0xe0, 0x00, 0x6d, 0xb5, 0xb1, 
0xb6, 0x0d, 0x6d, 0xa6, 0xb6, 0xd3, 0x2d, 0xa0, 0x00, 0x6d, 0xf7, 0x3d, 0xb6, 0x0e, 0x6d, 0xa6, 
0xbe, 0xe3, 0x2d, 0xa0, 0x00, 0x6d, 0x85, 0xb5, 0xba, 0x0f, 0x6d, 0xa6, 0xb0, 0xf3, 0x2d, 0xa0, 
0x00, 0x6d, 0xb4, 0xb5, 0xba, 0x0d, 0x6d, 0xa6, 0xb6, 0xcb, 0x2d, 0xa0, 0x00, 0xec, 0xe7, 0xbd, 
0xb2, 0x0d, 0x3b, 0x2c, 0x9c, 0xcb, 0x3d, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define PRAV_COLL_W 96
#define PRAV_COLL_H 14
const uint8_t prav_coll[PRAV_COLL_W * PRAV_COLL_H / 8] = {// 'prav_coll', 96x14px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0d, 0xbc, 0xe7, 0xb1, 0xb6, 0x0d, 0x39, 0xe7, 0x9c, 0xd7, 0xbd, 0xe0, 0x0d, 0xb5, 0xb5, 0xb1, 
0xb6, 0x0d, 0x6d, 0xa6, 0xb6, 0xd3, 0x2d, 0xa0, 0x0d, 0xb4, 0x77, 0x3d, 0xb6, 0x0e, 0x6d, 0xa6, 
0xbe, 0xe3, 0x2d, 0xa0, 0x0d, 0xb4, 0xf5, 0xb5, 0xba, 0x0f, 0x6d, 0xa6, 0xb0, 0xf3, 0x2d, 0xa0, 
0x0d, 0xb5, 0xb4, 0xb5, 0xba, 0x0d, 0x6d, 0xa6, 0xb6, 0xcb, 0x2d, 0xa0, 0x0d, 0xbd, 0xf7, 0xbd, 
0xb2, 0x0d, 0x3b, 0x2c, 0x9c, 0xcb, 0x3d, 0xe0, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


#define LORA_SIGNAL_W 40
#define LORA_SIGNAL_H 22
const uint8_t lora_signal_pict[LORA_SIGNAL_W * LORA_SIGNAL_H / 8] = {// 'LoRa', 40x22px
0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 
0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 
0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 
0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 
0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0};
	

#define ROUND_W 24
#define ROUND_H	24
const uint8_t round_1[ROUND_W * ROUND_H/8] = {
// 'round', 24x24px
0x01, 0xf8, 0x00, 0x07, 0xfe, 0x00, 0x0f, 0xff, 0x00, 0x1f, 0xff, 0x80, 0x3f, 0xff, 0x80, 0x7f, 
0xff, 0xc0, 0x7f, 0xff, 0xc0, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xe0, 0xff, 0xff, 
0xe0, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xc0, 0x7f, 0xff, 0xc0, 0x3f, 0xff, 0x80, 0x1f, 0xff, 0x80, 
0x0f, 0xff, 0x00, 0x07, 0xfc, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t round_2[ROUND_W * ROUND_H/8] = {// 'round_2', 24x24px
0x01, 0xf8, 0x00, 0x07, 0xfe, 0x00, 0x0f, 0xff, 0x00, 0x1e, 0x0f, 0x80, 0x3c, 0x03, 0x80, 0x78, 
0x01, 0xc0, 0x70, 0x00, 0xc0, 0xe0, 0x00, 0xe0, 0xe0, 0x00, 0x60, 0xe0, 0x00, 0x60, 0xe0, 0x00, 
0x60, 0xe0, 0x00, 0xe0, 0x70, 0x00, 0xc0, 0x78, 0x01, 0xc0, 0x3c, 0x03, 0x80, 0x1e, 0x07, 0x80, 
0x0f, 0xff, 0x00, 0x07, 0xfc, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define PC_W 256
#define PC_H	22
#define PC_X  110
#define PC_Y	120
const uint8_t potr_conc[PC_W * PC_H/8] = {
	// 'potr_conc', 256x22px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0x38, 0x78, 0xfe, 0xfe, 0x1e, 0x1f, 0x87, 0xf8, 0xf0, 0xee, 0x73, 0x87, 0x80, 0x78, 0xfe, 
0x0e, 0xe1, 0xe1, 0xdc, 0xee, 0x0f, 0x0e, 0xef, 0xef, 0xe1, 0xe3, 0xf8, 0xf0, 0xfe, 0x1e, 0x00, 
0x07, 0x38, 0xfc, 0xfe, 0xff, 0x3f, 0x1f, 0xc7, 0xf9, 0xf8, 0xee, 0x73, 0x8f, 0xc0, 0xfc, 0xfe, 
0x0e, 0xe3, 0xf1, 0xdc, 0xee, 0x1f, 0x8e, 0xef, 0xef, 0xf3, 0xf3, 0xf9, 0xf8, 0xff, 0x3f, 0x00, 
0x07, 0x39, 0xce, 0x38, 0xe7, 0x73, 0x9d, 0xc7, 0x3b, 0x9c, 0xee, 0x73, 0x9c, 0xe1, 0xce, 0x38, 
0x0e, 0xe7, 0x39, 0xdc, 0xee, 0x39, 0xce, 0xe3, 0x8e, 0x77, 0x38, 0xe3, 0x9c, 0xe7, 0x73, 0x80, 
0x07, 0x39, 0xce, 0x38, 0xe7, 0x71, 0x9d, 0xc7, 0x3b, 0x8c, 0xee, 0x77, 0x9c, 0x61, 0xce, 0x38, 
0x0e, 0xe7, 0x39, 0xdc, 0xee, 0x38, 0xce, 0xe3, 0x8e, 0x77, 0x38, 0xe3, 0x9c, 0xe7, 0x73, 0x80, 
0x07, 0x39, 0xce, 0x38, 0xe7, 0x71, 0x9d, 0xc7, 0x3b, 0x8c, 0xfe, 0x77, 0x9c, 0x61, 0xce, 0x38, 
0x0f, 0xc7, 0x39, 0xfc, 0xee, 0x38, 0xcf, 0xe3, 0x8e, 0x70, 0x38, 0xe3, 0x9c, 0xe7, 0x03, 0x80, 
0x07, 0x39, 0xce, 0x38, 0xe7, 0x7f, 0x9d, 0xc7, 0x3b, 0xfc, 0xfe, 0x7f, 0x9f, 0xe1, 0xce, 0x38, 
0x0f, 0x87, 0x39, 0xfc, 0xee, 0x3f, 0xcf, 0xe3, 0x8e, 0x70, 0xf8, 0xe3, 0x9c, 0xe7, 0x0f, 0x80, 
0x07, 0x39, 0xce, 0x38, 0xe7, 0x70, 0x1d, 0xc7, 0x3b, 0x80, 0xfe, 0x7f, 0x9c, 0x01, 0xce, 0x38, 
0x0e, 0xc7, 0x39, 0xfc, 0xee, 0x38, 0x0f, 0xe3, 0x8e, 0x73, 0xb8, 0xe3, 0x9c, 0xe7, 0x3b, 0x80, 
0x07, 0x39, 0xce, 0x38, 0xe7, 0x71, 0x9d, 0xc7, 0x3b, 0x8c, 0xee, 0x7f, 0x9c, 0x61, 0xce, 0x38, 
0x0e, 0xe7, 0x39, 0xdc, 0xee, 0x38, 0xce, 0xe3, 0x8e, 0x77, 0x38, 0xe3, 0x9c, 0xe7, 0x73, 0x80, 
0x07, 0x39, 0xce, 0x38, 0xe7, 0x73, 0x9d, 0xc7, 0x3b, 0x9c, 0xee, 0x7b, 0x9c, 0xe1, 0xce, 0x38, 
0x0e, 0xe7, 0x39, 0xdc, 0xee, 0x39, 0xce, 0xe3, 0x8e, 0x77, 0x38, 0xe3, 0x9c, 0xe7, 0x73, 0x80, 
0x07, 0x39, 0xfe, 0x38, 0xff, 0x3f, 0x1f, 0xcf, 0x39, 0xf8, 0xee, 0x7b, 0x8f, 0xc1, 0xfe, 0x38, 
0x0e, 0xe7, 0xf9, 0xdc, 0xff, 0x1f, 0x8e, 0xe3, 0x8f, 0xf7, 0xf8, 0xe3, 0xfc, 0xff, 0x7f, 0x80, 
0x07, 0x38, 0xfc, 0x38, 0xfe, 0x1e, 0x0f, 0x8e, 0x38, 0xf0, 0xee, 0x73, 0x87, 0x80, 0xfc, 0x38, 
0x0e, 0xe3, 0xf1, 0xdc, 0xff, 0x0f, 0x0e, 0xe3, 0x8f, 0xe3, 0xb8, 0xe1, 0xf8, 0xfe, 0x3b, 0x80, 
0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define ALARM_S_W 24
#define ALARM_S_H	22
const uint8_t alarm_s_t[ALARM_S_W * ALARM_S_H / 8] = {// 'alarm_small_triangle', 24x22px
0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x66, 0x00, 0x00, 
0x66, 0x00, 0x00, 0xc3, 0x00, 0x00, 0xc3, 0x00, 0x01, 0x81, 0x80, 0x03, 0x00, 0xc0, 0x03, 0x00, 
0xc0, 0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0x0c, 0x00, 0x30, 0x0c, 0x00, 0x30, 0x18, 0x00, 0x18, 
0x38, 0x00, 0x18, 0x30, 0x00, 0x0c, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00};
const uint8_t alarm_s_b[ALARM_S_W * ALARM_S_H / 8] = {// 'alarm_small_bg', 24x22px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 
0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
0x00, 0x01, 0xff, 0x80, 0x01, 0xff, 0x80, 0x03, 0xff, 0xc0, 0x03, 0xff, 0xc0, 0x07, 0xff, 0xe0, 
0x07, 0xff, 0xe0, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00};
const uint8_t alarm_s_m[ALARM_S_W * ALARM_S_H / 8] = {// 'alarm_small_mark', 24x22px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 
0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00};

#define ALARM_B_W 40
#define ALARM_B_H	34
const uint8_t alarm_b_t[ALARM_B_W * ALARM_B_H / 8] = {// 'alarm_big_triangle', 40x34px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 
0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xe7, 0x00, 0x00, 0x00, 0x01, 
0xc3, 0x80, 0x00, 0x00, 0x03, 0x81, 0xc0, 0x00, 0x00, 0x03, 0x81, 0xc0, 0x00, 0x00, 0x07, 0x00, 
0xe0, 0x00, 0x00, 0x07, 0x00, 0xe0, 0x00, 0x00, 0x0e, 0x00, 0x70, 0x00, 0x00, 0x1e, 0x00, 0x78, 
0x00, 0x00, 0x1c, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x1c, 0x00, 0x00, 0x78, 0x00, 0x1e, 0x00, 
0x00, 0x70, 0x00, 0x0e, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0x00, 0xe0, 0x00, 0x07, 0x00, 0x01, 
0xc0, 0x00, 0x03, 0x80, 0x01, 0xc0, 0x00, 0x03, 0x80, 0x03, 0x80, 0x00, 0x01, 0xc0, 0x07, 0x80, 
0x00, 0x01, 0xe0, 0x07, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0xf0, 0x0e, 0x00, 0x00, 
0x00, 0x70, 0x1c, 0x00, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x00, 0x3c, 0x38, 0x00, 0x00, 0x00, 
0x1c, 0x78, 0x00, 0x00, 0x00, 0x1e, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xfc, 
0x1f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t alarm_b_b[ALARM_B_W * ALARM_B_H / 8] = {// 'alarm_big_bg', 40x34px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 
0x3c, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0xff, 
0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0x80, 
0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 
0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x00, 0x00, 
0x3f, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 
0xff, 0xfe, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 
0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 
0xe0, 0x07, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t alarm_b_m[ALARM_B_W * ALARM_B_H / 8] = {// 'alarm_big_mark', 40x34px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 
0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 
0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 
0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 
0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 
0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define BAT_W 56
#define BAT_H	25
const uint8_t battery[BAT_W * BAT_H / 8] = {// 'Battery', 56x25px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x40, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x0e, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x0e, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x08, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


void DrawFlowVal(uint16_t val, uint16_t color){
	#define DIG_INTERVAL 30
	if(val > 999) DrawDigitB(FLOW_REF_X, FLOW_REF_Y, (val / 1000) % 10, color); else DrawDigitB(FLOW_REF_X, FLOW_REF_Y, 99, color);	
	if(val > 99) DrawDigitB(FLOW_REF_X + DIG_INTERVAL, FLOW_REF_Y, (val / 100) % 10, color);  else DrawDigitB(FLOW_REF_X + DIG_INTERVAL, FLOW_REF_Y, 99, color);
	if(val > 9) DrawDigitB(FLOW_REF_X + 2 * DIG_INTERVAL, FLOW_REF_Y, (val / 10) % 10, color);  else DrawDigitB(FLOW_REF_X + 2 * DIG_INTERVAL, FLOW_REF_Y, 99, color);
	DrawDigitB(FLOW_REF_X + 3 * DIG_INTERVAL, FLOW_REF_Y,  val % 10, color);
}

void DrawLinePress(float fval, uint16_t color){
	#define OP_REF_X 188
	#define OP_REF_Y 48
	#define COMMA_INT 10
	uint16_t val = (uint16_t)(fval * 100);
	DrawDigitB(OP_REF_X, OP_REF_Y, (val / 100) % 10, color);	
	DrawDigitB(OP_REF_X + DIG_INTERVAL + COMMA_INT, OP_REF_Y, (val / 10) % 10, color);
	DrawDigitB(OP_REF_X + 2 * DIG_INTERVAL + COMMA_INT, OP_REF_Y,  val % 10, color);
	DrawCommaB(OP_REF_X + 30, OP_REF_Y + 35, color);
}

void DrawConcPress(float fval, uint16_t color){
	#define CP_REF_X 388
	#define CP_REF_Y 72
	#define SDIG_INTERVAL 15
	#define SCOMMA_INT 6
	uint16_t val = (uint16_t)(fval * 100);
	DrawDigitS(CP_REF_X, CP_REF_Y, (val / 100) % 10, color);
	DrawDigitS(CP_REF_X + SDIG_INTERVAL + SCOMMA_INT, CP_REF_Y, (val / 10) % 10, color);
	DrawDigitS(CP_REF_X + 2 * SDIG_INTERVAL + SCOMMA_INT, CP_REF_Y,  val % 10, color);
	DrawCommaS(CP_REF_X + 15, CP_REF_Y + 19, color);
}

void DrawTheLine(uint16_t hight, uint16_t width){
	ili9488_DrawHLine(WHITE_COLOR, (DISPLAY_WIDTH - width)/2, DISPLAY_HIGHT - hight, width);
	ili9488_DrawHLine(WHITE_COLOR, (DISPLAY_WIDTH - width)/2, DISPLAY_HIGHT - hight + 1, width);
}

/*
*
*Round colorfull scale 
*@param uint16_t xx, uint16_t yy, uint16_t rr - coordinates and radius in pixels
*
*/
void DrawRoundScale(uint16_t xx, uint16_t yy, uint16_t rr){
	double alfa;
	double alfa_rad = 0;
	double alfa_step = 0.5;
	double sin_val = 0;
	double cos_val = 0;
	float red = 0;
	float green = 0;
	float blue = 0;
	uint16_t rgb565 = 0x0000;
	alfa = ALFA_MIN;
	while(alfa <= ALFA_MAX){
		alfa_rad = DEG_RAD * (double) alfa;
		sin_val = sin(alfa_rad);
		cos_val = cos(alfa_rad);
		red = (float)(alfa - ALFA_MIN) / 135;
		if(red > 1) red = 1;
		green = (float)(ALFA_MAX - alfa) / 135;
		if(green > 1) green = 1;		
		
		rgb565 = (0xf800 & (uint16_t)(red * 31) << 11) | 
					(0x07e0 & (uint16_t)(green * 63) << 5) |
					(0x001f & (uint16_t)(blue * 31));
		
		for(uint16_t r = rr; r <= rr + rr/5; r++){
			ili9488_WritePixel(xx + (int16_t)(r * sin_val), 
						yy + (int16_t)(r * cos_val), 
							rgb565);
		}
		alfa += alfa_step;
	}
}

/*
*
*Round colorfull scale with arrow and nuber inside
*@param uint16_t val - ,  uint16_t color   - color of number in the middle white or red
*
*/
void DrawLeftPress(uint16_t val, uint16_t color){
	#define LP_REF_X 31
	double alfa;
	double alfa_rad = 0;
	double sin_val = 0;
	double cos_val = 0;
	uint16_t this_color;
	
	if(color == MAIN_BGND) this_color = MAIN_BGND; else this_color = RED_COLOR;	
	
  //non-linearity poperdolenost
	//val_nl = A_ALFA * log(A_PRESS * val + B_PRESS) + B_ALFA;
	
	if(val <= ALFA_MAX) alfa = ALFA_MAX - val; else alfa = ALFA_MIN;
	if(alfa <= ALFA_MIN) alfa = ALFA_MIN;
	
	alfa = ALFA_MAX - (A_ALFA * log(A_PRESS * (ALFA_MAX - alfa) + B_PRESS) + B_ALFA) + ALFA_MIN;
	
	alfa_rad = DEG_RAD * (double) alfa;
	sin_val = sin(alfa_rad);
	cos_val = cos(alfa_rad);
	//Arrow part
		for(uint16_t r = ROUND_RADIUS - 16; r <= ROUND_RADIUS - 4; r++){
			for(uint16_t x = 0; x < 4; x++){
				for(uint16_t y = 0; y < 4; y++){
					ili9488_WritePixel(LEFT_ROUND_X + (int16_t)(r * sin_val) - 2 + x, 
							ROUNDS_Y + (int16_t)(r * cos_val) - 2 + y, 
							this_color);
				}
			}
		}
	//Number part
	if (val > 300) val = 300;	
	if(val > 99) DrawDigitS_no_bgn(LP_REF_X + HP_DIG_INTERVAL, HP_REF_Y, (val / 100) % 10, color);  
		else DrawDigitS_no_bgn(LP_REF_X + HP_DIG_INTERVAL, HP_REF_Y, 99, color);
	if(val > 9) DrawDigitS_no_bgn(LP_REF_X + 2 * HP_DIG_INTERVAL, HP_REF_Y, (val / 10) % 10, color);
		else DrawDigitS_no_bgn(LP_REF_X + 2 * HP_DIG_INTERVAL, HP_REF_Y, 99, color);
	DrawDigitS_no_bgn(LP_REF_X + 3 * HP_DIG_INTERVAL, HP_REF_Y,  val % 10, color);
}

/*
*
*Round colorfull scale with arrow and nuber inside
*@param uint16_t val - ,  uint16_t color   - color of number in the middle white or red
*
*/
void DrawRightPress(uint16_t val, uint16_t color){
	#define RP_REF_X 360
	double alfa;
	double alfa_rad = 0;
	double sin_val = 0;
	double cos_val = 0;
	uint16_t this_color;

	if(color == MAIN_BGND) this_color = MAIN_BGND; else this_color = RED_COLOR;
	
	if(val <= ALFA_MAX) alfa = ALFA_MAX - val; else alfa = ALFA_MIN;
	if(alfa <= ALFA_MIN) alfa = ALFA_MIN;
	
	alfa = ALFA_MAX - (A_ALFA * log(A_PRESS * (ALFA_MAX - alfa) + B_PRESS) + B_ALFA) + ALFA_MIN;
	
	alfa_rad = DEG_RAD * (double) alfa;
	sin_val = sin(alfa_rad);
	cos_val = cos(alfa_rad);
	//Arrow part
		for(uint16_t r = ROUND_RADIUS - 16; r <= ROUND_RADIUS - 4; r++){
			for(uint16_t x = 0; x < 4; x++){
				for(uint16_t y = 0; y < 4; y++){
					ili9488_WritePixel(RIGHT_ROUND_X + (int16_t)(r * sin_val) - 2 + x, 
							ROUNDS_Y + (int16_t)(r * cos_val) - 2 + y, 
							this_color);
				}
			}
		}
	//Number part
	if (val > 300) val = 300;	
	if(val > 99) DrawDigitS_no_bgn(RP_REF_X + HP_DIG_INTERVAL, HP_REF_Y, (val / 100) % 10, color);
		else DrawDigitS_no_bgn(RP_REF_X + HP_DIG_INTERVAL, HP_REF_Y, 99, color);
	if(val > 9) DrawDigitS_no_bgn(RP_REF_X + 2 * HP_DIG_INTERVAL, HP_REF_Y, (val / 10) % 10, color);
		else DrawDigitS_no_bgn(RP_REF_X + 2 * HP_DIG_INTERVAL, HP_REF_Y, 99, color);
	DrawDigitS_no_bgn(RP_REF_X + 3 * HP_DIG_INTERVAL, HP_REF_Y,  val % 10, color);
}

/*
*
*Right or left shoulder drawing
*@param A_G @ref  LEFT  RIGHT  CONCENTRATOR
*
*/
void DrawConsumption(uint8_t A_G){
	uint16_t xx, yy;
		
		if (A_G == LEFT){
			xx = UI_LEFT_GAS_X;
			yy = 120;
			for(uint16_t x = 0; x < ROUND_W; x++){
				for(uint16_t y = 0; y < ROUND_H; y++){
					if((round_1[(x + y * ROUND_W) / 8] & (0x80 >> ((x + y * ROUND_W) % 8))) > 0)
						ili9488_WritePixel(xx + x, yy + y, GREEN_COLOR); 
					else 
						ili9488_WritePixel(xx + x, yy + y, MAIN_BGND);
				}
			}
			xx = UI_RIGHT_GAS_X;
			yy = UI_GAS_Y;
			for(uint16_t x = 0; x < ROUND_W; x++){
				for(uint16_t y = 0; y < ROUND_H; y++){
					if((round_2[(x + y * ROUND_W) / 8] & (0x80 >> ((x + y * ROUND_W) % 8))) > 0)
						ili9488_WritePixel(xx + x, yy + y, PG_COLOR); 
					else 
						ili9488_WritePixel(xx + x, yy + y, MAIN_BGND);
				}
			}
			DrawImage(potr_conc, PC_W, PC_H, MAIN_BGND, PC_X, PC_Y);
		}
			if (A_G == RIGHT){
			xx = UI_RIGHT_GAS_X;
			yy = UI_GAS_Y;
			for(uint16_t x = 0; x < ROUND_W; x++){
				for(uint16_t y = 0; y < ROUND_H; y++){
					if((round_1[(x + y * ROUND_W) / 8] & (0x80 >> ((x + y * ROUND_W) % 8))) > 0)
						ili9488_WritePixel(xx + x, yy + y, GREEN_COLOR); 
					else 
						ili9488_WritePixel(xx + x, yy + y, MAIN_BGND);
				}
			}
			xx = UI_LEFT_GAS_X;
			yy = UI_GAS_Y;
			for(uint16_t x = 0; x < ROUND_W; x++){
				for(uint16_t y = 0; y < ROUND_H; y++){
					if((round_2[(x + y * ROUND_W) / 8] & (0x80 >> ((x + y * ROUND_W) % 8))) > 0)
						ili9488_WritePixel(xx + x, yy + y, PG_COLOR); 
					else 
						ili9488_WritePixel(xx + x, yy + y, MAIN_BGND);
				}
			}
			DrawImage(potr_conc, PC_W, PC_H, MAIN_BGND, PC_X, PC_Y);			
		}
			
			if (A_G == CONCENTRATOR){
			xx = UI_RIGHT_GAS_X;
			yy = UI_GAS_Y;
			for(uint16_t x = 0; x < ROUND_W; x++){
				for(uint16_t y = 0; y < ROUND_H; y++){
					if((round_2[(x + y * ROUND_W) / 8] & (0x80 >> ((x + y * ROUND_W) % 8))) > 0)
						ili9488_WritePixel(xx + x, yy + y, PG_COLOR); 
					else 
						ili9488_WritePixel(xx + x, yy + y, MAIN_BGND);
				}
			}
			xx = UI_LEFT_GAS_X;
			yy = UI_GAS_Y;
			for(uint16_t x = 0; x < ROUND_W; x++){
				for(uint16_t y = 0; y < ROUND_H; y++){
					if((round_2[(x + y * ROUND_W) / 8] & (0x80 >> ((x + y * ROUND_W) % 8))) > 0)
						ili9488_WritePixel(xx + x, yy + y, PG_COLOR); 
					else 
						ili9488_WritePixel(xx + x, yy + y, MAIN_BGND);
				}
			}
			DrawImage(potr_conc, PC_W, PC_H, GREEN_COLOR, PC_X, PC_Y);
		}
}

/*
Pair of functions for triangle alarm drawing-erasing
*/
void DrawAlarmSmall(uint16_t X, uint16_t Y){
	DrawImage(alarm_s_t, ALARM_S_W, ALARM_S_H, RED_COLOR, X, Y);
	DrawImage(alarm_s_b, ALARM_S_W, ALARM_S_H, WHITE_COLOR, X, Y);
	DrawImage(alarm_s_m, ALARM_S_W, ALARM_S_H, BLACK_COLOR, X, Y);
}
void EraseAlarmSmall(uint16_t X, uint16_t Y){
	DrawImage(alarm_s_t, ALARM_S_W, ALARM_S_H, MAIN_BGND, X, Y);
	DrawImage(alarm_s_b, ALARM_S_W, ALARM_S_H, MAIN_BGND, X, Y);
	DrawImage(alarm_s_m, ALARM_S_W, ALARM_S_H, MAIN_BGND, X, Y);
}

/*

Pair of functions for triangle alarm drawing-erasing

*/
void DrawAlarmBig(uint16_t X, uint16_t Y){
	DrawImage(alarm_b_t, ALARM_B_W, ALARM_B_H, RED_COLOR, X, Y);
	DrawImage(alarm_b_b, ALARM_B_W, ALARM_B_H, WHITE_COLOR, X, Y);
	DrawImage(alarm_b_m, ALARM_B_W, ALARM_B_H, BLACK_COLOR, X, Y);
}
void EraseAlarmBig(uint16_t X, uint16_t Y){
	DrawImage(alarm_b_t, ALARM_B_W, ALARM_B_H, MAIN_BGND, X, Y);
	DrawImage(alarm_b_b, ALARM_B_W, ALARM_B_H, MAIN_BGND, X, Y);
	DrawImage(alarm_b_m, ALARM_B_W, ALARM_B_H, MAIN_BGND, X, Y);
}


/*

Draws battery with charge level

*/
void DrawBattery(uint16_t percent, uint16_t xx, uint16_t yy){
	uint8_t pcnt, p_length;
	uint16_t color;	
	
	if(percent >= 100) pcnt = 100; else pcnt = percent;
	
	if(percent > 5) {
		if(PhValues_output.PSUVolt < PSU_LOW)
			color = WHITE_COLOR; 
		else
			color = GREEN_COLOR;
	}else color = RED_COLOR;
	p_length = pcnt / 2;	
	
	DrawImage(battery, BAT_W, BAT_H, color, xx, yy);
	for(uint8_t i = 0; i < 50; i++){
		if(i <= p_length)ili9488_DrawVLine(color, xx + i + 1, yy + 2, BAT_H - 4);
		else ili9488_DrawVLine(MAIN_BGND, xx + i + 1, yy + 2, BAT_H - 4);
	}
	if(percent == 100){
		ili9488_DrawVLine(color, xx + 50 + 1, yy + 4, BAT_H - 9);
		ili9488_DrawVLine(color, xx + 51 + 1, yy + 4, BAT_H - 9);
	}else{
		ili9488_DrawVLine(MAIN_BGND, xx + 50 + 1, yy + 4, BAT_H - 9);
		ili9488_DrawVLine(MAIN_BGND, xx + 51 + 1, yy + 4, BAT_H - 9);
	}
}



/*

Draws three dots lol

*/
void DrawMenuDots(uint16_t xx, uint16_t yy){
	ili9488_WritePixel(0 + xx, 0 + yy,  WHITE_COLOR); 
	ili9488_WritePixel(1 + xx, 0 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 0 + yy, WHITE_COLOR);
	ili9488_WritePixel(0 + xx, 1 + yy, WHITE_COLOR);
	ili9488_WritePixel(1 + xx, 1 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 1 + yy, WHITE_COLOR);
	ili9488_WritePixel(0 + xx, 2 + yy, WHITE_COLOR);
	ili9488_WritePixel(1 + xx, 2 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 2 + yy, WHITE_COLOR);
	
	ili9488_WritePixel(0 + xx,8 + yy , WHITE_COLOR); 
	ili9488_WritePixel(1 + xx, 8 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 8 + yy, WHITE_COLOR);
	ili9488_WritePixel(0 + xx, 9 + yy, WHITE_COLOR);
	ili9488_WritePixel(1 + xx, 9 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 9 + yy, WHITE_COLOR);
	ili9488_WritePixel(0 + xx, 10 + yy, WHITE_COLOR);
	ili9488_WritePixel(1 + xx, 10 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 10 + yy, WHITE_COLOR);
	
	ili9488_WritePixel(0 + xx, 16 + yy, WHITE_COLOR); 
	ili9488_WritePixel(1 + xx, 16 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 16 + yy, WHITE_COLOR);
	ili9488_WritePixel(0 + xx, 17 + yy, WHITE_COLOR);
	ili9488_WritePixel(1 + xx, 17 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 17 + yy, WHITE_COLOR);
	ili9488_WritePixel(0 + xx, 18 + yy, WHITE_COLOR);
	ili9488_WritePixel(1 + xx, 18 + yy, WHITE_COLOR);
	ili9488_WritePixel(2 + xx, 18 + yy, WHITE_COLOR);
}


/*

Main window lines, constatn writings and so on

*/
void DrawTheBase(void){
	FillBackground(MAIN_BGND);
	DrawTheLine(220, 460);
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
	DrawImage(lora_signal_pict, LORA_SIGNAL_W, LORA_SIGNAL_H, WHITE_COLOR, 345, 5);
}


/*

All the values displaed here

*/
void DrawMainWindow(void){
		static float OldLeftPressure;
		static float OldRightPressure;
		static float LeftPressure;
		static float RightPressure;
		
		DrawFlowVal(PhValues_output.Flow, WHITE_COLOR);
		if(DisplaySet.LinePressAlarm)DrawLinePress(PhValues_output.PressLine, RED_COLOR); 
				else DrawLinePress(PhValues_output.PressLine, WHITE_COLOR);
		if(DisplaySet.ConcPressAlarm)DrawConcPress(PhValues_output.PressConc, RED_COLOR); 
				else DrawConcPress(PhValues_output.PressConc, WHITE_COLOR);
		if(DisplaySet.LinePressAlarm) DrawAlarmBig(140,60); else EraseAlarmBig(140,60);
		if(DisplaySet.ConcPressAlarm) DrawAlarmSmall(360,75); else EraseAlarmSmall(360,75);
	
		if(PredictedTime != OldPredictedTime){
		if(PredictedTime > 1440){
				BSP_LCD_SetFont(&Font24);
				DrawProp.BackColor = MAIN_BGND;
				DrawProp.TextColor = WHITE_COLOR;
				Print(PRED_TIME_X, PRED_TIME_Y,   "( >24 h  )", &Font24);			
		}else{
				if(PredictedTime <= 30)
					Print(PRED_TIME_X, PRED_TIME_Y, "( <30 min)", &Font24);
				else{
					Print(PRED_TIME_X, PRED_TIME_Y, "(       m)", &Font24);
					PrintNum(PRED_TIME_X + 17 * 2, PRED_TIME_Y, PredictedTime);
					//Print(PRED_TIME_X + 17 * 5, PRED_TIME_Y, "  m) ", &Font24);
				}
		}
		}
		OldPredictedTime = PredictedTime;
	
		LeftPressure = PhValues_output.PressLeft;
		RightPressure = PhValues_output.PressRight;
		if((uint16_t) LeftPressure != (uint16_t) OldLeftPressure) DrawLeftPress(OldLeftPressure, MAIN_BGND);
		if((uint16_t) RightPressure != (uint16_t) OldRightPressure) DrawRightPress(OldRightPressure, MAIN_BGND);
		OldLeftPressure = LeftPressure;
		OldRightPressure = RightPressure;
		if(DisplaySet.LeftPressAlarm) DrawLeftPress(LeftPressure, RED_COLOR); else  DrawLeftPress(LeftPressure, WHITE_COLOR); 
		if(DisplaySet.RightPressAlarm) DrawRightPress(RightPressure, RED_COLOR); else DrawRightPress(RightPressure, WHITE_COLOR);
		
		DrawConsumption(ActiveGas);
		if(DisplaySet.LeftPressAlarm) DrawAlarmSmall(2,260); else EraseAlarmSmall(2,260);
		if(DisplaySet.RightPressAlarm) DrawAlarmSmall(325,260); else EraseAlarmSmall(325,260);
		uint16_t b_lev;
		if(PhValues_output.BatVolt > BatteryLow) b_lev = (uint16_t)(100.0 * (PhValues_output.BatVolt - BatteryLow)/(BatteryCharged - BatteryLow));
		else b_lev = 0;
		DrawBattery(b_lev, 395, 3);
		DrawMenuDots(465, 7);
}

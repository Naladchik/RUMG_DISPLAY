
#ifndef __ANALOG_H
#define __ANALOG_H

#include "stm32f1xx_hal.h"
#include "basic.h"
#include "config.h"

#define F_ARR_SIZE		480
#define FLOW_AVG    	124 //12413 for 24 hours scale on 480 dots
#define FLOW_30AVG    2069

typedef struct VoltStruct{
	float PressLeft;
  float PressRight;
  float PSUVolt;
  float BatVolt;
	float PressLine;
	float PressConc;
	float Flow;
	uint8_t new_data;
} TypeVolt;

void measure_volt(TypeVolt* Volt);
#endif

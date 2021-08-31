#ifndef __TIME_LIB_H
#define __TIME_LIB_H
#include "stm32f1xx_hal.h"

typedef struct DateTime{
	uint8_t ntp_date;
	uint32_t ntp_year;
	uint8_t ntp_hour;
	uint8_t ntp_minute;
	uint8_t ntp_second;
	uint8_t ntp_month;
	uint8_t ntp_week_day;
	uint32_t days_since_epoch;
	uint8_t leap_days;
	uint32_t day_of_year;
	uint8_t leap_year_ind;	
} TypeDateTime;

void epoch_to_datetime(uint32_t epoch, TypeDateTime* dt);

#endif

#ifndef __USER_LIB_H
#define __USER_LIB_H

#include "stm32f1xx_hal.h"
#include "main.h"
/*#include "SX1278.h"

typedef struct {
	SX1278_t *LoRa;
	uint64_t frequency;
	uint8_t BW;
	uint8_t freq_adjusted:1;
} IMT_link_t;*/

void PackLoRa(TypeAlarm* alrm, uint8_t* out_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas);
uint8_t UnPackLoRa(TypeAlarm* alrm, uint8_t* in_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas);
uint8_t make_byte(TypeAlarm* alrm);
void inject_rssi(uint32_t* alrm_byte, uint16_t rssi);
void Buzzer(uint8_t st);

void 				LOG_Log(void);
void 				LOG_LogInit(void);
uint8_t 		LOG_ReadLastEntry(uint32_t* array);
void 				LOG_Compile(uint32_t* array);
void 				LOG_WriteNewEntry(uint32_t* array);
uint8_t 		LOG_FindMaxUnique(uint32_t* max, uint32_t* addr);
uint8_t 		LOG_FindMinUnique(uint32_t* min, uint32_t* addr);
uint8_t 		LOG_ReadFlash(uint32_t startAddr,uint32_t *pdata, uint32_t len);
void 		 		LOG_ErasePage(uint32_t addr);
void     		LOG_EraseWhole(void);
uint8_t 		LOG_CheckIfEmpty(void);
uint32_t  LOG_FindEntry(uint32_t number);
#endif

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
void LogStoreNext(void);
uint32_t GetPageAddress(uint32_t address);
uint32_t FindNextEntryAddr(void);
uint8_t ReadFlash(uint32_t startAddr,uint32_t *pdata, uint32_t len);
void ErasePage(uint32_t addr);
void EraseWholeLog(void);
#endif

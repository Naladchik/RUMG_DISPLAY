#include "main.h"
#include <string.h>

extern uint8_t buzz_on;
extern TypeParameters DeviceParam;
extern TypeAlarm Alarm;
extern uint32_t EpochTime;
extern TypeVolt PhValues_output;

uint32_t log_memory_buf [LOG_ENTRY_SIZE];
uint32_t just_buffer [LOG_ENTRY_SIZE]; //for emty check and so on

void us_delay(void);

/**
  * @brief  
  * @param  
  * @retval
  */
void us_delay(void){
	for(uint8_t i; i<144; i++){
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
	}
}

/**
  * @brief  
  * @param  
  * @retval
  */
void Buzzer(uint8_t st){
	buzz_on = st;
	if(buzz_on)HAL_GPIO_WritePin(GPIOA, EXT_BUZZ, GPIO_PIN_SET); else HAL_GPIO_WritePin(GPIOA, EXT_BUZZ, GPIO_PIN_RESET);	
}

/**
  * @brief  
  * @param  
  * @retval
  */
void PackLoRa(TypeAlarm* alrm, uint8_t* out_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas)
{
	uint8_t buff = 0x00;	
	
	buff = DeviceParam.tx_device_num;
	buff <<= 6;
	buff |= *led_v_left;
	if(*activ_gas & 0x02) buff |= 0x20;
	out_buf[0] = buff;
	
	buff = DeviceParam.rx_device_num;
	buff <<= 6;
	buff |= *led_v_right;
	if(*activ_gas & 0x01) buff |= 0x20;
	out_buf[1] = buff;
	
	buff = 0x00;
	if(alrm->CylindersEmpty)   		buff |= 0x01;
	if(alrm->ConcentratorNOT_OK)  buff |= 0x02;
	if(alrm->ConcentratorMax)  		buff |= 0x04;
	if(alrm->LineMin) 				 		buff |= 0x08;
	if(alrm->LineMax)          		buff |= 0x10;
	if(alrm->PowerOff)         		buff |= 0x20;
	if(alrm->BatteryOut)          buff |= 0x40;
	out_buf[2] = buff;
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint8_t UnPackLoRa(TypeAlarm* alrm, uint8_t* in_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas){
  uint8_t tx_num = 0;
	uint8_t rx_num = 0;
	uint8_t buff;
	
	*activ_gas = 0;
	
	buff = in_buf[0];
	*led_v_left = buff & 0x1f;
	if(buff & 0x20) *activ_gas |= 0x02;
	buff &= 0xc0;
	buff >>= 6;
	tx_num = buff;
	
	buff = in_buf[1];
	*led_v_right = buff & 0x1f;
	if(buff & 0x20) *activ_gas |= 0x01;
	buff &= 0xc0;
	buff >>= 6;
	rx_num = buff;
	
	buff = in_buf[2];
	alrm->CylindersEmpty = 0;
	if(buff & 0x01) alrm->CylindersEmpty = 1;
	alrm->ConcentratorNOT_OK = 0;
	if(buff & 0x02) alrm->ConcentratorNOT_OK = 1;
	alrm->ConcentratorMax = 0;
	if(buff & 0x04) alrm->ConcentratorMax = 1;
	alrm->LineMin = 0;
	if(buff & 0x08) alrm->CylindersEmpty = 1;
	alrm->LineMax = 0;
	if(buff & 0x10) alrm->LineMax = 1;
	alrm->PowerOff = 0;
	if(buff & 0x20) alrm->PowerOff = 1;
	alrm->BatteryOut = 0;
	if(buff & 0x40) alrm->BatteryOut = 1;
	
	if((tx_num == DeviceParam.tx_device_num) && (rx_num == DeviceParam.rx_device_num))return(1); else return(0);
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint8_t make_byte(TypeAlarm* alrm){
	uint8_t buff = 0x00;
	if(alrm->CylindersEmpty)   		buff |= 0x01;
	if(alrm->ConcentratorNOT_OK)  buff |= 0x02;
	if(alrm->ConcentratorMax)  		buff |= 0x04;
	if(alrm->LineMin) 				 		buff |= 0x08;
	if(alrm->LineMax)          		buff |= 0x10;
	if(alrm->PowerOff)         		buff |= 0x20;
	if(alrm->BatteryOut)          buff |= 0x40;
	return(buff);
}

/**
  * @brief  
  * @param  
  * @retval none
  */
void inject_rssi(uint32_t* alrm_byte, uint16_t rssi){
	uint32_t bynary_buff = 0; //10 MSB bits value (0x000ffc00) bits order is reversed
	unsigned char val;
	
	rssi -= 10;
	
	val = rssi / 10;
	for(char i = 0; i < 10; i++){
		bynary_buff <<= 1;
		if(val > 0) bynary_buff |= 0x00000400;		
		if(val > 0) val--;
	}
  *alrm_byte |= bynary_buff;
}

/**
  * @brief  
  * @param  
  * @retval
  */
void LOG_Log(void){
	if(LOG_ReadLastEntry(log_memory_buf)){
		LOG_Compile(log_memory_buf);
	}else{
		log_memory_buf[1] = EPOCH_TIME;
	}
	LOG_WriteNewEntry(log_memory_buf);
}

/**
  * @brief  
  * @param  
  * @retval
  */
void LOG_LogInit(void){
	if(LOG_ReadLastEntry(log_memory_buf)){
		LOG_Compile(log_memory_buf);
	}else{
		log_memory_buf[1] = EPOCH_TIME;
	}
	LOG_WriteNewEntry(log_memory_buf);
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint8_t LOG_ReadLastEntry(uint32_t* array){
	uint32_t num, addr;
	uint8_t uniq;
	if(LOG_FindMaxUnique(&num,&addr, &uniq)){
			LOG_ReadFlash(addr, array, LOG_ENTRY_SIZE);
		return(1);
	}else{
		return(0);
	}
}

/**
  * @brief  
  * @param  
  * @retval
  */
extern uint8_t just_on_flag;

void LOG_Compile(uint32_t* array){
	array[1] = EpochTime;
	
	array[2]= 0; //alarm bits
	if(Alarm.BatteryOut) array[2] |= 0x80000000;
	if(Alarm.ConcentratorMax) array[2] |= 0x40000000;
	if(Alarm.ConcentratorNOT_OK) array[2] |= 0x20000000;
	if(Alarm.CylindersEmpty) array[2] |= 0x10000000;
	if(Alarm.EmergState) array[2] |= 0x08000000;
	if(Alarm.LineMax) array[2] |= 0x04000000;
	if(Alarm.LineMin) array[2] |= 0x02000000;
	if(Alarm.PowerOff) array[2] |= 0x01000000;
	if(just_on_flag){
		array[2] |= 0x00800000;
		just_on_flag = 0;
	}
	memcpy(&array[3], &PhValues_output, sizeof(PhValues_output));
}

/**
  * @brief  Writes new log entry to the memory
  * @param  
  * @retval
  */
void LOG_WriteNewEntry(uint32_t* array){
	uint32_t num, addr;
	uint8_t uniq;
	if(LOG_CheckIfEmpty()){
		array[0] = 1;
		HAL_FLASH_Unlock();
		for(uint32_t a = 0 ; a < LOG_ENTRY_SIZE; a ++){
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET + a * 4, array[a]);
		}
		HAL_FLASH_Lock();	
	}else{
		if(LOG_FindMaxUnique(&num, &addr, &uniq)){
			addr += LOG_ENTRY_SIZE * 4;
			if(addr >= (LOG_OFFSET + LOG_AREA_SIZE * PAGESIZE)) addr = LOG_OFFSET;
			num ++;
			if(num == 0xffffffff) num = 1;
			if((addr % PAGESIZE) == 0) LOG_ErasePage(addr);
			array[0] = num;
			HAL_FLASH_Unlock();
			for(uint32_t a = 0; a < LOG_ENTRY_SIZE; a ++){
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + a * 4, array[a]);
			}
			HAL_FLASH_Lock();	
		}	
	}
}

/**
  * @brief  
  * @param  
  * @retval
  */
void LOG_FindMinMaxNum(uint32_t* min, uint32_t* max){
	*min = 0xffffffff;
	*max = 0;
	for(uint32_t i = 0; i < (LOG_AREA_SIZE * PAGESIZE / LOG_ENTRY_SIZE / 4); i ++){ //count number of logs
		LOG_ReadFlash(LOG_OFFSET + i * LOG_ENTRY_SIZE * 4, just_buffer, LOG_ENTRY_SIZE); 
		if(just_buffer[0] > *max) *max = just_buffer[0];
		if(just_buffer[0] < *min) *min = just_buffer[0];
	}
}

/**
  * @brief  Valid numbers from 1 to 0xfffffffe. So 0 is not allowed and 0xffffffff too.
  * @param  
  * @retval
  */
uint8_t LOG_FindMaxUnique(uint32_t* max, uint32_t* addr, uint8_t* uniq){
	*max = 0;
	*uniq = 1;
	*addr = 0;
	for(uint32_t i = 0; i < (LOG_AREA_SIZE * PAGESIZE / LOG_ENTRY_SIZE / 4); i ++){ //count number of logs
		LOG_ReadFlash(LOG_OFFSET + i * LOG_ENTRY_SIZE * 4, just_buffer, LOG_ENTRY_SIZE);
		if((just_buffer[0] != 0) && (just_buffer[0] == *max)) *uniq = 0;
		if(just_buffer[0] != 0xffffffff){
			if(just_buffer[0] > *max){
				*max = just_buffer[0];
				*addr = LOG_OFFSET + i * LOG_ENTRY_SIZE * 4;
			}
			
		}
	}
	if((*addr != 0) && (*uniq == 1)) return(1);  else return(0);
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint8_t LOG_CheckIfEmpty(){
	uint8_t log_empty = 1;
	for(uint32_t i = 0; i < (LOG_AREA_SIZE * PAGESIZE / LOG_ENTRY_SIZE / 4); i ++){ //count number of logs
		LOG_ReadFlash(LOG_OFFSET + i * LOG_ENTRY_SIZE * 4, just_buffer, LOG_ENTRY_SIZE); 
		for(uint32_t j = 0; j < LOG_ENTRY_SIZE; j ++){
				if(just_buffer[j] != 0xffffffff){
					log_empty = 0;
					break;
				}
			}
			if(log_empty == 0) break;
		}	
	return(log_empty);
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint8_t LOG_ReadFlash(uint32_t startAddr,uint32_t *pdata, uint32_t len){
    if(pdata == NULL) return 0;
    while(len --){
        if(pdata == NULL) break;
        *pdata = *(__IO uint32_t*)startAddr;
        startAddr += 4;
        pdata++;
    }
    return 1;
}

/**
  * @brief  
  * @param  
  * @retval
  */
void LOG_ErasePage(uint32_t addr){
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef FLASH_EraseInit;
	uint32_t xxx;
	FLASH_EraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	FLASH_EraseInit.PageAddress = addr;
	FLASH_EraseInit.NbPages = 1;
	HAL_FLASHEx_Erase(&FLASH_EraseInit, &xxx);
	HAL_FLASH_Lock();
}

/**
  * @brief  
  * @param  
  * @retval
  */
void LOG_EraseWhole(){
		for(uint32_t i = 0; i < LOG_AREA_SIZE; i ++){			
			LOG_ErasePage(LOG_OFFSET + i * PAGESIZE);
		}
}

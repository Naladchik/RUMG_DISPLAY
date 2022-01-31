#include "main.h"
#include <string.h>

extern uint8_t buzz_on;
extern TypeParameters DeviceParam;

uint32_t memory_buf [LOG_ENTRY_SIZE / 4];

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
void LogStoreNext(){
	uint32_t current_address;
	uint16_t order_num;
	uint32_t mem_buf; 
	current_address = FindNextEntryAddr();
	
	if(current_address == GetPageAddress(current_address)) ErasePage(current_address);
	
	if(current_address == LOG_OFFSET) {
		if(ReadFlash(current_address + LOG_AREA_SIZE - LOG_ENTRY_SIZE, memory_buf, LOG_ENTRY_SIZE / 4)){
			if(memory_buf[0] == 0xffffffff) order_num = 0; else order_num = memory_buf[0];
		}
	}else{
		if(ReadFlash(current_address - LOG_ENTRY_SIZE, memory_buf, LOG_ENTRY_SIZE)){
			order_num = memory_buf[0];
		}
	}
		mem_buf = order_num + 1;
	ErasePage(LOG_OFFSET);
		HAL_FLASH_Unlock();
		//HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, current_address, mem_buf);
		
	  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, LOG_OFFSET, mem_buf);
		HAL_FLASH_Lock();
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint32_t GetPageAddress(uint32_t address){
	return((address / PAGESIZE) * (uint32_t) PAGESIZE);
}

/**
  * @brief  Checks 1-st words of all entries. It is order numbers. If this number is more than maximum possible - we start from the beginning
  * @param  
  * @retval address of the next entry
  */



uint32_t FindNextEntryAddr(){
	uint32_t current_address = LOG_OFFSET;
	uint32_t max_num = 0;
	uint32_t addr_of_max = LOG_OFFSET;
	for(current_address = LOG_OFFSET; current_address < (LOG_AREA_SIZE + LOG_OFFSET); current_address += LOG_ENTRY_SIZE){
			if(ReadFlash(current_address, memory_buf, LOG_ENTRY_SIZE / 4)){
				if((memory_buf[0] != 0xffffffff) && (memory_buf[0] > max_num)){
					max_num = memory_buf[0];
					addr_of_max = current_address;
				}
			}
		}
	
		if(max_num == 0)  addr_of_max = LOG_OFFSET; else addr_of_max += LOG_ENTRY_SIZE;
		if(addr_of_max >= (LOG_OFFSET + LOG_AREA_SIZE)) addr_of_max = LOG_OFFSET;
		return(addr_of_max);
}

/**
  * @brief  
  * @param  
  * @retval
  */
uint8_t ReadFlash(uint32_t startAddr,uint32_t *pdata, uint32_t len){
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
void ErasePage(uint32_t addr){
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
void EraseWholeLog(){
		for(uint32_t i = LOG_OFFSET; i < (LOG_OFFSET + LOG_AREA_SIZE); i += LOG_ENTRY_SIZE){
			ErasePage(i);
		}
}

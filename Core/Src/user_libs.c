#include "main.h"
#include <string.h>

extern uint8_t buzz_on;
extern TypeParameters DeviceParam;

void us_delay(void);



void us_delay(void){
	for(uint8_t i; i<144; i++){
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
	}
}

void Buzzer(uint8_t st){
	buzz_on = st;
	if(buzz_on)HAL_GPIO_WritePin(GPIOA, EXT_BUZZ, GPIO_PIN_SET); else HAL_GPIO_WritePin(GPIOA, EXT_BUZZ, GPIO_PIN_RESET);	
}

//---------------------------------------------------------
void PackPacket(TypeAlarm* alrm, uint8_t* out_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas)
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


uint8_t UnPackPacket(TypeAlarm* alrm, uint8_t* in_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas){
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

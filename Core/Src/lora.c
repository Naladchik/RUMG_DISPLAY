#include "main.h"
#include "cmsis_os.h"

extern QueueHandle_t myQueueLORAHandle;

extern TypeParameters DeviceParam;

extern uint8_t buzz_on;

extern TypeParameters DeviceParam;

extern SX1278_hw_t SX1278_hw;
extern SX1278_t SX1278;
uint8_t buffer[256];
uint8_t packet_data[MESS_LEN];

uint8_t lora_q_buff[MESS_LEN];

uint8_t ret;

uint8_t LR_BW = SX1278_LORA_BW_125KHZ; //SX1278_LORA_BW_7_8KHZ;
uint8_t LR_ML = MESS_LEN;
int16_t LR_RSSI = 0;
//uint32_t LR_FREQ = LoRa_FREQ;
int32_t LR_FREQ_ERR;
int32_t mod_freq_err;
uint32_t NoLinkCounter = 0;
unsigned char LoraLinkOK = 0;

uint8_t LORA_busy = 0;

void process_lora(void){
	const int32_t BW_Hz_array[10] = {7800, 10400, 15600, 20800, 31200, 41700, 62500, 125000, 250000, 500000};
	
  	//===========================================================================
		//======================= SENDER ============================================
		//===========================================================================
	if((DeviceParam.Role == CONTROLER) && (DeviceParam.CommDevice == LORA)){
		if(xQueueReceive(myQueueLORAHandle, &lora_q_buff, 0) == pdTRUE){
					for(uint8_t i = 0; i < MESS_LEN; i++){
						packet_data[i] = lora_q_buff[i];
					}
			LORA_busy = 1;
			if(SX1278_LoRaEntryTx(&SX1278, LR_ML, LoRa_TIMEOUT)){
				SX1278_LoRaTxPacket(&SX1278, packet_data, LR_ML, 10*LoRa_TIMEOUT);
			}
			SX1278_init(&SX1278, DeviceParam.LR_FREQ, SX1278_POWER_17DBM, SX1278_LORA_SF_12,	LR_BW, SX1278_LORA_CR_4_5, SX1278_LORA_CRC_EN, LR_ML);
			LORA_busy = 0;			
		}
			
	}
	
		//===========================================================================
		//======================= RECEIVER ==========================================
		//===========================================================================
	if((DeviceParam.Role == REPEATER) && (DeviceParam.CommDevice == LORA)){
		if((ret = SX1278_LoRaRxPacket(&SX1278)) > 0){
 				SX1278_read(&SX1278, (uint8_t*) buffer, ret);				
				//get RSSI
			  LR_RSSI = SX1278_SPIRead(&SX1278, LR_RegPktRssiValue);				
				//get frequency error
			  LR_FREQ_ERR = SX1278_get_freq_err(&SX1278);
				if(LR_FREQ_ERR >0) mod_freq_err = LR_FREQ_ERR; else mod_freq_err = -LR_FREQ_ERR;
				if(((mod_freq_err * 100)/BW_Hz_array[LR_BW]) > 1){
						DeviceParam.LR_FREQ -= LR_FREQ_ERR;
					  SX1278_init(&SX1278, DeviceParam.LR_FREQ, SX1278_POWER_17DBM, SX1278_LORA_SF_12,	LR_BW, SX1278_LORA_CR_4_5, SX1278_LORA_CRC_EN, LR_ML);
						SX1278_LoRaEntryRx(&SX1278, MESS_LEN, LoRa_TIMEOUT);
				}
				if(ret == MESS_LEN){
					for(uint8_t i = 0; i < MESS_LEN; i++){
						lora_q_buff[i] = buffer[i];
					}
					if(xQueueSend(myQueueLORAHandle, &lora_q_buff, 0) != pdTRUE){
						while(1){}
					}
					NoLinkCounter = 0;
					LoraLinkOK = 1;
				}
		  }
		if(NoLinkCounter < MAX_NOLINK) NoLinkCounter++; else NVIC_SystemReset(); //It resets the whole device when no link too long
	  }
	}

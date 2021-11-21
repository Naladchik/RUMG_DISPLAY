#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f1xx_hal.h"

/* DEVICE CONFIGURATION */

/*INDIVIDUAL PARAMETERS!!!*/
#define TX_DEV_NUM				   		0x01
#define RX_DEV_NUM				   		0x02
#define ROLE	 												REPEATER
#define COMM_DEV								ETHERNET
#define LORA_FREQ   						434500000  //Frequeny in Hz, was 434500000, was 859500000
#define BARANKI           			1 // 1 - do not take into account LineMin, 0 - do take into account (baranovichi_style)
#define CONC_DELAY            	10  //Delay for concentrator again-on
#define SWTCH_THRESHOLD (float)10.0 //threshold to switch to the next gas line
#define ALRM_THRESHOLD  (float)40.0 //threshold to activate alarm (if second cylinder <= SWTCH_threshold
#define LINE_P_MIN			(float)4.0
#define LINE_P_MAX			(float)6.0
#define CONC_P_MIN			(float)4.0
#define CONC_P_MAX			(float)6.0
#define CYL_NUM_LEFT						10
#define CYL_NUM_RIGHT						20

#define H_P_a           (float)0.083944 //ADC - cylinder pressure (bar) linear coefficient a
#define H_P_b           (float)-62.5 //ADC - cylinder pressure (bar) linear coefficient b

#define P_a							(float)0.0030525
#define P_b							(float)-2.5
	
#define V_a							(float)0.61050
#define V_b							(float)-500.0

#define Volt_a          (float)0.0088645 //ADC - battery and PSU voltage coefficient a
#define Volt_b          (float)0.0 //ADC - battery and PSU voltage coefficient b

#define BatteryCharged  (float)12.5 //V
#define BatteryLow      (float)9.0 //V
#define BatteryOK       (float)(BatteryLow + 0.5) //V
#define PSU_LOW         (float)11.0 //V
#define PSU_HIGH        (float)16.0 //V

#define PressMIN  	(float)10.0  //Only bottom LED blinking
#define PressMAX   	(float)150.0 //All LEDs light
	
#define CylinderVolume	(float)6000 //liters of gas if 150 bar

#define ADC_AVG_NUM     128  //Number of ADC measurements to for averaging

#define ALRM_PAUSE      60  //Mute delay for alarm 

#define CONC_SIG_DUR    3   //Beep duration when concentrator is off

#define Pquant          (float)((PressMAX - PressMIN)/(LED_NUM - 2))

typedef struct{
	uint8_t tx_device_num;
	uint8_t rx_device_num;
	uint8_t Role;
	uint8_t CommDevice;
	uint32_t LR_FREQ;
	uint8_t Baranki:1;
	uint16_t ConcDelay;
	float HPressSwitch;
	float HPressAlarm;
	float PressLineMax;
	float PressLineMin;
	float PressConcMin;
	float PressConcMax;
	uint16_t CylinderNumberLeft;
	uint16_t CylinderNumberRight;
} TypeParameters;

void InitParam(TypeParameters* Param);

#endif

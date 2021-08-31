#ifndef __BASIC_H
#define __BASIC_H

/* Pins definitions */
//Basic GPIO
//#define PORT_HPS_LEFT				GPIOA
//#define HPS_LEFT        		GPIO_PIN_1  //GPIOA AN1 input

//#define PORT_HPS_RIGHT			GPIOA
//#define HPS_RIGHT       		GPIO_PIN_2  //GPIOA AN2 input

//#define PORT_PSU_VOLT				GPIOC
//#define PSU_VOLT        		GPIO_PIN_3 //GPIOC AN13 input

//#define PORT_BAT_VOLT				GPIOC
//#define BAT_VOLT        		GPIO_PIN_4 //GPIOC AN14 input

#define PORT_INT_BUZZ				GPIOA
#define INT_BUZZ        		GPIO_PIN_8  

#define PORT_EXT_BUZZ				GPIOA
#define EXT_BUZZ        		GPIO_PIN_15

#define PORT_LEFT_VLV				GPIOC
#define LEFT_VLV        		GPIO_PIN_11

#define PORT_RIGHT_VLV			GPIOC
#define RIGHT_VLV       		GPIO_PIN_12

//Touch screen GPIO
#define T_IRQ_PORT					GPIOB
#define T_IRQ								GPIO_PIN_12

#define T_CS_PORT						GPIOB
#define T_CS								GPIO_PIN_11
/* Private defines -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#define NSS_Pin GPIO_PIN_2
#define NSS_GPIO_Port GPIOB

#define DIO0_Pin GPIO_PIN_3  // LoRa interrupt indicator pin (for receiver mode)
#define DIO0_GPIO_Port GPIOA

#define RESET_Pin GPIO_PIN_0
#define RESET_GPIO_Port GPIOA
/* ---------------------------------------------------------------------------*/

#define SENDER 	 1
#define RECEIVER 2
#define NOLORA   3

#define LoRa_TIMEOUT 2000 //2000

#define MAX_NOLINK 10000  //10000 corresponds to around 10 seconds

#define ADC_Left_Press  	ADC_CHANNEL_1
#define ADC_Right_Press 	ADC_CHANNEL_2
#define ADC_Concentrator 	ADC_CHANNEL_0
#define ADC_Line 					ADC_CHANNEL_3
#define ADC_Flow 					ADC_CHANNEL_4
#define ADC_PSU         	ADC_CHANNEL_13
#define ADC_BAT         	ADC_CHANNEL_14


/* Other definitions */
#define LEFT            1
#define RIGHT           2
#define CONCENTRATOR    3

#define TIM3_PERIOD     9600 // 4800 interrupts per second (for 2.4 kHz sound)
#define BUTT_TRIM       (uint8_t)100
#define LED_NUM         20 //how many LED combinations is allowed (though avtual LED number is 10)

#define MESS_LEN				3

#endif

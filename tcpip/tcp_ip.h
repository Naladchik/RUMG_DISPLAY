#ifndef __TCPIP_H
#define __TCPIP_H
#include "main.h"

//network parameters
#define IP_ADDR0 			192
#define IP_ADDR1 			168
#define IP_ADDR2 			100
#define IP_ADDR3 			104

#define GW0 					192
#define GW1 					168
#define GW2 					100
#define GW3 					1

#define SN0 					255
#define SN1 					255
#define SN2 					255
#define SN3 					0

#define MAC0					0xa4
#define MAC1					0x03
#define MAC2					0x26
#define MAC3					0xa7
#define MAC4					0x44
#define MAC5					0x01

//Server IP
#define SER_IP_ADDR0 			192
#define SER_IP_ADDR1 			168
#define SER_IP_ADDR2 			100
#define SER_IP_ADDR3 			50

//Port
#define TCP_PORT			502

/*
statuses of network
*/
#define NOT_INIT				0x00
#define NOT_ACTIVE  		0x01
#define LINK_DETECTED 	0x02
#define SOCKET_CREATED	0x03
#define CONNECTED				0x04

//GPIO definitions
//legacy R&D board
/*#define PORT_LED0 			GPIOC
#define LED0 						GPIO_PIN_0
#define PORT_LED1 			GPIOC
#define LED1 						GPIO_PIN_1
#define PORT_LED2 			GPIOC
#define LED2 						GPIO_PIN_2
#define PORT_WIZ_CS 		GPIOC
#define WIZ_CS 					GPIO_PIN_5
#define PORT_WIZ_RS 		GPIOB
#define WIZ_RS 					GPIO_PIN_5
#define PORT_WIZ_IN 		GPIOB
#define WIZ_IN 					GPIO_PIN_5*/

//V3 board
#define PORT_WIZ_CS 		GPIOB
#define WIZ_CS 					GPIO_PIN_3
#define PORT_WIZ_RS 		GPIOA
#define WIZ_RS 					GPIO_PIN_10
#define PORT_WIZ_IN 		GPIOB
#define WIZ_IN 					GPIO_PIN_6

#define SPI_FRAME_SIZE 	7
#define SPI_TIME_OUT 		1000

#define PDU_SIZE				7

void TCP_IP(void);
#endif

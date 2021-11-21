#include "main.h"
#include "cmsis_os.h"
#include "task.h"
#include <stdbool.h>
#include "wizchip_conf.h"
#include "socket.h"

uint16_t NETWORK_STATUS = NOT_INIT;

uint8_t gw[4] = {GW0, GW1, GW2, GW3};
uint8_t sn[4] = {SN0, SN1, SN2, SN3};
uint8_t sip_cl[4] = {IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3_CL};
uint8_t sip_sr[4] = {IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3_SR};
 uint8_t mac[6] = {MAC0, MAC1, MAC2, MAC3, MAC4, MAC5};

uint8_t tx_buff[SPI_FRAME_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t rx_buff[SPI_FRAME_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t rx2_buff[RX_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t 	srv_ip[4] = {SER_IP_ADDR0, SER_IP_ADDR1, SER_IP_ADDR2, SER_IP_ADDR3};
uint8_t sc_nr = 0;
uint16_t port = TCP_PORT;

extern SPI_HandleTypeDef hspi1;
extern TypeVolt PhValues_output;
extern TypeParameters DeviceParam;

uint8_t WizCheckLink(void);
void W5500_Select(void);
void W5500_Unselect(void);
void W5500_ReadBuff(uint8_t* buff, uint16_t len);
void W5500_WriteBuff(uint8_t* buff, uint16_t len);
uint8_t W5500_ReadByte(void);
void W5500_WriteByte(uint8_t byte);
void init_w5500(void);

//debug vars
int8_t buf_sock;
int32_t buf32_sock;
uint8_t buf_byte;



/*
		The main function
*/
void TCP_IP(void){
	/*
	*********************************************************************************************************************
	If our device is CONTROLLER it works as a TCP client, creates connection and sends data to a server
	*********************************************************************************************************************
	*/
	if(DeviceParam.Role == CONTROLER){
		switch(NETWORK_STATUS){
			case(NOT_INIT): 
				init_w5500();
				NETWORK_STATUS = NOT_ACTIVE;
				break;
			case(NOT_ACTIVE):	
				if(WizCheckLink())  NETWORK_STATUS = LINK_DETECTED;
				break;
			case(LINK_DETECTED):
				buf_byte = socket(sc_nr, Sn_MR_TCP, port, SF_TCP_NODELAY);
				NETWORK_STATUS = SOCKET_CREATED;
				break;
			case(SOCKET_CREATED):
				buf_sock = connect(sc_nr, srv_ip, port);
				if(buf_sock == SOCK_OK) {
					vTaskDelay(1000);
					NETWORK_STATUS = CONNECTED_SEND; 
				}else vTaskDelay(500);
				if(buf_sock ==  SOCKERR_SOCKINIT) { 
						buf_sock = close(sc_nr);  //this happens when no server
						NETWORK_STATUS = LINK_DETECTED;
				}
				break;
			case(CONNECTED_SEND):
				tx_buff[0] = (uint8_t) PhValues_output.PressLeft;
				tx_buff[1] = (uint8_t) PhValues_output.PressRight;
				tx_buff[2] = (uint8_t) PhValues_output.PressLine;
				tx_buff[3] = (uint8_t) PhValues_output.PressConc;
				tx_buff[4] = 0x00;
				tx_buff[5] = 0x00;
				tx_buff[6] = 0x00;
				buf_sock = send(sc_nr, tx_buff, PDU_SIZE);
				if(buf_sock == PDU_SIZE) {
					vTaskDelay(2000);
				}else{
					vTaskDelay(10000);
					NETWORK_STATUS = NOT_ACTIVE;
				}				
				break;
			case(DISCONNECT_TEST):
				buf_sock = disconnect(sc_nr);
			 NETWORK_STATUS = CLOSE_SC_TEST;
				break;
			case(CLOSE_SC_TEST):
				buf_sock = close(sc_nr);
				vTaskDelay(5000);
			NETWORK_STATUS = LINK_DETECTED;
				break;
			case(CONNECTED_RECEIVE):
				buf_sock = recv(sc_nr, rx2_buff, RX_SIZE);
				NETWORK_STATUS = CONNECTED_SEND;
				break;
			default: NETWORK_STATUS = NOT_ACTIVE; break;
		}	
	}
	
	/*
	*********************************************************************************************************************
	If our device is REPEATER it works as a TCP server, waits for connection reveives data and shows them on its diaplay
	*********************************************************************************************************************
	*/
	if(DeviceParam.Role == REPEATER){
		switch(NETWORK_STATUS){
			case(NOT_INIT): 
				init_w5500();
				NETWORK_STATUS = NOT_ACTIVE;
				break;
			case(NOT_ACTIVE):	
				if(WizCheckLink())  NETWORK_STATUS = LINK_DETECTED;
				break;
			case(LINK_DETECTED):
				buf_byte = socket(sc_nr, Sn_MR_TCP, port, SF_TCP_NODELAY);
				NETWORK_STATUS = SOCKET_CREATED;
				break;
			case(SOCKET_CREATED):
				buf_sock = listen(sc_nr);
				NETWORK_STATUS = WAIT_DATA;
				break;
			case(WAIT_DATA):
				buf_sock = recv(sc_nr, rx2_buff, RX_SIZE);
				break;
			default: NETWORK_STATUS = NOT_ACTIVE; break;
		}
	}
}


/*
		functions
*/

uint8_t WizCheckLink(void){
	W5500_Select();
	//tx_buff[0] = ; tx_buff[1] = ; tx_buff[2] = ; tx_buff[3] = ; tx_buff[4] = ; tx_buff[5] = ;  tx_buff[6] = ;
	tx_buff[0] = 0x00; tx_buff[1] = 0x2e; tx_buff[2] = 0x00; tx_buff[3] = 0x00; tx_buff[4] = 0x01; tx_buff[5] = 0x00;  tx_buff[6] = 0x00;
	HAL_SPI_TransmitReceive(&hspi1, tx_buff, rx_buff , 4, SPI_TIME_OUT);
		W5500_Unselect();
	return(rx_buff[3] & 0x01);
}

/*
		call back functions definitions
*/
void W5500_Select(void){
    HAL_GPIO_WritePin(PORT_WIZ_CS, WIZ_CS, GPIO_PIN_RESET);
}

void W5500_Unselect(void) {
    HAL_GPIO_WritePin(PORT_WIZ_CS, WIZ_CS, GPIO_PIN_SET);
}

void W5500_ReadBuff(uint8_t* buff, uint16_t len) {
		//W5500_Select();
    HAL_SPI_Receive(&hspi1, buff, len, HAL_MAX_DELAY);
		//W5500_Unselect();
}

void W5500_WriteBuff(uint8_t* buff, uint16_t len) {
		//W5500_Select();
    HAL_SPI_Transmit(&hspi1, buff, len, HAL_MAX_DELAY);
		//W5500_Unselect();
}


uint8_t W5500_ReadByte(void) {
    uint8_t byte;
	W5500_Select();
    W5500_ReadBuff(&byte, sizeof(byte));
	W5500_Unselect();
    return byte;
}

void W5500_WriteByte(uint8_t byte) {
	W5500_Select();
    W5500_WriteBuff(&byte, sizeof(byte));
	W5500_Unselect();
}


void init_w5500(void) {
		HAL_GPIO_WritePin(PORT_WIZ_RS, WIZ_RS, GPIO_PIN_RESET);
		vTaskDelay(100);
		HAL_GPIO_WritePin(PORT_WIZ_RS, WIZ_RS, GPIO_PIN_SET);
    reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);
    reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);
    reg_wizchip_spiburst_cbfunc(W5500_ReadBuff, W5500_WriteBuff);
	  reg_wizchip_cris_cbfunc(vPortEnterCritical, vPortExitCritical);
    uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
    wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);
		
		setSHAR(mac);
		setGAR(gw);
		setSUBR(sn);
		if(DeviceParam.Role == CONTROLER) setSIPR(sip_cl);
		if(DeviceParam.Role == REPEATER)   setSIPR(sip_sr);
}


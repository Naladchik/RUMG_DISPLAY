#include "stm32f1xx_hal.h"
#include "main.h"
#include "cmsis_os.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern osThreadId myTaskDisplayHandle;

uint8_t spi_arr_tx[4];
uint8_t spi_Xarr_rx[4];
uint8_t spi_Yarr_rx[4];

void T_delay(void);

void T_ReadTouch(struct TouchStructType* T_s){			
			float buff;
	
			SPI_switch_touch();		
	
			spi_arr_tx[0] = 0x90;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_RESET);
			T_delay();
			HAL_SPI_TransmitReceive(&hspi2, spi_arr_tx, spi_Xarr_rx, 4, 1000);
			while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
			;
			T_s->rawX = spi_Xarr_rx[2];
			T_s->rawX <<= 8;
			T_s->rawX |= spi_Xarr_rx[3];
			T_s->rawX >>= 3;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_SET);
			
			spi_arr_tx[0] = 0xD0;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_RESET);
			T_delay();
			HAL_SPI_TransmitReceive(&hspi2, spi_arr_tx, spi_Yarr_rx, 4, 1000);
			while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
			;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_SET);
			T_s->rawY = spi_Yarr_rx[1];
			T_s->rawY <<= 8;
			T_s->rawY |= spi_Yarr_rx[2];
			T_s->rawY >>= 3;			
			
			if(T_s->rawX <= T_X_OFFSET) T_s->X = T_s->rawX - T_X_OFFSET; else T_s->X = 0;
			if(T_s->rawY <= T_Y_OFFSET) T_s->Y = T_s->rawY - T_Y_OFFSET; else T_s->Y = 0;
			
			buff = T_s->rawX;
			buff /= T_X_COEFF;
			T_s->X = (uint16_t)buff;
			buff = T_s->rawY;
			buff /= T_Y_COEFF;
			T_s->Y = (uint16_t)buff;
			
			//T_SetWatch();
			
			T_s->Unprocessed = 1;
			SPI_switch_display();
}

void T_SetWatch(void){
			SPI_switch_touch();
			spi_arr_tx[0] = 0x90;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_RESET);
			T_delay();
			HAL_SPI_TransmitReceive(&hspi2, spi_arr_tx, spi_Xarr_rx, 4, 1000);
			while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
			;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_SET);
			SPI_switch_display();
}

void T_Read_ifIRQ(struct TouchStructType* T_s){
	static uint8_t t_irq = 0;
	static uint8_t t_irq_old = 0;
	if(HAL_GPIO_ReadPin(T_IRQ_PORT, T_IRQ) == GPIO_PIN_RESET) t_irq = 1; else t_irq = 0;
		if((t_irq == 1) && (t_irq_old == 0)){
			Buzzer(1);		
			T_ReadTouch(T_s);
		}		
		t_irq_old = t_irq;
}

void SPI_switch_touch(void){
	HAL_GPIO_WritePin(DISPLAY_CS_PORT, DISPLAY_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_RESET);
	__HAL_SPI_DISABLE(&hspi2);	
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
	__HAL_SPI_ENABLE(&hspi2);
}

void SPI_switch_display(void){
	HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DISPLAY_CS_PORT, DISPLAY_CS, GPIO_PIN_RESET);
	__HAL_SPI_DISABLE(&hspi2);	
	hspi2.Instance = SPI2;
	hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
	__HAL_SPI_ENABLE(&hspi2);
}

void T_delay(void){
	for(uint16_t i = 0; i < 1000; i++){
		__nop();
	}
}



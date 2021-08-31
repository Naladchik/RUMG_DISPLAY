#include "stm32f1xx_hal.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;	


void T_ReadTouch(struct TouchStructType* T_s){
			uint8_t spi_arr_tx[4];
			uint8_t spi_arr_rx[4];
			float buff;
	
			spi_arr_tx[0] = 0x90;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_RESET);
			HAL_SPI_TransmitReceive(&hspi2, spi_arr_tx, spi_arr_rx, 4, 1000);
			while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
			;
			T_s->rawX = spi_arr_rx[1];
			T_s->rawX <<= 8;
			T_s->rawX |= spi_arr_rx[2];
			T_s->rawX >>= 3;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_SET);
			spi_arr_tx[0] = 0xD0;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_RESET);
			HAL_SPI_TransmitReceive(&hspi2, spi_arr_tx, spi_arr_rx, 4, 1000);
			while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
			;
			HAL_GPIO_WritePin(T_CS_PORT, T_CS, GPIO_PIN_SET);
			T_s->rawY = spi_arr_rx[1];
			T_s->rawY <<= 8;
			T_s->rawY |= spi_arr_rx[2];
			T_s->rawY >>= 3;
			
			if(T_s->rawX <= T_X_OFFSET) T_s->X = T_s->rawX - T_X_OFFSET; else T_s->X = 0;
			if(T_s->rawY <= T_Y_OFFSET) T_s->Y = T_s->rawY - T_Y_OFFSET; else T_s->Y = 0;
			
			buff = T_s->rawX;
			buff /= T_X_COEFF;
			T_s->X = (uint16_t)buff;
			buff = T_s->rawY;
			buff /= T_Y_COEFF;
			T_s->Y = (uint16_t)buff;
			
			T_s->Unprocessed = 1;
}


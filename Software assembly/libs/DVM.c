
#include "DVM.h"
#include <stdint.h>
#include "LOLA.h"
#include "main.h" // for GPIO names
#include "board.h"


float DVM_GET_DATA()
{
	float value = 0;	// voltage or current

	int16_t RawValue = 0;
	uint8_t byte[4];

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)0;
	byte[2] = (int8_t)0;
	byte[3] = (int8_t)DVM_DATA;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);

	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	uint8_t rxBuffer[4];

	if (HAL_SPI_Receive(&hspi1, rxBuffer, 4, HAL_MAX_DELAY) == HAL_OK) RawValue = (int16_t)((rxBuffer[2] << 8) | rxBuffer[3]);

	value = RawValue;

	return value;
}

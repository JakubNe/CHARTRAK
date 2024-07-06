
#include "DVM.h"
#include <stdint.h>
#include "LOLA.h"
#include "main.h" // for GPIO names
#include "board.h"
#include "trim.h"


int16_t DVM_GET_DATA_RAW()
{
	int16_t RawValue = 0; // voltage or current
	uint8_t byte[4];

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)0;
	byte[2] = (int8_t)0;
	byte[3] = (int8_t)DVM_DATA;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);

	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	if (HAL_SPI_Receive(&hspi1, byte, 4, HAL_MAX_DELAY) == HAL_OK) RawValue = to_signed_12bit((int16_t)((byte[2] << 8) | byte[3]));

	return RawValue;
}

int16_t DVM_GET_FILTERED_DATA_RAW(uint16_t NoSamples)
{
	int64_t out = 0;

	for(int i = 0; i < NoSamples; i++)
	{
		out += DVM_GET_DATA_RAW();
	}
	out /= NoSamples;

	return (int16_t)out;
}

/*
 * HFDAC.c
 *
 *  Created on: Jul 6, 2024
 *      Author: pavlovic
 */

#include "HFDAC.h"
#include "main.h"
#include "LOLA.h"

void HFDAC_SET_MAX_AMPLITUDE(HFDAC_struct* HFDAC)
{
	DACREF((HFDAC->maxAmplitude)*2/6.4);	// setting DAC Voltage reference
	HFDAC->relativeDACcodeCoef = 2047/(HFDAC->maxAmplitude); // multiply any number from -1 to 1 and you will get direct code for DAC
}

void HFDAC_SET_MODE(HFDAC_MODE mode)
{
	HAL_GPIO_WritePin(MODE_GPIO_Port, MODE_Pin, mode);
}

void HFDAC_DIRECT_DATA(HFDAC_struct* HFDAC, float value)
{
	uint8_t byte[4];

	int16_t data = value * HFDAC->relativeDACcodeCoef;

	byte[0] = 0;
	byte[1] = (int8_t)((data>>8)&0x000f);
	byte[2] = (int8_t)(data&0x00ff);
	byte[3] = (int8_t)DAC_DIRECTDATA;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}

void HFDAC_SET_ALL(HFDAC_struct* HFDAC)
{
	HFDAC_SET_MAX_AMPLITUDE(HFDAC);
	HFDAC_SET_MODE(HFDAC->mode);

}

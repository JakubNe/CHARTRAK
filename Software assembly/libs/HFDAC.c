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
	switch(HFDAC1.mode)
	{
		case Voltage_output:
			HFDAC->relativeDACcodeCoefU_V = 2047/(HFDAC->maxAmplitudeU_V); // multiply any number from -1 to 1 and you will get direct code for DAC
			HFDAC->relativeDACcodeCoefI_mA = 0;

			DACREF((HFDAC->maxAmplitudeU_V) * VoltageFeedback_GAIN);	// setting DAC Voltage reference (fb = 1k/15k)
		break;

		case Current_output:
			HFDAC->relativeDACcodeCoefU_V = 0;
			HFDAC->relativeDACcodeCoefI_mA = 2047/(HFDAC->maxAmplitudeI_mA); // multiply any number from -1 to 1 and you will get direct code for DAC

			DACREF((HFDAC->maxAmplitudeI_mA) * CurrentFeedback_GAIN);	// setting DAC Voltage reference (fb = 2k/15k)
		break;
	}
}

void HFDAC_SET_MODE(HFDAC_MODE mode)
{
	HAL_GPIO_WritePin(MODE_OUT_GPIO_Port, MODE_OUT_Pin, mode);
}

void HFDAC_DIRECT_DATA(HFDAC_struct* HFDAC, uint16_t data)
{
	uint8_t byte[4];

	//int16_t data = value * HFDAC->relativeDACcodeCoef;

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

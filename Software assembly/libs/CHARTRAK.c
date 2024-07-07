/*
 * CHARTRAK.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Admin
 */
#include "CHARTRAK.h"
#include <stdint.h>
#include "main.h" // for GPIO names
#include "board.h"
#include "LOLA.h"
#include "ProgRef.h"

void CHT_Load(CHT_struct CHT1)
{
	uint8_t byte[4];
	uint16_t data;

	// loading waveform
	for(uint16_t adcInput = 0; adcInput < ADCMAXVAL; adcInput++)
	{
		switch(CHT1.characteristic)
		{
			default: data = (uint16_t)adcInput; break;	// open

			case Short:	data = 0; break;

			case CharFunc: data = 0; break;
		}

		byte[0] = (int8_t)((adcInput>>4)&0x000f);
		byte[1] = (int8_t)(((data>>8)&0x000f)|((adcInput<<4)&0x00f0));
		byte[2] = (int8_t)(data&0x00ff);
		byte[3] = (int8_t)CHT_DATA;

		HAL_SPI_Transmit(&hspi1, byte, 4, 100);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	}


}

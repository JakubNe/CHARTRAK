/*
 * DAC8165.c
 *
 *  Created on: Feb 13, 2024
 *      Author: Filip Pavlovic
 *
 *  DAC8165 4 channel 14bit DAC as voltage reference generator
 */

#include "ProgRef.h"
#include <stdint.h>
#include "main.h"
#include "board.h"
#include "trim.h"

float DACref = 0;

void DACREF(float v) // 0 <= v <= 2.5
{
	uint16_t DATA;
	v = trimFloat(v, 0, 2.5);
	if(v==2.5) DATA = 0xffff;
	else DATA = (uint16_t)(16384*(v/2.5));

	DACref = v;

	uint8_t byte[3];

	byte[0] = (3<<1)|(1<<4);	//3 shifted=channel D	1 shifted=load
	byte[1] = (uint8_t)((DATA >> 6)&0x00ff);
	byte[2] = (uint8_t)((DATA << 2)&0x00ff);

	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 0);
	HAL_SPI_Transmit(&hspi1, byte, 3, 100);
	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 1);
}

void DACOFFS(float v) // -12.5 <= v <= 12.5
{
	uint16_t DATA;
	v = trimFloat(v, -12.5, 12.5);
	if(v==12.5) DATA = 0xffff;
	else DATA = (uint16_t)(16384*((v+12.5)/25));

	uint8_t byte[3];

	byte[0] = (2<<1)|(1<<4);	//2 shifted=channel C	1 shifted=load
	byte[1] = (uint8_t)((DATA >> 6)&0x00ff);
	byte[2] = (uint8_t)((DATA << 2)&0x00ff);

	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 0);
	HAL_SPI_Transmit(&hspi1, byte, 3, 100);
	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 1);
}

void ADCREF(float v) // 0 <= v <= 2.5
{
	uint16_t DATA;
	v = trimFloat(v, 0, 2.5);
	if(v==2.5) DATA = 0xffff;
	else DATA = (uint16_t)(16384*(v/2.5));

	uint8_t byte[3];

	byte[0] = (1<<1)|(1<<4); //1 shifted=channel B	1 shifted=load
	byte[1] = (uint8_t)((DATA >> 6)&0x00ff);
	byte[2] = (uint8_t)((DATA << 2)&0x00ff);

	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 0);
	HAL_SPI_Transmit(&hspi1, byte, 3, 100);
	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 1);
}

void ADCOFFS(float v) // -12.5 <= v <= 12.5
{
	uint16_t DATA;
	v = trimFloat(v, -12.5, 12.5);
	if(v==12.5) DATA = 0xffff;
	else DATA = (uint16_t)(16384*((v+12.5)/25));

	uint8_t byte[3];

	byte[0] = (1<<4); //none shifted=channel A	1 shifted=load
	byte[1] = (uint8_t)((DATA >> 6)&0x00ff);
	byte[2] = (uint8_t)((DATA << 2)&0x00ff);

	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 0);
	HAL_SPI_Transmit(&hspi1, byte, 3, 100);
	HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 1);
}

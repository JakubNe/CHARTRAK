/*
 * OSC.c
 *
 *  Created on: May 20, 2024
 *      Author: Admin
 */

#include "OSC.h"
#include "main.h"

void OSC_SET_ALL(OSC_struct* OSC, HFADC_struct* HFADC)
{
	OSC_SET_SAMPLES_AFTER_TRIGGER(OSC);
	OSC_SET_TRIGGER_MODE(OSC);
	OSC_SET_TRIGGER_VAL(OSC, HFADC);
}

uint8_t OSC_GET_STATUS()
{
	uint8_t byte[4];

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)0;
	byte[2] = (int8_t)0;
	byte[3] = (int8_t)OSC_READY;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);

	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	if (HAL_SPI_Receive(&hspi1, byte, 4, HAL_MAX_DELAY) == HAL_OK)

	return byte[3];
}

void OSC_INIT_SAMPLING()
{
	uint8_t byte[4];

	byte[0] = (uint8_t)0;
	byte[1] = (uint8_t)0;
	byte[2] = (uint8_t)1;
	byte[3] = (uint8_t)OSC_SAMPLE;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

}

void OSC_SET_TRIGGER_VAL(OSC_struct* OSC, HFADC_struct* HFADC)
{
	uint8_t byte[4];

	int16_t data = HFADC_CONVERT_VALUE2RAW(HFADC, OSC->triggerLevel);

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)((data>>8)&0x000f);
	byte[2] = (int8_t)(data&0x00ff);
	byte[3] = (int8_t)OSC_TRIGLEVEL;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}

void OSC_SET_TRIGGER_MODE(OSC_struct* OSC)
{
	uint8_t byte[4];

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)0;
	byte[2] = (int8_t)OSC->trigMode;
	byte[3] = (int8_t)OSC_TRIGLEVEL;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}

void OSC_SET_SAMPLES_AFTER_TRIGGER(OSC_struct* OSC)
{
	uint8_t byte[4];

	int16_t data = OSC->samplesAfterTrig;

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)((data>>8)&0x00ff);
	byte[2] = (int8_t)(data&0x00ff);
	byte[3] = (int8_t)OSC_SAMPLESAFTERTRIG;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}

void OSC_SET_PRESCALER(OSC_struct* OSC)
{
	uint8_t byte[4];

	uint32_t prescaler = OSC->prescaler;

	// setting prescaler
	byte[0] = (uint8_t)((prescaler>>16)&0x00ff);
	byte[1] = (uint8_t)((prescaler>>8)&0x00ff);
	byte[2] = (uint8_t)(prescaler&0x00ff);
	byte[3] = (uint8_t)OSC_PRESCALER;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}

uint16_t OSC_GET_TRIGGER_ADDRESS(OSC_struct* OSC)
{
	int16_t TriggerAdress = 0; // address of FIFO circular buffer at which trigger occured (basically zero x axis)
	uint8_t byte[4];

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)0;
	byte[2] = (int8_t)0;
	byte[3] = (int8_t)OSC_TRIGADDRESS;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);

	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	if (HAL_SPI_Receive(&hspi1, byte, 4, HAL_MAX_DELAY) == HAL_OK) TriggerAdress = (uint16_t)((byte[2] << 8) | byte[3]);
}

uint16_t OSC_GET_DATA_RAW(OSC_struct* OSC)
{
	int16_t RawValue = 0; // voltage or current
	uint8_t byte[4];

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)0;
	byte[2] = (int8_t)0;
	byte[3] = (int8_t)OSC_DATA;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);

	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	if (HAL_SPI_Receive(&hspi1, byte, 4, HAL_MAX_DELAY) == HAL_OK) RawValue = to_signed_12bit((int16_t)((byte[2] << 8) | byte[3]));

	return RawValue;
}


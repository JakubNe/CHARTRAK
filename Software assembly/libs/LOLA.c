
#include "LOLA.h"
#include <stdint.h>
#include "main.h"
#include "board.h"
#include "ProgRef.h"

uint8_t LOLA_Init(InitType t, uint16_t maxAtempts) // waits forever if maxatempts > 10000
{
	DACREF(0.0);
	DACOFFS(0);

	// Reset
	HAL_GPIO_WritePin(PROGB_GPIO_Port, PROGB_Pin, 0);
	HAL_Delay(1);
	HAL_GPIO_WritePin(PROGB_GPIO_Port, PROGB_Pin, 1);
	HAL_Delay(1);

	switch(t)
	{
		// reference: http://dangerousprototypes.com/docs/Xilinx_Spartan_3_FPGA_quick_start#Boot_configuration
		case Master_Serial:
			HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 0);
			HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 0);
			HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 0);
		break;

		case SPI_FLASH:	// SPI FLASH
			HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 0);
			HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 0);
			HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 1);
		break;

		case BPI_Up:
			HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 0);
			HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 1);
			HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 0);
		break;

		case BPI_Down:
			HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 0);
			HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 1);
			HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 1);
		break;

		case Slave_parallel:
			HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 1);
			HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 1);
			HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 0);
		break;

		case Slave_Serial:
			HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 1);
			HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 1);
			HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 1);
		break;

		default: // JTAG on default
			HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 1);
			HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 0);
			HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 1);
			maxAtempts = 10000; // Unlimited wait time on JTAG configuration
		break;
	}

	while(HAL_GPIO_ReadPin(INITB_GPIO_Port, INITB_Pin) && maxAtempts > 0)
	{
		if(maxAtempts < 10000) maxAtempts--;
		HAL_Delay(100);
	}

	if(maxAtempts > 0) return 1;	// sucesfull configuration
	else return 0; // timer ran out
}

void LOLA_Reset()
{
	HAL_GPIO_WritePin(PROGB_GPIO_Port, PROGB_Pin, 0);
	HAL_Delay(1);
	HAL_GPIO_WritePin(PROGB_GPIO_Port, PROGB_Pin, 1);
	HAL_Delay(1);
}

//*********************************************************************************************************************
/*void LOLA_Set_CLK1(uint32_t freq)
{
	uint8_t byte[4];

	// setting prescaler
	byte[0] = (uint8_t)((prescaler>>16)&0x00ff);
	byte[1] = (uint8_t)((prescaler>>8)&0x00ff);
	byte[2] = (uint8_t)(prescaler&0x00ff);
	byte[3] = (uint8_t)CLKprescaler;
	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}*/

uint16_t enablersReg = 0;

void LOLA_enable_features(LOLAfeatures LOLAfeatures1, uint8_t ENABLE)
{
	uint16_t enablersMask = 0x0001 << LOLAfeatures1;
	uint8_t byte[4];

	if((uint16_t)LOLAfeatures1 == (uint16_t)ALL_EN) 	enablersMask = 0xffff;

	if(ENABLE) 	enablersReg |= enablersMask;
	else 		enablersReg &= ~enablersMask;

	byte[0] = 0;
	byte[1] = (uint8_t)((enablersReg>>8)&0x00ff);
	byte[2] = (uint8_t)(enablersReg&0x00ff);
	byte[3] = (uint8_t)ENABLERS;


	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}

float MAX_AMPLITUDE = 0;

void LOLA_SET_MAX_AMPLITUDE(float value)
{
	DACREF((value)*2/6.4);	// setting DAC Voltage reference
	MAX_AMPLITUDE = value;
}

void DAC_DIRECT_DATA(float value)
{
	uint8_t byte[4];

	int16_t data = (int16_t)(2048*value/MAX_AMPLITUDE);

	byte[0] = 0;
	byte[1] = (int8_t)((data>>8)&0x000f);
	byte[2] = (int8_t)(data&0x00ff);
	byte[3] = (int8_t)DAC_DIRECTDATA;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}



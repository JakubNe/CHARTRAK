
#include "LOLA.h"
#include <stdint.h>
#include "main.h"
#include "board.h"
#include "ProgRef.h"


void LOLA_CFG_SEL(InitType t)
{
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
			break;
		}
}

uint8_t LOLA_Init(LOLAconfig_struct* LOLAconfig)
{
	uint16_t AttemptsLeft;
	uint16_t FID = 0;
	uint16_t TrialsLeft = LOLAconfig->Trials;

	LOLAconfig->Status = NO_FIRMWARE;

	do{

		LOLA_Reset();
		HAL_Delay(200);
		LOLA_CFG_SEL(LOLAconfig->Config);

		AttemptsLeft = 20;

		if(LOLAconfig->Config == JTAG)	// unlimited timer for manual JTAG configuration
			while(HAL_GPIO_ReadPin(INITB_GPIO_Port, INITB_Pin)){}
		else
			while(HAL_GPIO_ReadPin(INITB_GPIO_Port, INITB_Pin) && AttemptsLeft > 0)
			{
				AttemptsLeft--;
				HAL_Delay(100);
			}

		AttemptsLeft = 20;
		LOLAconfig->Status = NO_FIRMWARE;

		do{
			HAL_Delay(100);
			FID = LOLA_GET_FIRMWAREID();

			if(LOLAconfig->compatibleFirmwareID == FID) LOLAconfig->Status = FIRMWARE_OK;
			else LOLAconfig->Status = INVALID_FIRMWARE;
		}while(AttemptsLeft > 0 && LOLAconfig->Status != FIRMWARE_OK);

		TrialsLeft--;

	}while(TrialsLeft > 0 && LOLAconfig->Status != FIRMWARE_OK);

	if(LOLAconfig->Status == FIRMWARE_OK) return 1;	// sucesfull configuration
	else return 0; // timer ran out
}

void LOLA_Reset()
{
	HAL_GPIO_WritePin(PROGB_GPIO_Port, PROGB_Pin, 0);
	HAL_GPIO_WritePin(PROGB_GPIO_Port, PROGB_Pin, 1);
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

void LOLA_process_init(ProcessList_struct* PROCESSLIST)
{
	memset(PROCESSLIST->processQuery, 0, MAX_PROCESS-1 * sizeof(uint8_t));
	PROCESSLIST->processSize = 0;
}

uint8_t LOLA_process_add(ProcessList_struct* PROCESSLIST, processes process)
{
	if(PROCESSLIST->processSize >= MAX_PROCESS) return;

	PROCESSLIST->processQuery[PROCESSLIST->processSize] = process;
}

void LOLA_process_finish(ProcessList_struct* PROCESSLIST)
{
	if(PROCESSLIST->processSize != 0) return;

	for(uint8_t i = 0; i < MAX_PROCESS-1; i++) PROCESSLIST->processQuery[i] = PROCESSLIST->processQuery[i+1];
	PROCESSLIST->processQuery[MAX_PROCESS-1] = 0;
	PROCESSLIST->processSize -= 1;
}

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

uint16_t LOLA_GET_FIRMWAREID()
{
	uint16_t FirmwareID = 0;
	uint8_t byte[4];

	byte[0] = (int8_t)0;
	byte[1] = (int8_t)0;
	byte[2] = (int8_t)0;
	byte[3] = (int8_t)FIRMWARE_ID;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);

	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	uint8_t rxBuffer[4];

	 // Receive 4 bytes
	if (HAL_SPI_Receive(&hspi1, rxBuffer, 4, HAL_MAX_DELAY) == HAL_OK) FirmwareID = (rxBuffer[2] << 8) | rxBuffer[3];

	return FirmwareID;
}




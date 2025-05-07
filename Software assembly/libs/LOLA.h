/*
 * LOLA.h
 *
 *  Created on: Feb 7, 2024
 *      Author: Admin
 */
#include <stdint.h>

#ifndef LOLA_H_
#define LOLA_H_

//#include "main.h"

typedef enum{
	Master_Serial = 0,
	SPI_FLASH1,
	SPI_FLASH2,
	BPI_Up,
	BPI_Down,
	Slave_parallel,
	Slave_Serial,
	JTAG_Rack,
	JTAG_Ext
} InitType;

typedef enum{
	AWG_D_MSB = 1,
	AWG_D_LSB,
	ENABLERS,
	DAC_DIRECTDATA,
	AWG_DATA,
	AWG_MAXADRESS,
	NOISE_AMPLITUDE,
	NOISE_PRESCALER,
	NOISE_SEED,
	OSC_TRIGMODE,
	OSC_TRIGLEVEL,
	OSC_SAMPLESAFTERTRIG,
	OSC_PRESCALER,
	OSC_DATA,
	OSC_TRIGADDRESS,
	OSC_READY,
	OSC_SAMPLE,
	CHT_DATA,
	FIRMWARE_ID,
	DVM_DATA
} LOLAregs;

typedef enum{
	ALL_EN = -1,
	OUT_EN = 0,
	NOISE_EN,
	AWG_EN,
	OSC_EN,
	CHT_EN
} LOLAfeatures;

typedef enum{
	NO_FIRMWARE = 0,
	INVALID_FIRMWARE,
	FIRMWARE_OK
} LOLAstatus;

typedef struct{
	LOLAstatus Status;
	InitType Config;
	uint16_t Trials; // number of tries to configure FPGA before giving up
	uint16_t compatibleFirmwareID;
	uint8_t outputEN;
	uint8_t FlashLOCK;
} LOLAconfig_struct;

uint8_t LOLA_Init(LOLAconfig_struct* LOLAconfig);

void LOLA_Reset();

uint16_t LOLA_GET_FIRMWAREID();

void LOLA_CFGFlashWriteLock(LOLAconfig_struct* LOLAconfig);
void LOLA_CFGFlashWriteUnlock(LOLAconfig_struct* LOLAconfig);

void LOLA_enable_features(LOLAfeatures LOLAfeatures, uint8_t ENABLE);

void LOLA_Output(LOLAconfig_struct* LOLAconfig, uint8_t Enable);

#endif /* LOLA_H_ */

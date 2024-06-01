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
	SPI_FLASH,
	BPI_Up,
	BPI_Down,
	Slave_parallel,
	Slave_Serial,
	JTAG
} InitType;

typedef enum{
	Voltage_output = 0,
	Current_output
} DACoutputMode;

typedef enum{
	AWG_M = 1,
	AWG_D,
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
	CHT_DATA
} LOLAregs;

typedef enum{
	ALL_EN = -1,
	NOISE_EN = 1,
	AWG_EN,
	OSC_EN,
	CHT_EN
} LOLAfeatures;

uint8_t LOLA_Init(InitType t, uint16_t maxAtempts);

void LOLA_Reset();

void LOLA_enable_features(InitType LOLAfeatures, int ENABLE);

void DAC_DIRECT_DATA(float value);

void LOLA_SET_MAX_AMPLITUDE(float value);

#endif /* LOLA_H_ */

/*
 * AWG.h
 *
 *  Created on: Feb 13, 2024
 *      Author: Filip Pavlovic
 *
 *      Arbitrary Waveform Generator with white noise engine
 *
 */
#include <stdint.h>

#ifndef AWG_H_
#define AWG_H_

typedef enum waveforms_{
	Square = 0,
	Triangle,
	Sine,
	Func
} waveforms;

typedef struct{
	waveforms waveform;
	float Uavg;
	float Upp;
	float DutyCycle;
	double Freq;
} AWG_setup_struct;

typedef struct{
	uint8_t Enable;
	float Upp;
	float Freq;
	uint64_t Seed;
} Noise_setup_struct;

void AWG_Load_Waveform(AWG_setup_struct AWG1);

void Noise_Set_CLK1(uint32_t freq);

void NOISE_Load_param(Noise_setup_struct NOISE1);


#endif /* AWG_H_ */

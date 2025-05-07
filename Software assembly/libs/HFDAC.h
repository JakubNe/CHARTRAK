/*
 * HFDAC.h
 *
 *  Created on: Jul 6, 2024
 *      Author: pavlovic
 */

#ifndef HFDAC_H_
#define HFDAC_H_

#include "stdint.h"

#define VoltageFeedback_GAIN 2.0/15.0 					//	2k/15k
#define CurrentFeedback_GAIN (10.0/1.0) * 500.0 * (2.0/2.0)	//	10k/1k * 500m * (2k/2k)

typedef enum{
	Voltage_output = 0,
	Current_output
} HFDAC_MODE;

typedef struct{
	HFDAC_MODE mode;
	float maxAmplitudeU_V;
	float maxAmplitudeI_mA;
	float offset;
	float relativeDACcodeCoefU_V;
	float relativeDACcodeCoefI_mA;
}HFDAC_struct;

void HFDAC_SET_MAX_AMPLITUDE(HFDAC_struct* HFDAC);
void HFDAC_DIRECT_DATA(HFDAC_struct* HFDAC, uint16_t data);
void HFDAC_SET_ALL(HFDAC_struct* HFDAC);

#endif /* HFDAC_H_ */

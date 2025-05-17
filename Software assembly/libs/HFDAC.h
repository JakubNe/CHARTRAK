/*
 * HFDAC.h
 *
 *  Created on: Jul 6, 2024
 *      Author: pavlovic
 */

#ifndef HFDAC_H_
#define HFDAC_H_

#include "stdint.h"

#define VoltageFeedback_GAIN 2.0/15.0 							//	2k/15k
#define CurrentFeedback_GAIN 2.0/5.1 * (10.0/1.0) * 0.5/1000.0	//	22k/1k * 500m * (2k/2k)

#define VoltageOffset_GAIN 	6.2/15.0 						//	6k2/15k
#define CurrentOffset_GAIN 	6.2/5.1 * (10.0/1.0) * 0.5/1000.0	//	22k/1k * 500m * (6k2/2k)

typedef enum{
	Voltage_output = 0,
	Current_output
} HFDAC_MODE;

typedef struct{
	HFDAC_MODE mode;
	float maxAmplitudeU_V;
	float maxAmplitudeI_mA;

	float offsetU_V;
	float offsetI_mA;

	float relativeDACcodeCoefU_V;
	float relativeDACcodeCoefI_mA;
}HFDAC_struct;

void HFDAC_SET_MAX_AMPLITUDE(HFDAC_struct* HFDAC);
void HFDAC_SET_OFFSET(HFDAC_struct* HFDAC);
void HFDAC_DIRECT_DATA(HFDAC_struct* HFDAC, uint16_t data);
void HFDAC_SET_ALL(HFDAC_struct* HFDAC);

#endif /* HFDAC_H_ */

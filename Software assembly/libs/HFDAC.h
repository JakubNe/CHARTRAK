/*
 * HFDAC.h
 *
 *  Created on: Jul 6, 2024
 *      Author: pavlovic
 */

#ifndef HFDAC_H_
#define HFDAC_H_

typedef enum{
	Voltage_output = 0,
	Current_output
} HFDAC_MODE;

typedef struct{
	HFDAC_MODE mode;
	float maxAmplitude;
	float offset;
	float relativeDACcodeCoef;
}HFDAC_struct;

void HFDAC_SET_MAX_AMPLITUDE(HFDAC_struct* HFDAC);
void HFDAC_DIRECT_DATA(HFDAC_struct* HFDAC, float value);
void HFDAC_SET_ALL(HFDAC_struct* HFDAC);

#endif /* HFDAC_H_ */

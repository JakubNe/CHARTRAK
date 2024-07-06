/*
 * HFADC.h
 *
 *  Created on: Jul 4, 2024
 *      Author: Admin
 */

#ifndef HFADC_H_
#define HFADC_H_

#include <stdint.h>


#define HFADCfrontendGain 3.1 // 6k2 / (1k * 2)
#define maxValOf11Bit 2048

#define HFADCoutVoltageGain 0
#define HFADCoutCurrentGain 0
#define HFADCinGain 47.0 // 47k / 1k
#define HFADCuioGain 1.0 // direct feed

typedef enum{
	Voltage_input = 0,
	Current_input
}HFADCmode;

typedef enum{
	OUT = 0,
	IN,
	UIO
}HFADCsource;

typedef struct{
	HFADCsource source;
	HFADCmode mode;
	uint8_t UIO_channel;
	float OUT_MEASURING_OFFSET;
	float ADCref;
}HFADC_struct;

float HFADC_CONVERT_RAW2VALUE(HFADC_struct* HFADC, uint16_t RAW);
uint16_t HFADC_CONVERT_VALUE2RAW(HFADC_struct* HFADC, float VALUE);

void HFADC_SET_ALL(HFADC_struct* HFADC);
void HFADC_ENABLE(uint8_t EN);


#endif /* HFADC_H_ */

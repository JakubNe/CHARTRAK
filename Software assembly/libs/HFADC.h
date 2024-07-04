/*
 * HFADC.h
 *
 *  Created on: Jul 4, 2024
 *      Author: Admin
 */

#ifndef HFADC_H_
#define HFADC_H_

#include <stdint.h>

extern typedef struct{
	HFADCsource HFADCsource;
	HFADCmode HFADCmode;
	uint8_t UIO_channel;
	float ADCref;
}HFADC_struct;

typedef enum{
	Voltage = 0,
	Current
}HFADCmode;

typedef enum{
	OUT = 0,
	IN,
	UIO
}HFADCsource;

float HFADC_CONVERT_DATA(int16_t RAW);

#endif /* HFADC_H_ */

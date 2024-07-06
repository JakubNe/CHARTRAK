/*
 * HFADC.c
 *
 *  Created on: Jul 4, 2024
 *      Author: Admin
 */

#include "HFADC.h"
#include "ProgRef.h"
#include "TCA9555.h"

float HFADC_CONVERT_RAW2VALUE(HFADC_struct* HFADC, uint16_t RAW)
{
	float VALUE = HFADCfrontendGain * HFADC->ADCref * (RAW/(maxValOf11Bit*1.0));

	switch(HFADC->source)
	{
		case OUT: if(HFADC->mode == Voltage_input) VALUE *= HFADCoutVoltageGain;
				  else 						 	   VALUE *= HFADCoutCurrentGain;
		break;

		case IN: VALUE *= HFADCinGain; break;

		case UIO: VALUE *= HFADCuioGain; break;

		default: VALUE = 0; break;
	}

	return VALUE;
}

uint16_t HFADC_CONVERT_VALUE2RAW(HFADC_struct* HFADC, float VALUE)
{
	uint16_t RAW = 0;


	return RAW;
}

void HFADC_SET_ALL(HFADC_struct* HFADC)
{
	ADCREF(HFADC->ADCref);


	return;
}

void HFADC_ENABLE(uint8_t EN)
{

}

void HFADC_SET_SOURCE(uint8_t UIOsource)
{

}

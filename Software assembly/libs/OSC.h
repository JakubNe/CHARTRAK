/*
 * OSC.h
 *
 *  Created on: May 20, 2024
 *      Author: Admin
 */

#ifndef OSC_H_
#define OSC_H_

#include <stdint.h>
#include "HFADC.h"

	typedef enum{
		none = 0,
		rising,
		falling,
		both
	} trigMode;

	typedef struct{
		float triggerLevel;
		trigMode trigMode;
		uint16_t samplesAfterTrig;
		uint32_t prescaler;
	} OSC_struct;

	void OSC_SET_ALL(OSC_struct* OSC, HFADC_struct* HFADC);
	uint8_t OSC_GET_STATUS();
	void OSC_INIT_SAMPLING();
	void OSC_SET_TRIGGER_VAL(OSC_struct* OSC, HFADC_struct* HFADC);
	void OSC_SET_TRIGGER_MODE(OSC_struct* OSC);
	void OSC_SET_SAMPLES_AFTER_TRIGGER(OSC_struct* OSC);
	void OSC_SET_PRESCALER(OSC_struct* OSC);
	uint16_t OSC_GET_TRIGGER_ADDRESS(OSC_struct* OSC);
	uint16_t OSC_GET_DATA_RAW(OSC_struct* OSC);

#endif /* OSC_H_ */

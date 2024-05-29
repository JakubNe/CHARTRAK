/*
 * OSC.h
 *
 *  Created on: May 20, 2024
 *      Author: Admin
 */

#ifndef OSC_H_
#define OSC_H_

	typedef enum trigmode_{
		none = 0,
		rising,
		falling,
		both
	} trigMode;

	typedef struct OSCsetup_{
		uint16_t triggerLevel = 0;
		trigMode trigMode = none;
		uint16_t samplesAfterTrig = 0;
		uint32_t prescaler = 1;
	} OSCsetup;



#endif /* OSC_H_ */

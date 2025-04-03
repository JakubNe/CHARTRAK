/*
 * board.h
 *
 *  Created on: Feb 13, 2024
 *      Author: Filip Pavlovic
 *
 *      Board capabilities
 */

#include "units.h"

#ifndef BOARD_H_
#define BOARD_H_

#define MCLKfreq 	40000000.0	//Hz

#define DACmaxFreq 	20000000.0 	//Hz

#define ADCmaxFreq 	40000000.0	//Hz
#define ADCMAXVAL	4096		// 12bit ADC

extern SPI_HandleTypeDef hspi1;

#define SerialNumber 1
#define DEVICE_ID 0x000f

//Analog stuff
#define	BOARD_VREF	2.5

// Driver stuff
#define DRIVER_MAXTEMP 		95	// exeeding this temperature will turn off the device until temperature falls under DRIVER_RECOVERYTEMP
#define DRIVER_RECOVERYTEMP	50
#define VoltageReserve		0.8 // when outputing sine with peak values of 1V and -0.5V, the PSU will be set to 1V+VoltageReserve and -0.5V-VoltageReserve

#define DRIVER_NTCPULLUP	10000
#define DRIVER_NTCR25		10000
#define DRIVER_NTCB			3455

// PSU stuff
#define PSU_REFDACBITS		8
#define PSU_MAXVOLTAGE		20
#define PSU_MINVOLTAGE		5
#define PSU_MAXDIFFVOLTAGE	35

// ADC and temperature stuff
#define AVG_SLOPE	4.3
#define V_AT_25C 	1.43
#define V_REF_INT	1.2

#endif /* BOARD_H_ */

/*
 * board.h
 *
 *  Created on: Feb 13, 2024
 *      Author: Filip Pavlovic
 *
 *      Board capabilities
 */

//#include "units.h"

#ifndef BOARD_H_
#define BOARD_H_

#define MCLKfreq 	100000000.0	//Hz

#define DACmaxFreq 	20000000.0 	//Hz

#define ADCmaxFreq 	40000000.0	//Hz
#define ADCMAXVAL	4096		// 12bit ADC

extern SPI_HandleTypeDef hspi1;

#define SerialNumber 1

#endif /* BOARD_H_ */

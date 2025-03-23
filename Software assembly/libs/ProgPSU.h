/*
 * ProgPSU.h
 *
 *  Created on: Feb 16, 2025
 *      Author: Admin
 */

#ifndef PROGPSU_H_
#define PROGPSU_H_

#include "stdint.h"

uint8_t PSUinit(uint8_t DAC_I2Caddress);
void PSUsetVoltage(float pos, float neg);
void PSUoutput(uint8_t enable);

#endif /* PROGPSU_H_ */

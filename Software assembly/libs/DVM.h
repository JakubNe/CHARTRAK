/*
 * DVM.h
 *
 *  Created on: Jul 1, 2024
 *      Author: Admin
 */

#ifndef DVM_H_
#define DVM_H_

#include <stdint.h>

extern int16_t DVM_RAW;

int16_t DVM_GET_DATA_RAW();
int16_t DVM_GET_FILTERED_DATA_RAW(uint16_t NoSamples);

#endif /* DVM_H_ */

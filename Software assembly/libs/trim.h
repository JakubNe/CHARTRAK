/*
 * TRIM.H
 *
 *  Created on: Feb 14, 2024
 *      Author: Admin
 */

#ifndef TRIM_H_
#define TRIM_H_

int16_t to_signed_12bit(uint16_t value);
int trimInt(int integer, int min, int max);
float trimFloat(float floating, float min, float max);
int trimString(char* str, uint16_t size);

int checkInt(int input, float min, float max);
int checkFloat(float input, float min, float max);

#endif /* TRIM_H_ */

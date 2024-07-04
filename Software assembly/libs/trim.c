/*
 * trim.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Filip Pavlovic
 */

#include "stdint.h"

int16_t to_signed_12bit(uint16_t value)
{
    // Mask to get the lower 12 bits
    value &= 0x0FFF;

    // Check if the sign bit (bit 11) is set
    if (value & 0x0800) {
        // If sign bit is set, make it negative
        value |= 0xF000; // Set the upper 4 bits to 1 to preserve the sign in 16-bit signed int
    }

    return (int16_t)value;
}

int trimInt(int integer, int min, int max)
{
	if(integer>max) integer = max;
	else if(integer<min) integer = min;
	return integer;
}

float trimFloat(float floating, float min, float max)
{
	if(floating>max) floating = max;
	else if(floating<min) floating = min;
	return floating;
}

int trimString(char* str, uint16_t size)
{
	int i;
	for(i = 0; i < size && str[i] != '\0'; i++)	// format into proper string so stdlib.h can be used
	{
		if(str[i] == '\r' || str[i] == '\n')
		{
			str[i] = '\0';
			break;
		}
	}
	return i;
}

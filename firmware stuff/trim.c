/*
 * trim.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Filip Pavlovic
 */

#include "stdint.h"

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

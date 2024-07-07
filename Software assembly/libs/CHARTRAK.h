/*
 * CHARTRAK.h
 *
 *  Created on: Mar 27, 2024
 *      Author: Admin
 */
#include <stdint.h>

#ifndef CHARTRAK_H_
#define CHARTRAK_H_

typedef enum{
	Open = 0,
	Short,
	R,
	CharFunc
} characteristics;

typedef struct{
	characteristics characteristic;
	float Uamp;
} CHT_struct;

void CHT_Load_Characteristics(CHT_struct CHT1);

#endif /* CHARTRAK_H_ */

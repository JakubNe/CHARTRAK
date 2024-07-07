/*
 * process.h
 *
 *  Created on: Jul 7, 2024
 *      Author: pavlo
 */

#include <stdint.h>

#ifndef PROCESS_H_
#define PROCESS_H_

#define MAX_PROCESS 20

typedef enum{
	PROCESS_DONE = 0,
	PROCESS_LOLA_CONFIG
}processes;

typedef struct{
	uint8_t processQuery[MAX_PROCESS];
	uint8_t processSize;
}ProcessList_struct;

void process_init(ProcessList_struct* PROCESSLIST);
uint8_t process_add(ProcessList_struct* PROCESSLIST, processes processEnum);
void process_finish(ProcessList_struct* PROCESSLIST);

#endif /* PROCESS_H_ */

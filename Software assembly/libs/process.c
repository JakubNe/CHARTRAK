/*
 * process.c
 *
 *  Created on: Jul 7, 2024
 *      Author: pavlo
 */

#include "process.h"
#include <stdint.h>
#include <string.h>

void process_init(ProcessList_struct* PROCESSLIST)
{
	memset(PROCESSLIST->processQuery, 0, MAX_PROCESS-1 * sizeof(uint8_t));
	PROCESSLIST->processSize = 0;
}

uint8_t process_add(ProcessList_struct* PROCESSLIST, processes processEnum)
{
	if(PROCESSLIST->processSize >= MAX_PROCESS) return 0;

	PROCESSLIST->processQuery[PROCESSLIST->processSize] = processEnum;
	PROCESSLIST->processSize += 1;
	return 1;
}

void process_finish(ProcessList_struct* PROCESSLIST)
{
	if(PROCESSLIST->processSize != 0) return;

	for(uint8_t i = 0; i < MAX_PROCESS-1; i++) PROCESSLIST->processQuery[i] = PROCESSLIST->processQuery[i+1];
	PROCESSLIST->processQuery[MAX_PROCESS-1] = 0;
	PROCESSLIST->processSize -= 1;
}

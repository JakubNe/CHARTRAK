/*
 * SCPI_Commands.c
 *
 *  Created on: Jul 1, 2024
 *      Author: kuban
 */

#include "SCPI_Commands.h"

void SCPIC_DVM_RAW(struct subword** subwords, int length)
{
	if(length != 1) return;
		if(subwords[0]->type != params) return;
		Subword* subword = subwords[0];

		if(subword->type == params && subword->paramType == EVAL_P)
		{
			int16_t DVM = DVM_GET_FILTERED_DATA_RAW(100);
			sprintf(TXbuff, "%d\r\n", DVM);
		}
}

void SCPIC_DVM_VAL(struct subword** subwords, int length)
{
	if(length != 1) return;
		if(subwords[0]->type != params) return;
		Subword* subword = subwords[0];

		if(subword->type == params && subword->paramType == EVAL_P)
		{
			char unit = 'V';
			float DVM = HFADC_CONVERT_RAW2VALUE(&HFADC1, DVM_GET_FILTERED_DATA_RAW(100));
			if(HFADC1.mode == Current_input) unit = 'A';
			sprintf(TXbuff, "%f%c\r\n", DVM, unit);
		}
}

void SCPIC_INIT(struct subword** subwords, int length)
{
	if(length != 1) return;
		if(subwords[0]->type != params) return;
		Subword* subword = subwords[0];

		if(subword->type == params && subword->paramType == EVAL_P)
		{
			switch(LOLA1.Status)
			{
				case INVALID_FIRMWARE: strcpy(TXbuff, "INVALID FIRMWARE"); break;
				case FIRMWARE_OK: strcpy(TXbuff, "OK"); break;
				default: strcpy(TXbuff, "NO FIRMWARE"); break;
			}
		}
	// ak :1 tak if(process_add(PROCESS, PROCESS_LOLA_CONFIG)) strcpy(TXbuff, "OK");
	//	 	 	 else										 strcpy(TXbuff, "ERR:PROCESS QUERY FULL");
}

void SCPIC_CFS(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->type == params && subword->paramType == EVAL_P)
	{
		switch((uint8_t)LOLA1.Status)
		{
			case INVALID_FIRMWARE: strcpy(TXbuff, "INVALID FIRMWARE"); break;
			case FIRMWARE_OK: strcpy(TXbuff, "OK"); break;
			default: strcpy(TXbuff, "NO FIRMWARE"); break;
		}
	}
}

void SCPIC_FID(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];
	strcpy(TXbuff,"OK\r\n");

	if(subword->type == params && subword->paramType == EVAL_P)
	{
		uint16_t id = LOLA_GET_FIRMWAREID();
		sprintf(TXbuff, "%x\r\n", id);
	}
	/*switch (subword.paramType)
	{
		case INT_P:

			break;

		case ON_P:

			break;

		case OFF_P:

			break;

		case EVAL_P:

			break;

		case OTHER_P:

			break;

		default:

			break;
	}*/
}

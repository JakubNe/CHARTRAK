/*
 * SCPI_Commands.c
 *
 *  Created on: Jul 1, 2024
 *      Author: kuban
 */

#include "SCPI_Commands.h"

void SCPIC_CFS(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->type == params && subword->paramType == EVAL_P)
	{
		char message[20];

		switch((uint8_t)LOLA1.Status)
		{
			case INVALID_FIRMWARE: strcpy(message, "INVALID FIRMWARE"); break;
			case FIRMWARE_OK: strcpy(message, "OK"); break;
			default: strcpy(message, "ERR"); break;
		}
		sprintf(TXbuff, "%s\r\n", message);
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

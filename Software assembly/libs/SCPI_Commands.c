/*
 * SCPI_Commands.c
 *
 *  Created on: Jul 1, 2024
 *      Author: kuban
 */

#include "SCPI_Commands.h"


void SCPIC_FID(struct subword* subwords, int length)
{
	if(length != 1) return;
	if(subwords->type != params) return;
	Subword subword = *subwords;
	strcpy(TXbuff,"OK\r\n");

	if(subword.type == params && subword.paramType == EVAL_P)
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

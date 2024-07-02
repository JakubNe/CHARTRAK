/*
 * SCPI_Commands.c
 *
 *  Created on: Jul 1, 2024
 *      Author: kuban
 */

#include "SCPI_Commands.h"


void SCPIC_LOLA(struct subword* subwords, int length)
{
	if(length != 2) return;
	if(subwords[0].type != params) return;
	struct subword subword = subwords[0];
	strcpy(TXbuff,"OK\n\r");

	if(subword.type == params && subword.paramType == OTHER_P && strcmp(subword.otherParam, "FID"))
	{
		if(++subword.paramType == params && subword.paramType == EVAL_P)
		{
			uint16_t id = LOLA_GET_FIRMWAREID();
			sprintf(TXbuff, "%d\n\r", id);
		}
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

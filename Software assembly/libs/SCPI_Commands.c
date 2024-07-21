/*
 * SCPI_Commands.c
 *
 *  Created on: Jul 1, 2024
 *      Author: kuban
 */

#include "SCPI_Commands.h"

void SCPIC_SYS_APPLY(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->paramType == INT_P)
	{
		if(subword->integerParam)
		{
			HFDAC_SET_ALL(&HFDAC1);
			HFADC_SET_ALL(&HFADC1);
			OSC_SET_ALL(&OSC1, &HFADC1);
			AWG_Load_Waveform(&AWG1, &HFDAC1);

			strcpy(TXbuff, "OK");
		}
	}
}

void SCPIC_SYS_RESET(struct subword** subwords, int length)
{
	if(length != 1) return;
		if(subwords[0]->type != params) return;
		Subword* subword = subwords[0];

		if(subword->paramType == INT_P)
		{
			if(subword->integerParam)
			{
				strcpy(TXbuff, "OK");
				HAL_NVIC_SystemReset();
			}
		}
}

void SCPIC_SYS_ID(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->paramType == EVAL_P)
	{
		sprintf(TXbuff, "%x\r\n", DEVICE_ID);
	}
}



void SCPIC_OUT_MAXAMPLITUDE(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->paramType == FLOAT_P)
	{
		if(checkFloat(subword->floatParam, 20, 0))
		{
			HFDAC1.maxAmplitude = subword->floatParam;
			strcpy(TXbuff, "OK");
		}
		else strcpy(TXbuff, "ERR:VAL");
	}
}

void SCPIC_OUT_MODE(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	switch(subword->paramType)
	{
		case EVAL_P:
			switch(HFDAC1.mode)
			{
				case Voltage_output: strcpy(TXbuff, "VOLTAGE"); break;
				case Current_output: strcpy(TXbuff, "CURRENT"); break;
			}
		break;

		case OTHER_P:
			if(!strcmp(subword->otherParam, "VOLTAGE"))
			{
				HFDAC1.mode = Voltage_output;
				strcpy(TXbuff, "OK");
			}
			else if(!strcmp(subword->otherParam, "CURRENT"))
			{
				HFDAC1.mode = Current_output;
				strcpy(TXbuff, "OK");
			}
		break;
	}

}



void SCPIC_DVM_RAW(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->paramType == EVAL_P)
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

	if(subword->paramType == EVAL_P)
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

	switch(subword->paramType)
	{
		case EVAL_P:
			switch(LOLA1.Status)
			{
				case INVALID_FIRMWARE: strcpy(TXbuff, "INVALID FIRMWARE"); break;
				case FIRMWARE_OK: strcpy(TXbuff, "OK"); break;
				default: strcpy(TXbuff, "NO FIRMWARE"); break;
			}
		break;

		case OTHER_P:
			if(!strcmp(subword->otherParam, "JTAG"))
			{
				LOLA1.Config = JTAG;
				if(Task_add(Task_LOLA_INIT, PRIORITY_URGENT, 10000, 20)) strcpy(TXbuff, "OK");
			}
			else if(!strcmp(subword->otherParam, "FLASH"))
			{
				LOLA1.Config = SPI_FLASH;
				if(Task_add(Task_LOLA_INIT, PRIORITY_URGENT, 10000, 20)) strcpy(TXbuff, "OK");
			}
	}

}

void SCPIC_FID(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];
	strcpy(TXbuff,"OK\r\n");

	if(subword->paramType == EVAL_P)
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



//void SCPIC_AWG_WF(struct subword** subwords, int length)
//{

//}

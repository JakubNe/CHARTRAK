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
		int* param = (int*)subword->param;
		if(*param)
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
		int* param = (int*)subword->param;
		if(*param)
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
		float* param = (float*) subword->param;
		if(checkFloat(*param, 20, 0))
		{
			HFDAC1.maxAmplitude = *param;
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
			if(!strcmp(subword->param, "VOLTAGE"))
			{
				HFDAC1.mode = Voltage_output;
				strcpy(TXbuff, "OK");
			}
			else if(!strcmp(subword->param, "CURRENT"))
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
			if(!strcmp(subword->param, "JTAG"))
			{
				LOLA1.Config = JTAG;
				if(Task_add(Task_LOLA_INIT, PRIORITY_URGENT, 10000, 20)) strcpy(TXbuff, "OK");
			}
			else if(!strcmp(subword->param, "FLASH"))
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



void SCPIC_AWG_WF(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	switch(subword->paramType)
	{
		case EVAL_P:
			switch(AWG1.waveform)
			{
				case Square: strcpy(TXbuff, "Square\r\n"); break;
				case Triangle: strcpy(TXbuff, "Triangle\r\n"); break;
				case Sine: strcpy(TXbuff, "Sine\r\n"); break;
				case Func: strcpy(TXbuff, "Func\r\n"); break;
				default: strcpy(TXbuff, "Wrong waveform\r\n"); break;
			}
		break;

		case OTHER_P:
			if(!strcmp(subword->param, "Square"))
			{
				AWG1.waveform = Square;
			}
			else if(!strcmp(subword->param, "Triangle"))
			{
				AWG1.waveform = Triangle;
			}
			else if(!strcmp(subword->param, "Sine"))
			{
				AWG1.waveform = Sine;
			}
			else if(!strcmp(subword->param, "Func"))
			{
				AWG1.waveform = Func;
			}
			else
			{
				strcpy(TXbuff, "Wrong value!!\r\n");
				break;
			}
			strcpy(TXbuff, "OK\r\n");
		break;
	}
}

void SCPIC_AWG_DC(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	float* param = NULL;
	switch(subword->paramType)
	{
		case EVAL_P:
			sprintf(TXbuff, "%f\r\n", AWG1.DutyCycle);
		break;

		case FLOAT_P:
			param = (float*) subword->param;
			if(checkFloat(*param, 0, 100))
			{
				strcpy(TXbuff, "Invalid value\r\n");
				break;
			}
			AWG1.DutyCycle = *param;
			strcpy(TXbuff, "OK\r\n");
		break;
	}
}

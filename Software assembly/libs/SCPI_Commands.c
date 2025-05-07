/*
 * SCPI_Commands.c
 *
 *  Created on: Jul 1, 2024
 *      Author: kuban
 */

#include "SCPI_Commands.h"

void SCPIC_SYS_STATUS(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->paramType == EVAL_P)
	{
		switch(LOLA1.Status)
		{
			case NO_FIRMWARE:
				sprintf(TXbuff, "NO FPGA FIRMWARE DETECTED");
			break;

			case INVALID_FIRMWARE:
				sprintf(TXbuff, "INVALID FPGA FIRMWARE DETECTED");
			break;

			case FIRMWARE_OK:
				sprintf(TXbuff, "OK");
			break;
		}
	}
}

void SCPIC_SYS_TEMP(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->paramType == EVAL_P)
	{
		sprintf(TXbuff, "%.1fC\r\n", DriverTemp);
	}
}

void SCPIC_SYS_APPLY(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	if(subword->paramType == OTHER_P)
	{
		int* param = (int*)subword->param;
		if(*param)
		{
			strcpy(TXbuff, "OK");

			if(!strcmp(subword->param, "ALL") )
			{
				HFDAC_SET_ALL(&HFDAC1);
				HFADC_SET_ALL(&HFADC1);
				OSC_SET_ALL(&OSC1, &HFADC1);
				AWG_Load_Waveform(&AWG1, &HFDAC1);
			}
			else if(!strcmp(subword->param, "HFDAC"))
			{
				HFDAC_SET_ALL(&HFDAC1);
			}
			else if(!strcmp(subword->param, "HFADC"))
			{
				HFADC_SET_ALL(&HFADC1);
			}
			else if(!strcmp(subword->param, "OSC"))
			{
				OSC_SET_ALL(&OSC1, &HFADC1);
			}
			else if(!strcmp(subword->param, "AWG"))
			{
				AWG_Load_Waveform(&AWG1, &HFDAC1);
			}
			else
			{
				strcpy(TXbuff, "Invalid value\r\n");
			}

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



void SCPIC_OUT_MAXAMPU(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	float* param = NULL;
	switch(subword->paramType)
	{
		case EVAL_P:
			sprintf(TXbuff, "%.3fV\r\n", HFDAC1.maxAmplitudeU_V);
		break;

		case FLOAT_P:
			param = (float*) subword->param;
			if(!checkFloat(*param, 0, 20))
			{
				strcpy(TXbuff, "Invalid value\r\n");
				break;
			}
			HFDAC1.maxAmplitudeU_V = *param;
			strcpy(TXbuff, "OK\r\n");
		break;
	}
}

void SCPIC_OUT_MAXAMPI(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	float* param = NULL;
	switch(subword->paramType)
	{
		case EVAL_P:
			sprintf(TXbuff, "%.3fmA\r\n", HFDAC1.maxAmplitudeI_mA);
		break;

		case FLOAT_P:
			param = (float*) subword->param;
			if(!checkFloat(*param, 0, 1000))
			{
				strcpy(TXbuff, "Invalid value\r\n");
				break;
			}
			HFDAC1.maxAmplitudeI_mA = *param;
			strcpy(TXbuff, "OK\r\n");
		break;
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

			HFDAC_MODE previousMode = HFDAC1.mode;

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
			else
				strcpy(TXbuff, "Invalid value");

			if(previousMode != HFDAC1.mode) LOLA_enable_features(ALL_EN, 0);
		break;
	}

}

void SCPIC_OUT_EN(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	int* param = NULL;
	switch(subword->paramType)
	{
		case EVAL_P:
			if(LOLA1.outputEN) 	sprintf(TXbuff, "ON\r\n");
			else 				sprintf(TXbuff, "OFF\r\n");
		break;

		case ON_P:
			if(LOLA1.Status != FIRMWARE_OK)
				sprintf(TXbuff, "ERR:CONFIG");
			else
			{
				LOLA1.outputEN = 1;
				LOLA_Output(&LOLA1, LOLA1.outputEN);
				strcpy(TXbuff, "OK");
			}

		break;

		case OFF_P:
			LOLA1.outputEN = 0;
			LOLA_Output(&LOLA1, LOLA1.outputEN);
			strcpy(TXbuff, "OK");
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
				LOLA1.Config = JTAG_Ext;
				if(Task_add(Task_LOLA_INIT, PRIORITY_URGENT, 10000, 20)) strcpy(TXbuff, "OK");
			}
			else if(!strcmp(subword->param, "FLASH1"))
			{
				LOLA1.Config = SPI_FLASH1;
				if(Task_add(Task_LOLA_INIT, PRIORITY_URGENT, 10000, 20)) strcpy(TXbuff, "OK");
			}
			else if(!strcmp(subword->param, "FLASH2"))
			{
				LOLA1.Config = SPI_FLASH2;
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
				strcpy(TXbuff, "Invalid value\r\n");
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
			sprintf(TXbuff, "%.2f%%\r\n", AWG1.DutyCycle);
		break;

		case FLOAT_P:
			param = (float*) subword->param;
			if(!checkFloat(*param, 0, 100))
			{
				strcpy(TXbuff, "Invalid value\r\n");
				break;
			}
			AWG1.DutyCycle = *param;
			strcpy(TXbuff, "OK\r\n");
		break;
	}
}

void SCPIC_AWG_FREQ(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	float* param = NULL;
	switch(subword->paramType)
	{
		case EVAL_P:
			sprintf(TXbuff, "%.3fHz\r\n", AWG1.Freq);
		break;

		case FLOAT_P:
			param = (float*) subword->param;
			if(!checkFloat(*param, 0, AWG_MaxFreq))
			{
				strcpy(TXbuff, "Invalid value\r\n");
				break;
			}
			AWG1.Freq = *param;
			strcpy(TXbuff, "OK\r\n");
		break;
	}
}

void SCPIC_AWG_AMPU(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	float* param = NULL;
	switch(subword->paramType)
	{
		case EVAL_P:
			sprintf(TXbuff, "%.3fV\r\n", AWG1.Uamp);
		break;

		case FLOAT_P:
			param = (float*) subword->param;
			if(!checkFloat(*param, 0, 20))
			{
				strcpy(TXbuff, "Invalid value\r\n");
				break;
			}
			AWG1.Uamp = *param;
			strcpy(TXbuff, "OK\r\n");
		break;
	}
}

void SCPIC_AWG_AMPI(struct subword** subwords, int length)
{
	if(length != 1) return;
	if(subwords[0]->type != params) return;
	Subword* subword = subwords[0];

	float* param = NULL;
	switch(subword->paramType)
	{
		case EVAL_P:
			sprintf(TXbuff, "%.3fmA\r\n", AWG1.Iamp);
		break;

		case FLOAT_P:
			param = (float*) subword->param;
			if(!checkFloat(*param, 0, 1000))
			{
				strcpy(TXbuff, "Invalid value\r\n");
				break;
			}
			AWG1.Iamp = *param;
			strcpy(TXbuff, "OK\r\n");
		break;
	}
}

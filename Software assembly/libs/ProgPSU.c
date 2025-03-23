/*
 * ProgPsu.c
 *
 *  Created on: Feb 16, 2025
 *      Author: Admin
 */

#include "ProgPSU.h"

#include "stdint.h"
#include "mcp47feb.h"
#include "trim.h"
#include "main.h"
#include "board.h"

MCP47FEB_TypeDef PsuDac;

uint8_t PSUinit(uint8_t DAC_I2Caddress)
{
	if(HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(DAC_I2Caddress << 1), 3, 5) != HAL_OK) return 0;

	MCP47FEB_Init(&PsuDac, DAC_I2Caddress, &hi2c1);

	MCP47FEB_LockSALCK(&PsuDac);

	MCP47FEB_SetWiperLock(&PsuDac, 0x00, 0x00);
	PSUoutput(0);
	MCP47FEB_SetGain(&PsuDac, 0x00, 0x00);
	MCP47FEB_SetVref(&PsuDac, 0b11, 0b11); // set external buffered reference

	return 1;
}

void PSUsetVoltage(float pos, float neg)
{
	pos = trimFloat(pos, PSU_MINVOLTAGE, PSU_MAXVOLTAGE);
	neg = trimFloat(neg, -PSU_MAXVOLTAGE, -PSU_MINVOLTAGE);

	if((pos - neg) > PSU_MAXDIFFVOLTAGE) // if the set voltage is higher than max differential voltage, trim both pos and neg voltages
	{
		float adjust = (pos - neg) - PSU_MAXDIFFVOLTAGE;

		if(neg + adjust/2 > -PSU_MINVOLTAGE)
			pos -= adjust;
		else if(pos - adjust/2 < PSU_MINVOLTAGE)
			neg += adjust;
		else
		{
			pos -= adjust/2;
			neg += adjust/2;
		}
	}

	float dacVpos = pos * 1.0 / (1.0 + 22.0); // convert acording to voltage divider
	uint16_t posRaw  = 1 + (1 << PSU_REFDACBITS) * dacVpos / BOARD_VREF;

	float dacVneg = neg * -1.0 / 22.0;	// convert acording to inverting opamp gain
	uint16_t negRaw  = 1 + (1 << PSU_REFDACBITS) * dacVneg / BOARD_VREF;

	MCP47FEB_AnalogWrite(&PsuDac, posRaw, negRaw);
}

void PSUoutput(uint8_t enable)
{
	uint8_t powerDownRegister = enable ? 0x00 : 0x01;
	MCP47FEB_SetPowerDown(&PsuDac, powerDownRegister, powerDownRegister);
}

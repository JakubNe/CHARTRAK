/*
 * SCPI_Commands.h
 *
 *  Created on: Jul 1, 2024
 *      Author: kuban
 */

#ifndef SCPI_COMMANDS_H_
#define SCPI_COMMANDS_H_

#include "SCPI_Lib.h"
#include "main.h"
#include "RS485.h"
#include "LOLA.h"
#include "HFADC.h"
#include "trim.h"
#include "SimpleOS.h"
#include "Tasks.h"
#include "board.h"

void SCPIC_SYS_APPLY(struct subword** subwords, int length);
void SCPIC_SYS_RESET(struct subword** subwords, int length);
void SCPIC_SYS_ID(struct subword** subwords, int length);

void SCPIC_OUT_MAXAMPLITUDE(struct subword** subwords, int length);
void SCPIC_OUT_MODE(struct subword** subwords, int length);

void SCPIC_DVM_RAW(struct subword** subwords, int length);
void SCPIC_DVM_VAL(struct subword** subwords, int length);

void SCPIC_INIT(struct subword** subwords, int length);
void SCPIC_FID(struct subword** subwords, int length);

void SCPIC_AWG_WF(struct subword** subwords, int length);
void SCPIC_AWG_DC(struct subword** subwords, int length);

#endif /* SCPI_COMMANDS_H_ */

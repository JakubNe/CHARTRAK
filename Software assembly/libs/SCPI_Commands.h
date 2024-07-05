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

void SCPIC_INIT(struct subword** subwords, int length);
void SCPIC_FID(struct subword** subwords, int length);
void SCPIC_CFS(struct subword** subwords, int length);

#endif /* SCPI_COMMANDS_H_ */

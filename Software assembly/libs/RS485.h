/*
 * RS485.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Admin
 */

#ifndef RS485_H_
#define RS485_H_

#include "main.h"

void RS485_Transmit(char *message);

#define RS485BUFFSIZE	125

extern char TXbuff[RS485BUFFSIZE];
extern char RXbuff[RS485BUFFSIZE];

extern UART_HandleTypeDef huart1;

#endif /* RS485_H_ */

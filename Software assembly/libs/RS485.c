/*
 * RS485.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Filip Pavlovic
 */

#include "main.h"
#include "RS485.h"

char TXbuff[RS485BUFFSIZE] = {0};
char RXbuff[RS485BUFFSIZE] = {0};

void RS485_Transmit(char *message)
{
	HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, 1);	// Enable Driver
	HAL_UART_Transmit(&huart1, message, strlen(message), 100);	// Transmit
	HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, 0);	// Disable Driver
}

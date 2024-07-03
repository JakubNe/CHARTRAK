/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LOLA.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern LOLAconfig_struct LOLA1;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_DACS_Pin GPIO_PIN_13
#define SPI1_DACS_GPIO_Port GPIOC
#define LDAC_Pin GPIO_PIN_14
#define LDAC_GPIO_Port GPIOC
#define Ain_Pin GPIO_PIN_0
#define Ain_GPIO_Port GPIOA
#define VselC0_Pin GPIO_PIN_1
#define VselC0_GPIO_Port GPIOA
#define VselC1_Pin GPIO_PIN_2
#define VselC1_GPIO_Port GPIOA
#define PROGB_Pin GPIO_PIN_3
#define PROGB_GPIO_Port GPIOA
#define SPI1_FPGAS_Pin GPIO_PIN_4
#define SPI1_FPGAS_GPIO_Port GPIOA
#define VselB1_Pin GPIO_PIN_0
#define VselB1_GPIO_Port GPIOB
#define VselB0_Pin GPIO_PIN_1
#define VselB0_GPIO_Port GPIOB
#define VselA1_Pin GPIO_PIN_2
#define VselA1_GPIO_Port GPIOB
#define VselA0_Pin GPIO_PIN_10
#define VselA0_GPIO_Port GPIOB
#define FPGA_IRQ_Pin GPIO_PIN_11
#define FPGA_IRQ_GPIO_Port GPIOB
#define MODE_Pin GPIO_PIN_12
#define MODE_GPIO_Port GPIOB
#define M2_Pin GPIO_PIN_13
#define M2_GPIO_Port GPIOB
#define M1_Pin GPIO_PIN_14
#define M1_GPIO_Port GPIOB
#define M0_Pin GPIO_PIN_15
#define M0_GPIO_Port GPIOB
#define DONE_Pin GPIO_PIN_8
#define DONE_GPIO_Port GPIOA
#define INITB_Pin GPIO_PIN_9
#define INITB_GPIO_Port GPIOA
#define UI_IRQ_Pin GPIO_PIN_10
#define UI_IRQ_GPIO_Port GPIOA
#define USB_detect_Pin GPIO_PIN_3
#define USB_detect_GPIO_Port GPIOB
#define DIR_Pin GPIO_PIN_5
#define DIR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

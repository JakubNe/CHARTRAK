/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
AWG_struct AWG1;
Noise_struct NOISE1;
CHT_struct CHT1;
LOLAconfig_struct LOLA1;
HFADC_struct HFADC1;
HFDAC_struct HFDAC1;
OSC_struct OSC1;

uint8_t RackID = 0;

uint32_t adc1_data[3] = {0};

float MCUtemp = 25.0, DriverTemp = 25.0;

#define MaxI2Cdevices	20
uint8_t I2Cdevices[MaxI2Cdevices] = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  	//GPIO SETUP
    HAL_GPIO_WritePin(SPI1_DACS_GPIO_Port, SPI1_DACS_Pin, 0);
    HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
    HAL_GPIO_WritePin(LDAC_GPIO_Port, LDAC_Pin, 0);
    HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, 0);


    // ADC board expander setup
    TCA_Init(0b0100001, hi2c1);

    TCA_PinMode(P07, 0);
    TCA_PinMode(P11, 0);
    TCA_PinMode(P12, 0);

    TCA_WritePin(P07, 1);
    TCA_WritePin(P11, 0);
    TCA_WritePin(P12, 0);

    // High-speed DAC setup
    DACREF(0.0);
    DACOFFS(0.0);

    // High-speed ADC setup
    ADCREF(1.2);
    ADCOFFS(0.0);

    //HAL_TIM_Base_Start_IT(&htim4);

    // system functions setup
    Function SYSfunctions[] = { {.name = "ID", .run = SCPIC_SYS_ID},
    							{.name = "STATUS", .run = SCPIC_SYS_STATUS},
								{.name = "TEMP", .run = SCPIC_SYS_TEMP},
       							{.name = "RESET", .run = SCPIC_SYS_RESET},
   								{.name = "APPLY", .run = SCPIC_SYS_APPLY}	};

    Class SYSclass = { .name = "SYS", .functions = SYSfunctions, .functionsLength = 5 };
    addClass(&SYSclass, 0);

    // output functions setup
    Function OUTfunctions[] = { {.name = "MAXAMPU", .run = SCPIC_OUT_MAXAMPU},
    							{.name = "MAXAMPI", .run = SCPIC_OUT_MAXAMPI},
								{.name = "OFFSU", .run = SCPIC_OUT_OFFSU},
								{.name = "OFFSI", .run = SCPIC_OUT_OFFSI},
           						{.name = "MODE", .run = SCPIC_OUT_MODE},
								{.name = "EN", .run = SCPIC_OUT_EN} };

    Class OUTclass = { .name = "OUT", .functions = OUTfunctions, .functionsLength = 6 };
    addClass(&OUTclass, 0);

    //SCPI setup
    Function Lolafunctions[] = { {.name = "FID", .run = SCPIC_FID},
								 {.name = "INIT", .run = SCPIC_INIT}	};

    Class Lolaclass = { .name = "LOLA", .functions = Lolafunctions, .functionsLength = 2 };
    addClass(&Lolaclass, 0);

    // Digital Voltmeter setup
    Function DVMfunctions[] = { {.name = "RAW", .run = SCPIC_DVM_RAW},
    							{.name = "VAL", .run = SCPIC_DVM_VAL}	};

    Class DVMclass = { .name = "DVM", .functions = DVMfunctions, .functionsLength = 2 };
    addClass(&DVMclass, 0);

    Function AWGfunctions[] = { {.name = "AMPU", .run = SCPIC_AWG_AMPU},
    							{.name = "AMPI", .run = SCPIC_AWG_AMPI},
    							{.name = "FREQ", .run = SCPIC_AWG_FREQ},
								{.name = "DC", .run = SCPIC_AWG_DC},
								{.name = "WF", .run = SCPIC_AWG_WF} };

    Class AWGclass = { .name = "AWG", .functions = AWGfunctions, .functionsLength = 5 };
    addClass(&AWGclass, 0);


    //SimpleOS setup
    kernel_init(20); // max 20 tasks


    //SPARTAN3 SETUP
    LOLA1.Config = JTAG_Ext;
    LOLA1.Trials = 100;
    LOLA1.compatibleFirmwareID = 0xF103;

    //High frequency DAC setup
    HFDAC1.maxAmplitudeU_V = 0;
    HFDAC1.maxAmplitudeI_mA = 0;
    HFDAC1.offsetU_V = 0;
    HFDAC1.offsetI_mA = 0;
    HFDAC1.mode = Voltage_output;

    //Hight Frequency ADC setup
    HFADC1.ADCref = 2.5;
    HFADC1.OUT_MEASURING_OFFSET = 0;
    HFADC1.source = OUT;
    HFADC1.UIO_channel = 1;
    HFADC1.UIO_channelLetter = 'A';
    HFADC1.mode = Voltage_input;

    //Oscilloscope setup
    OSC1.prescaler = 1;
    OSC1.samplesAfterTrig = 1000;
    OSC1.trigMode = rising;
    OSC1.triggerLevel = 0;

    //CharTrak setup
    CHT1.characteristic = Open;
    CHT1.Uamp = 0;

    // Arbitrary waveform generator setup
    AWG1.waveform = Square;
    AWG1.Uavg = 0.0;
    AWG1.Iavg = 0.0;
    AWG1.Uamp = 0.0;
    AWG1.Iamp = 0.0;
    AWG1.DutyCycle = 50.0;
    AWG1.Freq = 10000.0;

    // Noise generator setup
    NOISE1.Enable = 1;
    NOISE1.Freq = 1000.0;
    NOISE1.Uamp = 0.0;
    NOISE1.Seed = 0x800f000f000f0001;

    //****************************************************** scan for I2C devices
    uint8_t I2Ccount = 0;
    for(uint8_t i=1; i<128; i++)
    {
    	if(HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i << 1), 3, 5) == HAL_OK)
    	{
    	    if(I2Ccount < MaxI2Cdevices)
    	    	I2Cdevices[I2Ccount++] = i;
    	    else
    	    	Error_Handler();
    	}
    }

    // Programmable power supply setup
    if(!PSUinit(0x60)) Error_Handler();
    PSUoutput(0);

    // ADC temperature measurement
   	HAL_TIM_Base_Start(&htim3); // Start trigger Source For ADC1
   	HAL_ADC_Start_DMA(&hadc1, adc1_data, 3);

   	// RS485 receive interrupt setup
   	sprintf(TXbuff, "Initializing...\r\n");
    RS485_Transmit(TXbuff);
    HAL_Delay(10);
    if(HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*)RXbuff, RS485BUFFSIZE) != HAL_OK) Error_Handler();

   	// Initialize FPGA
    LOLA_CFGFlashWriteUnlock(&LOLA1);
    LOLA_Init(&LOLA1);

    //cfg of IN/OUT circuitry
    HFDAC_SET_ALL(&HFDAC1);
    HFADC_SET_ALL(&HFADC1);

    OSC_SET_ALL(&OSC1, &HFADC1);

    HFDAC_DIRECT_DATA(&HFDAC1, 0);
    LOLA_enable_features(ALL_EN, 0); // disable all features

    //NOISE_Load_param(NOISE1);

    //AWG_Load_Waveform(AWG1,NOISE1);

    //kernel_begin(); //////////////////////////////////// CODE DOESNT GET FURTHER

/*
    HFDAC1.maxAmplitudeU_V = 15.0;
    HFDAC_SET_MAX_AMPLITUDE(&HFDAC1);

    AWG1.Freq = 1000.0;
    AWG1.Uamp = 15.0;
    AWG1.waveform = Square;
    AWG1.DutyCycle = 40.0;
    AWG_Load_Waveform(&AWG1, &HFDAC1);*/

    //NOISE_Load_param(&NOISE1, &HFDAC1);
    //HFDAC_DIRECT_DATA(&HFDAC1, 10);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	 /*int16_t DVM = DVM_GET_FILTERED_DATA_RAW(50);
	 sprintf(TXbuff, "%d\r\n", DVM);
	 RS485_Transmit(TXbuff);
	 HAL_Delay(10);*/

	 HAL_Delay(1000);
	 //HFDAC_DIRECT_DATA(&HFDAC1, 0);
	 HAL_Delay(1000);
	 //HFDAC_DIRECT_DATA(&HFDAC1, 3);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 3;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VREFINT;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 48000-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 48000-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 50-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SPI1_DACS_Pin|LDAC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, AIO_EN_OUT_Pin|MODE_OUT_Pin|PROGB_Pin|SPI1_FPGAS_Pin
                          |FCFGSEL_OUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, VselB1_Pin|VselB0_Pin|VselA1_Pin|VselA0_Pin
                          |FLASHWP_OUT_Pin|M2_Pin|M1_Pin|M0_Pin
                          |RackJTAGen_OUT_Pin|DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SPI1_DACS_Pin LDAC_Pin */
  GPIO_InitStruct.Pin = SPI1_DACS_Pin|LDAC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : AIO_EN_OUT_Pin MODE_OUT_Pin PROGB_Pin SPI1_FPGAS_Pin
                           FCFGSEL_OUT_Pin */
  GPIO_InitStruct.Pin = AIO_EN_OUT_Pin|MODE_OUT_Pin|PROGB_Pin|SPI1_FPGAS_Pin
                          |FCFGSEL_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : VselB1_Pin VselB0_Pin VselA1_Pin VselA0_Pin
                           FLASHWP_OUT_Pin M2_Pin M1_Pin M0_Pin
                           RackJTAGen_OUT_Pin DIR_Pin */
  GPIO_InitStruct.Pin = VselB1_Pin|VselB0_Pin|VselA1_Pin|VselA0_Pin
                          |FLASHWP_OUT_Pin|M2_Pin|M1_Pin|M0_Pin
                          |RackJTAGen_OUT_Pin|DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : FPGA_IRQ_Pin */
  GPIO_InitStruct.Pin = FPGA_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(FPGA_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DONE_Pin INITB_Pin */
  GPIO_InitStruct.Pin = DONE_Pin|INITB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : UI_IRQ_Pin */
  GPIO_InitStruct.Pin = UI_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(UI_IRQ_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	 SCPI_EXECUTE();
	 RS485_Transmit(TXbuff);
	 if(HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*)RXbuff, RS485BUFFSIZE) != HAL_OK) Error_Handler();
}

#define filtCoef 0.9

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	float V_Ref = (float)((V_REF_INT * 4095.0) / adc1_data[0]); // get internal voltage reference

	// MCU internal temperature calculation
	float V_Sense = (float)(adc1_data[2] * V_Ref) / 4095.0;
	float tmp_MCUtemp = (((V_AT_25C - V_Sense) * 1000.0) / AVG_SLOPE) + 25.0;

	// Driver temperature calculation
	V_Sense = (float)(adc1_data[1] * V_Ref) / 4095.0;
	float Rntc = (V_Sense * DRIVER_NTCPULLUP)/(3.3 - V_Sense);
	float tmp_DriverTemp = 1/(logf(Rntc/DRIVER_NTCR25)/DRIVER_NTCB + 1/298.15) - 273.15;

	// IIR filter
	DriverTemp = filtCoef*DriverTemp + (1-filtCoef)*tmp_DriverTemp;
	MCUtemp = filtCoef*MCUtemp + (1-filtCoef)*tmp_MCUtemp;

	HAL_ADC_Start_DMA(&hadc1, adc1_data, 3);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

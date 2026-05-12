/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_LED		8
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int sentflag = 0;
uint8_t LED_Data[MAX_LED][4];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
			sentflag=1;
		}

	}

}

void Set_LED (int LEDnum, int Red, int Green, int Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

uint32_t pwmData[(24*MAX_LED) + 50];

void WS2812_Send()
{
	memset(pwmData, 0, sizeof(pwmData));

	uint32_t index = 0;
	uint32_t color;

//	color = ((uint32_t)In_color << 16) | ((uint32_t)In_color << 8) | In_color;

	for(int i=0; i<MAX_LED; i++)
	{
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | LED_Data[i][3]);

		for(int j=23; j>=0; j--)
		{
			if(color & (1<<j))
			{
				pwmData[index] = 60;
			}
			else
			{
				pwmData[index] = 30;
			}
			index++;

		}
	}


	for(int i=0; i<50; i++)
	{
		pwmData[index] = 0;
		index++;
	}

	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)pwmData, index);
	while(!sentflag){};
	sentflag = 0;
}

uint16_t effStep = 0;

uint8_t rainbow_effect_right() {
//     Strip ID: 0 - Effect: Rainbow - LEDS: 8
//     Steps: 14 - Delay: 30
//     Colors: 3 (255.0.0, 0.255.0, 0.0.255)
//     Options: rainbowlen=8, toLeft=false,
//  if(millis() - strip_0.effStart < 30 * (strip_0.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<MAX_LED;j++) {
    ind = 14 - (int16_t)(effStep - j * 1.75) % 14;
    switch((int)((ind % 14) / 4.666666666666667)) {
      case 0: factor1 = 1.0 - ((float)(ind % 14 - 0 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 0) % 14) / 4.666666666666667;
              Set_LED(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 14 - 1 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 4.666666666666667) % 14) / 4.666666666666667;
              Set_LED(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              WS2812_Send();
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 14 - 2 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 9.333333333333334) % 14) / 4.666666666666667;
              Set_LED(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
    }
  }
  if(effStep >= 14) {effStep = 0; return 0x03; }
  else effStep++;
  return 0x01;
}
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

//  Set_LED(0, 255, 0, 0);
//  Set_LED(1, 0, 255, 0);
//  Set_LED(2, 0, 0, 255);
//  Set_LED(3, 255, 255, 0);
//  Set_LED(4, 0, 255, 255);
//  Set_LED(5, 255, 0, 255);
//  Set_LED(6, 0, 0, 0);
//  Set_LED(7, 0, 0, 255);
//  WS2812_Send();
  for(int j=0; j<4; j++)
  {
	  switch(j){
	  case 0:
		for(int i=0; i< 8; i++){
			Set_LED(i, 50, 0, 50);
		}
		break;

	  case 1:
		for(int i=0; i< 8; i++){
			Set_LED(i, 0, 50, 0);
		}
		break;

	  case 2:
		for(int i=0; i< 8; i++){
			Set_LED(i, 0, 50, 50);
		}
		break;

	  case 3:
		for(int i=0; i< 8; i++){
			Set_LED(i, 50, 50, 250);
		}
		break;
	  default:
		  break;
	  }
	  WS2812_Send();
	  HAL_Delay(2500);
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {



	rainbow_effect_right();
	HAL_Delay (30);




//	  WS2812_Send(0x89);
//	  HAL_Delay(1000);
//
//	  WS2812_Send(0x46);
//	  HAL_Delay(1000);
//
//	  WS2812_Send(0x25);
//	  HAL_Delay(1000);



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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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

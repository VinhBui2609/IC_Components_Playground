/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    TM1637.h
  * @brief   This file contains all the function prototypes for
  *          the TM1637.c file
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef INC_TM1637_H_
#define INC_TM1637_H_

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern TIM_HandleTypeDef htim1;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void TM1637_DelayUs(uint16_t us);

void TM1637_Start();
void TM1637_Stop();

void TM1637_ClkH();
void TM1637_ClkL();
void TM1637_DioH();
void TM1637_DioL();

void TM1637_SetData();
void TM1637_SetAddress();

void TM1637_WriteByte(uint8_t data);
void TM1637_ACK();

void TM1637_TransferData(uint16_t var, int DisplayColon);
void Display();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* INC_AHT2X_H_ */

/* USER CODE BEGIN Header */
/**
  **********************************************************************************
  * @file    TM1637.c
  * @brief   This file provides code for the TM1637 4 Digits Seven Segment Display
  **********************************************************************************
  */
/* USER CODE END Header */
/* Includes ----------------------------------------------------------------------*/

#include "TM1637.h"
#include "main.h"
#include "stm32f4xx_hal.h"

unsigned char digitArr[4];

const uint8_t segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};


void TM1637_DelayUs(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);
	while(__HAL_TIM_GET_COUNTER(&htim1) < us);
}


void TM1637_ClkH()
{
	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}

void TM1637_ClkL()
{
	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
}

void TM1637_DioH()
{
	HAL_GPIO_WritePin(DIO_GPIO_Port, DIO_Pin, GPIO_PIN_SET);
}

void TM1637_DioL()
{
	HAL_GPIO_WritePin(DIO_GPIO_Port, DIO_Pin, GPIO_PIN_RESET);
}


void TM1637_Start()
{
	TM1637_ClkH();
	TM1637_DioH();
	TM1637_DelayUs(2);
	TM1637_DioL();
}

void TM1637_Stop()
{
	TM1637_ClkL();
	TM1637_DelayUs(2);
	TM1637_DioL();
	TM1637_DelayUs(2);
	TM1637_ClkH();
	TM1637_DelayUs(2);
	TM1637_DioH();
}


void TM1637_WriteByte(uint8_t data)
{
	for(int i=0; i<8; i++)
	{
		TM1637_ClkL();

		uint8_t check = data & 0x01;
		if(check)
		{
			TM1637_DioH();
		}
		else
		{
			TM1637_DioL();
		}
		TM1637_DelayUs(3);
		data >>= 1;

		TM1637_ClkH();
		TM1637_DelayUs(3);
	}
}

void TM1637_ACK()
{
	TM1637_ClkL();
	TM1637_DelayUs(5);
	TM1637_ClkH();
	TM1637_DelayUs(2);
}

void TM1637_SetData()
{
	TM1637_Start();
	TM1637_WriteByte(0x40); //0100 0000
	TM1637_ACK();
	TM1637_Stop();
}

void TM1637_SetAddress()
{
	TM1637_Start();
	TM1637_WriteByte(0xC0); //1100 0000
	TM1637_ACK();
	TM1637_Stop();
}

void TM1637_TransferData(uint16_t var, int DisplayColon)
{
	for(int i = 0; i < 4; ++i)
	{
		digitArr[3-i] = segmentMap[var % 10];
		if ((i == 1 || i == 2) && DisplayColon)
		{
			digitArr[3-i] |= 1 << 7;
		}
		var /= 10;
	}
}

void Display()
{
	for(int i = 0; i < 4; ++i)
	{
		TM1637_WriteByte(digitArr[3-i]);
		TM1637_ACK();
	}
}















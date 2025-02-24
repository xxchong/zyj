/**
 * ************************************************************************
 * 
 * @file My_DHT11.h
 * @author zxr
 * @brief 
 * 
 * ************************************************************************
 * @copyright Copyright (c) 2024 zxr 
 * ************************************************************************
 */
#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f4xx_hal.h"

#define DHT11_PORT			GPIOE
#define DHT11_PIN			GPIO_PIN_8

#define DHT11_PULL_1		HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET)
#define DHT11_PULL_0		HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET)

#define DHT11_ReadPin		HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)

/**
 * ************************************************************************
 * @brief �洢���������ݵĽṹ��
 * 
 * 
 * ************************************************************************
 */
typedef struct
{
	uint8_t humi_int;			// ʪ�ȵ���������
	uint8_t humi_dec;	 		// ʪ�ȵ�С������
	uint8_t temp_int;	 		// �¶ȵ���������
	uint8_t temp_dec;	 		// �¶ȵ�С������
	uint8_t check_sum;	 		// У���

} DHT11_Data_TypeDef;


uint8_t DHT11_ReadData(DHT11_Data_TypeDef* DHT11_Data);

#endif


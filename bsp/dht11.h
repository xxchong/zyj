
#ifndef __DHT11_H
#define __DHT11_H

#ifndef __DHT11_H__
#define __DHT11_H__

#include "main.h"

// DHT11引脚定义
#define DHT11_PORT    GPIOE
#define DHT11_PIN     GPIO_PIN_8
#define DHT11_PULL_1  HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET)
#define DHT11_PULL_0  HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET)
#define DHT11_ReadPin HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)

typedef struct
{
    uint8_t humi_int;    // 湿度整数部分
    uint8_t humi_dec;    // 湿度小数部分
    uint8_t temp_int;    // 温度整数部分
    uint8_t temp_dec;    // 温度小数部分
    uint8_t check_sum;   // 校验和
} DHT11_Data_TypeDef;

void DHT11_Init(void);
uint8_t DHT11_ReadData(DHT11_Data_TypeDef *DHT11_Data);
float DHT11_GetTemperature(DHT11_Data_TypeDef *DHT11_Data);
float DHT11_GetHumidity(DHT11_Data_TypeDef *DHT11_Data);

#endif

#endif


#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f4xx_hal.h"

#define RELAY_PORT	GPIOE
#define RELAY_PIN		GPIO_PIN_12

#define RELAY_OFF		HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET)
#define RELAY_ON		HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET)

#endif

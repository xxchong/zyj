#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f4xx_hal.h"

#define BEEP_PORT		GPIOE
#define BEEP_PIN		GPIO_PIN_7

#define BEEP_OFF	HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_SET)
#define BEEP_ON		HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_RESET)

#endif

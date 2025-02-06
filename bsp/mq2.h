#ifndef __MQ2_H
#define __MQ2_H

#include "stm32f4xx_hal.h"
#include "adc.h"
void Get_Mq2(uint32_t *mq2_adc_value ,float *mq2_percent);

#endif

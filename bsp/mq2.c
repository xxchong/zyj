#include "mq2.h"


void Get_Mq2(uint32_t *mq2_adc_value ,float *mq2_percent)
{
  HAL_ADC_Start(&hadc1);    
  HAL_ADC_PollForConversion(&hadc1,1);
  *mq2_adc_value = HAL_ADC_GetValue(&hadc1);
  *mq2_percent = (float)(*mq2_adc_value * 100.0f / 4096);
}
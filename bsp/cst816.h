#ifndef __CST816_H
#define __CST816_H

#include "stm32f4xx_hal.h"
#include "i2c.h"


typedef struct
{
    int16_t x;
    int16_t y;
    int state;
}cst816t_data_t;


void touch_driver_init(uint16_t x_limit,uint16_t y_limit);
void cst816t_read(int16_t *x,int16_t *y,int *state);


#endif

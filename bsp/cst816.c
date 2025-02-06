#include "cst816.h"

#define CST816T_ADDR    0x15

//边界值
static uint16_t s_usLimitX = 0;
static uint16_t s_usLimitY = 0;

// I2C读取寄存器函数
static HAL_StatusTypeDef i2c_read_reg(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, (CST816T_ADDR << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 100);
}

void touch_driver_init(uint16_t x_limit, uint16_t y_limit)
{
    s_usLimitX = x_limit;
    s_usLimitY = y_limit;
    // STM32 HAL库下I2C已经在CubeMX中完成初始化，这里不需要额外初始化
}

void cst816t_read(int16_t *x, int16_t *y, int *state)
{
    uint8_t data_x[2];        
    uint8_t data_y[2];       
    uint8_t touch_pnt_cnt = 0;  // 触摸点数量
    static int16_t last_x = 0;  // 12位数据
    static int16_t last_y = 0;  // 12位数据

    // 读取触摸点数
    i2c_read_reg(0x02, &touch_pnt_cnt, 1);
    

    if (touch_pnt_cnt != 1) {    // 忽略无触摸或多点触摸
        *x = last_x;
        *y = last_y;
        *state = 0;
        return;
    }

    //读取X坐标
    if(i2c_read_reg(0x03, data_x, 2) != HAL_OK)
    {
        *state = 0;
        return;
    }

    //读取Y坐标
    if(i2c_read_reg(0x05, data_y, 2) != HAL_OK)
    {
        *state = 0;
        return;
    }

    //数据12bit
    int16_t current_x = ((data_x[0] & 0x0F) << 8) | (data_x[1] & 0xFF); 
    int16_t current_y = ((data_y[0] & 0x0F) << 8) | (data_y[1] & 0xFF); 

    if(last_x != current_x || current_y != last_y)
    {
        last_x = current_x;
        last_y = current_y;
    }

    // 边界检查
    if(last_x >= s_usLimitX)
        last_x = s_usLimitX - 1;
    if(last_y >= s_usLimitY)
        last_y = s_usLimitY - 1;

    *x = last_y;
    *y = last_x;
    *state = 1;
}
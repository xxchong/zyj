#ifndef __GY302_H
#define __GY302_H

#include "main.h"

// 器件地址
#define BH1750_ADDR_GND      0x23    // ADDR接地
#define BH1750_ADDR_VCC      0x5C    // ADDR接VCC

// 指令集
#define BH1750_POWER_OFF     0x00    // 断电
#define BH1750_POWER_ON      0x01    // 通电
#define BH1750_RESET         0x07    // 重置
#define BH1750_CONTINUE_H2   0x11    // 连续高分辨率模式2 (0.5lx)
#define BH1750_CONTINUE_H    0x10    // 连续高分辨率模式 (1lx)
#define BH1750_CONTINUE_L    0x13    // 连续低分辨率模式 (4lx)

void GY302_Init(void);
uint16_t GY302_ReadLight(void);

#endif
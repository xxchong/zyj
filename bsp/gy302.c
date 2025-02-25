#include "gy302.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#define GY302_PORT		GPIOE
#define GY302_SCL		GPIO_PIN_14
#define GY302_SDA		GPIO_PIN_15

// IO操作宏定义
#define GY302_SCL_H()    HAL_GPIO_WritePin(GY302_PORT, GY302_SCL, GPIO_PIN_SET)
#define GY302_SCL_L()    HAL_GPIO_WritePin(GY302_PORT, GY302_SCL, GPIO_PIN_RESET)
#define GY302_SDA_H()    HAL_GPIO_WritePin(GY302_PORT, GY302_SDA, GPIO_PIN_SET)
#define GY302_SDA_L()    HAL_GPIO_WritePin(GY302_PORT, GY302_SDA, GPIO_PIN_RESET)
#define GY302_SDA_READ() HAL_GPIO_ReadPin(GY302_PORT, GY302_SDA)

// 延时函数
static void GY302_Delay(void)
{
    for(uint8_t i = 0; i < 10; i++)
    {
        __NOP();
    }
}
// 起始信号
static void GY302_Start(void)
{
    GY302_SDA_H();
    GY302_SCL_H();
    GY302_Delay();
    GY302_SDA_L();
    GY302_Delay();
    GY302_SCL_L();
}

// 停止信号
static void GY302_Stop(void)
{
    GY302_SDA_L();
    GY302_SCL_H();
    GY302_Delay();
    GY302_SDA_H();
    GY302_Delay();
}

// 等待应答

static uint8_t GY302_WaitAck(void)
{
    uint16_t timeout = 1000;
    
    GY302_SDA_H();
    GY302_Delay();
    GY302_SCL_H();
    GY302_Delay();
    
    while(GY302_SDA_READ())
    {
        timeout--;
        if(timeout == 0)
        {
            GY302_Stop();
            return 1;
        }
        __NOP();
    }
    
    GY302_SCL_L();
    return 0;
}
// 发送一个字节
static void GY302_SendByte(uint8_t data)
{
    uint8_t i;
    
    for(i = 0; i < 8; i++)
    {
        GY302_SCL_L();
        GY302_Delay();
        if(data & 0x80)
            GY302_SDA_H();
        else
            GY302_SDA_L();
        data <<= 1;
        GY302_Delay();
        GY302_SCL_H();
        GY302_Delay();
    }
    GY302_SCL_L();
}

// 读取一个字节
static uint8_t GY302_ReadByte(uint8_t ack)
{
    uint8_t i, data = 0;
    
    GY302_SDA_H();
    for(i = 0; i < 8; i++)
    {
        data <<= 1;
        GY302_SCL_L();
        GY302_Delay();
        GY302_SCL_H();
        GY302_Delay();
        if(GY302_SDA_READ())
            data |= 0x01;
    }
    GY302_SCL_L();
    
    // 发送应答信号
    if(ack)
        GY302_SDA_L();
    else
        GY302_SDA_H();
    
    GY302_Delay();
    GY302_SCL_H();
    GY302_Delay();
    GY302_SCL_L();
    
    return data;
}

// 写命令
static void BH1750_WriteByte(uint8_t cmd)
{
    GY302_Start();
    GY302_SendByte(BH1750_ADDR_GND << 1);  // 写地址
    GY302_WaitAck();
    GY302_SendByte(cmd);
    GY302_WaitAck();
    GY302_Stop();
}

// 初始化BH1750
void GY302_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOE_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = GY302_SCL | GY302_SDA;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GY302_PORT, &GPIO_InitStruct);
    
    GY302_SCL_H();
    GY302_SDA_H();
    
  // 替换HAL_Delay
    uint32_t startTime = HAL_GetTick();
    while(HAL_GetTick() - startTime < 100);  // 等待100ms
    
    BH1750_WriteByte(BH1750_POWER_OFF);
    startTime = HAL_GetTick();
    while(HAL_GetTick() - startTime < 10);   // 等待10ms
    
    BH1750_WriteByte(BH1750_POWER_ON);
    startTime = HAL_GetTick();
    while(HAL_GetTick() - startTime < 10);   // 等待10ms
    
    BH1750_WriteByte(BH1750_RESET);
    startTime = HAL_GetTick();
    while(HAL_GetTick() - startTime < 10);   // 等待10ms
    
    BH1750_WriteByte(BH1750_CONTINUE_H2);
    startTime = HAL_GetTick();
    while(HAL_GetTick() - startTime < 180);  // 等待180ms
}

// 读取光照强度值
uint16_t GY302_ReadLight(void)
{
    uint16_t value;
    uint8_t msb, lsb;
    
    GY302_Start();
    GY302_SendByte((BH1750_ADDR_GND << 1) | 0x01);  // 读地址
    GY302_WaitAck();
    
    msb = GY302_ReadByte(1);  // 读取高字节，发送ACK
    lsb = GY302_ReadByte(0);  // 读取低字节，发送NACK
    
    GY302_Stop();
    
    value = (msb << 8) | lsb;
    return value;  // 转换为实际光照值(lx)
}
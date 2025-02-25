#include "dht11.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"

static uint8_t dht11_data[5] = {0};  // 存储读取的温湿度信息

static void DHT11_Mode_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

static void DHT11_Mode_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

static uint8_t DHT11_ReadByte(void)
{
    uint8_t i;
    uint8_t data = 0;
    uint8_t retry = 0;
    
    for(i = 0; i < 8; i++)
    {
        // 等待变为高电平
        while(DHT11_ReadPin == 0 && retry < 100)
        {
            my_delay_us(1);
            retry++;
        }
        retry = 0;
        
        // 延时40us
        my_delay_us(40);
        
        // 判断数据位
        data <<= 1;
        if(DHT11_ReadPin == 1)
        {
            data |= 1;
        }
        
        // 等待高电平结束
        while(DHT11_ReadPin == 1 && retry < 100)
        {
            my_delay_us(1);
            retry++;
        }
        retry = 0;
    }
    
    return data;
}

void DHT11_Init(void)
{
    DHT11_Mode_OUT();
    DHT11_PULL_1;
    HAL_Delay(1000);  // 上电等待1s
    printf("DHT11 initialized\r\n");
}

uint8_t DHT11_ReadData(DHT11_Data_TypeDef *DHT11_Data)
{
    uint8_t retry = 0;
    uint8_t i;
    
    
    // 主机发送开始信号
    DHT11_Mode_OUT();
    DHT11_PULL_0;
    HAL_Delay(18);  // 至少18ms
    DHT11_PULL_1;
    my_delay_us(20);  // 20-40us
    
    // 切换为输入模式
    DHT11_Mode_IN();
    my_delay_us(20);
    
    // 等待DHT11响应
    if(DHT11_ReadPin == 0)  // DHT11会拉低40-80us
    {
        // 等待低电平结束
        while(DHT11_ReadPin == 0 && retry < 100)
        {
            my_delay_us(1);
            retry++;
        }
        retry = 0;
        
        // 等待高电平结束
        while(DHT11_ReadPin == 1 && retry < 100)
        {
            my_delay_us(1);
            retry++;
        }
        retry = 0;
        
        // 读取40位数据
        for(i = 0; i < 5; i++)
        {
            dht11_data[i] = DHT11_ReadByte();
        }
        
        taskEXIT_CRITICAL();
        
        // 校验数据
        if(dht11_data[4] == (dht11_data[0] + dht11_data[1] + 
                            dht11_data[2] + dht11_data[3]))
        {
            DHT11_Data->humi_int = dht11_data[0];
            DHT11_Data->humi_dec = dht11_data[1];
            DHT11_Data->temp_int = dht11_data[2];
            DHT11_Data->temp_dec = dht11_data[3];
            DHT11_Data->check_sum = dht11_data[4];
            return 1;
        }
    }
    
    return 0;
}

float DHT11_GetTemperature(DHT11_Data_TypeDef *DHT11_Data)
{
    return (float)DHT11_Data->temp_int + (float)DHT11_Data->temp_dec / 10.0f;
}

float DHT11_GetHumidity(DHT11_Data_TypeDef *DHT11_Data)
{
    return (float)DHT11_Data->humi_int + (float)DHT11_Data->humi_dec / 10.0f;
}
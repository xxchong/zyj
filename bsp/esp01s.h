#ifndef __ESP01S_H
#define __ESP01S_H

#include "main.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include <stdlib.h>
// 接收缓冲区大小
#define ESP_RXBUFFER_SIZE 512

// AT命令响应超时时间（毫秒）
#define AT_TIMEOUT 3000



#define Time_TCP 	"AT+CIPSTART=\"TCP\",\"api.k780.com\",80\r\n"
#define Time_GET	"GET http://api.k780.com/?app=life.time&appkey=70408&sign=8682a146af30c35ae92d249e23e0984b&format=json\r\n"



// ESP01S工作模式
typedef enum {
    ESP_MODE_STATION = 1,
    ESP_MODE_AP = 2,
    ESP_MODE_BOTH = 3
} ESP_Mode;

// ESP01S连接状态
typedef enum {
    ESP_DISCONNECTED = 0,
    ESP_CONNECTED = 1
} ESP_WiFiStatus;

// ESP01S返回状态
typedef enum {
    ESP_OK = 0,
    ESP_ERROR = 1,
    ESP_TIMEOUT = 2
} ESP_Status;

// ESP01S句柄结构体
typedef struct {
    uint8_t rxBuffer[ESP_RXBUFFER_SIZE];  // 接收缓冲区
    uint16_t rxLen;                       // 接收数据长度
    uint8_t isInit;                       // 初始化标志
    ESP_WiFiStatus wifiStatus;            // WiFi连接状态
    uint8_t dataReady;                    // 数据就绪标志
} ESP01S_HandleTypeDef;

// 外部变量声明
extern ESP01S_HandleTypeDef esp01s;



// 函数声明
ESP_Status ESP01S_Init(void);
ESP_Status ESP01S_Test(void);
ESP_Status ESP01S_SetMode(ESP_Mode mode);
ESP_Status ESP01S_ConnectWiFi(const char* ssid, const char* password);
ESP_Status ESP01S_DisconnectWiFi(void);
ESP_Status ESP01S_SendATCmd(const char* cmd, const char* response, uint32_t timeout);
uint32_t ESP01S_GetNetworkTime(void);

ESP_Status ESP01S_UartSend(const char* data);

#endif
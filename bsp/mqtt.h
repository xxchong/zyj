#ifndef __MQTT_H
#define __MQTT_H

#include "main.h"
#include "esp01s.h"

// MQTT错误代码
#define MQTT_OK                  0
#define MQTT_ERROR_NTP          1
#define MQTT_ERROR_USER_CONFIG  2
#define MQTT_ERROR_CONNECT      3
#define MQTT_ERROR_SUBSCRIBE    4
#define MQTT_ERROR_PUBLISH      5

// MQTT连接状态
typedef enum {
    MQTT_DISCONNECTED = 0,
    MQTT_CONNECTED = 1
} MQTT_Status;

extern MQTT_Status mqttStatus;

// 函数声明
uint8_t MQTT_Init(void);
uint8_t MQTT_Connect(void);
uint8_t MQTT_Subscribe(const char* topic);
uint8_t MQTT_Publish(const char* topic, const char* message);
uint8_t MQTT_Disconnect(void);

#endif
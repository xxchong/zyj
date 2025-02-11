#include "mqtt.h"   
#include "esp01s.h"   
#include "mqtt_config.h"

MQTT_Status mqttStatus = MQTT_DISCONNECTED;
static char *TAG = "MQTT";



uint8_t MQTT_Init(void)
{
    int i = 10;
    char clientId[128];
    
    // 1. 清理缓存
    ESP01S_SendATCmd("AT+MQTTCLEAN=0\r\n", "OK", 1000);
    HAL_Delay(1000);
    
    // 2. 配置NTP
    while(i > 0)
    { 
        if(ESP01S_SendATCmd("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n", "OK", 200) == ESP_OK) {
            break;
        }
        i--;
        if(i == 0) return MQTT_ERROR_NTP;
    }
    
    HAL_Delay(500);
    i = 10;
    
    // 3. 配置MQTT用户 - 使用完整的设备名作为用户名
    while(i > 0)
    { 
        if(ESP01S_SendATCmd("AT+MQTTUSERCFG=0,1,\"NULL\",\"Museum_Hardware&k0404wymIZ4\",\"749BA6790708D3CE5802C2010AAB3F214F7518FB8AB55B808924EEEED907C04E\",0,0,\"\"\r\n", "OK", 200) == ESP_OK) {
            break;
        }
        i--;
        if(i == 0) return MQTT_ERROR_USER_CONFIG;
    }
    
    HAL_Delay(500);
    i = 10;
      
    // 4. 设置ClientID - 使用正确的格式
    sprintf(clientId, "AT+MQTTCLIENTID=0,\"test123|securemode=3\\,signmethod=hmacsha256\\,timestamp=12345|\"\r\n");
    while(i > 0)
    {                      
        if(ESP01S_SendATCmd(clientId, "OK", 200) == ESP_OK) {
            break;
        }
        i--;
        if(i == 0) return MQTT_ERROR_USER_CONFIG;
    }
    
    HAL_Delay(500);
    i = 10;
    
    // 5. 连接MQTT服务器
    while(i > 0)
    { 
        if(ESP01S_SendATCmd("AT+MQTTCONN=0,\"k0404wymIZ4.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1\r\n", "OK", 5000) == ESP_OK) {
            printf("MQTT connected\r\n");
            mqttStatus = MQTT_CONNECTED;
            break;
        }
        i--;
        if(i == 0) return MQTT_ERROR_CONNECT;
    }
    
    HAL_Delay(1000); // 增加连接后的延时
    
    // 6. 取消订阅主题
    ESP01S_SendATCmd("AT+MQTTUNSUB=0,\"/sys/k0404wymIZ4/Museum_Hardware/thing/event/property/post_reply\"\r\n", "OK", 200);
    ESP01S_SendATCmd("AT+MQTTUNSUB=0,\"/sys/k0404wymIZ4/Museum_Hardware/thing/event/+/post_reply\"\r\n", "OK", 200);
    
    return MQTT_OK;
}
// ... existing code ...
uint8_t MQTT_Connect(void)
{
    char cmd[256];
    int retry = 3;
    
    while(retry > 0) {
        sprintf(cmd, "AT+MQTTCONN=0,\"%s\",%d,1\r\n", MQTT_ADDRESS, MQTT_PORT);
        
        if(ESP01S_SendATCmd(cmd, "OK", 10000) == ESP_OK) {
            printf("%s: MQTT connected\r\n", TAG);
            mqttStatus = MQTT_CONNECTED;
            
            // 连接成功后订阅主题
            if(MQTT_Subscribe(MQTT_SUBSCRIBE_TOPIC) == 0) {
                return MQTT_OK;
            }
            return MQTT_ERROR_SUBSCRIBE;
        }
        
        retry--;
        HAL_Delay(2000);
    }
    
    printf("%s: MQTT connect failed\r\n", TAG);
    mqttStatus = MQTT_DISCONNECTED;
    return MQTT_ERROR_CONNECT;
}

uint8_t MQTT_Subscribe(const char* topic)
{
    if(mqttStatus != MQTT_CONNECTED) {
        printf("%s: MQTT not connected\r\n", TAG);
        return MQTT_ERROR_CONNECT;
    }
    
    char cmd[256];
    sprintf(cmd, "AT+MQTTSUB=0,\"%s\",1\r\n", topic);
    
    if(ESP01S_SendATCmd(cmd, "OK", 5000) != ESP_OK) {
        printf("%s: Subscribe failed\r\n", TAG);
        return MQTT_ERROR_SUBSCRIBE;
    }
    
    printf("%s: Subscribed to %s\r\n", TAG, topic);
    return MQTT_OK;
}

uint8_t MQTT_Publish(const char* topic, const char* message)
{
    if(mqttStatus != MQTT_CONNECTED) {
        printf("%s: MQTT not connected\r\n", TAG);
        return MQTT_ERROR_CONNECT;
    }
    
    char cmd[512];  // 增加缓冲区大小以适应更长的消息
    sprintf(cmd, "AT+MQTTPUB=0,\"%s\",\"%s\",1,0\r\n", topic, message);
    
    if(ESP01S_SendATCmd(cmd, "OK", 5000) != ESP_OK) {
        printf("%s: Publish failed\r\n", TAG);
        return MQTT_ERROR_PUBLISH;
    }
    
    printf("%s: Published to %s\r\n", TAG, topic);
    return MQTT_OK;
}









uint8_t MQTT_Disconnect(void)
{
    if(ESP01S_SendATCmd("AT+MQTTCLEAN=0\r\n", "OK", 5000) != ESP_OK) {
        printf("%s: MQTT disconnect failed\r\n", TAG);
        return MQTT_ERROR_CONNECT;
    }
    
    printf("%s: MQTT disconnected\r\n", TAG);
    mqttStatus = MQTT_DISCONNECTED;
    return MQTT_OK;
}
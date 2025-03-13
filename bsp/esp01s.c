#include "esp01s.h"

#define ESP_SSID "XXCHONG"
#define ESP_PASSWORD "abc18813491718"

ESP01S_HandleTypeDef esp01s;

static char *TAG = "ESP01S";

ESP_Status ESP01S_Init(void)
{
	memset(&esp01s, 0, sizeof(ESP01S_HandleTypeDef));
	
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE); //
    __HAL_UART_CLEAR_IDLEFLAG(&huart2); //
    if (HAL_UART_Receive_DMA(&huart2, (uint8_t *)esp01s.rxBuffer, ESP_RXBUFFER_SIZE) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_Delay(500);

    while(ESP01S_SendATCmd("AT+RST\r\n", "OK", 2000) != ESP_OK)
    {
        printf("%s: AT+RST failed\r\n", TAG);
        HAL_Delay(100);
    }
    printf("%s: AT+RST success\r\n", TAG);
    

    while(ESP01S_SendATCmd("ATE0\r\n", "OK", AT_TIMEOUT) != ESP_OK) {
        printf("%s: ATE0 failed\r\n", TAG);
        HAL_Delay(100);
    }
    printf("%s: Echo off\r\n", TAG);
    
    while(ESP01S_SetMode(ESP_MODE_STATION) != ESP_OK) {
        printf("%s: Set mode failed\r\n", TAG);
        HAL_Delay(100);
    }
    printf("%s: Set mode success\r\n", TAG);

    while(ESP01S_ConnectWiFi(ESP_SSID, ESP_PASSWORD) != ESP_OK) {
        printf("%s: Connect WiFi failed\r\n", TAG);
        HAL_Delay(100);
    }
    printf("%s: Connect WiFi success\r\n", TAG);
    
    esp01s.isInit = 1;
    return ESP_OK;
}



// 获取网络时间戳
uint32_t ESP01S_GetNetworkTime(void)
{
    char send_buf[128];
    uint32_t timestamp = 0;
    
    if(ESP01S_SendATCmd(Time_TCP, "OK", 5000) != ESP_OK) {
        printf("TCP connect failed\r\n");
        return 0;
    }
    
    // 2. 发送HTTP请求
    sprintf(send_buf, "AT+CIPSEND=%d\r\n", strlen(Time_GET));
    if(ESP01S_SendATCmd(send_buf, ">", 1000) != ESP_OK) {
        printf("Send length failed\r\n");
        return 0;
    }
    
    if(ESP01S_SendATCmd(Time_GET, "\"timestamp\":", 5000) != ESP_OK) {
        printf("HTTP request failed\r\n");
        return 0;
    }
    
    // 3. 解析时间戳
    char *p = strstr((char*)esp01s.rxBuffer, "\"timestamp\":\"");
    if(p) {
        p += strlen("\"timestamp\":\"");
        timestamp = atol(p);
        printf("Get timestamp: %lu\r\n", timestamp);
    }
    
    // 4. 关闭TCP连接
    ESP01S_SendATCmd("AT+CIPCLOSE\r\n", "OK", 1000);
    
    return timestamp;
}


ESP_Status ESP01S_SetMode(ESP_Mode mode)
{
    char cmd[20];
    sprintf(cmd, "AT+CWMODE=%d\r\n", mode);
    return ESP01S_SendATCmd(cmd, "OK", AT_TIMEOUT);
}

ESP_Status ESP01S_ConnectWiFi(const char* ssid, const char* password)
{
    char cmd[100];
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    ESP_Status status = ESP01S_SendATCmd(cmd, "WIFI GOT IP", 20000); // WiFi连接需要更长的超时时间
    
    if(status == ESP_OK) {
        esp01s.wifiStatus = ESP_CONNECTED;
        printf("WiFi connected\r\n");
    } else {
        printf("WiFi connect failed\r\n");
    }
    
    return status;
}


ESP_Status ESP01S_DisconnectWiFi(void)
{
    ESP_Status status = ESP01S_SendATCmd("AT+CWQAP\r\n", "OK", AT_TIMEOUT);
    if(status == ESP_OK) {
        esp01s.wifiStatus = ESP_DISCONNECTED;
        printf("WiFi disconnected\r\n");
    }
    
    return status;
}



ESP_Status ESP01S_UartSend(const char* data)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen(data), 100);
}


ESP_Status ESP01S_SendATCmd(const char* cmd, const char* response, uint32_t timeout)
{
    uint32_t tickstart = HAL_GetTick();
    
    memset(esp01s.rxBuffer, 0, ESP_RXBUFFER_SIZE);  // esp01s.rxBuffer


    ESP01S_UartSend(cmd);
    
    while((HAL_GetTick() - tickstart) < timeout)
    {
        if(esp01s.dataReady)
        {
            if(strstr((char*)esp01s.rxBuffer, response)) 
            {
                esp01s.dataReady = 0;
                esp01s.rxLen = 0;
                return ESP_OK;
            }
            esp01s.dataReady = 0;
            esp01s.rxLen = 0;
        }
        HAL_Delay(1);  
    }
    
    printf("Timeout!\r\n");
    return ESP_TIMEOUT;
}
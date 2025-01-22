#include "esp01s.h"

// 定义ESP01S句柄
ESP01S_HandleTypeDef esp01s;

uint8_t Buffer[ESP_RXBUFFER_SIZE];


/**
 * @brief 初始化ESP01S
 * @return ESP_Status
 */
ESP_Status ESP01S_Init(void)
{
    // 初始化变量
//	memset(&esp01s, 0, sizeof(ESP01S_HandleTypeDef));
	
    // 开启DMA接收
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE); //开启串口空闲中断
    __HAL_UART_CLEAR_IDLEFLAG(&huart2);
    if (HAL_UART_Receive_DMA(&huart2, (uint8_t *)Buffer, ESP_RXBUFFER_SIZE) != HAL_OK)
    {
        Error_Handler();
    }

    // 等待模块启动
    HAL_Delay(1000);
    
    // 测试AT命令
    while(ESP01S_Test() != ESP_OK) {
        printf("AT test failed\r\n");
        HAL_Delay(1000);
    }
    printf("AT test success\r\n");

//    while(ESP01S_SendATCmd("AT\r\n", "OK", AT_TIMEOUT) != ESP_OK)
//    {
//        printf("AT test failed\r\n");
//        HAL_Delay(1000);
//    }
//    printf("AT test success\r\n");
    
    // // 关闭回显
    // if(ESP01S_SendATCmd("ATE0\r\n", "OK", AT_TIMEOUT) != ESP_OK) {
    //     printf("ATE0 failed\r\n");
    //     return ESP_ERROR;
    // }
    // printf("Echo off\r\n");
    
    // // 设置工作模式为Station模式
    // if(ESP01S_SetMode(ESP_MODE_STATION) != ESP_OK) {
    //     printf("Set mode failed\r\n");
    //     return ESP_ERROR;
    // }
    // printf("Set mode success\r\n");
    
    esp01s.isInit = 1;
    return ESP_OK;
}

/**
 * @brief 测试AT命令
 * @return ESP_Status
 */
ESP_Status ESP01S_Test(void)
{
    return ESP01S_SendATCmd("AT\r\n", "OK", AT_TIMEOUT);
}

/**
 * @brief 设置ESP01S工作模式
 * @param mode: 工作模式
 * @return ESP_Status
 */
ESP_Status ESP01S_SetMode(ESP_Mode mode)
{
    char cmd[20];
    sprintf(cmd, "AT+CWMODE=%d\r\n", mode);
    return ESP01S_SendATCmd(cmd, "OK", AT_TIMEOUT);
}

/**
 * @brief 连接WiFi
 * @param ssid: WiFi名称
 * @param password: WiFi密码
 * @return ESP_Status
 */
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

/**
 * @brief 断开WiFi连接
 * @return ESP_Status
 */
ESP_Status ESP01S_DisconnectWiFi(void)
{
    ESP_Status status = ESP01S_SendATCmd("AT+CWQAP\r\n", "OK", AT_TIMEOUT);
    if(status == ESP_OK) {
        esp01s.wifiStatus = ESP_DISCONNECTED;
        printf("WiFi disconnected\r\n");
    }
    
    return status;
}

/**
 * @brief 发送AT命令并等待响应
 * @param cmd: AT命令
 * @param response: 期望的响应
 * @param timeout: 超时时间（毫秒）
 * @return ESP_Status
 */
ESP_Status ESP01S_SendATCmd(const char* cmd, const char* response, uint32_t timeout)
{
    uint32_t tickstart = HAL_GetTick();
    
    // 清空接收缓冲区
    memset(Buffer, 0, ESP_RXBUFFER_SIZE);  // 使用全局Buffer而不是esp01s.rxBuffer
    
    // 重新启动DMA接收
    HAL_UART_DMAStop(&huart2);
    if(HAL_UART_Receive_DMA(&huart2, (uint8_t*)Buffer, ESP_RXBUFFER_SIZE) != HAL_OK)
    {
        Error_Handler();
    }
    
    // 发送AT命令
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 100);
    printf("Send: %s", cmd);
    
    // 等待响应
    while((HAL_GetTick() - tickstart) < timeout)
    {
        if(strstr((char*)Buffer, response)) 
        {
            printf("Receive: %s\r\n", Buffer);
            return ESP_OK;
        }
        HAL_Delay(1);  // 减小延时时间
    }
    
    printf("Timeout!\r\n");
    return ESP_TIMEOUT;
}
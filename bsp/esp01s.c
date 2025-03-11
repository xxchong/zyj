#include "esp01s.h"

#define ESP_SSID "XXCHONG"
#define ESP_PASSWORD "abc18813491718"

//ESP01S�ṹ��
ESP01S_HandleTypeDef esp01s;

static char *TAG = "ESP01S";

// ��ʼ��ESP01S
ESP_Status ESP01S_Init(void)
{
    // ��ʼ��ESP01S�ṹ��
	memset(&esp01s, 0, sizeof(ESP01S_HandleTypeDef));
	
    // ʹ�ܴ���2�����ж�
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE); //ʹ�ܴ���2�����ж�
    __HAL_UART_CLEAR_IDLEFLAG(&huart2); //�������2���б�־
    if (HAL_UART_Receive_DMA(&huart2, (uint8_t *)esp01s.rxBuffer, ESP_RXBUFFER_SIZE) != HAL_OK)
    {
        Error_Handler();
    }

    // ��ʱ500ms
    HAL_Delay(500);

    // ����AT+RST��������ESP01S
    while(ESP01S_SendATCmd("AT+RST\r\n", "OK", 2000) != ESP_OK)
    {
        printf("%s: AT+RST failed\r\n", TAG);
        HAL_Delay(100);
    }
    printf("%s: AT+RST success\r\n", TAG);
    
    // ����AT�������
//    while(ESP01S_SendATCmd("AT\r\n", "OK", AT_TIMEOUT) != ESP_OK)
//    {
//        printf("%s: AT test failed\r\n", TAG);
//        HAL_Delay(100);
//    }
//    printf("%s: AT test success\r\n", TAG);
    
    // �رջ���
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



// ����ģʽ
ESP_Status ESP01S_SetMode(ESP_Mode mode)
{
    char cmd[20];
    sprintf(cmd, "AT+CWMODE=%d\r\n", mode);
    return ESP01S_SendATCmd(cmd, "OK", AT_TIMEOUT);
}

// ����WiFi
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


// �Ͽ�WiFi
ESP_Status ESP01S_DisconnectWiFi(void)
{
    ESP_Status status = ESP01S_SendATCmd("AT+CWQAP\r\n", "OK", AT_TIMEOUT);
    if(status == ESP_OK) {
        esp01s.wifiStatus = ESP_DISCONNECTED;
        printf("WiFi disconnected\r\n");
    }
    
    return status;
}



// ��������
ESP_Status ESP01S_UartSend(const char* data)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen(data), 100);
}


// ����AT����
ESP_Status ESP01S_SendATCmd(const char* cmd, const char* response, uint32_t timeout)
{
    uint32_t tickstart = HAL_GetTick();
    
    // ��ս��ջ�����
    memset(esp01s.rxBuffer, 0, ESP_RXBUFFER_SIZE);  // esp01s.rxBuffer
    // ��ӡ���͵�����
    // printf("%s: %s", TAG, cmd);

    ESP01S_UartSend(cmd);
    
    // �ȴ���Ӧ
    while((HAL_GetTick() - tickstart) < timeout)
    {
        if(esp01s.dataReady)
        {
            if(strstr((char*)esp01s.rxBuffer, response)) 
            {
                esp01s.dataReady = 0;
                esp01s.rxLen = 0;
//                printf("Receive: %s\r\n", esp01s.rxBuffer);
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
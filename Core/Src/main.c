/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demo_benchmark.h"
#include "gui_guider.h"
#include "events_init.h"
#include "dht11.h"
#include "beep.h"
#include "relay.h"
#include "gy302.h"
#include "stdio.h"
#include "esp01s.h"
#include "mq2.h"
#include "mqtt.h"
#include "mqtt_config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// 定义任务状态
typedef enum {
    TASK_IDLE,   //空闲状态
    TASK_SENSOR_READ, //传感器读取状态
    TASK_MQTT_PUBLISH, //MQTT发布状态
    TASK_MQTT_RECONNECT //MQTT重连状态
} SystemState;


// 定义系统数据结构
typedef struct {
    // 传感器数据
    DHT11_Data_TypeDef dht11_data;
    uint32_t mq2_adc_value;
    float mq2_percent;
    float light_value;
    
    // 时间管理
    uint32_t last_sensor_time;
    uint32_t last_mqtt_time;
    uint32_t last_display_time;
    
    // 系统状态
    SystemState state;
    uint8_t alarm_flag;
    char mqtt_message[512];
} System_HandleTypeDef;

System_HandleTypeDef sys = {0};



uint16_t brightness_pwm = 499;
uint16_t brightness_percentage = 50;


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4)
	{
		static int i;
		i++;
		if( i == 1000)
		{
			i=0;
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
		}

     static uint8_t cnt = 0;
        cnt++;
        if(cnt >= 5)
        {
            lv_tick_inc(5);
            cnt = 0;
        }
		
	}

}

lv_ui guider_ui;
DHT11_Data_TypeDef DHT11_Data;  



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	

 // 初始化报警状态
  BEEP_OFF;
  sys.alarm_flag = 0;


  //WIFI初始化
//	ESP01S_Init();
//  //MQTT初始化
//  MQTT_Init();
//  //订阅消息
//  MQTT_Subscribe(MQTT_USER_TOPIC);
//  MQTT_Subscribe(MQTT_SUBSCRIBE_TOPIC);

//  //发布测试消息
//  MQTT_Publish(MQTT_PUBLIC_TOPIC, "Hello World");
//   

   /*LCD屏幕和LVGL初始化*/
	lcd_set_dir(LCD_CROSSWISE_180);
	lcd_init();	
  lv_init();
 	lv_port_disp_init();
  lv_port_indev_init();
	HAL_TIM_Base_Start_IT(&htim4);
  //LCD背光通过cubemx配置pwm
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
  //打开背光
  LCD_SetBrightness(brightness_pwm);

  /*传感器硬件初始化*/
  //DHT11通过cubemx配置引脚   GPIOE8
  //MQ2通过cubemx配置adc      GPIOA4
  //蜂鸣器通过cubemx配置引脚   GPIOE7
  //火焰传感器通过外部中断配置  GPIOB14
  //继电器通过cubemx配置引脚   GPIOB8
  GY302_Init(); //使用软件i2c
	setup_ui(&guider_ui);
  events_init(&guider_ui);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		lv_task_handler();
		HAL_Delay(10);

//    uint32_t current_time = HAL_GetTick();
//        
//        // 1. LVGL显示刷新（20ms）
//        if(current_time - sys.last_display_time >= 20) {
//            lv_task_handler();
//            sys.last_display_time = current_time;
//        }
//        
//        // 2. 状态机处理
//        switch(sys.state) {
//            case TASK_IDLE:
//                // 检查传感器读取时间（2秒间隔）
//                if(current_time - sys.last_sensor_time >= 2000) {
//                    sys.state = TASK_SENSOR_READ;
//                }
//                // 检查MQTT发送时间（5秒间隔）
//                if(current_time - sys.last_mqtt_time >= 5000) {
//                    sys.state = TASK_MQTT_PUBLISH;
//                }
//                break;
//                
//            case TASK_SENSOR_READ:
//                // 读取DHT11
//                if(DHT11_ReadData(&sys.dht11_data)) {
//                    // 更新温湿度显示
//                    // lv_label_set_text_fmt(guider_ui.label_temp, "温度: %d.%d℃", 
//                    //     sys.dht11_data.temp_int, sys.dht11_data.temp_dec);
//                    // lv_label_set_text_fmt(guider_ui.label_humi, "湿度: %d.%d%%",
//                    //     sys.dht11_data.humi_int, sys.dht11_data.humi_dec);
//                }
//                
//                // 读取MQ2
//                Get_Mq2(&sys.mq2_adc_value, &sys.mq2_percent);
//                // lv_label_set_text_fmt(guider_ui.label_mq2, "气体: %.1f%%",
//                //     sys.mq2_percent);

//                      // 读取光照
//                sys.light_value = GY302_ReadLight();
//                // lv_label_set_text_fmt(guider_ui.label_light, "光照: %.1f lux",
//                //     sys.light_value);
//                
//                // 报警检测
//                if(sys.mq2_percent > 60.0f || sys.dht11_data.temp_int > 35) {
//                    if(!sys.alarm_flag) {
//                        BEEP_ON;
//                        sys.alarm_flag = 1;
//                    }
//                } else if(sys.alarm_flag) {
//                    BEEP_OFF;
//                    sys.alarm_flag = 0;
//                }
//                
//                sys.last_sensor_time = current_time;
//                sys.state = TASK_IDLE;
//                break;
//                
//            case TASK_MQTT_PUBLISH:
//                // 格式化MQTT消息
//                sprintf(sys.mqtt_message, 
//                    "{\\\"params\\\":{"
//                    "\\\"Temperature\\\":%d.%d,"
//                    "\\\"Humidity\\\":%d.%d,"
//                    "\\\"Gas\\\":%.1f,"
//                    "\\\"Light\\\":%.1f,"
//                    "\\\"Alarm\\\":%d"
//                    "}}",
//                    sys.dht11_data.temp_int, sys.dht11_data.temp_dec,
//                    sys.dht11_data.humi_int, sys.dht11_data.humi_dec,
//                    sys.mq2_percent,
//                    sys.light_value,
//                    sys.alarm_flag);
//                
//                // 发送MQTT消息
//                if(MQTT_Publish(MQTT_PARAM_TOPIC, sys.mqtt_message) != MQTT_OK) {
//                    sys.state = TASK_MQTT_RECONNECT;
//                    break;
//                }
//                
//                sys.last_mqtt_time = current_time;
//                sys.state = TASK_IDLE;
//                break;
//                
//            case TASK_MQTT_RECONNECT:
//                // 重新初始化ESP8266和MQTT
//                if(ESP01S_Init() == ESP_OK && MQTT_Init() == MQTT_OK) {
//                    MQTT_Subscribe(MQTT_USER_TOPIC);
//                    MQTT_Subscribe(MQTT_SUBSCRIBE_TOPIC);
//                    sys.state = TASK_IDLE;
//                } else {
//                    HAL_Delay(5000); // 等待5秒后重试
//                }
//                break;
//        }
//        
//        // 3. ESP8266接收数据处理
//        if(esp01s.dataReady) {
//            // 处理MQTT接收数据
//            // 可以添加对接收命令的处理
//            esp01s.dataReady = 0;
//        }



  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

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




uint16_t brightness_pwm = 499;
uint16_t brightness_percentage = 50;


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4)
	{
		static uint32_t i;
    static uint32_t cnt = 0;
		i++;
		if( i == 1000)
		{
			i=0;
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
		}

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

static lv_timer_t *sensor_timer = NULL;
static lv_timer_t *mqtt_timer = NULL;

static uint32_t mq2_adc_value ;
static	float mq2_percent,light_value;

static void sensor_timer_callback(lv_timer_t *timer)
{

    static uint8_t update_state = 0;
    
    // 只更新UI显示，不直接读取传感器
    switch(update_state) {
        case 0:  // 更新温湿度显示
            lv_label_set_text_fmt(guider_ui.main_screen_label_temp_percentage, "%d%%", DHT11_Data.temp_int);
            lv_label_set_text_fmt(guider_ui.main_screen_label_humi_percentage, "%d%%", DHT11_Data.humi_int);
            lv_bar_set_value(guider_ui.main_screen_bar_temp, DHT11_Data.temp_int, LV_ANIM_OFF);
            lv_bar_set_value(guider_ui.main_screen_bar_humi, DHT11_Data.humi_int, LV_ANIM_OFF);
            break;
            
        case 1:  // 更新烟雾显示
            lv_label_set_text_fmt(guider_ui.main_screen_label_fumes_percentage, "%d%%", (int)mq2_percent);
            lv_arc_set_value(guider_ui.main_screen_arc_fumes, mq2_percent);
            break;
            
        case 2:  // 更新光照显示
//            lv_label_set_text_fmt(guider_ui.main_screen_label_light_percentage, "%d%%", (int)light_value);
//            lv_arc_set_value(guider_ui.main_screen_arc_light, light_value);
            break;
    }
    
    update_state = (update_state + 1) % 3;
}


static void mqtt_timer_callback(lv_timer_t *timer)
{

}



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
  /*传感器硬件初始化*/
  //DHT11通过cubemx配置引脚   GPIOE8
  //MQ2通过cubemx配置adc      GPIOA4
  //蜂鸣器通过cubemx配置引脚   GPIOE7
  //火焰传感器通过外部中断配置  GPIOB14
  //继电器通过cubemx配置引脚   GPIOB8
  GY302_Init(); //使用软件i2c
//  sys.alarm_flag = 0;


//  //WIFI初始化
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

  
	setup_ui(&guider_ui);
  events_init(&guider_ui);
  sensor_timer = lv_timer_create(sensor_timer_callback,2000, NULL);
//  mqtt_timer = lv_timer_create(mqtt_timer_callback, 5000, NULL);
  static uint32_t last_dht11_time = 0;
  static uint32_t last_gy302_time = 0;
  static uint32_t last_mq2_time = 0;
  static uint32_t last_lvgl_time = 0;
  static uint32_t current_time = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      current_time = HAL_GetTick();
      // LVGL任务处理，确保每5ms执行一次
      if(current_time - last_lvgl_time >= 5)
      {
          last_lvgl_time = current_time;
          lv_task_handler();
      }

      // DHT11读取（每2秒一次）
      if(current_time - last_dht11_time >= 2000)
      {
          last_dht11_time = current_time;
          DHT11_ReadData(&DHT11_Data);
      }
      
      // GY302读取（每1秒一次）
//      if(current_time - last_gy302_time >= 1000)
//      {
//          last_gy302_time = current_time;
//          light_value = GY302_ReadLight();
//      }
      
      // MQ2读取（每100ms一次）
      if(current_time - last_mq2_time >= 100)
      {
          last_mq2_time = current_time;
          Get_Mq2(&mq2_adc_value, &mq2_percent);
      }
  
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

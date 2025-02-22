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

static lv_obj_t *label;


void timer_callback(lv_timer_t *timer)
{
//    float light= GY302_ReadLight();
//    lv_label_set_text_fmt(label, "Light: %d lux", (int)light);
//    printf("Light: %d lux\n", (int)light);

    if(DHT11_ReadData(&DHT11_Data))
    {
        printf("T:%d H:%d", DHT11_Data.temp_int, DHT11_Data.humi_int);
    }else{
        printf("DHT11 ERROR");
    }
		
		    lv_timer_del(timer);

}

void beep_callback(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    // bool state = lv_obj_has_state(obj, LV_STATE_CHECKED);

    lv_timer_create(timer_callback, 10, NULL);


    // if(state) {
    //     // switch打开，蜂鸣器?
    //     // RELAY_ON;
    // } else {
    //     // switch关闭，蜂鸣器停止
    //     // RELAY_OFF;
    // }
}
 void demo(void)
 {
     lv_obj_t *dis = lv_scr_act();
     label = lv_label_create(dis);
     lv_obj_center(label);
     lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);



     lv_obj_t *beep = lv_btn_create(dis);
     lv_obj_set_size(beep,70,40);
     lv_obj_align_to(beep,label,LV_ALIGN_OUT_BOTTOM_MID,0,20);
     lv_obj_add_event_cb(beep,beep_callback,LV_EVENT_CLICKED,NULL);





  
// 	// lv_obj_t *button = lv_btn_create(dis);
// 	// lv_obj_set_size(button,50,40);
// 	// lv_obj_center(button);
// 	// lv_obj_t *button1 = lv_btn_create(dis);
// 	// lv_obj_set_size(button1,50,40);
// 	// lv_obj_align_to(button1,button,LV_ALIGN_OUT_RIGHT_MID,20,0);
// //	lv_group_t *group = lv_group_create();
// //	lv_group_set_default(group);
// //	lv_group_add_obj(group,beep);
// //	// lv_group_add_obj(group,button1);

// //	
// //	lv_indev_set_group(indev_encoder,group);
	
// 	// lv_group_focus_obj(button);

 }



void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    // 将滑动条的值(0-100)转换为PWM值(0-999)
    uint16_t brightness = (value * 999) / 100;
    LCD_SetBrightness(brightness);
    
    // 更新标签显示
    lv_obj_t * label = lv_event_get_user_data(e);
    lv_label_set_text_fmt(label, "Light : %d%%", (int)value);
}


//void demo(void)
//{
//    lv_obj_t *dis = lv_scr_act();
//    
//    // 创建标签
//    lv_obj_t *label = lv_label_create(dis);
//    lv_label_set_text(label, "Light: 50%");
//    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
//    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);

//    // 创建滑动条
//    lv_obj_t *slider = lv_slider_create(dis);
//    lv_obj_set_size(slider, 200, 10);                    // 设置滑动条大小
//    lv_obj_align_to(slider, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20); // 放在标签下方
//    lv_slider_set_range(slider, 0, 100);                 // 设置范围0-100
//    lv_slider_set_value(slider, 50, LV_ANIM_OFF);       // 设置初始值50%
//    
//    // 设置滑动条样式
//    lv_obj_set_style_bg_color(slider, lv_color_hex(0x808080), LV_PART_MAIN);
//    lv_obj_set_style_bg_color(slider, lv_color_hex(0x00FF00), LV_PART_INDICATOR);
//    lv_obj_set_style_bg_color(slider, lv_color_hex(0x00FF00), LV_PART_KNOB);
//    
//    // 添加事件回调
//    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, label);
//    
//    // 设置初始亮度为50%
//}



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
	
	ESP01S_Init();

  MQTT_Init();
   

  MQTT_Subscribe(MQTT_USER_TOPIC);
  MQTT_Subscribe(MQTT_SUBSCRIBE_TOPIC);

   // 发布消息
  //  MQTT_Publish(MQTT_PUBLIC_TOPIC, "Hello World");
   

	// lcd_set_dir(LCD_CROSSWISE_180);
	// lcd_init();	
	
	// lv_init();
	// lv_port_disp_init();
	// lv_port_indev_init();
	// HAL_TIM_Base_Start_IT(&htim4);
	// GY302_Init();

	// HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
  // LCD_SetBrightness(499);

	// printf("Hardware Init Ok\n");

//	
//	

//	setup_ui(&guider_ui);
//  events_init(&guider_ui);
	// demo();
  // static uint32_t mq2_adc_value;
  // static float mq2_percent;

	static char MQTT_Message[256];
//	lv_demo_benchmark();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

     if(DHT11_ReadData(&DHT11_Data))
     {
          printf("T:%d H:%d", DHT11_Data.temp_int, DHT11_Data.humi_int);
      }else{
          printf("DHT11 ERROR");
      }
      
    sprintf(MQTT_Message,"{\\\"params\\\":{\\\"Humidity\\\":%d.%d\\,\\\"temperature\\\":%d.%d}}",DHT11_Data.humi_int,DHT11_Data.humi_dec,DHT11_Data.temp_int,DHT11_Data.temp_dec);
	


  // {\\\"params\\\":{\\\"Humi\\\":%d.%d\\,\\\"Temp\\\":%d.%d}}
      MQTT_Publish(MQTT_PARAM_TOPIC, MQTT_Message);
//     static uint32_t time_cnt = 0;
//     time_cnt++;
//     if(time_cnt >= 200)
//     {
//       time_cnt = 0;
// 			 float light= GY302_ReadLight();
// 			lv_label_set_text_fmt(label, "Light: %d lux", (int)light);
// 			printf("Light: %d lux\n", (int)light);

// //      Get_Mq2(&mq2_adc_value,&mq2_percent);
// //      printf("mq2_adc_value: %d, mq2_percent: %.2f\n", mq2_adc_value, mq2_percent);
//     }

//   	lv_task_handler();
		HAL_Delay(5000);

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

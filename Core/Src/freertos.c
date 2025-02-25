/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
#include "lcd.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void displayTask(void *argument);
void sensorTask(void *argument);
osThreadId_t sensorTaskHandle;
const osThreadAttr_t sensorTask_attributes = {
  .name = "sensorTask",
  .stack_size = 3 * 1024,
  .priority = (osPriority_t) osPriorityNormal,
};


osThreadId_t displayTaskHandle;
const osThreadAttr_t displayTask_attributes = {
  .name = "displayTask",
  .stack_size = 2*1024,
  .priority = (osPriority_t) osPriorityNormal,
};

osMutexId_t lvgl_MutexHandle;
const osMutexAttr_t lvgl_Mutex_attributes = {
  .name = "lvgl_Mutex"
};

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
	// lv_tick_inc(1);
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}

static lv_timer_t *sensor_timer = NULL;

static DHT11_Data_TypeDef DHT11_Data;
static uint32_t mq2_adc_value;

static float mq2_percent;
static float light_value;

static char light_str[10];  
static char temp_str[20];
static char humi_str[20];
static char fumes_str[10];


static void sensor_timer_callback(lv_timer_t *timer)
{

    
     
		snprintf(fumes_str,sizeof(fumes_str), "%d%%", (int)mq2_percent);
		lv_label_set_text(guider_ui.main_screen_label_fumes_percentage, fumes_str);
		lv_arc_set_value(guider_ui.main_screen_arc_fumes, mq2_percent);
		

	 lv_label_set_text_fmt(guider_ui.main_screen_label_light_percentage, "%d%%", (int)light_value);
	 lv_arc_set_value(guider_ui.main_screen_arc_light, light_value);

    
}
/* USER CODE END 3 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	lvgl_MutexHandle = osMutexNew(&lvgl_Mutex_attributes);

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
//  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
//  displayTaskHandle = osThreadNew(displayTask, NULL, &displayTask_attributes);
  sensorTaskHandle = osThreadNew(sensorTask, NULL, &sensorTask_attributes);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	printf("Hello World\n");

  /* Infinite loop */
  for(;;)
  {
//    printf("Hello World\n");
//    osDelay(2000);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void displayTask(void *argument)
{
	lcd_set_dir(LCD_CROSSWISE_180);
	lcd_init();	
  lv_init();
 	lv_port_disp_init();
  lv_port_indev_init();
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
  LCD_SetBrightness(brightness_pwm);
	setup_ui(&guider_ui);
  events_init(&guider_ui);
//  sensor_timer = lv_timer_create(sensor_timer_callback, 2000, NULL);
	
	for(;;)
	{
		osMutexAcquire(lvgl_MutexHandle, portMAX_DELAY);	
		lv_task_handler();
		osMutexRelease(lvgl_MutexHandle);
		osDelay(10);
	}
  
}


void sensorTask(void *argument)
{
    DHT11_Init();
    DHT11_Data_TypeDef dht11_data;
    
    for(;;)
    {
        printf("\r\n--- Reading DHT11 ---\r\n");
        if(DHT11_ReadData(&dht11_data))
        {
            // printf("Success! Temperature: %.1f°C, Humidity: %.1f%%\r\n",
            //        DHT11_GetTemperature(&dht11_data),
            //        DHT11_GetHumidity(&dht11_data));
        }
        else
        {
            printf("DHT11 read failed!\r\n");
        }
        
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
/* USER CODE END Application */


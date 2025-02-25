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



#define SENSOR_TASK_STACK_SIZE 3 * 1024
#define DISPLAY_TASK_STACK_SIZE 2 * 1024

#define SENSOR_TASK_PRIORITY osPriorityNormal2
#define DISPLAY_TASK_PRIORITY osPriorityNormal








void displayTask(void *argument);
void sensorTask(void *argument);
osThreadId_t sensorTaskHandle;
const osThreadAttr_t sensorTask_attributes = {
  .name = "sensorTask",
  .stack_size = SENSOR_TASK_STACK_SIZE,
  .priority = (osPriority_t) SENSOR_TASK_PRIORITY,
};


osThreadId_t displayTaskHandle;
const osThreadAttr_t displayTask_attributes = {
  .name = "displayTask",
  .stack_size = DISPLAY_TASK_STACK_SIZE,
  .priority = (osPriority_t) DISPLAY_TASK_PRIORITY,
};

osMutexId_t lvgl_MutexHandle;
const osMutexAttr_t lvgl_Mutex_attributes = {
  .name = "lvgl_Mutex"
};

osMutexId_t sensor_data_MutexHandle;
const osMutexAttr_t sensor_data_Mutex_attributes = {
  .name = "sensor_data_Mutex"
};

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
	lv_tick_inc(1);
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}

static lv_timer_t *sensor_timer = NULL;



static char light_str[10];  
static char temp_str[20];
static char humi_str[20];
static char fumes_str[10];



// 将传感器数据结构体改为静态变量
static struct {
    DHT11_Data_TypeDef dht11;
    uint8_t mq2_percent;
    uint32_t mq2_adc_value;
    uint16_t light_value;
} sensor_data;


static void sensor_timer_callback(lv_timer_t *timer)
{
    // 获取互斥量
    if(osMutexAcquire(sensor_data_MutexHandle, 10) == osOK) {
        snprintf(temp_str, sizeof(temp_str), "%d°C", sensor_data.dht11.temp_int);
        lv_label_set_text(guider_ui.main_screen_label_temp_percentage, temp_str);
        lv_bar_set_value(guider_ui.main_screen_bar_temp, sensor_data.dht11.temp_int, LV_ANIM_OFF);

        snprintf(humi_str, sizeof(humi_str), "%d%%", sensor_data.dht11.humi_int);
        lv_label_set_text(guider_ui.main_screen_label_humi_percentage, humi_str);
        lv_bar_set_value(guider_ui.main_screen_bar_humi, sensor_data.dht11.humi_int, LV_ANIM_OFF);
     
        snprintf(fumes_str, sizeof(fumes_str), "%d%%", (int)sensor_data.mq2_percent);
        lv_label_set_text(guider_ui.main_screen_label_fumes_percentage, fumes_str);
        lv_arc_set_value(guider_ui.main_screen_arc_fumes, sensor_data.mq2_percent);

        lv_label_set_text_fmt(guider_ui.main_screen_label_light_percentage, "%d%%", (int)sensor_data.light_value);
        lv_arc_set_value(guider_ui.main_screen_arc_light, sensor_data.light_value);
        
        // 释放互斥量
        osMutexRelease(sensor_data_MutexHandle);
    }else
		{
			return;
		}
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
  sensor_data_MutexHandle = osMutexNew(&sensor_data_Mutex_attributes);


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
  displayTaskHandle = osThreadNew(displayTask, NULL, &displayTask_attributes);
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
  sensor_timer = lv_timer_create(sensor_timer_callback, 4000, NULL);
	
	for(;;)
	{
		osMutexAcquire(lvgl_MutexHandle, portMAX_DELAY);	
		lv_task_handler();
		osMutexRelease(lvgl_MutexHandle);
		osDelay(30);
	}
  
}


void sensorTask(void *argument)
{    
    for(;;)
    {
        
        // 获取互斥量
        if(osMutexAcquire(sensor_data_MutexHandle, portMAX_DELAY) == osOK) {
            // 读取MQ2传感器数据
            Get_Mq2(&sensor_data.mq2_adc_value, &sensor_data.mq2_percent);
//            printf("MQ2: %d, %d%%\r\n", sensor_data.mq2_adc_value, sensor_data.mq2_percent);
            
            // 读取GY302传感器数据
            sensor_data.light_value = GY302_ReadLight();
            printf("GY302: %d\r\n", sensor_data.light_value);
            
           if(DHT11_ReadData(&sensor_data.dht11))
           {
               printf("Temp: %d,Humi: %d\r\n", 
                      sensor_data.dht11.temp_int, 
                      sensor_data.dht11.humi_int);
           }
            
            // 释放互斥量
            osMutexRelease(sensor_data_MutexHandle);
        }
        
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
/* USER CODE END Application */


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
#include "queue.h"
#include "timers.h"
#include "tim.h"

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
/* 定义传感器数据结构体 */
typedef struct {
    DHT11_Data_TypeDef dht11;
    uint8_t mq2_percent;
    uint32_t mq2_adc_value;
    uint16_t light_value;
} SensorData_t;



#define SENSOR_TASK_STACK_SIZE 3 * 1024
#define DISPLAY_TASK_STACK_SIZE 2 * 1024
#define MQTT_TASK_STACK_SIZE 2*1024

#define SENSOR_TASK_PRIORITY osPriorityNormal1
#define DISPLAY_TASK_PRIORITY osPriorityNormal
#define MQTT_TASK_PRIORITY osPriorityNormal

/* 定义队列句柄 */
static QueueHandle_t sensorDataQueue;
#define QUEUE_LENGTH    5
#define QUEUE_ITEM_SIZE sizeof(SensorData_t)

TimerHandle_t flame_timer = NULL;

static void flame_timer_callback(TimerHandle_t xTimer)
{
  flame_status = false;
}


void mqttTask(void *argument);
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

osThreadId_t mqttTaskHandle;
const osThreadAttr_t mqttTask_attributes = {
  .name = "mqttTask",
  .stack_size = MQTT_TASK_STACK_SIZE,
  .priority = (osPriority_t) MQTT_TASK_PRIORITY,
};
osMutexId_t lvgl_MutexHandle;
const osMutexAttr_t lvgl_Mutex_attributes = {
  .name = "lvgl_Mutex"
};

osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal,
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



void ledTask(void *argument)
{
    for(;;)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
        osDelay(pdMS_TO_TICKS(1000));
    }
}

/* 修改LVGL定时器回调函�?? */
void sensor_timer_callback(lv_timer_t *timer)
{
    static SensorData_t receivedData;
    
    // 从队列接收数据，设置超时时间�??10ms
    if(xQueueReceive(sensorDataQueue, &receivedData, 0) == pdPASS)
    {
        char light_str[10];  
        char temp_str[10];
        char humi_str[10];
        char fumes_str[10];

        if(receivedData.dht11.temp_int > 0 && receivedData.dht11.temp_int < 100)
        {
            snprintf(temp_str, sizeof(temp_str), "%d°C", receivedData.dht11.temp_int);
            lv_label_set_text(guider_ui.main_screen_label_temp_percentage, temp_str);
            lv_bar_set_value(guider_ui.main_screen_bar_temp, receivedData.dht11.temp_int, LV_ANIM_OFF);
        }

        if(receivedData.dht11.humi_int > 0 && receivedData.dht11.humi_int <= 100)
        {
            snprintf(humi_str, sizeof(humi_str), "%d%%", receivedData.dht11.humi_int);
            lv_label_set_text(guider_ui.main_screen_label_humi_percentage, humi_str);
            lv_bar_set_value(guider_ui.main_screen_bar_humi, receivedData.dht11.humi_int, LV_ANIM_OFF);
        }
        
       
        if(receivedData.mq2_percent <= 100)
        {
            snprintf(fumes_str, sizeof(fumes_str), "%d%%", receivedData.mq2_percent);
            lv_label_set_text(guider_ui.main_screen_label_fumes_percentage, fumes_str);
            lv_arc_set_value(guider_ui.main_screen_arc_fumes, receivedData.mq2_percent);
        }
        
        if(receivedData.light_value > 0)
        {
            snprintf(light_str, sizeof(light_str), "%d%%", receivedData.light_value);
            lv_label_set_text(guider_ui.main_screen_label_light_percentage, light_str);
            lv_arc_set_value(guider_ui.main_screen_arc_light, receivedData.light_value);
        }
        if(flame_status)
        {
            lv_led_set_color(guider_ui.main_screen_led_1, lv_color_hex(0xFF3030));
        }
        else
        {
            lv_led_set_color(guider_ui.main_screen_led_1, lv_color_hex(0xFFFFFF));
        }

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
    // 创建队列
    sensorDataQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    if(sensorDataQueue == NULL)
    {
        printf("Queue creation failed!\r\n");
        Error_Handler();
    }
    // 创建火焰定时器,单次触发
    flame_timer = xTimerCreate("flame_timer", pdMS_TO_TICKS(10000), pdFALSE, NULL, flame_timer_callback);
    if(flame_timer == NULL)
    {
        printf("Timer creation failed!\r\n");
        Error_Handler();
    }


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
  // defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  displayTaskHandle = osThreadNew(displayTask, NULL, &displayTask_attributes);
  sensorTaskHandle = osThreadNew(sensorTask, NULL, &sensorTask_attributes);
  // ledTaskHandle = osThreadNew(ledTask, NULL, &ledTask_attributes);
  mqttTaskHandle = osThreadNew(mqttTask, NULL, &mqttTask_attributes);
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

    TickType_t xLastWakeTime;

    lcd_set_dir(LCD_CROSSWISE_180);
    lcd_init();	
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    LCD_SetBrightness(brightness_pwm);
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    

    for(;;)
    {
        
        osMutexAcquire(lvgl_MutexHandle, 0);
        lv_task_handler();
        osMutexRelease(lvgl_MutexHandle);
        
        vTaskDelay(pdMS_TO_TICKS(5));
    
    }
}


/* 修改传感器任�?? */
void sensorTask(void *argument)
{    
    TickType_t xLastWakeTime;
    SensorData_t sensorData;
    uint8_t retry_count;
    
    xLastWakeTime = xTaskGetTickCount();
    
    for(;;)
    {
        
      
         DHT11_ReadData((DHT11_Data_TypeDef*)&sensorData.dht11);
         Get_Mq2(&sensorData.mq2_adc_value, &sensorData.mq2_percent);
         sensorData.light_value = GY302_ReadLight();
				
        if(xQueueSend(sensorDataQueue, &sensorData, 0) != pdPASS)
        {
            printf("Queue send failed!\r\n");
        }else{
            // printf("Queue send success!\r\n");
        }
				
				
				if(sensorData.mq2_percent > threshold_data.mq2)
				{
          BEEP_ON;
          vTaskDelay(pdMS_TO_TICKS(30));
          BEEP_OFF;
        }else if(sensorData.light_value > threshold_data.light)
        {
          BEEP_ON;
          vTaskDelay(pdMS_TO_TICKS(30));
          BEEP_OFF;
        }else if(sensorData.dht11.temp_int > threshold_data.temp)
        {
          BEEP_ON;
          vTaskDelay(pdMS_TO_TICKS(30));
          BEEP_OFF;
        }else if(sensorData.dht11.humi_int > threshold_data.humi)
        {
          BEEP_ON;
          vTaskDelay(pdMS_TO_TICKS(30));
          BEEP_OFF;
        }else{
          BEEP_OFF;
        }
        
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2500));

    }
}

void mqttTask(void *argument)
{
    TickType_t xLastWakeTime;
    SensorData_t sensorData;
    char mqtt_msg[256];
    
    osDelay(pdMS_TO_TICKS(2000));
    xLastWakeTime = xTaskGetTickCount();
    
    for(;;)
    {
        if(xQueuePeek(sensorDataQueue, &sensorData, pdMS_TO_TICKS(100)) == pdPASS)
        {
            sprintf(mqtt_msg, "{\\\"params\\\":{\\\"temperature\\\":%d.%d\\,\\\"Humidity\\\":%d.%d\\,\\\"LightLux\\\":%d\\,\\\"SmokeConcentration\\\":%.1f\\,\\\"Flame_State\\\":%d}}",
                    sensorData.dht11.temp_int, 
                    sensorData.dht11.temp_dec,
                    sensorData.dht11.humi_int, 
                    sensorData.dht11.humi_dec,
                    sensorData.light_value,
                    (float)sensorData.mq2_percent,
                    flame_status);
                    
            MQTT_Publish(MQTT_PARAM_TOPIC, mqtt_msg);
        }
        
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(5000));
    }
}

/* USER CODE END Application */






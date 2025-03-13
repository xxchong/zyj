/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "esp01s.h"
#include "mqtt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "timers.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
void HAL_UART_IdleCallback(UART_HandleTypeDef *huart);

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_spi1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim3;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET)
  {
    HAL_UART_IdleCallback(&huart2);
  }
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream3 global interrupt.
  */
void DMA2_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream3_IRQn 0 */

  /* USER CODE END DMA2_Stream3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi1_tx);
  /* USER CODE BEGIN DMA2_Stream3_IRQn 1 */

  /* USER CODE END DMA2_Stream3_IRQn 1 */
}

/* USER CODE BEGIN 1 */


void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart);   
        
        HAL_UART_DMAStop(huart);    
        
        uint16_t rxLen = ESP_RXBUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);  
                
        if(rxLen > 0)
        {
            esp01s.rxBuffer[rxLen] = '\0';  
            
            //
            if(strstr((char*)esp01s.rxBuffer, "+MQTTSUBRECV"))
            {
                printf("MQTT Message: %s\n", esp01s.rxBuffer);
            }
            else 
            {
                esp01s.rxLen = rxLen;
                esp01s.dataReady = 1;
            }
        }
        
        // ��������DMA����
        if(HAL_UART_Receive_DMA(&huart2, (uint8_t *)esp01s.rxBuffer, ESP_RXBUFFER_SIZE) != HAL_OK)
        {
            Error_Handler();
        }
    }
}


volatile int16_t current_people = 0;    // 当前人数
volatile uint32_t total_people = 0;     // 历史总人�?

// 定义状�?�枚�?
typedef enum {
    STATE_IDLE,      // 空闲状�??
    STATE_S1_ENTER,  // 1号传感器触发，可能是进入
    STATE_S2_EXIT    // 2号传感器触发，可能是离开
} PassageState;

volatile PassageState current_state = STATE_IDLE;  // 当前状�??
static uint32_t last_pa6_tick = 0;     // PA6上次触发时间
static uint32_t last_pb8_tick = 0;     // PB8上次触发时间
static uint32_t state_change_time = 0;  // 状�?�改变时�?

const uint32_t DEBOUNCE_TIME = 500;    // 防抖时间500ms
const uint32_t PASSAGE_TIMEOUT = 2000;  // 通过超时时间2�?

volatile bool flame_status = false;
extern TimerHandle_t flame_timer;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t current_tick = HAL_GetTick();
    
    // 火焰传感器处�?
    if(GPIO_Pin == GPIO_PIN_14)
    {
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14) == GPIO_PIN_RESET)
        {
            flame_status = true;
            if(flame_timer != NULL)
            {
                xTimerResetFromISR(flame_timer, &xHigherPriorityTaskWoken);
            }
        }
    }
    // PB8�?1号传感器（入口外侧）
    else if(GPIO_Pin == GPIO_PIN_8)
    {
        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET && 
           (current_tick - last_pb8_tick) > DEBOUNCE_TIME)
        {
            last_pb8_tick = current_tick;
            
            switch(current_state)
            {
                case STATE_IDLE:
                    current_state = STATE_S1_ENTER;
                    state_change_time = current_tick;
                    printf("1号传感器触发，等�?2号传感器确认进入\r\n");
                    break;
                    
                case STATE_S2_EXIT:
                    if((current_tick - state_change_time) < PASSAGE_TIMEOUT)
                    {
                        // 确认为离�?
                        if(current_people > 0) current_people--;
                        printf("人员离开，当前人�?: %d\r\n", current_people);
                    }
                    current_state = STATE_IDLE;
                    break;
                    
                default:
                    // 重置状�??
                    current_state = STATE_IDLE;
                    break;
            }
        }
    }
    // PA6�?2号传感器（入口内侧）
    else if(GPIO_Pin == GPIO_PIN_6)
    {
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_RESET && 
           (current_tick - last_pa6_tick) > DEBOUNCE_TIME)
        {
            last_pa6_tick = current_tick;
            
            switch(current_state)
            {
                case STATE_IDLE:
                    current_state = STATE_S2_EXIT;
                    state_change_time = current_tick;
                    printf("2号传感器触发，等�?1号传感器确认离开\r\n");
                    break;
                    
                case STATE_S1_ENTER:
                    if((current_tick - state_change_time) < PASSAGE_TIMEOUT)
                    {
                        // 确认为进�?
                        current_people++;
                        total_people++;
                        printf("人员进入，当前人�?: %d，历史�?�人�?: %ld\r\n", 
                               current_people, total_people);
                    }
                    current_state = STATE_IDLE;
                    break;
                    
                default:
                    // 重置状�??
                    current_state = STATE_IDLE;
                    break;
            }
        }
    }
    
    // 超时�?�?
    if(current_state != STATE_IDLE && 
       (current_tick - state_change_time) >= PASSAGE_TIMEOUT)
    {
        current_state = STATE_IDLE;
        printf("超时，重置状态\r\n");
    }
    
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}

/* USER CODE END 1 */

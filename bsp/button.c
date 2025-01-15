
#include "stm32f4xx_hal.h"
#include "button.h"

#define BUTTON_PORT GPIOE

#define BUTTON_RIGHT_PIN GPIO_PIN_11 // 使用GPIO0作为按钮引脚
#define BUTTON_ENTER_PIN GPIO_PIN_10 // 使用GPIO0作为按钮引脚
#define BUTTON_LEFT_PIN GPIO_PIN_9  // 使用GPIO0作为按钮引脚

static uint8_t last_button_state = 0;

uint8_t get_button(void)
{
    uint8_t current_state = 0;

    if (HAL_GPIO_ReadPin(BUTTON_PORT,BUTTON_RIGHT_PIN) == 0)
    {
        current_state = 1;
    }
    else if (HAL_GPIO_ReadPin(BUTTON_PORT,BUTTON_ENTER_PIN) == 0)
    {
        current_state = 2;
    }
    else if (HAL_GPIO_ReadPin(BUTTON_PORT,BUTTON_LEFT_PIN) == 0)
    {
        current_state = 3;
    }

    if (current_state == 2) // 确认键特殊处理
    {
        return current_state;
    }

    if (current_state != 0 && current_state != last_button_state)
    {
        last_button_state = current_state;
        switch (current_state)
        {
        case 1:
            break;
        case 3:
            break;
        }
        return current_state;
    }

    if (current_state == 0)
    {
        last_button_state = 0;
    }

    return 0;
}
/**
  ******************************************************************************
  * @file           : button.cpp
  * @brief          : pushbutton GPIO driver
  ******************************************************************************
*/
#include "button.h"
#include "stm32f7508_discovery.h"

volatile uint32_t button_interrupt_count; //!< button ISR -> user interface

/**
  * @brief blue pushbutton initialization
  */
void Button_Init(void)
{
  GPIO_InitTypeDef gpio_init_structure={0};

  __HAL_RCC_GPIOI_CLK_ENABLE();

  gpio_init_structure.Pin = GPIO_PIN_11;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Mode = GPIO_MODE_IT_RISING;

  HAL_GPIO_Init(GPIOI, &gpio_init_structure);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
  * @brief button GPIO external interrupt handler
  */
extern "C" void EXTI15_10_IRQHandler( void)
{
  __HAL_GPIO_EXTI_CLEAR_IT(KEY_BUTTON_PIN); // reset interrupt latch
  ++button_interrupt_count;
}


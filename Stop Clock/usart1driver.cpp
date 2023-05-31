/**
  ******************************************************************************
  * @file           : usart1driver.cpp
  * @brief          : driver module for USART 1
  ******************************************************************************
*/
#include "usart1driver.h"
#include "stm32f7xx_hal.h"
#include "stm32f7508_discovery.h"
#include "string.h"
#include "stm32f7xx_hal.h"

#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __USART1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_7
#define USARTx_RX_GPIO_PORT              GPIOB
#define USARTx_RX_AF                     GPIO_AF7_USART1

#define USARTx_IRQn                      USART1_IRQn

UART_HandleTypeDef UartHandle;

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
extern "C" void HAL_UART1_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct={0};

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();

  /* Enable USARTx clock */
  USARTx_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(USARTx_IRQn, 15,0);
  HAL_NVIC_EnableIRQ(USARTx_IRQn);
}
//! USART driver constructor from baudrate
usart1_driver::usart1_driver(unsigned baudrate)
{
	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = baudrate;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
			asm("bkpt 0");
	  if(HAL_UART_Init(&UartHandle) != HAL_OK)
			asm("bkpt 0");

	  HAL_NVIC_SetPriority(USARTx_IRQn, 15,0);
	  HAL_NVIC_EnableIRQ(USARTx_IRQn);

	/* Enable the UART Data Register not empty Interrupt */
	__HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);
}

//! usart 1 string output method
void usart1_driver::puts(char const * s)
{
	if(HAL_UART_Transmit_IT(&UartHandle, (uint8_t *)s, strlen(s))!= HAL_OK)
	{
		asm("bkpt 0");
	}
}

//! usart 1 interrupt handler
extern "C" void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandle);
}


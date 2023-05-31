/**
  ******************************************************************************
  * @file           : button.h
  * @brief          : pushbutton GPIO driver
  ******************************************************************************
*/
#ifndef BUTTON_H_
#define BUTTON_H_
#include "stdint.h"

void Button_Init(void);
extern volatile uint32_t button_interrupt_count; // button ISR -> user interface

#endif /* BUTTON_H_ */

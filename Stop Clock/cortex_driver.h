/**
  ******************************************************************************
  * @file           : cortex_driver.h
  * @brief          : initialization functions for uC
  ******************************************************************************
*/
#ifndef CORTEX_DRIVER_H_
#define CORTEX_DRIVER_H_

void SystemClock_Config(void);
void cortex_m7_init(void);
void Error_Handler(void);

#endif /* CORTEX_DRIVER_H_ */

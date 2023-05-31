/**
  ******************************************************************************
  * @file           : sys_tick.h
  * @brief          : priodic interrupt driver
  ******************************************************************************
*/
#ifndef SYS_TICK_H_
#define SYS_TICK_H_
#include "stdint.h"

extern volatile uint32_t timer_ticks_1000Hz; //!< written by SysTick ISR
uint64_t getTime_usec(void);

#endif /* SYS_TICK_H_ */

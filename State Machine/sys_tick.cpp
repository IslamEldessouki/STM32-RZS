/**
 ******************************************************************************
 * @file           : sys_tick.cpp
 * @brief          : periodic interrupt driver
 ******************************************************************************
 */
#include "sys_tick.h"
#include "event.h"

volatile uint32_t timer_ticks_1000Hz; //!< written by SysTick ISR

/**
 * @brief systick callback
 *
 * called from SysTick ISR within interrupt context
 */
extern "C" void sys_tick_callback (void)
{

  static unsigned down_counter_10Hz = 100;
  static unsigned down_counter_100Hz = 10;

  --down_counter_10Hz;
  --down_counter_100Hz;

  //Wenn 0.1 Sekunde vorbei ist
  if (down_counter_10Hz == 0)
    {
      down_counter_10Hz = 100;
      signal_event (EVENT_TICK_10Hz);
    }
  //Wenn 0.01 Sekunde vorbei ist
  if (down_counter_100Hz == 0)
    {
      down_counter_100Hz = 10;
      signal_event (EVENT_TICK_100Hz);
    }

  ++timer_ticks_1000Hz;
}
//! @brief read time from SysTick in microseconds
uint64_t
getTime_usec (void)
{
  uint64_t time;
  uint64_t present_systick;
  uint64_t reload = (*(uint32_t*) 0xe000e014) + 1;

  do
    {
      __DSB ();
      // dummy read (modify) write of "time" to enforce atomicity
      time = __LDREXW ((uint32_t*) &timer_ticks_1000Hz);
      present_systick = (uint64_t) (*(uint32_t*) 0xe000e018);
      __DSB ();
    }
  while (__STREXW ((uint32_t) time, (uint32_t*) &timer_ticks_1000Hz) != 0);

  // milliseconds -> microseconds
  time *= 1000;

  present_systick = reload - present_systick; // because it's a down-counter
  present_systick *= 1000; // millisecs -> microsecs
  present_systick /= reload;

  return time + present_systick;
}


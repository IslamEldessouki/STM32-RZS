/**
 ******************************************************************************
 * @file           : touchscreen.h
 * @brief          : touch-screen interface
 ******************************************************************************
 */
#ifndef APPLICATION_TOUCHSCREEN_H_
#define APPLICATION_TOUCHSCREEN_H_

#include <event.h>

typedef struct
{
  int16_t x; //!< horizontal coordinate on LCD
  int16_t y; //!< vertical coordinate on LCD
}

touch_coordinates;

bool touch_screen_check( touch_coordinates & coo);
void touch_screen_init( void);
event_type check_touch_event( void);

#endif /* APPLICATION_TOUCHSCREEN_H_ */

/**
  ******************************************************************************
  * @file           : touchscreen.cpp
  * @brief          : touch-screen interface
  ******************************************************************************
*/
#include "stm32f7508_discovery.h"
#include "stm32f7508_discovery_ts.h"
#include "stm32f7508_discovery_lcd.h"
#include "touchscreen.h"

void touch_screen_init( void)
{
	uint8_t status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	if (status != TS_OK)
	  asm("bkpt 0");
}

bool touch_screen_check( touch_coordinates & coo)
{
  static bool touch_detected=false;

  TS_StateTypeDef TS_State;
  BSP_TS_GetState(&TS_State);

  if (TS_State.touchDetected && (touch_detected == false))
  {
	  coo.x = TS_State.touchX[0];
	  coo.y = TS_State.touchY[0];
	  return true;
  }
  else
	  return false;
}


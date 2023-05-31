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
#include "event.h"

/**
 * merkt sich das letzte vom Touchscreen gemeldete Event
 */
event_type lastEvent = EVENT_NONE;

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

/**
 * Funktion zur Auswertung der Tastendrücke auf dem Touchscreen
 * wird in der Hauptschleife alle zehntel Sekunde aufgerufen
 * gibt entsprechende "Hardware-Events" des Touchscreens an
 * die Hauptschleife weiter
 *
 * @param keine
 * @return Event vom Typ event_type
 */
event_type
check_touch_event (void)
{
  BSP_TS_ITClear ();
  TS_StateTypeDef TS_State;
  BSP_TS_GetState (&TS_State);

  if (TS_State.touchDetected)
    {
      touch_coordinates coo;
      coo.x = TS_State.touchX[0];
      coo.y = TS_State.touchY[0];

      // Start-Button
      if ((coo.x >= 350) && (coo.x <= 470) && (coo.y >= 80) && (coo.y <= 100)
	  && lastEvent != EVENT_START)
	{ // detektiertes Event zurückgeben und in lastEvent merken
	  lastEvent = EVENT_START;
	  return EVENT_START;
	}

      // Stop-Button
      else if ((coo.x >= 350) && (coo.x <= 440) && (coo.y >= 130)
	  && (coo.y <= 150) && lastEvent != EVENT_STOP)
	{ // detektiertes Event zurückgeben und in lastEvent merken
	  lastEvent = EVENT_STOP;
	  return EVENT_STOP;
	}

      // Reset-Button
      else if ((coo.x >= 350) && (coo.x <= 470) && (coo.y >= 180)
	  && (coo.y <= 200) && lastEvent != EVENT_RESET)
	{ // detektiertes Event zurückgeben und in lastEvent merken
	  lastEvent = EVENT_RESET;
	  return EVENT_RESET;
	}

      // Lap-Button
      else if ((coo.x >= 350) && (coo.x <= 440) && (coo.y >= 230)
	  && (coo.y <= 250) && lastEvent != EVENT_LAP)
	{ // detektiertes Event zurückgeben und in lastEvent merken
	  lastEvent = EVENT_LAP;
	  return EVENT_LAP;
	}
    }

  /**
   * wenn keine Berührung festgestellt wurde, wird lastEvent
   * auf EVENT_NONE zurückgesetzt, damit z.B. mehrmalige Ausführung
   * von EVENT_LAP hintereinander funktioniert
   */
  else if (TS_State.touchDetected == false)
    {
      lastEvent = EVENT_NONE;
    }
  return EVENT_NONE;
}


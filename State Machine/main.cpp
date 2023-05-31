/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Main program and system start
 * @mainpage
 * Project for the STM32F7508-dk Evaluation-Board
 *
 * @see main.cpp
 *
 ******************************************************************************
 */
#include "cortex_driver.h"
#include "stm32f7508_discovery.h"
#include "stm32f7508_discovery_lcd.h"
#include "my_assert.h"
#include "touchscreen.h"
#include "string.h"
#include "button.h"
#include "sys_tick.h"
#include "usart1driver.h"
#include "stdlib.h"
#include "event.h"
#include "stopwatch.h"
#include "my_time.h"

void LCD_init (void);
void Button_Init (void);
void cortex_m7_init (void);
void handle_touch_screen (void);
void prepare_LCD (void);

volatile event_bitfield_type event_bitfield; //!< 32 bits full of events

extern my_time time;

/**
 * @brief  The application entry point.
 *
 * initialization, implements the super loop
 */
extern "C" int
main (void)
{
  cortex_m7_init (); 			// diverse settings for the micro-controller
  BSP_LED_Init (LED1); 			// GPIO setup
  Button_Init (); 			// GPIO + ISR setup
  touch_screen_init (); 		// touchscreen I/O HW setup
  usart1_driver usart1 (115200); 	// create USART driver object

  prepare_LCD ();

  usart1.puts ("Hello from USART\r\n"); // goes to CDC ACM device -> USB COM port

  uint8_t rotator=0;

  // Zeit zu Beginn vor Hauptschleife einmal ausgeben (also 00:00:00)
  BSP_LCD_DisplayStringAtLine (5, time.getTime ());

  while (true) // the SUPERLOOP
    {
      event_type next_event = get_and_reset_event ();

      switch (next_event)
      {
	case EVENT_NONE:
	  BSP_LED_Off (LED1); // light off while sleeping :-)
	  __WFI(); // wait for interrupt / go sleeping
	  BSP_LED_On (LED1);
	  continue;
	  break;
	case EVENT_TICK_10Hz:
	  {
	    BSP_LCD_DisplayChar (20, 20, "|/-\\"[rotator++ & 3]);
	    // alle zehntel Sekunde den Touchscreen auf neues Event prüfen
	    event_type ev = check_touch_event ();
	    // Event in bit-field eintragen
	    if (ev != EVENT_NONE)
	      {
		signal_event (ev);
	      }
	  }
	  break;
	  // Events aus bit-field abarbeiten und an stopwatch_statemachine
	  // senden
	case EVENT_TICK_100Hz:
	  {
	    control_stopwatch (ev_TICK);
	  }
	  break;
	case EVENT_START:
	  {
	    control_stopwatch (ev_START);
	    displayEvent ((char*) "ev_START");
	  }
	  break;
	case EVENT_STOP:
	  {
	    control_stopwatch (ev_STOP);
	    displayEvent ((char*) "ev__STOP");
	  }
	  break;
	case EVENT_LAP:
	  {
	    control_stopwatch (ev_LAP);
	    displayEvent ((char*) "ev___LAP");
	  }
	  break;
	case EVENT_RESET:
	  {
	    control_stopwatch (ev_RESET);
	    displayEvent ((char*) "ev_RESET");
	  }
	  break;
	default:
	  // unbekanntes Event
	  ASSERT(false);
	  break;
      }
    }
}

/**
 * @brief  Touch screen handler
 *
 * Test for "touched"
 * and report coordinates if touch detected
 */
/*void handle_touch_screen (void)
{
  touch_coordinates t;
  if (touch_screen_check (t)) // if new touch detected
    {
      char buf[40]; // beware: limited length !
      strcpy (buf, "Touch x =");
      itoa (t.x, buf + strlen (buf), 10);
      strcpy (buf + strlen (buf), "       "); // wipe old info
      BSP_LCD_DisplayStringAtLine (6, buf);
      strcpy (buf, "Touch y =");
      itoa (t.y, buf + strlen (buf), 10);
      strcpy (buf + strlen (buf), "       ");
      BSP_LCD_DisplayStringAtLine (7, buf);
    }
}*/


/**
 * @brief  LCD initialization
 *
 * initialization and content setup
 */
void
prepare_LCD (void)
{
  LCD_init (); // LCD initialization + start-screen

  // Start-Button
  BSP_LCD_SetBackColor (LCD_COLOR_GREEN);
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAt (350, 80, (char*) " START ", LEFT_MODE);

  // Stop-Button
  BSP_LCD_SetBackColor (LCD_COLOR_RED);
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAt (350, 130, (char*) " STOP ", LEFT_MODE);

  // Reset-Button
  BSP_LCD_SetBackColor (LCD_COLOR_RED);
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAt (350, 180, (char*) " RESET ", LEFT_MODE);

  // Lap-Button
  BSP_LCD_SetBackColor (LCD_COLOR_BLUE);
  BSP_LCD_SetTextColor (LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAt (350, 230, (char*) " LAP ", LEFT_MODE);

  // set LCD defaults
  BSP_LCD_SetBackColor (LCD_COLOR_YELLOW);
  BSP_LCD_SetTextColor (LCD_COLOR_BLUE);
}

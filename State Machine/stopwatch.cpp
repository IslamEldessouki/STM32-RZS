/**
 * @file    rolltor.cpp
 * @brief   rolltor implementation
 */

#include "stopwatch.h"
#include "memory.h"
#include "my_time.h"
#include "stm32f7508_discovery_lcd.h"
#include "string.h"

my_time time{};

/**
 * Reset-Funktion zum Zurücksetzen der Zeit
 * ruft die resetTime()-Funktion des my_time-Objekts auf
 * gibt die Zeit einmal aus
 *
 * @param keine
 * @return void
 */
void Reset (void){
  time.resetTime();
  BSP_LCD_DisplayStringAtLine (5, time.getTime ());
  displayState();
}

/**
 * Funktion zum Inkrementieren der Zeit im Zustand stRUNNING
 * ruft incrementMilliseconds() des my_time-Objekts auf
 * gibt die Zeit auf dem Touchscreen aus
 *
 * @param keine
 * @return void
 */
void Increment (void){
  time.incrementMilliseconds();
  BSP_LCD_DisplayStringAtLine (5, time.getTime ());
  displayState();
}

/**
 * Funktion zum Inkrementieren der Zeit im Zustand stLAPTIME
 * ruft incrementMilliseconds() des my_time-Objekts auf
 *
 * @param keine
 * @return void
 */
void IncrementLap (void){
  time.incrementMilliseconds();
  displayState();
}


/** @brief definition of the state-machine behavior. */
ROM transition_matrix_type transition_matrix =
    {
	{ //Event zur Verarbeitung: ev_START
	    { displayState, st_RUNNING }, // Ausgangszustand: st_STOPPED
	    { displayState, PRESERVE_STATE }, // Ausgangszustand: st_RUNNING
	    { displayState, PRESERVE_STATE } // Ausgangszustand: st_LAPTIME
	},
	{ //Event zur Verarbeitung: ev_STOP
	    { displayState, PRESERVE_STATE }, // Ausgangszustand: st_STOPPED
	    { displayState, st_STOPPED }, // Ausgangszustand: st_RUNNING
	    { displayState, PRESERVE_STATE } // Ausgangszustand: st_LAPTIME
	},
	{ //Event zur Verarbeitung: ev_RESET
	    { Reset, PRESERVE_STATE }, // Ausgangszustand: stSTOPPED
	    { displayState, PRESERVE_STATE }, // Ausgangszustand: st_RUNNING
	    { displayState, PRESERVE_STATE } // Ausgangszustand: st_LAPTIME
	},
	{ //Event zur Verarbeitung: ev_TICK
	    { displayState, PRESERVE_STATE }, // Ausgangszustand: st_STOPPED
	    { Increment, PRESERVE_STATE }, // Ausgangszustand: st_RUNNING
	    { IncrementLap, PRESERVE_STATE } // Ausgangszustand: st_LAPTIME
	},
	{ //Event zur Verarbeitung: ev_LAP
	    { displayState, PRESERVE_STATE }, // Ausgangszustand: st_STOPPED
	    { displayState, st_LAPTIME }, // Ausgangszustand: st_RUNNING
	    { displayState, st_RUNNING } // Ausgangszustand: st_LAPTIME
	}

    };

statemachine stopwatch_statemachine(transition_matrix, st_STOPPED); //!< the state-machine object

/**
 * Hilfsfunktion zur Funktionsüberprüfung der Implementierung und der stopwatch_statemachine
 * diese Funktion wird immer in der Hauptschleife aufgerufen
 * und dient ausschließlich dazu, dass aktuelle Event
 * das an die stopwatch_statemachine gesendet wurde auf dem Touchscreen auszugeben
 *
 * @param char* event
 * @return void
 */
void displayEvent(char* event){
  BSP_LCD_DisplayStringAtLine (7, (char*)" ");
  BSP_LCD_DisplayStringAtLine (7, event);
}

/**
 * Funktion wird entsprechend der "Hardware-Events" in der Hauptschleife aufgerufen
 * Funktion bekommt Event für stopwatch_statemachine übergeben
 * über den Aufruf der Funktion signal_event() wird das Event mit Hilfe der
 * transition_matrix weiter verarbeitet und die stopwatch_statemachine führt
 * eine entsprechende Aktion oder Übergang in einen anderen Zustand aus
 *
 * @param event vom Typ statemachine_event_type
 * @return void
 */
void control_stopwatch( statemachine_event_type event)
{
  stopwatch_statemachine.signal_event( event);
}

/**
 * Hilfsfunktion zum Ausgeben des Zustands der stopwatch_statemachine
 *
 * @param keine
 * @return void
 */
void displayState (void)
{
  switch (stopwatch_statemachine.get_state ())
  {
    case PRESERVE_STATE:
      {
	BSP_LCD_DisplayStringAtLine (9, (char*) "PRESERVE_STATE");
      }
      break;
    case st_RUNNING:
      {
	BSP_LCD_DisplayStringAtLine (9, (char*) "st_RUNNING");
      }
      break;
    case st_LAPTIME:
      {
	BSP_LCD_DisplayStringAtLine (9, (char*) "st_LAPTIME");
      }
      break;
    case st_STOPPED:
      {
	BSP_LCD_DisplayStringAtLine (9, (char*) "st_STOPPED");
      }
      break;
    case N_STATES:
      {
	BSP_LCD_DisplayStringAtLine (9, (char*) "N_STATES");
      }
      break;
  }
}

/*
 * stopwatch.h
 *
 *  Created on: Nov 25, 2020
 *      Author: schaefer
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

//! State type, application specific
typedef enum
{
  st_STOPPED, //!< state STOPPED
  st_RUNNING, //!< state RUNNING
  st_LAPTIME, //!< state LAPTIME
  N_STATES, //!< pseudostate number of states
  PRESERVE_STATE //!< pseudostate NO target state, stay here !
} state_type;

//! Event type, application specific
typedef enum
{
  ev_START, //!< START button
  ev_STOP, //!< STOP button
  ev_RESET, //!< RESET button
  ev_TICK, //!< Sys_tick Event
  ev_LAP, //!< LAP button
  N_STATEMACHINE_EVENTS //!< pseudoevent vector size
} statemachine_event_type;

void control_stopwatch( statemachine_event_type);
void displayEvent(char* event);
void displayState(void);
void Increment (void);
void IncrementLap (void);
void Reset (void);

#include "statemachine.h"

#endif /* STOPWATCH_H_ */

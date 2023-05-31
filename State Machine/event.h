/**
 * @file    event.h
 * @brief   event signaling mechanism
 * @author  Dr. Klaus Schaefer schaefer@eit.h-da.de
 */

#ifndef EVENT_H_
#define EVENT_H_

/*Hardware-Events werden in Hauptschleife für stopwatch_statemachine
übersetzt*/
typedef enum
{
  EVENT_TICK_10Hz, //!< timer event
  EVENT_TICK_100Hz, //!< timer event
  EVENT_START, //!< Touchscreen event
  EVENT_STOP, //!< Touchscreen event
  EVENT_LAP, //!< Touchscreen event
  EVENT_RESET, //!< Touchscreen event
  N_EVENTS, //!< pseudoevent: vector size
  EVENT_NONE //!< pseudoevent: NOTHING
} event_type; //!< event names corresponding to bits in @ref event_bitfield

#include "event_generic.h"

#endif /* EVENT_H_ */

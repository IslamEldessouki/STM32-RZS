/**
 * @file    event_generic.h
 * @brief   portable + generic event signaling mechanism
 * @author  Dr. Klaus Schaefer klaus.schaefer@h-da.de
 */
#ifndef EVENT_GENERIC_H_
#define EVENT_GENERIC_H_

#include "stdint.h"
#include "cmsis_gcc.h" // for the machine language macros

typedef uint32_t event_bitfield_type;
extern volatile event_bitfield_type event_bitfield;

/** @brief signal event by setting single bit within @ref event_bitfield
@param  event specifies event to be signaled
@return true true if event was already set, else false
*/
static inline volatile bool signal_event( event_type event)
{
  __DMB();
  bool retval = // test bit state before it is being set
	((1 << event)
	    &
	__atomic_fetch_or( &event_bitfield, 1 << event, __ATOMIC_SEQ_CST))
      != 0;
  __DMB();
  return retval;
}

/** @brief get most important event and reset it within @ref event_bitfield
* @return most important event : event_type
*/
static inline event_type get_and_reset_event( void)
{
  uint8_t event_bitnumber;
  uint32_t no_success=1;

  do
  {
      __DMB();
      volatile uint32_t event_snapshot = __LDREXW( &event_bitfield);
      unsigned bit_index = __CLZ( event_snapshot); // find most significant 1 bit
      if( bit_index == 32) // 32 means: no bit was set
	{
	  __CLREX();
	  __DMB();
	  return EVENT_NONE;
	}
      event_bitnumber = 31 - bit_index; // calculate corresponding bit number 0 .. 31
      event_snapshot &= ~ (1 << event_bitnumber);
      no_success = __STREXW( event_snapshot, &event_bitfield);
  }
  while( no_success);

  __DMB();
  return (event_type)event_bitnumber;
}

#endif /* EVENT_GENERIC_H_ */

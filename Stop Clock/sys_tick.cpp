/**
 ******************************************************************************
 * @file           : sys_tick.cpp
 * @brief          : periodic interrupt driver
 ******************************************************************************
 */
#include "sys_tick.h"
#include "my_time.h"
#include "clock.h"
my_time time { };
my_time touchLock { };
clock clock1;
volatile uint32_t timer_ticks_1000Hz; //!< written by SysTick ISR
volatile uint32_t secondsCounter;
volatile bool secondsGuard;
/**
 * @brief systick callback
 *
 * called from SysTick ISR within interrupt context
 */
extern "C" void sys_tick_callback(void) {
	++timer_ticks_1000Hz;

	/*
	 * prüft ob, eine Sekunde vorbei ist.
	 * wenn eine Sekunde vorbei ist, dann wird
	 * die Variable secondsGuard als true gesetzt.
	 */
	if(secondsCounter!=0)
	{
		--secondsCounter;
	}
	if(secondsCounter==0)
	{
		secondsGuard=true;
	}

	/*
	 * Erhöhung des Attributes Milliseconds des Objekts time vom Typ my_time
	 * Alle 100 Millisekunden wird inkrementiert
	 * zusätzlich wird geprüft, ob die Uhr tatsächlich laufen soll
	 */
	if ((timer_ticks_1000Hz % 10 == 0) && (clock1.runClock() == true)) {
		time.incrementMilliseconds();
	}
	/*
	 * Erhöhung des Attributes Milliseconds des Objekts touchLock vom Typ my_time
	 * Alle 100 Millisekunden wird inkrementiert
	 */
	if (timer_ticks_1000Hz % 10 == 0) {
		touchLock.incrementMilliseconds();
	}
}






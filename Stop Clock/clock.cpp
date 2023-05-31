/*
 * clock.cpp
 *
 *  Created on: 3 Nov 2021
 *      Author: Islam Eldessouki
 */

#include "my_time.h"
#include "clock.h"
extern my_time time;
/*
 * Zustand der Uhr
 *
 * Funktion gibt Attribut m_run der Klasse Clock zurück
 *
 * @param keine
 * @return Rückgabewert ist das Attribut bool run der Klasse Clock
 */
bool clock::runClock() {
	return m_run;
}

/*
 * Funktion zum Starten und Stoppen der Uhr sowie zum Einstellen der Uhr
 *
 * Funktion prüft zunächst mit dem Aufruf der Funktion touch_screen_check()
 * ob eine Eingabe erfolgt ist
 * danach werden die Koordinaten geprüft und die entsprechende Funktion der
 * Clock ausgeführt (z.B. Start oder Stop)
 *
 * @param keine
 * @return Rückgabewert void
 */
void clock::RunandStopandSetClock() {
	touch_coordinates coord;
	if (touch_screen_check(coord)) {
		if ((coord.x >= 350) && (coord.x <= 390) && (coord.y >= 100)
				&& (coord.y <= 120)) {
			m_run = true;
		} else if ((coord.x >= 350) && (coord.x <= 400) && (coord.y >= 160)
				&& (coord.y <= 180)) {
			m_run = false;
		} else if ((coord.x >= 0) && (coord.x <= 40) && (coord.y >= 80)
				&& (coord.y <= 120)) {
			time.incrementMinutes();
		} else if ((coord.x >= 60) && (coord.x <= 90) && (coord.y >= 80)
				&& (coord.y <= 120)) {time.incrementSeconds();
		} else if ((coord.x >= 0) && (coord.x <= 40) && (coord.y >= 160)
				&& (coord.y <= 200)) {
			time.decrementMinutes();
		} else if ((coord.x >= 60) && (coord.x <= 90) && (coord.y >= 160)
				&& (coord.y <= 200)) {
			time.decrementSeconds();
		}
	}
}

/*
 * Funktion zum Starten und Stoppen der Uhr sowie zum Reset der Uhr
 *
 * Funktion prüft zunächst mit dem Aufruf der Funktion touch_screen_check()
 * ob eine Eingabe erfolgt ist
 * danach werden die Koordinaten geprüft und die entsprechende Funktion der
 * Clock ausgeführt (z.B. Start, Stop oder Reset)
 *
 * @param keine
 * @return Rückgabewert void
 */
void clock::RunandStopandResetClock()
{
	touch_coordinates coord;
	if (touch_screen_check(coord)) {
		if ((coord.x >= 350) && (coord.x <= 390) && (coord.y >= 100)
				&& (coord.y <= 120)) {
			m_run = true;
		} else if ((coord.x >= 350) && (coord.x <= 400) && (coord.y >= 160)
				&& (coord.y <= 180)) {
			m_run = false;
		} else if ((coord.x >= 350) && (coord.x <= 410) && (coord.y >= 220)
				&& (coord.y <= 240)) {
			time.resetTime();
			m_run = false;
		}
	}

}


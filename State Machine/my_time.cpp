/*
 * my_time.cpp
 *
 *  Created on: 31 Oct 2021
 *      Author: Islam Eldessouki
 */

#include <stdlib.h>
#include <string.h>
#include <my_time.h>

my_time::my_time(uint32_t m, uint32_t s, uint32_t milli) :
m_minutes { m }, m_seconds { s }, m_milliseconds { milli }
{
}


/*
 * Funktion, die die Minuten liest
 *
 * @param m die Anzahl der abgegebenen Minuten
 * @return kein
 */
void my_time::setMinutes(uint32_t m) {
	m_minutes = m;
}

/*
 * Funktion, die die Sekunden liest
 *
 * @param s die Anzahl der abgegebenen Sekunden
 * @return kein
 */
void my_time::setSeconds(uint32_t s) {
	m_seconds = s;
}

/*
 * Funktion, die die Millisekunden liest
 *
 * @param milli die Anzahl der abgegebenen Millisekunden
 * @return kein
 */
void my_time::setMilliseconds(uint32_t milli) {
	m_milliseconds = milli;
}

/*
 * Funktion, die die Minuten zurückgibt
 *
 * @param kein
 * @return m_minutes die Anzahl der stehenden Minuten
 */
uint32_t my_time::getMinutes() {
	return m_minutes;
}

/*
 * Funktion, die die Sekunden zurückgibt
 *
 * @param kein
 * @return m_seconds die Anzahl der stehenden Sekunden
 */
uint32_t my_time::getSeconds() {
	return m_seconds;
}

/*
 * Funktion, die die Millisekunden zurückgibt
 *
 * @param kein
 * @return m_milliseconds die Anzahl der stehenden Millisekunden
 */
uint32_t my_time::getMilliseconds() {
	return m_milliseconds;
}

/*
 * Funktion, die die Anzahl der stehenden Minuten inkrementiert
 *
 * @param kein
 * @return kein
 */
void my_time::incrementMinutes() {
	if (m_minutes < 59) {
		m_minutes++;
	}
}


/*
 * Funktion, die die Anzahl der stehenden Sekunden inkrementiert
 *
 * @param kein
 * @return kein
 */
void my_time::incrementSeconds() {
	if (m_seconds < 59) {
		m_seconds++;
	} else {
		m_minutes++;
		m_seconds = 0;
	}
	m_milliseconds = 0;
}


/*
 * Funktion, die die Anzahl der stehenden Millisekunden inkrementiert
 *
 * @param kein
 * @return kein
 */
void my_time::incrementMilliseconds() {
	m_milliseconds++;
	if (m_milliseconds >= 100) {
		m_seconds = m_seconds + m_milliseconds / 100;
		m_milliseconds = 0;
	}
	if (m_seconds >= 60) {
		m_minutes = m_minutes + m_seconds / 60;
		m_seconds = 0;
		m_milliseconds = 0;
	}
}


/*
 * Funktion, die die Anzahl der stehenden Minuten dekrementiert
 *
 * @param kein
 * @return kein
 */
void my_time::decrementMinutes() {
	if (m_minutes > 0) {
		m_minutes--;
	} else if (m_minutes == 0) {
		m_minutes = 59;
	}
}

/*
 * Funktion, die die Anzahl der stehenden Sekunden dekrementiert
 *
 * @param kein
 * @return kein
 */
void my_time::decrementSeconds() {
	if (m_seconds > 0) {
		m_seconds--;
		m_milliseconds = 0;
	} else if (m_seconds == 0) {
		m_seconds = 59;
		m_milliseconds = 0;
	}
}

/*
 * Funktion zur Ausgabe der Zeit als String
 *
 * Funktion liest die Attribute der Klasse my_time aus und schreibt die
 * entsprechenden Millisekunden, Sekunden und Minuten in eine String
 * es erfolgt die Ausgabe gemäß MM::SS:HH
 *
 * @param keine
 * @return Rückgabewert char* Zeit als String
 */
char* my_time::getTime() {
	timeString[0] = my_time::m_minutes / 10 + '0';
	timeString[1] = my_time::m_minutes % 10 + '0';
	timeString[2] = ':';
	timeString[3] = my_time::m_seconds / 10 + '0';
	timeString[4] = my_time::m_seconds % 10 + '0';
	timeString[5] = ':';
	timeString[6] = my_time::m_milliseconds / 10 + '0';
	timeString[7] = my_time::m_milliseconds % 10 + '0';
	timeString[8] = 0;
	return timeString;
}

/*
 * Funktion zum Prüfen einer Zeitdauer
 *
 * die Funktion dient zur Überprüfung, ob seit ihrem Aufruf 10 Hundertstel
 * Millisekunden vergangen sind
 * die Funktion wird zum kurzzeitigen Sperren des Touch-Screens verwendet
 *
 * @param keine
 * @return Rückgabewert bool
 */
bool my_time::lockTimeReached() {
	if (m_milliseconds >= 50) {
		return true;
	} else {
		return false;
	}
}

/*
 * Funktion zum Reset der Zeit
 *
 *die Funktion gibt Attribute der Klasse (m_minutes,
 *m_seconds und m_milliseconds) den Wert Null.
 *
 * @param keine
 * @return Keine
 */
void my_time::resetTime()
{
	m_minutes = 0;
	m_seconds = 0;
	m_milliseconds = 0;
}

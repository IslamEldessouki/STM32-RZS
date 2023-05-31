/*
 * my_time.h
 *
 *  Created on: 31 Oct 2021
 *      Author: Islam Eldesouki
 */

#ifndef MY_TIME_H_
#define MY_TIME_H_

#include "stdint.h"

class my_time {

public:

	my_time(uint32_t m = 0, uint32_t s = 0, uint32_t milli = 0);
	void setMinutes(uint32_t m);
	void setSeconds(uint32_t s);
	void setMilliseconds(uint32_t milli);
	uint32_t getMinutes();
	uint32_t getSeconds();
	uint32_t getMilliseconds();
	void incrementMinutes();
	void incrementSeconds();
	void incrementMilliseconds();
	void decrementMinutes();
	void decrementSeconds();
	char* getTime();
	bool lockTimeReached();
	void resetTime();

private:
	uint32_t m_minutes;
	uint32_t m_seconds;
	uint32_t m_milliseconds;
	//Es ist nicht die beste Loesung, aber ich weiss nicht, was die Alternative ist.
	char timeString[10];
};

#endif /* MY_TIME_H_ */

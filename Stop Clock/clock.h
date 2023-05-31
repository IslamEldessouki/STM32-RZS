/*
 * clock.h
 *
 *  Created on: 3 Nov 2021
 *      Author: Islam Eldessouki
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "stdint.h"
#include "touchscreen.h"
class clock {
public:
	bool runClock();
	void RunandStopandSetClock();
	void RunandStopandResetClock();
private:
	bool m_run;
};

#endif /* CLOCK_H_ */

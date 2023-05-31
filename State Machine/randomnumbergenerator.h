/**
  ******************************************************************************
  * @file           : randomnumbergenerator.h
  * @brief          : wrapper around hardware true random number generator
  ******************************************************************************
*/
#ifndef DRIVERS_RANDOMNUMBERGENERATOR_H_
#define DRIVERS_RANDOMNUMBERGENERATOR_H_

#include "stm32f7xx_hal.h"

class random_number_generator_t
{
public:
	random_number_generator_t(); //!< constructor initializes hardware RNG
	uint32_t get( void) //!< get newly created random number
	{
		uint32_t n;
		HAL_RNG_GenerateRandomNumber( &hrng, &n);
		return n;
	}
private:
	RNG_HandleTypeDef hrng;
};

extern random_number_generator_t random_number_generator; //!< globally accessible RNG object

#endif /* DRIVERS_RANDOMNUMBERGENERATOR_H_ */

/**
  ******************************************************************************
  * @file           : randomnumbergenerator.cpp
  * @brief          : wrapper around hardware true random number generator
  ******************************************************************************
*/
#include <randomnumbergenerator.h>

random_number_generator_t::random_number_generator_t()
{
	hrng.Instance=RNG;
	__RNG_CLK_ENABLE();
	HAL_RNG_Init( &hrng);
}

random_number_generator_t random_number_generator;

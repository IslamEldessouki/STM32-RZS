/**
  ******************************************************************************
  * @file           : usart1driver.h
  * @brief          : driver module for USART 1
  ******************************************************************************
*/
#ifndef APPLICATION_USER_USART1DRIVER_H_
#define APPLICATION_USER_USART1DRIVER_H_

class usart1_driver
{
public:
	usart1_driver( unsigned baudrate);
	void put( char c)
	{
	  char s[2]={c,0};
	  puts( s);
	};
	void puts( const char *);
	bool input_ready(void)
	{
	  return false;
	};
	virtual char get( void)
	{
	  return 0;
	};
};

#endif /* APPLICATION_USER_USART1DRIVER_H_ */

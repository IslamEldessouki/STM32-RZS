/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Main program and system start
 * @mainpage
 * Project for the STM32F7508-DK Evaluation-Board
 *
 * @see main.cpp
 *
 ******************************************************************************
 */
#include "cortex_driver.h"
#include "stm32f7508_discovery.h"
#include "stm32f7508_discovery_lcd.h"
#include "touchscreen.h"
#include "string.h"
#include "button.h"
#include "sys_tick.h"
#include "usart1driver.h"
#include "stdlib.h"
#include "my_time.h"
#include "clock.h"

void LCD_init(void);
void Button_Init(void);
void cortex_m7_init(void);
void handle_touch_screen( void);
void Tot_Mann_Schalter(void);
void prepare_LCD_1_2( void);
void echtzeit_Uhr(void);
void prepare_LCD_1_3(void) ;
void stoppUhr(void);

extern clock clock1;
extern my_time time;
extern my_time touchLock;


/**
 * @brief The application entry point.
 *
 * initialization, implements the super loop
 */
extern "C" int main(void) {
	cortex_m7_init(); // diverse settings for the micro-controller
	BSP_LED_Init(LED1); // GPIO setup
	Button_Init(); // GPIO + ISR setup
	touch_screen_init(); // touchscreen I/O HW setup
	usart1_driver usart1(115200); // create USART driver object
	//prepare_LCD_1_2(); // für Aufgabe 1.2
	prepare_LCD_1_3(); // für Aufgabe 1.3
	usart1.puts("Hello from USART\r\n"); // goes to CDC ACM device -> USB COM port
	unsigned loops=0;

	while (true) // *THE* SUPERLOOP
	{
		Tot_Mann_Schalter(); // Augabe 1.1
		//echtzeit_Uhr(); // Aufgabe 1.2
		stoppUhr();  // Aufgabe 1.3

		char buf[40]; // beware: limited length !
		strcpy(buf, "Loops   =");
		itoa( loops, buf + strlen(buf),10);
		BSP_LCD_DisplayStringAtLine ( 8, buf);
		++loops;
	}
}

/**
 * @brief Touch screen handler
 *
 * Test for "touched"
 * and report coordinates if touch detected
 */
void handle_touch_screen(void) {
	touch_coordinates t;
	if (touch_screen_check(t)) // if new touch detected
	{
		char buf[40]; // beware: limited length !
		strcpy(buf, "Touch x =");
		itoa(t.x, buf + strlen(buf), 10);
		strcpy(buf + strlen(buf), " "); // wipe old info
		BSP_LCD_DisplayStringAtLine(6, buf);
		strcpy(buf, "Touch y =");
		itoa(t.y, buf + strlen(buf), 10);
		strcpy(buf + strlen(buf), " ");
		BSP_LCD_DisplayStringAtLine(7, buf);
	}
}

/*
 * Funktion, die die Aufgabe 1.1 realisiert
 * Man muss mindestens ein mal pro Sekunde
 * die Taste drücken, sonst geht die LED aus.
 *
 * @param keine
 * @return keine
 */
void Tot_Mann_Schalter(void)
{
	if(button){
		button=false;
		BSP_LED_On(LED1);
		secondsCounter=1000;
	}
	else if(secondsGuard){
		secondsGuard=false;
		BSP_LED_Off(LED1);
	}
}

/**
 * @brief LCD initialization
 *
 * initialization and content setup
 */
void prepare_LCD_1_2(void) {
	LCD_init(); // LCD initialization + start-screen
	// write sample rectangle
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(350, 160, "Stop", LEFT_MODE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	// write sample key text box
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(350, 100, "Run", LEFT_MODE);
	// set LCD defaults
	BSP_LCD_SetBackColor(LCD_COLOR_YELLOW);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
}

/**
 * @brief LCD initialization
 *
 * initialization and content setup
 */
void prepare_LCD_1_3(void) {
	LCD_init(); // LCD initialization + start-screen
	// write sample rectangle
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(350, 160, "Stop", LEFT_MODE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	// write sample key text box
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(350, 100, "Run", LEFT_MODE);
	// write sample key text box
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(350, 220, "Reset", LEFT_MODE);
	// set LCD defaults
	BSP_LCD_SetBackColor(LCD_COLOR_YELLOW);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
}

/*
 * Funktion, die die Aufgabe 1.2 realisiert.
 *
 *
 * @param keine
 * @return keine
 */
void echtzeit_Uhr(void)
{
	/*
	 * Uhr ausgeben
	 */
	BSP_LCD_DisplayStringAtLine(5, time.getTime());
	/*
	 * prüfen, ob Uhr gestartet oder gestoppt wurde
	 * Uhr stellen
	 */
	clock1.RunandStopandSetClock();
}

/*
 * Funktion, die die Aufgabe 1.2 realisiert.
 *
 * @param keine
 * @return keine
 */
void stoppUhr(void)
{
	/*
	 * Uhr ausgeben
	 */
	BSP_LCD_DisplayStringAtLine(5, time.getTime());
	/*
	 * prüfen, ob Uhr gestartet oder gestoppt wurde
	 * Uhr reset
	 */
	clock1.RunandStopandResetClock();

}

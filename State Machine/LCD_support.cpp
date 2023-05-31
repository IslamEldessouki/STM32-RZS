/**
  ******************************************************************************
  * @file           : LCD_support.cpp
  * @brief          : interface to BSP LCD library
  ******************************************************************************
*/
#include "main.h"
#include "stm32f7508_discovery.h"
#include "stm32f7508_discovery_lcd.h"
#include "string.h"
#include "stdlib.h"

static const char hexdigits[] = "0123456789abcdef";

/**
  * @brief  LCD hardware initialization
  *
  * initialization, draw framework
  */
void LCD_init(void)
{
  uint64_t serial; // microcontroller's serial number
  serial = *(uint32_t*) 0x1ff0f420;
  serial |= (uint64_t) (*(uint32_t*) 0x1ff0f424) << 32;
  serial ^= (uint64_t) (*(uint32_t*) 0x1ff0f428) << 24;
  serial ^= serial >>32;


  BSP_LCD_Init ();
  BSP_LCD_LayerDefaultInit (LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer (LTDC_ACTIVE_LAYER);
  BSP_LCD_DisplayOn ();
  BSP_LCD_SetFont (&LCD_DEFAULT_FONT);
  BSP_LCD_Clear(LCD_COLOR_YELLOW);

  BSP_LCD_SetFont (&Font24);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), Font24.Height * 3);

  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_DisplayStringAt( 0, Font24.Height , (char*)"RZS Construction Site", CENTER_MODE);

  BSP_LCD_SetBackColor(LCD_COLOR_YELLOW);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);

  char serial_string[25] = "Serial  =";
  itoa(serial, serial_string + strlen( serial_string),16);
  BSP_LCD_DisplayStringAtLine (10, serial_string);
}

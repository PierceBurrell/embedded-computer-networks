/*
 * main.c
 *
 * this is the main lcd application
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2018
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include <stdio.h>
#include <adc.h>

// LCD DEFINES

// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] =

{
  "*      Pierce Burrell      *",
  "*      Welcome to SHU      *"
};

// CODE
	gpio_pin_t pot = {PA_0, GPIOA, GPIO_PIN_0}; // SETS POT PIN UP PIN 0 MAP
	gpio_pin_t temp = {PF_10, GPIOF, GPIO_PIN_10}; // SETS POT PIN UP PIN 0 MAP
	gpio_pin_t light = {PF_9, GPIOF, GPIO_PIN_9}; // SETS POT PIN UP PIN 0 MAP

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	init_adc(pot); // SETTING ADC AS PIN POT
	init_adc(temp); // SETTING ADC AS TEMP PIN
	init_adc(light); // SETTING ADC AS TEMP PIN

 
  // initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // CHANGED TO BLUE CUZ COOL
  BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
  BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER); 
    
  // delay a little ...
  HAL_Delay(5000);

	
  while(1)
  {
		// Reading the adc pot value
		// Analog Input Is PA_0 --> PF_6
		uint16_t adc_val = read_adc(pot);
		uint16_t temp_val = read_adc(temp);
		uint16_t light_val = read_adc(light);
		
		float Voltage = (3300.0 * (temp_val/4095.0)); // Calc For Voltage
		float Temperature = (Voltage - 500) / 10.0; // Calc For Converting Volt To Temp 3.3V	
		
    // format a string based around the uptime counter
    char str[12];
    sprintf(str, "Raw ADC: = %4d", adc_val);
		BSP_LCD_ClearStringLine(6); //clr string
    BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
		
		// making percentage reading Constrained
    sprintf(str, "Pot Value: = %03.1f", (adc_val/4095.0)*35); // Converts to Percent float 2 decimal places
		BSP_LCD_ClearStringLine(7); //clr string
    BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str); // clearing string for line 7
		
		// bargraph - makes a line then you add another line on top [---   ]
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK); // Transparent (Same colour as ur bg)
		BSP_LCD_FillRect(0, 200, 480, 20); // Creating rectangle
		BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Your actual graph colour	
		BSP_LCD_FillRect(0, 200, 480*(adc_val/4095.0), 20); // Actual values changing 480 pixels width
		
		
		// Temp Print
		sprintf(str, "Temp = %03.2f", (((temp_val/4095.0)*3300)- 500) / 10.0); // Converts to Percent float 2 decimal places
//	sprintf(str, "Temp: = %03.3f", (Temperature));
		BSP_LCD_ClearStringLine(9); //clr string
    BSP_LCD_DisplayStringAtLine(9, (uint8_t *)str); // clearing string for line 7
		
		// Light Print -- Perform Calculation For %
		sprintf(str, "Light = %03.2f", (light_val/4095.0)*100); // Converts to Percent float 2 decimal places
		BSP_LCD_ClearStringLine(10); //clr string
    BSP_LCD_DisplayStringAtLine(10, (uint8_t *)str); // clearing string for line 7
    
    HAL_Delay(1000);
  }
}

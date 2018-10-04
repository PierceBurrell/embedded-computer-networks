/*
 * main.c
 *
 * this is the main blinky application (this code is dependent on the
 * extra shu libraries such as the pinmappings list and the clock configuration
 * library)
 *
 * author:    Dr. Alex Shenfield
 * date:      01/09/2018
 * purpose:   55-604481 embedded computer networks : lab 101
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to GPIO PI1 (again, this is the inbuilt led)
gpio_pin_t led = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOI, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOI, GPIO_PIN_15};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  
  // initialise the gpio pins
  init_gpio(led, OUTPUT);
//	init_gpio(led2, OUTPUT);
//	init_gpio(led3, OUTPUT);
  
  // loop forever ...
  while(1)
  {
    // toggle the led on the gpio pin
    toggle_gpio(led);
    
    // wait for 1 second
    HAL_Delay(1000);
		
		    // toggle the led on the gpio pin
    toggle_gpio(led2);
    
    // wait for 1 second
    HAL_Delay(1000);
		
		    // toggle the led on the gpio pin
    toggle_gpio(led3);
    
    // wait for 1 second
    HAL_Delay(1000);
		

  }
}

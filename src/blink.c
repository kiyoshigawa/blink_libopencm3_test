/* 
This is my attempy at learning how to blink on an STM32F070F6 arm chip using the libopencm3 libraries.
Copyright 2019 - kiyoshigawa - tim@twa.ninja
*/
/*
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "timing.h"

//number of milliseconds between LED changing states
#define LED_BLINK_RATE 1000

int main(void) {
	//Setup external clock:
	setup_external_48MHz_clock_from_16MHz_crystal();
	//setup sys_tick:
	systick_setup();

	//Clock to GPIO:
	rcc_periph_clock_enable(RCC_GPIOA);

	//GPIO Pin to Output:
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

	//make blink work without a delay function:
	volatile uint64_t last_led_blink_time = 0;

	//Blinky Loop:
	while(1){
		if((millis()-last_led_blink_time) >= LED_BLINK_RATE){
			gpio_toggle(GPIOA, GPIO5);
			last_led_blink_time = millis();
		}
	}
	return 0;
}
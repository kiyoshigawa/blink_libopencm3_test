/* 
This is my attempy at learning how to blink on an STM32F070F6 arm chip using the libopencm3 libraries.
*/

#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "timing.h"

int main(void) {
	//Setup clocks:
	rcc_clock_setup_in_hsi_out_48mhz();

	//setup sys_tick:
	systick_setup();

	//Clock to GPIO:
	rcc_periph_clock_enable(RCC_GPIOA);

	//GPIO Pin to Output:
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

	//Blinky Loop:
	while(1){
		gpio_toggle(GPIOA, GPIO5);
		delay(1000);
	}
	return 0;
}
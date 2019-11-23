/*
This uses the systick timer to keep track of how many milliseconds have ellapsed since the program began.
It also adds a blocking delay function.
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

#include "timing.h"

//this sets the clock up to use an external 16MHz crystal with a 3x PLL multiplier for a system clock of 48MHz
void setup_external_48MHz_clock_from_16MHz_crystal(void){
	//enable external clock and wait for stabilization, then set the sysclock to the external clock
	rcc_osc_on(RCC_HSE);
	rcc_wait_for_osc_ready(RCC_HSE);
	rcc_set_sysclk_source(RCC_HSE);

	//this sets the prescale values to not divide the clock signal for the AHB and APB1 prescales.
	rcc_set_hpre(RCC_CFGR_HPRE_NODIV);
	rcc_set_ppre(RCC_CFGR_PPRE_NODIV);

	//this controls flash prefetch settings - see notes in function definitions for why this has to be called before increasing the clock speed to 48MHz.
	flash_prefetch_enable();
	flash_set_ws(FLASH_ACR_LATENCY_024_048MHZ);

	//this sets up the PLL to use the external 16MHz crystal: 16MHz * 3 = 48MHz */
	rcc_set_pll_multiplication_factor(RCC_CFGR_PLLMUL_MUL3);
	rcc_set_pll_source(RCC_CFGR_PLLSRC_HSE_CLK);
	rcc_set_pllxtpre(RCC_CFGR_PLLXTPRE_HSE_CLK);

	//turn on the pll clock and wait for it to be ready, then switch over to 48MHz operation on the external crystal:
	rcc_osc_on(RCC_PLL);
	rcc_wait_for_osc_ready(RCC_PLL);
	rcc_set_sysclk_source(RCC_PLL);

	//set the global values for the clocks so they can be used in other functions.
	rcc_apb1_frequency = 48000000;
	rcc_ahb_frequency = 48000000;
}

void systick_setup(void){
	//set systick clocksource to main clock
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	//reset the register for systick to 0
	STK_CVR = 0;
	//reset _millis to 0
	_millis = 0;
	//setup how often the systick interrupt will occur
	//this is set to (processor speed/1000)-1
	systick_set_reload( (rcc_ahb_frequency / 1000) -1 );
	//enable the systick interrupt
	systick_interrupt_enable();
	//enable the systick counter
	systick_counter_enable();
}

uint64_t millis(void){
	return _millis;
}

void sys_tick_handler(void){
	//increase whenever the systick interrupt is called.
	_millis++;
}

//this will hang until delay_time has passed:
void delay(uint64_t delay_time){
	uint64_t timeout = millis() + delay_time;
	while(millis() < timeout);
}

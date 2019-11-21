/*
This uses the systick timer to keep track of how many milliseconds have ellapsed since the program began.
It also adds a blocking delay function.
*/

#include "timing.h"

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

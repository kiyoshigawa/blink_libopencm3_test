/*
This uses the systick timer to keep track of how many milliseconds have ellapsed since the program began.
It also adds a blocking delay function.
*/

#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>

//this will keep track of milliseconds since the program begins:
static volatile uint64_t _millis;

//this will start the systick and set it to increment every 1ms.
void systick_setup(void);

//this returns the number of ms since systick_setup() was called.
uint64_t millis(void);

//this is named per the vector table in cm3/vector.h
//it will be called by the systick interrupt
void sys_tick_handler(void);

//this will hang until delay_time has passed:
void delay(uint64_t delay_time);

#endif
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
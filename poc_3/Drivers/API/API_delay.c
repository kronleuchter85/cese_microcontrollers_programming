/*
 * API_delay.c
 *
 *  Created on: 19 Mar 2022
 *      Author: feder
 */

#include "API_delay.h"

void delayInit(delay_t *delay, tick_t duration) {
	delay->duration = duration;
}

bool_t delayRead(delay_t *delay) {
	if (delay->running) {
		if (HAL_GetTick() >= (delay->startTime + delay->duration)) {
			delay->running = false;
			return true;
		} else {
			return false;
		}
	} else {
		delay->startTime = HAL_GetTick();
		delay->running = true;
		return false;
	}
}

void delayWrite(delay_t *delay, tick_t duration) {
	delay->duration = duration;
}

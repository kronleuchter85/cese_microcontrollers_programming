/*
 * API_delay.h
 *
 *  Created on: 19 Mar 2022
 *      Author: feder
 */

#ifndef API_API_DELAY_H_
#define API_API_DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

// Qué biblioteca se debe incluir para que esto compile? Rpta: stdint.h
typedef uint32_t tick_t;

// Qué biblioteca se debe incluir para que esto compile? Rpta: stdbool.h
typedef bool bool_t;

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);

#endif /* API_API_DELAY_H_ */

/*
 * led_sequence_service.h
 *
 *  Created on: 6 Apr 2022
 *      Author: gonzalo
 */

#ifndef API_INC_LEDS_BLINKING_SERVICE_H_
#define API_INC_LEDS_BLINKING_SERVICE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h"

#include "API_delay.h"

//
//-------------------------------------- Type definitions  ---------------------------------------------------------------
//

typedef struct {
	Led_TypeDef led;
	delay_t delay;
	tick_t duration;
} LedDelay;

//
//-------------------------------------- Public members ------------------------------------------------------------------
//

void led_sequence_service_config();

void led_sequence_service_reset();

void led_sequence_service_execute();

#endif /* API_INC_LEDS_BLINKING_SERVICE_H_ */

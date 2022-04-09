/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "inc/Firmware_Init.h"
#include "main.h"
#include <stdlib.h>

#define EXECUTION_MODE_DEP = 1
#define EXECUTION_MODE_INDEP = 0
#define LEDS_AMOUNT  3;

const tick_t LED_TIME_SLOW = 500;
const tick_t LED_TIME_FAST = 100;

typedef struct {
	Led_TypeDef led;
	delay_t delay;
	tick_t duration;
} LedDelay;

static LedDelay* initializeLedDelay(Led_TypeDef led, tick_t duration);
static void initializeAllLeds(tick_t duration);

static bool leds_speed_fast = true;
static LedDelay *ledsDelays[3];

int main(void) {

	//
	// inicializamos los componentes del firmware que configuran
	// la HAL y setean el systick
	//
	HAL_Init();
	SystemClock_Config();

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	//
	// inicializamos los leds en FAST
	//
	initializeAllLeds(LED_TIME_FAST);

	uint8_t last_led_index = 2;
	int8_t current_led_index = 0;

	//
	// inicializamos el modulo de debounce
	//
	debounceFSM_init();

	while (true) {

		//
		// ejecutamos el modulo de debounce
		//
		debounceFSM_update();

		if (readKey()) {
			leds_speed_fast = !leds_speed_fast;

			tick_t speed = leds_speed_fast ? 100 : 500;

			//
			// re-inicializamos los leds con la velocidad actual
			//
			initializeAllLeds(speed);
		}

		BSP_LED_On(ledsDelays[current_led_index]->led);

		if (delayRead(&ledsDelays[current_led_index]->delay)) {

			BSP_LED_Off(ledsDelays[current_led_index]->led);

			current_led_index--;

			if (current_led_index < 0)
				current_led_index = last_led_index;
		}
	}
}

static void initializeAllLeds(tick_t speed) {
	ledsDelays[0] = initializeLedDelay(LED1, speed);
	ledsDelays[1] = initializeLedDelay(LED2, speed);
	ledsDelays[2] = initializeLedDelay(LED3, speed);
}

static LedDelay* initializeLedDelay(Led_TypeDef led, tick_t duration) {
	LedDelay *ledDelay = (LedDelay*) malloc(sizeof(LedDelay));
	ledDelay->led = led;
	ledDelay->duration = duration;
	delayInit(&ledDelay->delay, ledDelay->duration);

	BSP_LED_Init(ledDelay->led);
	BSP_LED_Off(ledDelay->led);

	return ledDelay;
}


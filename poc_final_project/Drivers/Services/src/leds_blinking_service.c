/*
 * led_sequence_service.c
 *
 *  Created on: 6 Apr 2022
 *      Author: gonzalo
 */
#include <leds_blinking_service.h>

//
//-------------------------------------- Contants ----------------------------------------------------------------------
//

const tick_t LED_TIME_SLOW = 500;
const tick_t LED_TIME_FAST = 100;

//
//-------------------------------------- Private Global Variables -------------------------------------------------------
//

static uint8_t last_led_index = 2;
static int8_t current_led_index = 0;

static LedDelay *ledsDelays[3];
static LedSequenceConfig *ledConfig;

//
//-------------------------------------- Prototypes of Private functions -------------------------------------------------
//

static LedDelay* initializeLedDelay(Led_TypeDef led, tick_t duration);

//
//-------------------------------------- Public members ------------------------------------------------------------------
//

/*
 * Realiza la configuracion de los modulos de leds y delays correspondientes
 */
void led_sequence_service_config(LedSequenceConfig *config) {

	ledConfig = config;

	ledsDelays[0] = initializeLedDelay(config->sequence[0], config->speed);
	ledsDelays[1] = initializeLedDelay(config->sequence[1], config->speed);
	ledsDelays[2] = initializeLedDelay(config->sequence[2], config->speed);

}

void led_sequence_service_update() {

}

/*
 * Ejecuta la visualizacion de la secuencia de leds activa a la velocidad seleccionada
 */
void led_sequence_service_execute() {

	BSP_LED_On(ledsDelays[current_led_index]->led);

	if (delayRead(&ledsDelays[current_led_index]->delay)) {

		BSP_LED_Off(ledsDelays[current_led_index]->led);

		current_led_index--;

		if (current_led_index < 0)
			current_led_index = last_led_index;
	}
}

//
//-------------------------------------- Private members -------------------------------------------------------------------
//

static LedDelay* initializeLedDelay(Led_TypeDef led, tick_t duration) {
	LedDelay *ledDelay = (LedDelay*) malloc(sizeof(LedDelay));
	ledDelay->led = led;
	ledDelay->duration = duration;
	delayInit(&ledDelay->delay, ledDelay->duration);

	BSP_LED_Init(ledDelay->led);
	BSP_LED_Off(ledDelay->led);

	return ledDelay;
}

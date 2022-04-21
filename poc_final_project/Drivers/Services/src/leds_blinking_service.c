/*
 * led_sequence_service.c
 *
 *  Created on: 6 Apr 2022
 *      Author: gonzalo
 */
#include <leds_blinking_service.h>

#include <repository.h>

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
void led_sequence_service_config() {

	uint8_t active_sequence_index = repository_active_sequence_index_get();
	uint8_t active_speed_index = repository_active_speed_index_get();

	LedSequence *sequence = repository_available_sequences_get(active_sequence_index);
	uint16_t speed = repository_available_speed_get(active_speed_index);

	ledsDelays[0] = initializeLedDelay(sequence->led_1, speed);
	ledsDelays[1] = initializeLedDelay(sequence->led_2, speed);
	ledsDelays[2] = initializeLedDelay(sequence->led_3, speed);

}

void led_sequence_service_reset() {
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);
}

void led_sequence_service_update() {
	BSP_LED_Off(ledsDelays[current_led_index]->led);
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

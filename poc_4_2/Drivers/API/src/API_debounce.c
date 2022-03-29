/*
 * MEF.c
 *
 *  Created on: 29 Mar 2022
 *      Author: feder
 */

#include <API_debounce.h>
#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h"

static bool_t key_pressed = false;

static debounceState_t currentState;
static delay_t delay;

bool_t readKey() {

	if (key_pressed) {
		key_pressed = false;
		return true;
	}
	return false;
}

void debounceFSM_init() {
	currentState = BUTTON_UP;
}

void debounceFSM_update() {

	uint32_t userButtonReading = BSP_PB_GetState(BUTTON_USER);

	switch (currentState) {

		case BUTTON_UP:
			//
			// inicialmente se va a encontrar en BUTTON_UP
			// ahi checkeamos el estado del boton , si esta presionado entonces
			// cambiamos a estado FALLING y ponemos en cero el contador de tiempo
			// para empezar a registrar la ventana de tiempo
			//
			if (userButtonReading) {

				currentState = BUTTON_FALLING;

				delayInit(&delay, 40);
			}
			break;

		case BUTTON_FALLING:

			//
			// cuando se encuentra en estado FALLING significa que previamente se detecto
			// que habia un flanco descendiente (por presion del boton o un error)
			// por lo cual checkeamos el paso del tiempo. Si el tiempo paso el intervalo
			// delta rebote y el estado del boton sigue siendo de humbral bajo entonces
			// el boton fue presionado, de lo contrario era solo un glitch y lo volvemos
			// a su estado normal UP
			//
			if (delayRead(&delay)) {
				if (userButtonReading) {
					currentState = BUTTON_DOWN;

					//
					// invocamos al evento de boton presionado ahora que efectivamente
					// sabemnos que esta presionado
					//
					buttonPressed();
				} else {
					currentState = BUTTON_UP;
				}
			}

			break;

		case BUTTON_DOWN:

			//
			// si el estado es presionado entonces checkeamos la lectura del boton. En caso de indicar q
			// no se ya encuentra presionado entonces iniciamos el cambio de estado para pasarlo a UP
			// por medio de cambiar el estado a RAISING e iniciar el contador a cero.
			//
			if (!userButtonReading) {
				currentState = BUTTON_RAISING;

				delayInit(&delay, 40);
			}
			break;

		case BUTTON_RAISING:

			//
			// si el estado es RAISING controlamos si paso el tiempo del delta debounce
			// en caso de haber pasado checkeamos la lectura del boton y cambiamos el estado
			// de la maquina de estados conforme a esto liberando o presionando.
			//
			if (delayRead(&delay)) {
				if (!userButtonReading) {
					currentState = BUTTON_UP;

					//
					// invocamos al evento de boton liberado ahora que efectivamente
					// sabemnos que esta presionado
					//
					buttonReleased();

				} else {
					currentState = BUTTON_DOWN;
				}
			}

			break;

	}

}

void buttonPressed() {

	key_pressed = true;

//	BSP_LED_Off(LED2);
//	BSP_LED_On(LED1);
}

void buttonReleased() {
//	BSP_LED_Off(LED1);
//	BSP_LED_On(LED2);
}


/*
 * API_delay.c
 *
 *  Created on: 19 Mar 2022
 *      Author: feder
 */

#include "API_delay.h"

/*
 * Implementacion de delayInit
 * Inicializa un delay object utilizando la funcion HAL_GetTick() y seteando el flag running en false
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *  duracion - valor de la duracion
 */
void delayInit(delay_t *delay, tick_t duration) {

	// validamos que duration tenga un valor permitido
	if (duration < 0) {
		return;
	}

	delay->duration = duration;
	delay->startTime = HAL_GetTick();
	delay->running = false;
}

/*
 * Implementacion de delayRead
 * Valida si el tiempo ha transcurrido con respecto al momento inicial guardado en el objeto delay, el tiempo actual y la duracion.
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *
 * @returns:
 *  true - el tiempo ya supero la duracion
 *  false - el tiempo aun no supero la duracion seteada
 */
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

/*
 * Implementacion de delayWrite
 * Permite cambiar el valor de duracion de un objeto delay existente
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *  duracion - valor de la duracion
 */
void delayWrite(delay_t *delay, tick_t duration) {
	delay->duration = duration;
}

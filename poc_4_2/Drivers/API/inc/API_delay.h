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

/*
 * Implementacion de delayInit
 * Inicializa un delay object utilizando la funcion HAL_GetTick() y seteando el flag running en false
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *  duracion - valor de la duracion
 */
void delayInit(delay_t *delay, tick_t duration);

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
bool_t delayRead(delay_t *delay);

/*
 * Implementacion de delayWrite
 * Permite cambiar el valor de duracion de un objeto delay existente
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *  duracion - valor de la duracion
 */
void delayWrite(delay_t *delay, tick_t duration);

#endif /* API_API_DELAY_H_ */

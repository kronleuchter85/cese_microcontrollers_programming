/*
 * MEF.c
 *
 *  Created on: 29 Mar 2022
 *      Author: feder
 */

typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING,
} debounceState_t;

/*
 * Inicializa el modulo de debouncing
 */
void debounceFSM_init();

/*
 * Realiza el checkeo periodico de la maquina de estados gestionada
 * por el modulo de debouncing que invoca las funciones
 * 'buttonPressed' y 'buttonReleased' cuando el boton de la placa
 * se presiona o libera.
 */
void debounceFSM_update();

/*
 * Funcion de implementacion a nivel de consumidor del modulo.
 * Implementa la logica de la accion a realizar cuando se
 * presiona el boton de usaurio
 */
void buttonPressed();
/*
 * Funcion de implementacion a nivel de consumidor del modulo.
 * Implementa la logica de la accion a realizar cuando se
 * libera el boton de usaurio
 */
void buttonReleased();


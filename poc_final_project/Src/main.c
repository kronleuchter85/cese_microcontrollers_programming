/*
 * main.c
 *
 *  Created on: 6 Apr 2022
 *      Author: gonzalo
 */

#include <uart_communication_service.h>
#include <leds_blinking_service.h>
#include <local_operations_service.h>
#include <API_debounce.h>
#include <API_uart.h>

#include <repository.h>

#include "Firmware_Init.h"
#include "main.h"

//
// Funcion principal - Entrada del programa
//

int main(void) {

	//
	// inicializamos las funciones de la plataforma definidas en un archivo
	// que implementa el prototipo Firmware_Init.h
	//
	platform_initialze();

	//
	// inicializamos el repository
	//
	repository_initialize();

	//
	// inicializamos los servicios
	//
	local_operations_service_config();
	uart_communication_service_config();
	led_sequence_service_config();

	//
	// super loop
	//
	while (1) {

		//
		// Ejecutamos las acciones del usuario Activador desde la terminal serie
		//
		uart_communication_service_execute();

		//
		// Ejecutamos las acciones del usuario Visualizador desde la placa nucleo
		//
		local_operations_service_execute();

		//
		// obtenemos el estado actual de las acciones del usuario para poder si
		// existen actualizaciones
		//
		UartFlowState state = uart_communication_service_current_state_get();

		//
		// En caso de haberse activado una nueva secuencia o velocidad
		// pausamos la visualizacion del blinking y reconfiguramos para actualizar
		// la secuencia y velocidad que deben utilizarse
		//
		if (state == SEQUENCE_ACTIVATED || state == SPEED_ACTIVATED) {
			local_operations_service_show_sequence_set(false);

			led_sequence_service_config();
		}

		//
		// si por accion del usuario Visualizador hay que comenzar la visualizacion
		// procedemos con la ejecucion, en caso contrario se la pausa.
		//
		if (local_operations_service_show_sequence_get()) {
			led_sequence_service_execute();
		} else {
			led_sequence_service_reset();
		}
		
	}
}


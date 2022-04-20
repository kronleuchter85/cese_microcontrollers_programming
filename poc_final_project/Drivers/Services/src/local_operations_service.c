/*
 * local_operations_service.c
 *
 *  Created on: 16 Apr 2022
 *      Author: gonzalo
 */

#include <API_debounce.h>
#include <local_operations_service.h>

static bool show_sequence;

bool local_operations_service_is_show_sequence() {
	return show_sequence;
}

void local_operations_service_config() {

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	//
	// inicializamos el modulo de debounce
	//
	debounceFSM_init();

}

void local_operations_service_execute() {

	//
	// ejecutamos el modulo de debounce
	//
	debounceFSM_update();

	if (readKey()) {

		show_sequence = !show_sequence;
	}
	
}

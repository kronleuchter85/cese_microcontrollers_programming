#include <uart_communication_service.h>
#include <leds_blinking_service.h>
#include <local_operations_service.h>

#include <API_debounce.h>
#include "Firmware_Init.h"
#include "main.h"
#include "API_uart.h"

//
// Funcion principal - Entrada del programa
//

int main(void) {

	HAL_Init();
	SystemClock_Config();
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	local_operations_service_config();

//	uart_communication_service_config();

	LedSequenceConfig config;
	config.sequence[0] = 0;
	config.sequence[1] = 0;
	config.sequence[2] = 2;
	config.speed = (uint8_t) 2000;
	led_sequence_service_config(&config);

	//
	// inicializamos el modulo de debounce
	//
	debounceFSM_init();

	bool show = false;

	while (1) {

		//
		// ejecutamos el modulo de debounce
		//
		debounceFSM_update();

		if (readKey()) {

			show = !show;
		}

		if (show) {
			led_sequence_service_execute();
		}

		local_operations_service_execute();
//		uart_communication_service_execute();

	}
}


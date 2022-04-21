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

	HAL_Init();
	SystemClock_Config();

	repository_initialize();

	local_operations_service_config();
	uart_communication_service_config();
	led_sequence_service_config();

	while (1) {

		uart_communication_service_execute();

		local_operations_service_execute();

		UartFlowState state = uart_communication_service_current_state_get();

		if (state == SEQUENCE_ACTIVATED || state == SPEED_ACTIVATED) {
			local_operations_service_show_sequence_set(false);

			led_sequence_service_config();

		}

		if (local_operations_service_show_sequence_get()) {
			led_sequence_service_execute();
		} else {
			led_sequence_service_reset();
		}
		
	}
}


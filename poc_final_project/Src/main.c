#include <uart_communication_service.h>
#include <leds_blinking_service.h>
#include <local_operations_service.h>

#include "Firmware_Init.h"
#include "main.h"
#include "API_uart.h"

//
// Funcion principal - Entrada del programa
//

int main(void) {
	HAL_Init();

	SystemClock_Config();

	local_operations_service_config();

	uart_communication_service_config();

	LedSequenceConfig config;
	config.sequence[0] = 0;
	config.sequence[1] = 0;
	config.sequence[2] = 2;

	config.speed = (uint8_t) 2000;

	led_sequence_service_config(&config);

	while (1) {

		local_operations_service_execute();
		uart_communication_service_execute();
		led_sequence_service_execute();

	}
}


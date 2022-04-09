#include <uart_communication_service.h>
#include <leds_blinking_service.h>
#include "Firmware_Init.h"
#include "main.h"
#include "API_uart.h"

//
// Funcion principal - Entrada del programa
//

int main(void) {
	HAL_Init();

	SystemClock_Config();

//	uart_communication_service_config();

	LedSequenceConfig config;
	config.sequence[0] = 0;
	config.sequence[1] = 1;
	config.sequence[2] = 2;

	config.speed = (uint8_t) 1000;

	led_sequence_service_config(&config);

	while (1) {

//		uart_communication_service_execute();
		led_sequence_service_execute();

	}
}


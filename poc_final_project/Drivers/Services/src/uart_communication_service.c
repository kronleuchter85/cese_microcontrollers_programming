/*
 * serial_service.c
 *
 *  Created on: 6 Apr 2022
 *      Author: gonzalo
 */

#include <uart_communication_service.h>
#include <leds_blinking_service.h>
#include "API_uart.h"

//
//-------------------------------------- Contants ----------------------------------------------------------------------
//

const char *standardSeparator = "---------------------------------------------------------";
const char *standardCR = "\n\r";
const char *welcomeMessage = "Bienvenido!";
const char *optionsMessage = "Los Comandos validos son:\n\r - a \n\r - b";
const char *inputRequestMessage = "Por favor ingrese un comando:";

//
//-------------------------------------- MEF ------------------------------------------------------------------
//

typedef enum {
	WAITING_FOR_USER_ACTIONS,
	WAITING_FOR_SEQUENCE_LED_1,
	WAITING_FOR_SEQUENCE_LED_2,
	WAITING_FOR_SEQUENCE_LED_3,
	RECORD_SEQUENCE,

} UART_Service_Config_MEF;

uint8_t uart_command[2];

UART_Service_Config_MEF state = WAITING_FOR_USER_ACTIONS;

uint8_t led_sequence[3];

void process_mef() {

	switch (state) {

		case WAITING_FOR_USER_ACTIONS:

			strncpy(uart_command, "", strlen(uart_command));
			uartReceiveStringSize(uart_command, 1);

			if (strlen(uart_command) > 0)
				uartsendString((uint8_t*) uart_command);

			if (!strcmp((const char*) uart_command, "s") || !strcmp((const char*) uart_command, "S")) {

				//
				// si el usuario selecciona S nos vamos al primer estado de ingreso
				// de secuencia de LEDS
				//
				state = WAITING_FOR_SEQUENCE_LED_1;
			}

			break;

		case WAITING_FOR_SEQUENCE_LED_1:

			strncpy(uart_command, "", strlen(uart_command));
			uartReceiveStringSize(uart_command, 1);

			if (strlen(uart_command) > 0)
				uartsendString((uint8_t*) uart_command);

			if (!strcmp((const char*) uart_command, "0")
					|| !strcmp((const char*) uart_command, "1")
					|| !strcmp((const char*) uart_command, "2")
					|| !strcmp((const char*) uart_command, "3")
					|| !strcmp((const char*) uart_command, "4")
					|| !strcmp((const char*) uart_command, "5")
					|| !strcmp((const char*) uart_command, "6")
					|| !strcmp((const char*) uart_command, "7")
					|| !strcmp((const char*) uart_command, "8")
					|| !strcmp((const char*) uart_command, "9")) {

				//
				// si el usuario ingresa un valor numerico guardamos la seleccion del primer led de la secuencia
				// y nos vamos al segundo estado de ingreso de secuencia de LEDS
				//

				led_sequence[0] = atoi(uart_command);

				state = WAITING_FOR_SEQUENCE_LED_2;
			}

			break;

		case WAITING_FOR_SEQUENCE_LED_2:

			strncpy(uart_command, "", strlen(uart_command));
			uartReceiveStringSize(uart_command, 1);

			if (strlen(uart_command) > 0)
				uartsendString((uint8_t*) uart_command);

			if (!strcmp((const char*) uart_command, "0")
					|| !strcmp((const char*) uart_command, "1")
					|| !strcmp((const char*) uart_command, "2")
					|| !strcmp((const char*) uart_command, "3")
					|| !strcmp((const char*) uart_command, "4")
					|| !strcmp((const char*) uart_command, "5")
					|| !strcmp((const char*) uart_command, "6")
					|| !strcmp((const char*) uart_command, "7")
					|| !strcmp((const char*) uart_command, "8")
					|| !strcmp((const char*) uart_command, "9")) {

				//
				// si el usuario selecciona S nos vamos al segundo estado de ingreso
				// de secuencia de LEDS
				//

				led_sequence[1] = atoi(uart_command);

				state = WAITING_FOR_SEQUENCE_LED_3;
			}
			break;

		case WAITING_FOR_SEQUENCE_LED_3:

			strncpy(uart_command, "", strlen(uart_command));
			uartReceiveStringSize(uart_command, 1);

			if (strlen(uart_command) > 0)
				uartsendString((uint8_t*) uart_command);

			if (!strcmp((const char*) uart_command, "0")
					|| !strcmp((const char*) uart_command, "1")
					|| !strcmp((const char*) uart_command, "2")
					|| !strcmp((const char*) uart_command, "3")
					|| !strcmp((const char*) uart_command, "4")
					|| !strcmp((const char*) uart_command, "5")
					|| !strcmp((const char*) uart_command, "6")
					|| !strcmp((const char*) uart_command, "7")
					|| !strcmp((const char*) uart_command, "8")
					|| !strcmp((const char*) uart_command, "9")) {

				//
				// si el usuario selecciona S nos vamos al segundo estado de ingreso
				// de secuencia de LEDS
				//

				led_sequence[2] = atoi(uart_command);

				state = WAITING_FOR_USER_ACTIONS;
			}
			break;
		case RECORD_SEQUENCE:

			break;

	}

}

//
//-------------------------------------- Public members ------------------------------------------------------------------
//

void uart_communication_service_config() {

	//
	// Configuracion de la UART
	//
	uartinit();

	//
	// Mensaje de bienvenida
	//
	int i;
	for (i = 0; i < 10; i++)
		uartsendString((uint8_t*) standardSeparator);

	uartsendString((uint8_t*) standardCR);
	uartsendString((uint8_t*) welcomeMessage);

}

void uart_communication_service_execute() {
	process_mef();
}

void process_poc() {

	uint8_t serial_input[128];
	uint8_t command[2];

	memset(serial_input, '\0', sizeof(serial_input));
	memset(command, '\0', sizeof(command));

	//
	// Imprimiendo las instrucciones estandar
	//

	int i;
	for (i = 0; i < 7; i++)
		uartsendString((uint8_t*) standardSeparator);

	uartsendString((uint8_t*) standardCR);
	uartsendString((uint8_t*) optionsMessage);
	uartsendString((uint8_t*) standardCR);
	uartsendString((uint8_t*) inputRequestMessage);

	//
	// Recibimos la respuesta
	//
	uartReceiveStringSize(command, 1);
	while (!strcmp((const char*) command, "")) {
		uartReceiveStringSize(command, 1);
	}

	uartsendString((uint8_t*) command);
	uartsendString((uint8_t*) standardCR);
	uartsendString((uint8_t*) standardCR);

	char *responseMessage;

	if (!strcmp((const char*) command, "a")) {
		responseMessage = "El commando ingresado fue A";
	} else if (!strcmp((const char*) command, "b")) {
		responseMessage = "El commando ingresado fue B";
	} else {
		responseMessage = "El comando ingresado es invalido";
	}
	
	uartsendString((uint8_t*) responseMessage);
	uartsendString((uint8_t*) standardCR);
}

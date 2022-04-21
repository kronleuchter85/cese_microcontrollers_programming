/*
 * serial_service.c
 *
 *  Created on: 6 Apr 2022
 *      Author: gonzalo
 */

#include <uart_communication_service.h>
#include <leds_blinking_service.h>
#include <API_uart.h>
#include <repository.h>

//
//-------------------------------------- Contants ----------------------------------------------------------------------
//

const char *standardSeparator = "---------------------------------------------------------";
const char *welcomeMessage = "Bienvenido!";

//
//-------------------------------------- Private members ------------------------------------------------------------------
//

static LedSequence *new_sequence = NULL;

static UartFlowState state = WAITING_FOR_USER_ACTIONS;

//
//-------------------------------------- Public members ------------------------------------------------------------------
//

UartFlowState uart_communication_service_current_state_get() {
	return state;
}

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

	uartsendString("\n\r");
	uartsendString((uint8_t*) welcomeMessage);

	state = WELCOME;
}

static void uart_communication_service_print_options() {

	uartsendString("\n\r");
	uartsendString("Ingrese una Opcion:");
	uartsendString("\n\r");
	uartsendString(" [L] Listar Secuencias y Velocidades Disponibles ");
	uartsendString("\n\r");
	uartsendString(" [S] Ingresar una Nueva Secuencia ");
	uartsendString("\n\r");
	uartsendString(" [V] Ingresar una Nueva Velocidad ");
	uartsendString("\n\r");
	uartsendString(" [Z] Activar una Secuencia ");
	uartsendString("\n\r");
	uartsendString(" [B] Activar una Velocidad ");
	uartsendString("\n\r");

}

void uart_communication_service_execute() {

	char message[30];

	uint8_t uart_command[2];
	strncpy(uart_command, "", strlen(uart_command));

	switch (state) {

		case WELCOME:

			uartsendString("\n\r");
			uart_communication_service_print_options();

			state = WAITING_FOR_USER_ACTIONS;

			break;

		case WAITING_FOR_USER_ACTIONS:

			uartReceiveStringSize(uart_command, 1);

			if (strlen(uart_command) > 0) {
				uartsendString((uint8_t*) uart_command);
			}

			///
			/// Se selecciona ingresar una nueva secuencia
			///
			if (!strcmp((const char*) uart_command, "s") || !strcmp((const char*) uart_command, "S")) {

				//
				// si el usuario selecciona S nos vamos al primer estado de ingreso
				// de secuencia de LEDS
				//
				state = WAITING_FOR_SEQUENCE_LED_1;

				uartsendString("\n\r");
				uartsendString("Ingrese una secuencia de tres digitos:");

				new_sequence = malloc(sizeof(LedSequence));
			}

			///
			/// Se selecciona listar las secuencias y velocidades disponibles
			///
			else if (!strcmp((const char*) uart_command, "l") || !strcmp((const char*) uart_command, "L")) {

				uartsendString("\n\r");
				uartsendString("Secuencias disponibles:");
				uartsendString("\n\r");

				int i;
				for (i = 0; i < repository_available_sequences_count(); i++) {

					LedSequence *seq = repository_available_sequences_get(i);

					strncpy(message, "", strlen(message));

					//
					// si el elemento actual es de la secuencia activa
					//
					if (repository_active_sequence_index_get() == i) {
						sprintf(message, " %i: [%i,%i,%i] (Active) \n\r", i, seq->led_1, seq->led_2, seq->led_3);
					}

					//
					// caso contrario
					//
					else {
						sprintf(message, " %i: [%i,%i,%i] \n\r", i, seq->led_1, seq->led_2, seq->led_3);

					}

					uartsendString(message);
				}

				uartsendString("\n\r");
				uartsendString("Velocidades disponibles:");
				uartsendString("\n\r");

				for (i = 0; i < repository_available_speed_count(); i++) {

					uint16_t speed = repository_available_speed_get(i);

					strncpy(message, "", strlen(message));

					//
					// si el elemento actual es de la velocidad activa
					//
					if (repository_active_speed_index_get() == i) {

						sprintf(message, " %i: '%i' (Active) \n\r", i, speed);
					}

					//
					// caso contrario
					//
					else {

						sprintf(message, " %i: '%i' \n\r", i, speed);
					}

					uartsendString(message);
				}

			}

			///
			/// Se selecciona ingresar una nueva velocidad
			///

			else if (!strcmp((const char*) uart_command, "v") || !strcmp((const char*) uart_command, "V")) {

			}

			///
			/// Se selecciona activar una secuencia
			///

			else if (!strcmp((const char*) uart_command, "z") || !strcmp((const char*) uart_command, "Z")) {

				uartsendString("\n\r");
				uartsendString("Ingrese el numero de secuencia a activar: ");

				state = WAITING_FOR_SEQUENCE_ACTIVATION;

			}

			///
			/// Se selecciona activar una velocidad
			///

			else if (!strcmp((const char*) uart_command, "b") || !strcmp((const char*) uart_command, "B")) {

			} else if (strlen(uart_command) > 0) {
				uartsendString("\n\r");
				uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
				uartsendString("\n\r");
				uartsendString("Intente de nuevo: ");
			}

			break;

		case WAITING_FOR_SEQUENCE_LED_1:

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
				new_sequence->led_1 = atoi(uart_command);

				state = WAITING_FOR_SEQUENCE_LED_2;

			} else if (strlen(uart_command) > 0) {
				uartsendString("\n\r");
				uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
				uartsendString("\n\r");
				uartsendString("Intente de nuevo: ");
			}

			break;

		case WAITING_FOR_SEQUENCE_LED_2:

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
				new_sequence->led_2 = atoi(uart_command);

				state = WAITING_FOR_SEQUENCE_LED_3;

			} else if (strlen(uart_command) > 0) {
				uartsendString("\n\r");
				uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
				uartsendString("\n\r");
				uartsendString("Intente de nuevo: ");
			}
			break;

		case WAITING_FOR_SEQUENCE_LED_3:

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
				new_sequence->led_3 = atoi(uart_command);

				state = RECORD_SEQUENCE;

			} else if (strlen(uart_command) > 0) {
				uartsendString("\n\r");
				uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
				uartsendString("\n\r");
				uartsendString("Intente de nuevo: ");

			}
			break;

		case RECORD_SEQUENCE:

			//
			// agregamos la secuencia de leds
			//
			repository_available_sequences_add(new_sequence);

			//
			// imprimimos la nueva secuencia creada
			//
			strncpy(message, "", strlen(message));
			sprintf(message, "Secuencia Agregada: [%i,%i,%i] \n\r", new_sequence->led_1, new_sequence->led_2, new_sequence->led_3);

			uartsendString("\n\r");
			uartsendString(message);

			new_sequence = NULL;

			state = WELCOME;

			break;

		case WAITING_FOR_SEQUENCE_ACTIVATION:

			uartReceiveStringSize(uart_command, 1);

			if (strlen(uart_command) > 0) {
				uartsendString((uint8_t*) uart_command);
			}

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

				uint8_t selected_sequence_index = atoi(uart_command);

				repository_active_sequence_index_set(selected_sequence_index);

				state = SEQUENCE_ACTIVATED;

			} else if (strlen(uart_command) > 0) {
				uartsendString("\n\r");
				uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
				uartsendString("\n\r");
				uartsendString("Intente de nuevo: ");
			}

			break;

		case SEQUENCE_ACTIVATED:

			///
			/// agrego un statement vacio porque a C no le gusta que despues de una etiqueta
			/// se empiece con una declaracion de variables x_X
			///
			;

			uint8_t index = repository_active_sequence_index_get();
			LedSequence *sequence = repository_available_sequences_get(index);

			//
			// imprimimos la nueva secuencia creada
			//
			strncpy(message, "", strlen(message));
			sprintf(message, "Secuencia Activada:  %i [%i,%i,%i] \n\r", index, sequence->led_1, sequence->led_2, sequence->led_3);
			
			uartsendString("\n\r");
			uartsendString(message);
			
			state = WELCOME;
			
			break;
			
	}
	
}


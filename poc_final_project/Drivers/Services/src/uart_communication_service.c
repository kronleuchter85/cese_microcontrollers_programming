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
//-------------------------------------- Private Variables ------------------------------------------------------------------
//

static LedSequence *new_sequence = NULL;
static UartFlowState state = WAITING_FOR_USER_ACTIONS;

//-------------------------------------- Functions Prototypes ------------------------------------------------------------------

static void uart_flow_process_step_welcome();
static void uart_flow_process_step_waiting_for_user_actions();
static void uart_flow_process_step_sequence_activated();
static void uart_flow_process_step_waiting_for_sequence_activation();
static void uart_flow_process_step_record_sequence();
static void uart_flow_process_step_waiting_for_sequence_led_3();
static void uart_flow_process_step_waiting_for_sequence_led_2();
static void uart_flow_process_step_waiting_for_sequence_led_1();
static void uart_flow_process_utils_print_options();
static void uart_flow_process_step_waiting_for_speed();
static void uart_flow_process_step_recorded_speed();
static void uart_flow_process_step_waiting_for_speed_activation();
static void uart_flow_process_step_speed_activated();

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

uint8_t speed_digits[4];
uint8_t last_speed_digit = 0;

void uart_communication_service_execute() {

	switch (state) {

		case WELCOME:

			uart_flow_process_step_welcome();

			break;

		case WAITING_FOR_USER_ACTIONS:

			uart_flow_process_step_waiting_for_user_actions();

			break;

		case WAITING_FOR_SEQUENCE_LED_1:

			uart_flow_process_step_waiting_for_sequence_led_1();

			break;

		case WAITING_FOR_SEQUENCE_LED_2:
			uart_flow_process_step_waiting_for_sequence_led_2();

			break;

		case WAITING_FOR_SEQUENCE_LED_3:

			uart_flow_process_step_waiting_for_sequence_led_3();

			break;

		case RECORD_SEQUENCE:

			uart_flow_process_step_record_sequence();

			break;

		case WAITING_FOR_SEQUENCE_ACTIVATION:

			uart_flow_process_step_waiting_for_sequence_activation();

			break;

		case SEQUENCE_ACTIVATED:

			uart_flow_process_step_sequence_activated();

			break;

		case WAITING_FOR_SPEED:

			uart_flow_process_step_waiting_for_speed();

			break;

		case RECORDED_SPEED:

			uart_flow_process_step_recorded_speed();

			break;

		case WAITING_FOR_SPEED_ACTIVATION:

			uart_flow_process_step_waiting_for_speed_activation();

			break;

		case SPEED_ACTIVATED:

			uart_flow_process_step_speed_activated();

			break;

	}
}

///
/// ------------------------------------ Private Functions ----------------------------------------
///

static void uart_flow_process_step_speed_activated() {

	char message[30];

	///
	/// agrego un statement vacio porque a C no le gusta que despues de una etiqueta
	/// se empiece con una declaracion de variables x_X
	///
	;

	uint8_t index = repository_active_speed_index_get();
	uint16_t speed = repository_available_speed_get(index);

	//
	// imprimimos la nueva secuencia creada
	//
	strncpy(message, "", strlen(message));
	sprintf(message, "Velocidad Activada:  %i: %i \n\r", index, speed);

	uartsendString("\n\r");
	uartsendString(message);

	state = WELCOME;
}

static void uart_flow_process_step_waiting_for_speed_activation() {

	uint8_t uart_command[2];
	strncpy(uart_command, "", strlen(uart_command));

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

		uint8_t selected_speed_index = atoi(uart_command);

		repository_active_speed_index_set(selected_speed_index);

		state = SPEED_ACTIVATED;

	} else if (strlen(uart_command) > 0) {
		uartsendString("\n\r");
		uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
		uartsendString("\n\r");
		uartsendString("Intente de nuevo: ");
	}
}

static void uart_flow_process_step_waiting_for_speed() {

	uint8_t uart_command[2];
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

		if (last_speed_digit < 4) {
			speed_digits[last_speed_digit] = uart_command[0];
			last_speed_digit++;
		}

	}

	else if (!strcmp(uart_command, "\r\n") || !strcmp(uart_command, "\r")) {

		state = RECORDED_SPEED;
	}

	else if (strlen(uart_command) > 0) {
		uartsendString("\n\r");
		uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
		uartsendString("\n\r");
		uartsendString("Intente de nuevo: ");
	}

}

static void uart_flow_process_step_recorded_speed() {
	char message[30];

	uint16_t new_speed = atoi(speed_digits);

	//
	// agregamos la secuencia de leds
	//
	repository_available_speed_add(new_speed);

	//
	// imprimimos la nueva secuencia creada
	//
	strncpy(message, "", strlen(message));
	sprintf(message, "Velocidad Agregada: %i \n\r", new_speed);

	uartsendString("\n\r");
	uartsendString(message);

	strncpy(speed_digits, "", strlen(speed_digits));

	//
	// reseteamos el indice para agregar velocidades
	//
	last_speed_digit = 0;

	state = WELCOME;
}

static void uart_flow_process_step_welcome() {

	char message[30];

	uint8_t uart_command[2];
	strncpy(uart_command, "", strlen(uart_command));
	uartsendString("\n\r");
	uart_flow_process_utils_print_options();

	state = WAITING_FOR_USER_ACTIONS;
}

static void uart_flow_process_step_waiting_for_user_actions() {

	char message[30];

	uint8_t uart_command[2];
	strncpy(uart_command, "", strlen(uart_command));

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
				sprintf(message, " %i: [%i,%i,%i]   (active) \n\r", i, seq->led_1, seq->led_2, seq->led_3);
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

				sprintf(message, " %i: %i ms   (active) \n\r", i, speed);
			}

			//
			// caso contrario
			//
			else {

				sprintf(message, " %i: %i ms \n\r", i, speed);
			}

			uartsendString(message);
		}

	}

	///
	/// Se selecciona ingresar una nueva velocidad
	///

	else if (!strcmp((const char*) uart_command, "v") || !strcmp((const char*) uart_command, "V")) {
		//
		// si el usuario selecciona v nos vamos al estado de ingreso
		// de Velocidad de LEDS
		//
		state = WAITING_FOR_SPEED;

		uartsendString("\n\r");
		uartsendString("Ingrese una Velocidad de hasta 4 digitos:");

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

		uartsendString("\n\r");
		uartsendString("Ingrese el numero de velocidad a activar: ");

		state = WAITING_FOR_SPEED_ACTIVATION;

	}

	else if (strlen(uart_command) > 0) {
		uartsendString("\n\r");
		uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
		uartsendString("\n\r");
		uartsendString("Intente de nuevo: ");
	}
}

static void uart_flow_process_step_sequence_activated() {

	char message[30];

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
}

static void uart_flow_process_step_waiting_for_sequence_activation() {

	uint8_t uart_command[2];
	strncpy(uart_command, "", strlen(uart_command));

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
}

static void uart_flow_process_step_record_sequence() {
	char message[30];

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
}

static void uart_flow_process_step_waiting_for_sequence_led_3() {

	uint8_t uart_command[2];
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
		new_sequence->led_3 = atoi(uart_command);

		state = RECORD_SEQUENCE;

	} else if (strlen(uart_command) > 0) {
		uartsendString("\n\r");
		uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
		uartsendString("\n\r");
		uartsendString("Intente de nuevo: ");

	}
}

static void uart_flow_process_step_waiting_for_sequence_led_2() {

	uint8_t uart_command[2];
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
		new_sequence->led_2 = atoi(uart_command);

		state = WAITING_FOR_SEQUENCE_LED_3;

	} else if (strlen(uart_command) > 0) {
		uartsendString("\n\r");
		uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
		uartsendString("\n\r");
		uartsendString("Intente de nuevo: ");
	}

}

static void uart_flow_process_step_waiting_for_sequence_led_1() {

	uint8_t uart_command[2];
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
		new_sequence->led_1 = atoi(uart_command);

		state = WAITING_FOR_SEQUENCE_LED_2;

	} else if (strlen(uart_command) > 0) {
		uartsendString("\n\r");
		uartsendString("La opcion ingresada no se encuentra dentro de los valores permitidos ");
		uartsendString("\n\r");
		uartsendString("Intente de nuevo: ");
	}

}

static void uart_flow_process_utils_print_options() {

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


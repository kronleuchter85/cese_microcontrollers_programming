#include "Firmware_Init.h"
#include "main.h"
#include "API_uart.h"

//
// Declaracion de constantes para los mensajes estandares del programa
//

const char *standardSeparator = "---------------------------------------------------------";
const char *standardCR = "\n\r";
const char *welcomeMessage = "Bienvenido!";
const char *optionsMessage = "Los Comandos validos son:\n\r - a \n\r - b";
const char *inputRequestMessage = "Por favor ingrese un comando:";

//
// Funcion principal - Entrada del programa
//

int main(void) {
	HAL_Init();

	SystemClock_Config();

	BSP_LED_Init(LED2);

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

	uint8_t serial_input[128];
	uint8_t command[2];

	while (1) {

		BSP_LED_Toggle(LED2);

		memset(serial_input, '\0', sizeof(serial_input));

		memset(command, '\0', sizeof(command));

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

		BSP_LED_Toggle(LED2);

		HAL_Delay(1000);
	}
}


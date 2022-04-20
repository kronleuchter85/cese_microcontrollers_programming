/*
 * API_uart.c
 *
 *  Created on: 2 Apr 2022
 *      Author: feder
 */

#include "API_uart.h"

/**
 * Instancia de la UART configurada de acuerdo a la parametria indicada en la funcion uartinit
 */
UART_HandleTypeDef UartHandle;

/**
 * Inicializa la configuracion de la UART indicando:
 * - paridad
 * - bits de parada
 * - bits de datos
 * - COM usado
 * - baud rate
 *
 * @return[bool_t]: Retorna verdadero o falso indicando si hubo o no un error
 */
bool_t uartinit() {

	UartHandle.Instance = USART3;
	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) == HAL_ERROR) {
		printf("El estado de HAL_StatusTypeDef resulto con error. Hay errores en la configuracion de la comunicacion serie de la UART");

		return false;
	}

	return true;
}

/**
 * Envia un mensaje por la UART configurada
 *
 * @param[uint8_t*]: mensaje a enviar por la UART
 * @param[uint16_t*]: tamaño mensaje a enviar por la UART
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	HAL_StatusTypeDef ret = HAL_UART_Transmit(&UartHandle, pstring, size, 1000);

	if (ret == HAL_ERROR) {
		printf("El estado de HAL_StatusTypeDef resulto con error. Hay errores en la configuracion de la comunicacion serie de la UART");
	}
}

/**
 * Envia un mensaje por la UART configurada
 *
 * @param[uint8_t*]: mensaje a enviar por la UART
 */
void uartsendString(uint8_t *pstring) {
	uint16_t size = (uint16_t) strlen((const char*) pstring);
	HAL_StatusTypeDef ret = HAL_UART_Transmit(&UartHandle, pstring, size, 1000);

	if (ret == HAL_ERROR) {
		printf("El estado de HAL_StatusTypeDef resulto con error. Hay errores en la configuracion de la comunicacion serie de la UART");
	}
}

/**
 * Recibe un mensaje por la UART configurada
 *
 * @param[uint8_t*]: mensaje a recibir por la UART
 * @param[uint16_t*]: tamaño mensaje a recibir por la UART
 */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	HAL_StatusTypeDef ret = HAL_UART_Receive(&UartHandle, pstring, size, 1);

	if (ret == HAL_ERROR) {
		printf("El estado de HAL_StatusTypeDef resulto con error. Hay errores en la configuracion de la comunicacion serie de la UART");
	}
}

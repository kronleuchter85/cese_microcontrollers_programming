/*
 * API_uart.h
 *
 *  Created on: 2 Apr 2022
 *      Author: feder
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

typedef bool bool_t;

/**
 * Inicializa la configuracion de la UART indicando:
 * - paridad
 * - bits de parada
 * - bits de datos
 * - COM usado
 * - baud rate
 */
bool_t uartinit();

/**
 * Envia un mensaje por la UART configurada
 *
 * @param[uint8_t*]: mensaje a enviar por la UART
 */
void uartsendString(uint8_t *pstring);

/**
 * Envia un mensaje por la UART configurada
 *
 * @param[uint8_t*]: mensaje a enviar por la UART
 * @param[uint16_t*]: tamaño mensaje a enviar por la UART
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size);

/**
 * Recibe un mensaje por la UART configurada
 *
 * @param[uint8_t*]: mensaje a recibir por la UART
 * @param[uint16_t*]: tamaño mensaje a recibir por la UART
 */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */

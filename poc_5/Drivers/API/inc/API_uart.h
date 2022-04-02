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

typedef bool bool_t;

bool_t uartinit();
void uartsendString(uint8_t *pstring);
void uartSendStringSize(uint8_t *pstring, uint16_t size);
void uartReceiveStringSize(uint8_t *pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */

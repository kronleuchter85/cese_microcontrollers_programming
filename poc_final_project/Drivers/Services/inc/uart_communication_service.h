/*
 * serial_service.h
 *
 *  Created on: 6 Apr 2022
 *      Author: gonzalo
 */

#ifndef API_INC_UART_COMMUNICATION_SERVICE_H_
#define API_INC_UART_COMMUNICATION_SERVICE_H_

typedef enum {
	WELCOME,
	WAITING_FOR_USER_ACTIONS,
	WAITING_FOR_SEQUENCE_LED_1,
	WAITING_FOR_SEQUENCE_LED_2,
	WAITING_FOR_SEQUENCE_LED_3,
	RECORD_SEQUENCE,

	WAITING_FOR_SEQUENCE_ACTIVATION,
	SEQUENCE_ACTIVATED,

} UartFlowState;

UartFlowState uart_communication_service_current_state_get();

void uart_communication_service_config();

void uart_communication_service_execute();

#endif /* API_INC_UART_COMMUNICATION_SERVICE_H_ */

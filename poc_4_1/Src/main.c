/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "Firmware_Init.h"
#include <API_MEF.h>
#include <stdint.h>
#include <stdbool.h>
#include "API_delay.h"
#include "main.h"

void buttonPressed() {
	BSP_LED_Off(LED2);
	BSP_LED_On(LED1);
}

void buttonReleased() {
	BSP_LED_Off(LED1);
	BSP_LED_On(LED2);
}

int main(void) {
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);

	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);

	debounceFSM_init();

	while (true) {
		debounceFSM_update();
	}

}


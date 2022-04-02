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
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

int main(void) {
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	while (true) {
		;
	}

}


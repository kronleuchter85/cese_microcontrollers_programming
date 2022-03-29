/*
 * Firmware_Init.h
 *
 *  Created on: 29 Mar 2022
 *      Author: feder
 */

#ifndef API_FIRMWARE_INIT_H_
#define API_FIRMWARE_INIT_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h"

void SystemClock_Config(void);
void Error_Handler(void);

#endif /* API_FIRMWARE_INIT_H_ */

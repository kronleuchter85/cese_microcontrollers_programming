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

#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "API_delay.h"

#define EXECUTION_MODE_DEP = 1
#define EXECUTION_MODE_INDEP = 0

UART_HandleTypeDef UartHandle;

static void SystemClock_Config(void);
static void Error_Handler(void);

const tick_t LED_1_TIME = 200;
const tick_t LED_2_TIME = 200;
const tick_t LED_3_TIME = 200;

bool IN_PROGRESS = false;

void process_leds(delay_t *delay, Led_TypeDef led) {

//	if (!IN_PROGRESS) {
//
//		IN_PROGRESS = true;

	if (delayRead(delay)) {
		BSP_LED_Toggle(led);
	}

//		IN_PROGRESS = false;
//	}
}

int main(void) {
	HAL_Init();

	SystemClock_Config();

	// Create three structs of type delay_t
	static delay_t delayLed1;
	static delay_t delayLed2;
	static delay_t delayLed3;

	// Initialize the three leds.
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	// Power off the three leds.
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);

	// Initialize the three structs.
	delayInit(&delayLed1, LED_1_TIME);	//delay 100ms
	delayInit(&delayLed2, LED_2_TIME);	//delay 500ms
	delayInit(&delayLed3, LED_3_TIME);	//delay 1000ms

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	/* Infinite loop */
	while (1) {

		// hay que mantener el boton presionado
		// no le implementamos la logica para mantener el
		// estado.
		if (BSP_PB_GetState(BUTTON_USER)) {

			process_leds(&delayLed1, LED1);
		} else {

			process_leds(&delayLed2, LED2);

		}

	}
}

static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	 clocked below the maximum system frequency, to update the voltage scaling value
	 regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


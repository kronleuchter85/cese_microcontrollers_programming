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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <stdint.h>
#include <stdbool.h>

#define EXECUTION_MODE_DEP = 1
#define EXECUTION_MODE_INDEP = 0

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup UART_Printf
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

// Qué biblioteca se debe incluir para que esto compile? Rpta: stdint.h
typedef uint32_t tick_t;

// Qué biblioteca se debe incluir para que esto compile? Rpta: stdbool.h
typedef bool bool_t;

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);

/*
 * Implementacion de delayInit
 * Inicializa un delay object utilizando la funcion HAL_GetTick() y seteando el flag running en false
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *  duracion - valor de la duracion
 */
void delayInit(delay_t *delay, tick_t duration) {

	// validamos que duration tenga un valor permitido
	if (duration < 0) {
		return;
	}

	delay->duration = duration;
	delay->startTime = HAL_GetTick();
	delay->running = false;
}

/*
 * Implementacion de delayRead
 * Valida si el tiempo ha transcurrido con respecto al momento inicial guardado en el objeto delay, el tiempo actual y la duracion.
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *
 * @returns:
 *  true - el tiempo ya supero la duracion
 *  false - el tiempo aun no supero la duracion seteada
 */
bool_t delayRead(delay_t *delay) {

	if (delay->running) {

		if (HAL_GetTick() >= (delay->startTime + delay->duration)) {
			delay->running = false;
			return true;
		} else {
			return false;
		}
	} else {
		delay->startTime = HAL_GetTick();
		delay->running = true;
		return false;
	}

}

/*
 * Implementacion de delayWrite
 * Permite cambiar el valor de duracion de un objeto delay existente
 *
 * @params:
 *  delay - direccion de memoria donde esta definido el delay
 *  duracion - valor de la duracion
 */
void delayWrite(delay_t *delay, tick_t duration) {

// validamos los parameetros
	if (duration < 0)
		return;

	delay->duration = duration;
}

const tick_t LED_1_TIME = 100;
const tick_t LED_2_TIME = 500;
const tick_t LED_3_TIME = 1000;

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {

	HAL_Init();

	SystemClock_Config();

	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	delay_t delay3;
	delay_t delay2;
	delay_t delay1;

	// Power off the three leds.
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);

	delayInit(&delay3, LED_3_TIME);
	delayInit(&delay2, LED_2_TIME);
	delayInit(&delay1, LED_1_TIME);

	/* Infinite loop */
	while (1) {

		if (delayRead(&delay3)) {
			BSP_LED_Toggle(LED3);
		}
		if (delayRead(&delay2)) {
			BSP_LED_Toggle(LED2);
		}
		if (delayRead(&delay1)) {
			BSP_LED_Toggle(LED1);
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


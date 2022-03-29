/*
 * MEF.c
 *
 *  Created on: 29 Mar 2022
 *      Author: feder
 */

typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING,
} debounceState_t;

void debounceFSM_init();
void debounceFSM_update();

void buttonPressed();
void buttonReleased();


/*
 * repository.h
 *
 *  Created on: 21 Apr 2022
 *      Author: gonzalo
 */

#ifndef SERVICES_INC_REPOSITORY_H_
#define SERVICES_INC_REPOSITORY_H_

#include <stdint.h>

/**
 * Esto representa una secuencia de leds
 */
typedef struct {
	uint8_t led_1;
	uint8_t led_2;
	uint8_t led_3;
} LedSequence;

/**
 * Esta estructura representa una combinacion entre secuencia y velocidad de leds
 */
void repository_initialize();

uint8_t repository_active_sequence_index_get();
void repository_active_sequence_index_set(uint8_t index);
uint8_t repository_active_speed_index_get();
void repository_active_speed_index_set(uint8_t index);

void repository_available_speed_add(uint16_t speed);
uint16_t repository_available_speed_get(uint8_t index);
uint8_t repository_available_speed_count();

LedSequence* repository_available_sequences_get(uint8_t index);
void repository_available_sequences_add(LedSequence *seq);
uint8_t repository_available_sequences_count();

#endif /* SERVICES_INC_REPOSITORY_H_ */

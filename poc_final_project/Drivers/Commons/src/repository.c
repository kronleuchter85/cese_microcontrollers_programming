/*
 * storage.c
 *
 *  Created on: 21 Apr 2022
 *      Author: gonzalo
 */

#include <repository.h>
#include <stdlib.h>

//
//-------------------------------------- Repository ------------------------------------------------------------------
//

static uint8_t active_sequence_index = -1;
static uint8_t active_speed_index = -1;

static LedSequence *available_sequences[10];
static uint8_t added_sequences = 0;

static uint16_t available_speeds[10];
static uint8_t added_speeds = 0;

//
//-------------------------------------- Public members ------------------------------------------------------------------
//

uint8_t repository_available_sequences_count() {
	return added_sequences;
}

LedSequence* repository_available_sequences_get(uint8_t index) {
	if (index < repository_available_sequences_count())
		return available_sequences[index];
	else
		return NULL;
}

void repository_available_sequences_add(LedSequence *seq) {
	available_sequences[added_sequences] = seq;
	added_sequences++;
}

uint16_t repository_available_speed_get(uint8_t index) {
	if (index < repository_available_speed_count())
		return available_speeds[index];
	else
		return -1;
}

uint8_t repository_available_speed_count() {
	return added_speeds;
}

void repository_available_speed_add(uint16_t speed) {
	available_speeds[added_speeds] = speed;
	added_speeds++;
}

uint8_t repository_active_sequence_index_get() {
	return active_sequence_index;
}
void repository_active_sequence_index_set(uint8_t index) {
	active_sequence_index = index;
}
uint8_t repository_active_speed_index_get() {
	return active_speed_index;
}
void repository_active_speed_index_set(uint8_t index) {
	active_speed_index = index;
}

void repository_initialize() {
	LedSequence *new_sequence = malloc(sizeof(LedSequence));
	new_sequence->led_1 = 0;
	new_sequence->led_2 = 1;
	new_sequence->led_3 = 2;

	uint16_t new_speed = 100;

	repository_available_sequences_add(new_sequence);
	repository_available_speed_add(new_speed);

	repository_active_sequence_index_set(0);
	repository_active_speed_index_set(0);

}

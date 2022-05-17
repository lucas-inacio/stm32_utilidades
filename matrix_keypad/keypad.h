/*
 * keypad.h
 *
 *  Created on: May 1, 2022
 *      Author: lucas
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "main.h"

typedef struct KeypadState_t {
	uint16_t k_1    : 1;
	uint16_t k_2    : 1;
	uint16_t k_3    : 1;
	uint16_t k_4    : 1;
	uint16_t k_5    : 1;
	uint16_t k_6    : 1;
	uint16_t k_7    : 1;
	uint16_t k_8    : 1;
	uint16_t k_9    : 1;
	uint16_t k_star : 1;
	uint16_t k_0    : 1;
	uint16_t k_hash : 1;
	uint16_t        : 4;
} KeypadState;

void get_keypad_state(KeypadState *state);

void get_keys_released(KeypadState *state);

#endif /* INC_KEYPAD_H_ */

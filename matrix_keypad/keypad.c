/*
 * keypad.c
 *
 *  Created on: May 1, 2022
 *      Author: lucas
 */

#include "keypad.h"

void get_keypad_state(KeypadState *state)
{
	// Reinicia o estado das teclas
	uint16_t *data = (uint16_t *)state;
	*data = 0;

	// Liga uma linha de cada vez
	int i;
	for (i = 1; i < 5; ++i)
	{
		// Energiza a linha de índice i - 1
		GPIOB->BSRR = 1 << i;

		// E cada coluna
		int j;
		for (j = 0; j < 3; ++j)
		{
			uint8_t shift = 11 + j;
			uint8_t bit = (GPIOB->IDR >> shift) & 0x01;
			*data |= bit << (3 * (i - 1) + j);
		}

		// Desliga a linha de índice i - 1
		GPIOB->BSRR = 1 << (i + 16);
	}
}

void get_keys_released(KeypadState *state)
{
	static KeypadState prevState = { 0 };

	uint16_t *data = (uint16_t *)state;
	*data = 0;

	KeypadState newState;
	get_keypad_state(&newState);

	// Testa pela condição prev = 1 e new = 0 (tecla foi solta)
	uint16_t edge = *((uint16_t*)&prevState) ^ *((uint16_t *)&newState);
	*data = *((uint16_t*)&prevState) & edge;

	// Salva o novo estado
	prevState = newState;
}

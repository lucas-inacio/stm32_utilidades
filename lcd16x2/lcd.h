/*
 * lcd.h
 *
 *  Created on: Apr 16, 2022
 *      Author: lucas
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

// main.h é gerado automaticamente pelo STM32CubeIDE
#include "main.h"

#define ENABLE_HIGH (GPIOA->BSRR = 0x100)
#define ENABLE_LOW  (GPIOA->BSRR = 0x100 << 16)
#define RS_HIGH     (GPIOA->BSRR = 0x200)
#define RS_LOW      (GPIOA->BSRR = 0x200 << 16)

#define PIN_D4 GPIOA->BSRR = 0x10
#define PIN_D5 GPIOA->BSRR = 0x20
#define PIN_D6 GPIOA->BSRR = 0x40
#define PIN_D7 GPIOA->BSRR = 0x80

#define digitalWrite(pin, state) (pin << ((state) + 1) % 2 * 16)

// Envia o nibble alto seguido no nibble baixo para o display
void WriteByteLCD(uint8_t value);

// Envia um nibble para o display
void WriteNibbleLCD(uint8_t value);

void ClockLCD();

// Seleciona o registrador de dados
void SelectDataLCD();

// Seleciona o registrador de instruções
void SelectInstructionLCD();

// Configura o display LCD
void InitLCD();

// Assume o uso de um display de 2 linhas e 16 colunas
void SetCursorLCD(uint8_t line, uint8_t col);

// Desloca o display. RL = 1 para direita ou 0 para esquerda
void ShiftDisplayLCD(int RL);

void ClearLCD();

// Imprime uma string no display (deve terminar com caractere nulo)
void PrintLCD(const char *str);

#endif /* INC_LCD_H_ */

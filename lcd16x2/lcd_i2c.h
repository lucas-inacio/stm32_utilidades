#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "main.h"

#define LCD_ENABLE (1 << 4)
#define LCD_RS     (1 << 5)
#define MAX_I2C_TIMEOUT 100

typedef struct _LCD_Port {
	I2C_HandleTypeDef *i2c_handle;
	uint8_t address;
} LCD_Port;

// Envia o nibble alto seguido no nibble baixo para o display
void i2c_WriteByteLCD(uint8_t value);

// Envia um nibble para o display
void i2c_WriteNibbleLCD(uint8_t value);

// Seleciona o registrador de dados
void i2c_SelectDataLCD();

// Seleciona o registrador de instruções
void i2c_SelectInstructionLCD();

// Configura o display LCD
void i2c_InitLCD(I2C_HandleTypeDef *hi2c, uint8_t address);

// Assume o uso de um display de 2 linhas e 16 colunas
void i2c_SetCursorLCD(uint8_t line, uint8_t col);

// Desloca o display. RL = 1 para direita ou 0 para esquerda
void i2c_ShiftDisplayLCD(int RL);

void i2c_ClearLCD();

// Imprime uma string no display (deve terminar com caractere nulo)
void i2c_PrintLCD(const char *str);

#endif // LCD_I2C_H

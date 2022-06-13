/*
 * lcd_i2c.c
 *
 *  Created on: Jun 12, 2022
 *      Author: lucas
 */
#include "lcd_i2c.h"

/* **********************************************************
 * Os pinos devem estar conectados da seguinte maneira:
 *    LCD   |   PCF8574
 * --------- -----------
 *   D4-D7  |   0-3
 *   ENABLE |   4
 *   RS     |   5
 * **********************************************************/
LCD_Port port;
uint8_t ENABLE_STATUS;
uint8_t RS_STATUS;

// Envia o nibble alto seguido no nibble baixo para o display
void i2c_WriteByteLCD(uint8_t value)
{
	i2c_WriteNibbleLCD((value >> 4) & 0x0f);
	HAL_Delay(2);
	i2c_WriteNibbleLCD(value & 0x0f);
	HAL_Delay(2);
}

// Envia um nibble para o display
void i2c_WriteNibbleLCD(uint8_t value)
{
	uint8_t data[2];
	data[0] = RS_STATUS | LCD_ENABLE | (value & 0x0f),
	data[1] = RS_STATUS | (value & 0x0f);
	HAL_I2C_Master_Transmit(port.i2c_handle, port.address << 1, data, 2, MAX_I2C_TIMEOUT);
}

// Seleciona o registrador de dados
void i2c_SelectDataLCD()
{
	RS_STATUS = LCD_RS;
}

// Seleciona o registrador de instruções
void i2c_SelectInstructionLCD()
{
	RS_STATUS = 0;
}

// Configura o display LCD
void i2c_InitLCD(I2C_HandleTypeDef *hi2c, uint8_t address)
{
	port.i2c_handle = hi2c;
	port.address = address;

	HAL_Delay(50);

	// Configura display para trabalhar com 4 vias de dados
	i2c_SelectInstructionLCD();
	i2c_WriteNibbleLCD(0x02); // Ativa o display para o modo de 4 bits
	i2c_WriteByteLCD(0x28);   // quatro bits; duas linhas
	i2c_WriteByteLCD(0x0F);   // Liga display, cursor piscante
	i2c_WriteByteLCD(0x06);   // Deslocamento automático do cursor da direita para a esquerda. Scroll ligado.
	i2c_WriteByteLCD(0x01);   // Limpa o display.
	i2c_WriteByteLCD(0x80);   // Coloca o cursor no início da primeira linha
}

// Assume o uso de um display de 2 linhas e 16 colunas
void i2c_SetCursorLCD(uint8_t line, uint8_t col)
{
	uint8_t comando = (line > 0) ? 0xC0 : 0x80;
	comando |= col;
	i2c_SelectInstructionLCD();
	i2c_WriteByteLCD(comando);
}

// Desloca o display. RL = 1 para direita ou 0 para esquerda
void i2c_ShiftDisplayLCD(int RL)
{
	uint8_t comando = (RL > 0) ? 0x1C : 0x18;
	i2c_SelectInstructionLCD();
	i2c_WriteByteLCD(comando);
}

void i2c_ClearLCD()
{
	i2c_SelectInstructionLCD();
	i2c_WriteByteLCD(0x01);
}

// Imprime uma string no display (deve terminar com caractere nulo)
void i2c_PrintLCD(const char *str)
{
	i2c_SelectDataLCD();
	char c;
	while ((c = *str++))
		i2c_WriteByteLCD(c);
}


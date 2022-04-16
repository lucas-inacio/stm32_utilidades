/*
 * lcd.c
 *
 *  Created on: Apr 16, 2022
 *      Author: lucas
 */

#include "lcd.h"

// Envia o nibble alto seguido no nibble baixo para o display
void WriteByteLCD(uint8_t value)
{
  WriteNibbleLCD((value >> 4) & 0x0F);
  WriteNibbleLCD(value & 0x0F);
}

// Envia um nibble para o display
void WriteNibbleLCD(uint8_t value)
{
  digitalWrite(PIN_D7, (value >> 3) & 0x01);
  digitalWrite(PIN_D6, (value >> 2) & 0x01);
  digitalWrite(PIN_D5, (value >> 1) & 0x01);
  digitalWrite(PIN_D4, value & 0x01);
  ClockLCD();
}

void ClockLCD()
{
  HAL_Delay(2);
  ENABLE_HIGH;
  HAL_Delay(2);
  ENABLE_LOW;
  HAL_Delay(2);
}

// Seleciona o registrador de dados
void SelectDataLCD()
{
  RS_HIGH;
}

// Seleciona o registrador de instruções
void SelectInstructionLCD()
{
  RS_LOW;
}

// Configura o display LCD
void InitLCD()
{
  HAL_Delay(50);

  // Configura display para trabalhar com 4 vias de dados
  SelectInstructionLCD();
  WriteNibbleLCD(0x02); // Ativa o display para o modo de 4 bits
  WriteByteLCD(0x28);   // quatro bits; duas linhas
  WriteByteLCD(0x0F);   // Liga display, cursor piscante
  WriteByteLCD(0x06);   // Deslocamento automático do cursor da direita para a esquerda. Scroll ligado.
  WriteByteLCD(0x01);   // Limpa o display.
  WriteByteLCD(0x80);   // Coloca o cursor no início da primeira linha
}

// Assume o uso de um display de 2 linhas e 16 colunas
void SetCursorLCD(uint8_t line, uint8_t col)
{
  uint8_t comando = (line > 0) ? 0xC0 : 0x80;
  comando |= col;
  SelectInstructionLCD();
  WriteByteLCD(comando);
}

// Desloca o display. RL = 1 para direita ou 0 para esquerda
void ShiftDisplayLCD(int RL)
{
  uint8_t comando = (RL > 0) ? 0x1C : 0x18;
  SelectInstructionLCD();
  WriteByteLCD(comando);
}

void ClearLCD()
{
  SelectInstructionLCD();
  WriteByteLCD(0x01);
}

// Imprime uma string no display (deve terminar com caractere nulo)
void PrintLCD(const char *str)
{
  SelectDataLCD();
  char c;
  while ((c = *str++))
    WriteByteLCD(c);
}

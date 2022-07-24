/*
 * HX711.c
 *
 *  Created on: Jul 3, 2022
 *      Author: lucas
 */

#include "HX711.h"

TIM_HandleTypeDef *_hx711_timer;
void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(_hx711_timer,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(_hx711_timer) < us);  // wait for the counter to reach the us input in the parameter
}

void hx711_init(
	HX711 *hx711,
	GPIO_TypeDef *clock_port, uint16_t clock_pin,
	GPIO_TypeDef *data_port, uint16_t data_pin)
{
	hx711->clock_pin = clock_pin;
	hx711->clock_port = clock_port;
	hx711->data_pin = data_pin;
	hx711->data_port = data_port;

	// Coloca PD_SCK no nível baixo para ligar o HX711.
	HAL_GPIO_WritePin(hx711->clock_port, hx711->clock_pin, GPIO_PIN_RESET);
	HAL_Delay(500);
}

uint32_t hx711_read(HX711 *hx711)
{
	uint32_t start = HAL_GetTick();
	while (HAL_GPIO_ReadPin(hx711->data_port, hx711->data_pin) == GPIO_PIN_SET)
	{
		delay_us(1);
		// Caso passe mais de 100 milisegundos sem resposta do HX711 retorna
		if (HAL_GetTick() - start > 100)
			return 0;
	}

	delay_us(1);
	int32_t data = 0;
	int i = 0;
	for (; i < 24; ++i)
	{
		HAL_GPIO_WritePin(hx711->clock_port, hx711->clock_pin, GPIO_PIN_SET);
		delay_us(1);
		HAL_GPIO_WritePin(hx711->clock_port, hx711->clock_pin, GPIO_PIN_RESET);
		delay_us(1);
		// Lê o pino de saída do HX711
		data = data << 1;
		if (HAL_GPIO_ReadPin(hx711->data_port, hx711->data_pin) == GPIO_PIN_SET)
			++data;
	}
	// Pulso número 25 necessário para completar a leitura
	HAL_GPIO_WritePin(hx711->clock_port, hx711->clock_pin, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(hx711->clock_port, hx711->clock_pin, GPIO_PIN_RESET);
	delay_us(1);
	return data ^ 0x800000;
}

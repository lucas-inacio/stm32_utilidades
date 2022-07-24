/*
 * HX711.h
 *
 *  Created on: Jul 3, 2022
 *      Author: lucas
 */

#ifndef INC_HX711_H_
#define INC_HX711_H_

#include "main.h"

extern TIM_HandleTypeDef *_hx711_timer;
typedef struct _HX711 {
	GPIO_TypeDef *clock_port;
	uint16_t clock_pin;
	GPIO_TypeDef *data_port;
	uint16_t data_pin;
} HX711;

void delay_us (uint16_t us);
void hx711_init(
	HX711 *hx711,
	GPIO_TypeDef *clock_port, uint16_t clock_pin,
	GPIO_TypeDef *data_port, uint16_t data_pin);

uint32_t hx711_read(HX711 *hx711);

#endif /* INC_HX711_H_ */

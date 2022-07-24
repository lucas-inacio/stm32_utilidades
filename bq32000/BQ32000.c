/*
 * BQ32000.c
 *
 *  Created on: Jun 14, 2022
 *      Author: Lucas.Viegas
 */


#include "BQ32000.h"
#include <string.h>
#include <stdlib.h>

static I2C_HandleTypeDef *_i2c_handle = NULL;
void set_i2c_interface(I2C_HandleTypeDef *hi2c)
{
	_i2c_handle = hi2c;
}

int get_clock_date(ClockDate *date)
{
    // Lê os campos a partir do registrador de segundos (SECOND_REG)
	// e converte de BCD para decimal padrão
	uint8_t data[REG_COUNT] = { 0 };
	uint8_t startReg = SECOND_REG;
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
			_i2c_handle, CLOCK_ADDR, startReg, I2C_MEMADD_SIZE_8BIT, data, REG_COUNT, MAX_I2C_TIMEOUT);
	date->second = ((data[0] >> 4) & 0x7) * 10 + (data[0] & 0x0f);
	date->minute = ((data[1] >> 4) & 0x7) * 10 + (data[1] & 0x0f);
	date->hour   = ((data[2] >> 4) & 0x03) * 10 + (data[2] & 0x0f);
	date->week   = data[3] & 0x07;
	date->day    = ((data[4] >> 4) & 0x03) * 10 + (data[4] & 0x0f);
	date->month  = ((data[5] >> 4) & 0x01) * 10 + (data[5] & 0x0f);
	date->year   = ((data[6] >> 4) & 0x0f) * 10 + (data[6] & 0x0f);
	return status == HAL_OK;
}

void set_clock_date(ClockDate *date)
{
	// Converte os números para BCD e depois grava no BQ32000
	uint8_t second, minute, hour, week, day, month, year;
	clockdate_to_rtc(date, &second, &minute, &hour, &week, &day, &month, &year);
	uint8_t data[REG_COUNT+1] = { 0 };
	data[0] = SECOND_REG;
	data[1] = second;
	data[2] = minute;
	data[3] = hour;
	data[4] = week;
	data[5] = day;
	data[6] = month;
	data[7] = year;
	HAL_I2C_Master_Transmit(_i2c_handle, CLOCK_ADDR, data, REG_COUNT+1, MAX_I2C_TIMEOUT);
}

int clock_to_string(ClockDate *date, char *buffer, int size)
{
	itoa(date->hour, buffer, 10);
	int len = strlen(buffer);
	buffer[len] = ':';
	++len;

	itoa(date->minute, &buffer[len], 10);
	len += strlen(buffer);
	buffer[len] = ':';
	++len;

	itoa(date->second, &buffer[len], 10);
	len += strlen(buffer);
	return len;
}

// Converte os campos em date para BCD
void clockdate_to_rtc(
		ClockDate *date,
		uint8_t *second, uint8_t *minute, uint8_t *hour,
		uint8_t *week, uint8_t *day, uint8_t *month, uint8_t *year)
{
	*second = (((date->second / 10) & 0x07) << 4) | ((date->second % 10) & 0x0f);
	*minute = (((date->minute / 10) & 0x07) << 4) | ((date->minute % 10) & 0x0f);
	*hour = (((date->hour / 10) & 0x03) << 4) | ((date->hour % 10) & 0x0f);
	*week = date->week & 0x07;
	*day = (((date->day / 10) & 0x03) << 4) | ((date->day % 10) & 0x0f);
	*month = (((date->month / 10) & 0x01) << 4) | ((date->month % 10) & 0x0f);
	*year = (((date->year / 10) & 0x0f) << 4) | ((date->year % 10) & 0x0f);
}


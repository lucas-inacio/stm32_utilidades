/*
 * BQ32000.h
 *
 *  Created on: Jun 14, 2022
 *      Author: Lucas.Viegas
 */

#ifndef INC_BQ32000_H_
#define INC_BQ32000_H_

#include "main.h"

#define SECOND_REG 0x00
#define MINUTE_REG 0x01
#define HOUR_REG   0x02
#define WEEK_REG   0x03
#define DAY_REG    0x04
#define MONTH_REG  0x05
#define YEAR_REG   0x06

#define REG_COUNT 7

#define CLOCK_ADDR 0xd0

#define MAX_I2C_TIMEOUT 100

typedef struct _ClockDate {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t week;
	uint8_t day;
	uint8_t month;
	uint8_t year;
} ClockDate;

void set_i2c_interface(I2C_HandleTypeDef *hi2c);
int get_clock_date(ClockDate *date);
void set_clock_date(ClockDate *date);
int clock_to_string(ClockDate *date, char *buffer, int size);
void clockdate_to_rtc(
		ClockDate *date,
		uint8_t *second, uint8_t *minute, uint8_t *hour,
		uint8_t *week, uint8_t *day, uint8_t *month, uint8_t *year);

#endif /* INC_BQ32000_H_ */

/*
 * flash.h
 *
 *  Created on: Jun 28, 2022
 *      Author: Lucas.Viegas
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"

// Até 0x0800FFFF (1024 bytes)
#define START_DATA_ADDR 0x0800F800

uint32_t write_flash(uint32_t address, uint16_t *data, uint16_t size);
uint32_t read_flash(uint32_t address, uint16_t *data, uint16_t size);

#endif /* INC_FLASH_H_ */

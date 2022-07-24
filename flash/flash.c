/*
 * flash.c
 *
 *  Created on: Jun 28, 2022
 *      Author: Lucas.Viegas
 */
#include "flash.h"

uint32_t write_flash(uint32_t address, uint16_t *data, uint16_t size)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError;

	HAL_FLASH_Unlock();

	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.NbPages     = 1;
	EraseInitStruct.PageAddress = START_DATA_ADDR;

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
	{
		/*Error occurred while page erase.*/
		return HAL_FLASH_GetError();
	}

	uint32_t currentAddress = address;
	int i;
	for (i = 0; i < size; ++i, currentAddress += 2)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, currentAddress, data[i]) != HAL_OK)
		{
			return HAL_FLASH_GetError();
		}
	}

	HAL_FLASH_Lock();
	return 0;
}

uint32_t read_flash(uint32_t address, uint16_t *data, uint16_t size)
{
	uint32_t currentAddress = address;
	int i = 0;
	for(; i < size; ++i, currentAddress += 2)
	{
		data[i] = *(__IO uint16_t*)currentAddress;
	}
	return 0;
}


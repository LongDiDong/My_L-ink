#include "flash.h"
#include <stdint.h>

uint8_t *Address_Base;

void MY_DATAFLASH_Program(uint32_t Address, uint8_t *Data)   
{
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError = 0;
    Address_Base = (uint8_t *)Address;

    
	HAL_FLASH_Unlock(); 
			 		 
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;	// ˢ³ý·½ʽ
    EraseInitStruct.PageAddress = Address;	// ưʼµؖ·
    EraseInitStruct.NbPages = 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
    {
    // ȧ¹ûˢ³ý´펳
        printf("\r\n FLASH Erase Fail\r\n");
        printf("Fail Code:%d\r\n",HAL_FLASH_GetError());
        printf("Fail Page:%d\r\n",PAGEError);
    }


    memcpy(Address_Base, Data, 128);
	HAL_FLASH_Lock();
} 



//
uint32_t FLASH_ReadWord(uint32_t address)
{
  return *(__IO uint32_t*)address;
}



uint32_t uchar_to_uint32_big_endian(unsigned char *buffer, uint16_t offset) 
{
    return ((uint32_t)buffer[0 + offset] << 24) | ((uint32_t)buffer[1 + offset] << 16) |
           ((uint32_t)buffer[2 + offset] << 8) | (uint32_t)buffer[3 + offset];
}

uint32_t uchar_to_uint32_little_endian(unsigned char *buffer ,uint16_t offset) {
    return ((uint32_t)buffer[3 + offset] << 24) | ((uint32_t)buffer[2 + offset] << 16) |
           ((uint32_t)buffer[1 + offset] << 8) | (uint32_t)buffer[0 + offset];
}




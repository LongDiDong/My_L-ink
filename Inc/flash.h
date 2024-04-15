#ifndef __FLASH_H
#define __FLASH_H

#include "main.h"
#include "stdio.h"
#include <string.h>

#define ADDR_FLASH_PAGE_470      0X08000000 + 128*470   //开始

#define ADDR_FLASH_PAGE_506      0X08000000 + 128*505   //
#define ADDR_FLASH_PAGE_507      0X08000000 + 128*506   //
#define ADDR_FLASH_PAGE_508      0X08000000 + 128*507   //
#define ADDR_FLASH_PAGE_509      0X08000000 + 128*508   //
#define ADDR_FLASH_PAGE_510      0X08000000 + 128*509   //
#define ADDR_FLASH_PAGE_511      0X08000000 + 128*510   //
#define ADDR_FLASH_PAGE_512      0X08000000 + 128*511   //最后一页

void MY_DATAFLASH_Program(uint32_t Address, uint8_t *Data);   
//读取指定地址的半字(16位数据)
uint16_t FLASH_ReadHalfWord(uint32_t address);

//读取指定地址的全字(32位数据)
uint32_t FLASH_ReadWord(uint32_t address);

uint32_t uchar_to_uint32_big_endian(unsigned char *buffer, uint16_t offset);
uint32_t uchar_to_uint32_little_endian(unsigned char *buffer, uint16_t offset);


#endif


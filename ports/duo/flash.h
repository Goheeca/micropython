#ifndef __FLASH_H
#define __FLASH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void sFLASH_eraseSector(uint32_t SectorAddr);
void sFLASH_writeBuffer(const uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void sFLASH_readBuffer(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
int sFLASH_selfTest(void);

extern const uint32_t sFLASH_END_ADDRESS;
extern const uint32_t sFLASH_SECTOR_SIZE;

#ifdef __cplusplus
}
#endif

#endif //__FLASH_H
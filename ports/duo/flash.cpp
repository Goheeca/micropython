#include "flash.h"
#include "spark_wiring_sflash.h"

void sFLASH_eraseSector(uint32_t SectorAddr) {
	sFLASH.eraseSector(SectorAddr);
};
void sFLASH_writeBuffer(const uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite) {
	sFLASH.writeBuffer(pBuffer, WriteAddr, NumByteToWrite);
}
void sFLASH_readBuffer(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead) {
	sFLASH.readBuffer(pBuffer, ReadAddr, NumByteToRead);
}
int sFLASH_selfTest(void) {
	return sFLASH.selfTest();
}
const uint32_t sFLASH_END_ADDRESS = SFLASH_RESERVED_ADDRESS;
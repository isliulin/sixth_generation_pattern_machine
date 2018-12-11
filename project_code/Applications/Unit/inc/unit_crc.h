#ifndef __UNIT_CRC_H__
#define __UNIT_CRC_H__


/*----------------------------------------------------------------------------*/
uint16_t unit_CalcCrc16(uint8_t *pFrame, uint32_t Len);

uint32_t unit_CalcCrc32Software(uint8_t *pData, uint32_t Size);
uint32_t unit_CalcCrc32Hardware(uint8_t *pData, uint32_t Size);
uint32_t unit_CalcCrc32InitvalSoftware(uint32_t Initval, uint32_t *pData, uint32_t Size);
uint32_t unit_CalcCrc32InitvalHardware(uint32_t Initval, uint32_t *pData, uint32_t Size);
void unit_CrcTest(void);







#endif


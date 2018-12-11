#ifndef APP_EEPROM_H
#define APP_EEPROM_H





/*----------------------------------------------------------------------------*/
void app_EepromInit(void);
void app_EepromTest(void);

uint8_t app_EepromReadBytes(uint8_t *pReadBuf, uint16_t Address, uint16_t Size);
uint8_t app_EepromWriteBytes(uint8_t *pWriteBuf, uint16_t Address, uint16_t Size);
uint8_t app_EepromWriteCheck(uint8_t *pWriteBuf, uint16_t Address, uint16_t Size);

/*----------------------------------------------------------------------------*/


#endif /* APP_EEPROM_H */
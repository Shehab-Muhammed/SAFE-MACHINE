#ifndef		EEPROM_FUNC.h
#define		EEPROM_FUNC.h
#include	"EEPROM_REG.h"

void		EEPROM_WRITE(uint_16 address,uint_8 data);
uint_8		EEPROM_READ(uint_16 address);

#endif
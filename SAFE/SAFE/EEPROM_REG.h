#ifndef			EEPROM_REG.h
#define			EEPROM_REG.h
#include		"TYPEDEF.h"
#include		"STD_MACROS.h"
#define			EERL				*(volatile uint_8*)(0x3E)
#define			EERH				*(volatile uint_8*)(0x3F)
#define			EEAR				*(volatile uint_16*)(0x3E)

#define			EEDR				*(volatile uint_8*)(0x3D)
#define			EECR				*(volatile uint_8*)(0x3C)
#define			EERIE				3
#define			EEMWE				2
#define			EEWE				1
#define			EERE				0
#endif
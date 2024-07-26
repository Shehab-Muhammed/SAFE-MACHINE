#ifndef KEYPAD_FUNC.h
#define KEYPAD_FUNC.h
#define KEYPAD_PORT 'd'
#define NOT_PRESSED 0xff
#include "DIO_FUNC.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/*_________________________________________________*///BUTTON_READ///*_________________________________________________*/

uint_8	BUTTON_READ_STATE			(uint_8 port, uint_8 pin);
/*_________________________________________________*///KEYPAD_INIT///*_________________________________________________*/

void		KEYPAD_INIT				(void );
/*_________________________________________________*///KEYPAD_READ///*_________________________________________________*/

uint_8		KEYPAD_READ				(void);
/*_________________________________________________*///KEYPAD_RETURN_NUMBER///*________________________________________*/
uint_8		KEYPAD_PRESSED_NUM		(void);

#endif
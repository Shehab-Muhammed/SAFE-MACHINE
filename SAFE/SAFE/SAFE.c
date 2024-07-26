#define F_CPU 8000000UL
#include <util/delay.h>
/*____________________________________*///DELAY_SET
#include "KEYPAD_FUNC.h"
#include "LCD_INTERFACE.h"
#include "EEPROM_FUNC.h"
/*____________________________________*///INCLUDES
#define EEPROM_STATUS_LOCATIN	0x20
#define EEPROM_LOCATION1		0x21		/**********************/
#define EEPROM_LOCATION2		0x22		/**FIRST_PASSWORD_SET**/
#define EEPROM_LOCATION3		0x23		/**********************/
#define EEPROM_LOCATION4		0x24
/*____________________________________*///EEPROM_CONFIG
#define MAX_TRIES				2
sint_8 arr[4];
sint_8 back[3];
/*____________________________________*///IMPORTANT_VALUES

#define EEPROM_BACKUP1			0x25		/***********************/
#define EEPROM_BACKUP2			0x26		/**SECOND_PASSWORD_SET**/
#define EEPROM_BACKUP3			0x27		/***********************/
/*____________________________________*/
void main(void)
{
	uint_8 val=NOT_PRESSED;
	uint_8 flag=0,counter;
	uint_8 tries=MAX_TRIES;
/*__________________________________*/
	LCD_4_BIT_INIT(HIGH_NIPPLE);
	KEYPAD_INIT();
/*__________________________________*/
	MOVE_CURSOR_4_BIT(1,4);
	LCD_WRITE_STRING_4_BIT("WELCOME TO");
	MOVE_CURSOR_4_BIT(2,3);
	LCD_WRITE_STRING_4_BIT("SAFE MACHINE");
	_delay_ms(1500);
	LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
	DIO_SET_PIN_DIRECTION('B',6,PIN_OUTPUT);
	DIO_SET_PIN_DIRECTION('B',7,PIN_OUTPUT);
	
/*_______________________________________________________*/
/*____________________________SET________________________*/
while(1)
{
	if(EEPROM_READ(EEPROM_STATUS_LOCATIN)==NOT_PRESSED)
	{
		LCD_WRITE_STRING_4_BIT("ENTER YOUR NEW");
		MOVE_CURSOR_4_BIT(2,1);
		LCD_WRITE_STRING_4_BIT("PASSWORD:");
	/*______________________________________*/
			for(counter=0;counter<=3;counter++)
			{
				while(KEYPAD_READ()==NOT_PRESSED);											
				EEPROM_WRITE(EEPROM_LOCATION1+counter,KEYPAD_READ());			/**********************************/
				MOVE_CURSOR_4_BIT(2,10+counter);								/**********************************/
				LCD_SEND_DATA_FOUR_BIT(KEYPAD_READ(),HIGH_NIPPLE);				/**********EEPROM_SET**************/
				_delay_ms(500);													/**********************************/
				MOVE_CURSOR_4_BIT(2,10+counter);								/**********************************/
				LCD_SEND_DATA_FOUR_BIT('*',HIGH_NIPPLE);
			}		
		LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
		MOVE_CURSOR_4_BIT(1,5);
		LCD_WRITE_STRING_4_BIT("PASSWORD");
		MOVE_CURSOR_4_BIT(2,6);
		LCD_WRITE_STRING_4_BIT("SETTED");
		_delay_ms(500);
		EEPROM_WRITE(EEPROM_STATUS_LOCATIN,0x00);
		LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
		_delay_ms(500);
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
		if(EEPROM_READ(EEPROM_STATUS_LOCATIN)==0x00)
		{
			LCD_WRITE_STRING_4_BIT("SET BACKUP");
			MOVE_CURSOR_4_BIT(2,1);
			LCD_WRITE_STRING_4_BIT("PASS:");
			/*______________________________________*/
			for(counter=0;counter<=2;counter++)
			{
				while(KEYPAD_READ()==NOT_PRESSED);
				EEPROM_WRITE(EEPROM_BACKUP1+counter,KEYPAD_READ());			/**********************************/
				MOVE_CURSOR_4_BIT(2,6+counter);								/**********************************/
				LCD_SEND_DATA_FOUR_BIT(KEYPAD_READ(),HIGH_NIPPLE);			/**********BACKUP_SET**************/
				_delay_ms(500);												/**********************************/
				MOVE_CURSOR_4_BIT(2,6+counter);								/**********************************/
				LCD_SEND_DATA_FOUR_BIT('*',HIGH_NIPPLE);
			}
			LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
			MOVE_CURSOR_4_BIT(1,6);
			LCD_WRITE_STRING_4_BIT("BACKUP");
			MOVE_CURSOR_4_BIT(2,6);
			LCD_WRITE_STRING_4_BIT("SETTED");
			_delay_ms(500);
			LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
		}
		flag=0;
	}
/*_______________________________________________________*/
/*_______________________________________________________*///----------------->READY_CHECK_PASSWORD

	

	while (flag==0)
	{
		arr[0]=arr[1]=arr[2]=arr[3]=NOT_PRESSED;
		back[0]=back[1]=back[2]=NOT_PRESSED;
		LCD_WRITE_STRING_4_BIT("PLEASE ENTER THE");
		MOVE_CURSOR_4_BIT(2,1);
		LCD_WRITE_STRING_4_BIT("PASSWORD:");
/*____________________________________________________________________________*/	
		
		for(counter=0;counter<=3;counter++)
			{
				
				while(KEYPAD_READ()==NOT_PRESSED);					/**************************/
				arr[counter]=KEYPAD_READ();							/**************************/
				LCD_SEND_DATA_FOUR_BIT(arr[counter],HIGH_NIPPLE);	/****SOTRES_PASS_IN_ARRAY**/	
				MOVE_CURSOR_4_BIT(2,10+counter);					/**************************/
				_delay_ms(500);										/**************************/
				LCD_SEND_DATA_FOUR_BIT('*',HIGH_NIPPLE);
			}
/*____________________________________________________________________________*/	
			
			if(EEPROM_READ(EEPROM_LOCATION1)==arr[0] && EEPROM_READ(EEPROM_LOCATION2)==arr[1] && EEPROM_READ(EEPROM_LOCATION3)==arr[2] &&EEPROM_READ(EEPROM_LOCATION4)==arr[3] )
			{
				LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
				MOVE_CURSOR_4_BIT(1,3);
				LCD_WRITE_STRING_4_BIT("CORRECT PASS");						/******************/
				MOVE_CURSOR_4_BIT(2,4);										/**CHECK_PASSWORD**/
				LCD_WRITE_STRING_4_BIT("LOCK OPENED!");						/******************/
				flag=1;
				DIO_PORT_PIN_WRITE('b',6,PIN_HIGH);
			}/*________________________________*///--->CASE_CORRECT			
	
			else
			{
				tries=tries-1;
				if(tries>0)
				{
					LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
					MOVE_CURSOR_4_BIT(1,4);
					LCD_WRITE_STRING_4_BIT("INCORRECT!");
					MOVE_CURSOR_4_BIT(2,1);
					LCD_WRITE_STRING_4_BIT("TRY AGAINS:");
					LCD_SEND_DATA_FOUR_BIT(tries+48,HIGH_NIPPLE);
					_delay_ms(1000);
					LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
				}
				else
				{
					LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
					MOVE_CURSOR_4_BIT(1,2);
					LCD_WRITE_STRING_4_BIT("INTRUDER ALARM");
					MOVE_CURSOR_4_BIT(2,2);
					DIO_PORT_PIN_WRITE('b',7,PIN_HIGH);
					_delay_ms(2500);
					DIO_PORT_PIN_WRITE('b',7,PIN_LOW);
					LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
					LCD_WRITE_STRING_4_BIT("ENTER BACKUP");
					MOVE_CURSOR_4_BIT(2,1);
					LCD_WRITE_STRING_4_BIT("PASS:");
					for(counter=0;counter<=2;counter++)
					{
						
						while(KEYPAD_READ()==NOT_PRESSED);					/****************************/
						back[counter]=KEYPAD_READ();						/****************************/
						LCD_SEND_DATA_FOUR_BIT(back[counter],HIGH_NIPPLE);	/****SOTRES_BACKUP_IN_ARRAY**/
						MOVE_CURSOR_4_BIT(2,6+counter);						/****************************/
						_delay_ms(500);										/****************************/
						LCD_SEND_DATA_FOUR_BIT('*',HIGH_NIPPLE);
					}
					if(EEPROM_READ(EEPROM_BACKUP1)==back[0] && EEPROM_READ(EEPROM_BACKUP2)==back[1] && EEPROM_READ(EEPROM_BACKUP3)==back[2])
					{
						EEPROM_WRITE(EEPROM_STATUS_LOCATIN,0xff);
						EEPROM_WRITE(EEPROM_LOCATION1,0xff);
						EEPROM_WRITE(EEPROM_LOCATION2,0xff);
						EEPROM_WRITE(EEPROM_LOCATION3,0xff);
						EEPROM_WRITE(EEPROM_LOCATION4,0xff);
						LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
						MOVE_CURSOR_4_BIT(1,1);
						DIO_PORT_PIN_WRITE('b',7,PIN_LOW);
						flag=1;
					}
					else
					{
						LCD_SEND_CMD_FOUR_BIT(0x01,HIGH_NIPPLE);
						MOVE_CURSOR_4_BIT(1,5);
						LCD_WRITE_STRING_4_BIT("SECURITY");
						MOVE_CURSOR_4_BIT(2,6);
						LCD_WRITE_STRING_4_BIT("ALARM!");
						while(1)
						{
						DIO_TOGGLE_PORT_PIN('b',7);
						_delay_ms(200);
						}						
					}
				}
			}/*________________________________*///--->CASE_INCORRECT		
/*____________________________________________________________________________*/
	
	}//----->while		
  }	
}
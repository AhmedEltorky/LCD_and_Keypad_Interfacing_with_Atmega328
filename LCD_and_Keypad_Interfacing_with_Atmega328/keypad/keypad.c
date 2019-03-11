/*
 * keypad.c
 *
 * Created: 3/10/19 2:39:34 AM
 *  Author: Ahmed El-Torky
 */

#define F_CPU 1000000ul

#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"

unsigned char colloc, rowloc;
unsigned char keypad[4][4] = {{'7', '8', '9', '/'}, {'4', '5', '6', '*'}, {'1', '2', '3', '-'}, {'.', '0', '=', '+'}};

void keypad_init(void)
{
	KEY_DDR = 0x0F; // set first four pins in the port to output (D0-D3) and the last four pins to input (D4-D7)
	KEY_PRT = 0xF0; // activate pull up on input pins
}

unsigned char keypad_get_key(void)
{
	do
	{
		KEY_PRT = 0xF0;			 // ground all rows
		colloc = KEY_PIN & 0xF0; // read all columns
	} while (colloc != 0xF0);	// check until all keys released

	do
	{
		do
		{
			_delay_ms(20);			 // wait
			colloc = KEY_PIN & 0xF0; // read all columns
		} while (colloc == 0xF0);	// check until any key pressed
		_delay_ms(20);				 // wait for debouncing
		colloc = KEY_PIN & 0xF0;	 // read all columns
	} while (colloc == 0xF0);
	// row detection
	unsigned char ground = 0xFE;
	for (unsigned char i = 0; i < 4; i++)
	{
		KEY_PRT = ground;		 // ground row no. i
		colloc = KEY_PIN & 0xF0; // read all columns
		if (colloc != 0xF0)
		{
			rowloc = i;
			break;
		}
		else
		{
			ground -= 1;
		}
	}
	// column detection
	switch (colloc)
	{
	case 0xE0:
		return keypad[rowloc][3];
		break;
	case 0xD0:
		return keypad[rowloc][2];
		break;
	case 0xB0:
		return keypad[rowloc][1];
		break;
	case 0x70:
		return keypad[rowloc][0];
		break;
	default:
		break;
	}

	return -1; // return -1 if failed to get key
}

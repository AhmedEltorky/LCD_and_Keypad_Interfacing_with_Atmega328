/*
 * LCD_and_Keypad_Interfacing_with_Atmega328.c
 *
 * Created: 3/9/19 1:02:06 PM
 * Author : Ahmed El-Torky
 */

#define F_CPU 1000000ul

#include <avr/io.h>
#include <util/delay.h>
#include "lcd/lcd.h"
#include "keypad/keypad.h"

void displayMyName(void);

int main(void)
{
	lcd_init();
	keypad_init();
	lcd_cursor_setup(LCD_CURSOR_OFF); // disable the cursor
	lcd_write_string("Hello 0123456789");
	_delay_ms(2000);
	lcd_write_cmnd(LCD_CLEAR);
	displayMyName();
	_delay_ms(500);
	lcd_write_cmnd(LCD_CLEAR);
 
	while (1)
	{
		unsigned char k = keypad_get_key();
		if (k != -1)
		{
			lcd_write_data(k);
			_delay_ms(100);
		}
	}
}

void displayMyName(void)
{
	char *name = "Ahmed El-Torky";
	unsigned char index = 0;
	lcd_gotoxy(2, 2);
	while (name[index] != 0)
	{
		lcd_write_data(name[index]);
		index++;
		_delay_ms(500);
	}

	for (int i = 0; i < 3; i++)
	{
		lcd_write_cmnd(LCD_CLEAR);
		lcd_gotoxy(2, 2);
		_delay_ms(200);
		lcd_write_string(name);
		_delay_ms(200);
	}
}

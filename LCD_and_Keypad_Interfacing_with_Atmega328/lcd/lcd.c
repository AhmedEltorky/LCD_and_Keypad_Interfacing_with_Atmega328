/*
 * lcd.c
 *
 * Created: 3/9/19 1:02:53 PM
 *  Author: Ahmed El-Torky
 */

/* Driver for 16 x 2 alphanumeric LCD
*  lcd_init()   Must be called before any other function.
*																					y/x	1 | 2 | 3 | .... | 16
*  lcd_gotoxy(x, y) Set write position on LCD (upper left is (1,1)) - 16 x and 2 y	1 | # | # | # | .... | #
*																					2 | # | # | # | .... | #
*
*  lcd_goto_rc(r, c)  Set write position on LCD (upper left is (0,0)) - 2 rows and 16 columns
*/

#define F_CPU 1000000ul

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void lcd_write_cmnd(unsigned char cmnd)
{
	LCD_DPRT = cmnd & 0xF0;		// send high nibble of command to D4-D7
	LCD_CPRT &= ~(1 << LCD_RS); // LCD_RS = 0, for command
	LCD_CPRT &= ~(1 << LCD_RW); // LCD_RW = 0, for write operation
	LCD_CPRT |= (1 << LCD_EN);  // LCD_EN = 1, for High to Low pulse
	_delay_us(200);				// wait to make enable wide
	LCD_CPRT &= ~(1 << LCD_EN); // LCD_EN = 0, for High to Low pulse
	_delay_us(600);				// wait to make enable wide
	LCD_DPRT = cmnd << 4;		// send low nibble of command to D4-D7
	LCD_CPRT |= (1 << LCD_EN);  // LCD_EN = 1, for High to Low pulse
	_delay_us(200);				// wait to make enable wide
	LCD_CPRT &= ~(1 << LCD_EN); // LCD_EN = 0, for High to Low pulse
	_delay_us(600);
}

void lcd_write_data(unsigned char data)
{
	LCD_DPRT = data & 0xF0;		// send high nibble of data to D4-D7
	LCD_CPRT |= (1 << LCD_RS);  // LCD_RS = 1, for data
	LCD_CPRT &= ~(1 << LCD_RW); // LCD_RW = 0, for write operation
	LCD_CPRT |= (1 << LCD_EN);  // LCD_EN = 1, for High to Low pulse
	_delay_us(50);				// wait to make enable wide
	LCD_CPRT &= ~(1 << LCD_EN); // LCD_EN = 0, for High to Low pulse
	_delay_us(100);				// wait to make enable wide
	LCD_DPRT = data << 4;		// send low nibble of data to D4-D7
	LCD_CPRT |= (1 << LCD_EN);  // LCD_EN = 1, for High to Low pulse
	_delay_us(50);				// wait to make enable wide
	LCD_CPRT &= ~(1 << LCD_EN); // LCD_EN = 0, for High to Low pulse
	_delay_us(100);				// wait to make enable wide
}

void lcd_init()
{
	LCD_DDDR = 0xF0;			// set D4-D7 to output port
	LCD_CDDR = 0x07;			// set first three pins in cmd_port to output
	LCD_CPRT &= ~(1 << LCD_EN); // LCD_EN = 0
	_delay_us(2000);			// wait for initialization
	lcd_write_cmnd(0x33);		
	lcd_write_cmnd(0x32);		// set display 4 bit, 2 lines mode
	lcd_write_cmnd(0x28);
	lcd_write_cmnd(LCD_CURSOR_ON_WITH_BLINK); // display on, cursor on and blinking
	_delay_ms(5);							  // wait
	lcd_write_cmnd(LCD_CLEAR);				  // clear LCD
	_delay_ms(5);							  // wait
	lcd_write_cmnd(LCD_SET_CURSOR);			  // seek 00, start of line 
	_delay_ms(5);							  // wait
	lcd_write_cmnd(LCD_ENTRY_MODE);			  // shift cursor right
	_delay_ms(5);							  // wait
}

void lcd_cursor_setup(unsigned char cursor)
{
	switch (cursor)
	{
	case LCD_CURSOR_ON:
		lcd_write_cmnd(LCD_CURSOR_ON);
		break;
	case LCD_CURSOR_OFF:
		lcd_write_cmnd(LCD_CURSOR_OFF);
		break;
	case LCD_CURSOR_ON_WITH_BLINK:
		lcd_write_cmnd(LCD_CURSOR_ON_WITH_BLINK);
		break;
	default:
		break;
	}
}

void lcd_goto_rc(unsigned char row, unsigned char column)
{
	unsigned char lcd_matrix[2][16] = {{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F},
									   {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF}};
	lcd_write_cmnd(lcd_matrix[row][column]);
	_delay_us(100);
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char arr_address[] = {0x80, 0xC0};
	lcd_write_cmnd(arr_address[y - 1] + x - 1);
	_delay_us(100);
}

void lcd_write_string(char *str)
{
	unsigned char index = 0;
	while (str[index] != 0)
	{
		lcd_write_data(str[index]);
		index++;
	}
}

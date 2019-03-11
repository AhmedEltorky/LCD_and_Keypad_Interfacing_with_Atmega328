/*
 * lcd.h
 *
 * Created: 3/9/19 1:03:51 PM
 *  Author: Ahmed El-Torky
 */

#ifndef LCD_H_
#define LCD_H_

#define LCD_DPRT PORTD
#define LCD_DDDR DDRD
#define LCD_DPIN PIND
#define LCD_CPRT PORTC
#define LCD_CDDR DDRC
#define LCD_CPIN PINC
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#define LCD_CLEAR 0x01                // replace all characters with ASCII 'space'
#define LCD_RET_HOME 0x02             // return cursor to first position on first line
#define LCD_ENTRY_MODE 0x06           // shift cursor from left to right on read/write
#define LCD_DISPLAY_OFF 0x08          // turn display off
#define LCD_CURSOR_OFF 0x0C           // display on, cursor off, don't blink character
#define LCD_CURSOR_ON 0x0E            // display on, cursor on, don't blink character
#define LCD_CURSOR_ON_WITH_BLINK 0x0F // display on, cursor on, blink character
#define LCD_RESET 0x30                // reset the LCD
#define LCD_SET_8BIT 0x38             // 8-bit data, 2-line display, 5 x 7 font
#define LCD_SET_CURSOR 0x80           // set cursor position

extern void lcd_write_cmnd(unsigned char cmnd);
extern void lcd_write_data(unsigned char data);
extern void lcd_init();
extern void lcd_cursor_setup(unsigned char cursor);
extern void lcd_goto_rc(unsigned char row, unsigned char column);
extern void lcd_gotoxy(unsigned char x, unsigned char y);
extern void lcd_write_string(char *str);

#endif /* LCD_H_ */

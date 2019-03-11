/*
 * keypad.h
 *
 * Created: 3/10/19 2:39:50 AM
 *  Author: Ahmed El-Torky
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEY_PRT PORTB
#define KEY_PIN PINB
#define KEY_DDR DDRB

extern void keypad_init(void);
extern unsigned char keypad_get_key(void);

#endif /* KEYPAD_H_ */
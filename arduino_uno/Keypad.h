/*
 * Keypad.h
 *
 * Created: 2019-04-17 오전 11:05:17
 *  Author: scolpig
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define Keypad_PORT_DDR DDRD
#define Keypad_PORT PORTD
#define Keypad_PIN_DDR DDRD
#define Keypad_PIN_PORT PORTD
#define Keypad_PIN PIND

void Keypad_init(void);
void clock_Keypad_init(void);
char Keyscan(void);
char Keyscan_sub(void);

#endif /* KEYPAD_H_ */
/*
 * Keypad.c
 *
 * Created: 2019-04-16 오후 12:06:46
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Uart.h"
#include "Keypad.h"

int Keypad_main(void){
	int number=0;
	char long_key_flag = 0;
	Keypad_init();
	UART0_init(9600);
	while(1){
		if(long_key_flag){
			if(Keyscan() != 'A'){
				TX0_char(Keyscan());
				if(Keyscan() == 'B')TX0_string("Hello");
				long_key_flag = 0;
			}
		}
		else {
			if(Keyscan() == 'A'){
				long_key_flag = 1;
			}
		}
	}
}
void Keypad_init(void){
	Keypad_PORT_DDR |= 0b11110000;
	Keypad_PORT |= 0b11110000;
	Keypad_PIN_DDR &= 0b11110000;
	Keypad_PIN_PORT |= 0b00001111;
}
char Keyscan_sub(void){
	if(!(Keypad_PIN & 0b00000001))return 1;
	else if(!(Keypad_PIN & 0b00000010))return 2;
	else if(!(Keypad_PIN & 0b00000100))return 3;
	else if(!(Keypad_PIN & 0b00001000))return 4;
	else return 0;
}
char Keyscan(void){
	char data;
	for(int i=0;i<4;i++){
		Keypad_PORT |= 0b11110000;
		Keypad_PORT &= ~(0b10000000>>i);
		_delay_us(1);
		if(Keyscan_sub())return 'A' + Keyscan_sub() + i*4;
	}
	return 'A';
}


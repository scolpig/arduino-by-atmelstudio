/*
 * Bluetooth.c
 *
 * Created: 2019-05-14 오후 2:45:21
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Uart.h"

extern volatile char RX_flag;
extern volatile char RX_data;

int Bluetooth_main(void){
	int red=0, blue=0;
	char green=0;
	DDRB |= 1 << PORTB5;
	PORTB &= ~(1 << PORTB5);
	Bluetooth_init();
	Timer1_init_fast_PWM_outA();
	Timer2_init_fast_PWM_outA();
	sei();
	//setName("IoT_Master");
	
	/*
	OCR1A = red;
	OCR1B = blue;
	OCR2A = green;
	*/
	while(1){
		if(RX_flag){
			RX_flag = 0;
			switch(RX_data){
				case 'F': 
					red++;
					if(red >= 150)red = 150;
					OCR1A = red;
					break;
				case 'B': 
					red--;
					if(red <= 0)red = 0;
					OCR1A = red;
					break;
				case 'L': 
					blue++;
					if(blue >= 150)blue = 150;
					OCR1B = blue;
					break;
				case 'R': 
					blue--;
					if(blue <= 0)blue = 0;
					OCR1B = blue;
					break;
				case 'H': 
					green++;
					if(green >= 150)green = 150;
					OCR2A = green;
					break;
				case 'I': 
					green--;
					if(green <= 0)green = 1;
					OCR2A = green;
					break;
				default: break;
			}
		}
	}
	return 0;
}
void Bluetooth_init(void){
	UART0_init(9600);
}
void setName(char *name){
	TX0_string("AT+NAME");
	TX0_string(name);
	return;
}
void setPIN(char *pin){    //네자리 숫자
	TX0_string("AT+PIN");
	TX0_string(pin);
	return;
}
void connectTest(void){
	TX0_string("AT");
	return;
}

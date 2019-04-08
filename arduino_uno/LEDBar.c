/*
 * LEDBar.c
 * 
 * Created: 2019-04-04 오전 10:34:51
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "LEDBar.h"

int LEDBar_main(void)
{
    Ledbar_init();
	
    while (1) 
    {
		Led_toggle_center();
		/*Led_up_down();
		Led_on_up();
		Led_off_up();
		Led_on_down();
		Led_off_down();*/
    }
}
void Led_on_up(void){
	for(int i=0;i<9;i++){
		LEDBar_PORT &= ~(0b00000001 << i);
		_delay_ms(200);
	}
	return;
}
void Led_on_down(void){
	for(int i=0;i<9;i++){
		LEDBar_PORT &= ~(0b10000000 >> i);
		_delay_ms(200);
	}
	return;
}
void Led_off_up(void){
	LEDBar_PORT = 0b00000000;
	/*for(int i=0;i<9;i++){
		LEDBar_PORT = ~(0b11111110 << i);
		_delay_ms(200);
	}*/
	/*for(int i=0;i<9;i++){
		LEDBar_PORT |= 0b00000001 << i;
		_delay_ms(200);
	}*/
	/*for(int i=0;i<9;i++){
		LEDBar_PORT = (LEDBar_PORT << 1) + 1;
		_delay_ms(200);
	}*/
	for(int i=0;i<8;i++){
		LEDBar_PORT = 0b11111111 >> (7-i);
		_delay_ms(200);
	}
	return;
}
void Led_off_down(void){
	for(int i=0;i<9;i++){
		LEDBar_PORT = ~(0b01111111 >> i);
		_delay_ms(200);
	}
	
	return;
}
void Led_up_down(void){
	for(int i=0;i<9;i++){
		LEDBar_PORT = ~(0b00000001 << i);
		_delay_ms(200);
	}
	for(int i=0;i<9;i++){
		LEDBar_PORT = ~(0b10000000 >> i);
		_delay_ms(200);
	}
	
}
void Ledbar_init(void){
	LEDBar_DDR = 0b11111111;
	LEDBar_PORT = 0b11111111;
	return;
}
void Led_toggle_center(void){
	for(int i=0;i<4;i++){
		LEDBar_PORT = (0b11111111 >> i) & (0b11111111 << i);
		_delay_ms(500);
	}
	for(int i=0;i<4;i++){
		LEDBar_PORT = (0b11111111 >> (4-i)) & (0b11111111 << (4-i));
		_delay_ms(500);
	}
	return;	
}



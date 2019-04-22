/*
 * External_INT.c
 *
 * Created: 2019-04-22 오후 3:16:49
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

int External_INT_main(void){
	
	while(1){
		
	}
}
void EINT_init_for_HC_SR04(void){
	EICRA |= 1 << ISC00 | 1 << ISC01 | 1 << ISC11; //INT0 rising edge, INT1 falling edge
	EIMSK |= 1 << INT0 | 1 << INT1;		//INT0, INT1 connect to echo pin
	return;
}
/*
 * HC_SR04.c
 *
 * Created: 2019-04-22 오전 10:39:07
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Uart.h"
#include "Timer.h"
#include "HC_SR04.h"
#include "External_INT.h"

char echo_time;

ISR(INT0_vect){
	TCNT0 = 0;
}
ISR(INT1_vect){
	echo_time = TCNT0;
}

int HC_SR04_main(void){
	
	char cm = 0, hight = 0;
	
	HC_SR04_init();
	EINT_init_for_HC_SR04();
	Timer0_HCSR06_init();
	UART0_init(9600);
	sei();
	
	while(1){
		HC_SR04_trigger();
		_delay_ms(1000);
		cm = time_to_cm(echo_time);
		hight = cm_to_hight(cm);
		printf(" distance : %d \n", cm);
	}
}

void HC_SR04_init(void){
	Trg_DDR |= 1 << Trg_pinnum;
	Trg_PORT &= ~(1 << Trg_pinnum);
	return;
}
void HC_SR04_trigger(void){
	Trg_PORT |= 1 << Trg_pinnum;
	_delay_us(10);
	Trg_PORT &= ~(1 << Trg_pinnum);
	return;
}
char time_to_cm(char time){
	char cm = (time+1) * 64 / 59;
	return cm;	
}
char cm_to_hight(char cm){
	char hight = 200 - cm;
	return hight;
}

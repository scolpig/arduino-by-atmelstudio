﻿/*
 * ADC.c
 *
 * Created: 2019-04-24 오전 10:01:26
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Uart.h"
#include "ADC.h"

int ADC_main(void){
	
	int value = 0;
	int distance = 0;
	
	ADC_init();
	UART0_init(9600);
	
	while(1){
		/*value = ADC_converting_value(0);
		printf("Potentiometer : %d.%d%d \t", value/100%10, value/10%10, value%10);
		value = ADC_converting_value(1);
		printf("CDS : %d.%d%d \t", value/100%10, value/10%10, value%10);*/
		//value = ADC_converting_value(2);
		//distance = 20.0 / (value / 100.0 -0.3);
		//distance = 23.7 / (value/100.0 - 0.19);
		distance = volt_to_cm(ADC_converting_value(0));
		printf("Distance : %d", distance);
		//printf("Distance : %d.%d%d \n", distance/100%10, distance/10%10, distance%10);
		_delay_ms(500);
	}
	return 0;
}
int ADC_converting_value(char channel){
	int value = 0;
	ADMUX &= 0b11110000;
	ADMUX |= channel;
	_delay_us(200);
	ADCSRA |= 1 << ADSC;
	while(!(ADCSRA & (1 << ADIF)));
	value = ADCL + ADCH * 256;
	value = (value + 1) * 5 * 100.0 / 1024 + 3 ;
	return value;
}
void ADC_init(void){
	ADMUX |= 1 << REFS0;
	ADCSRA |= 1 << ADEN | 1 << ADPS0 | 1 << ADPS1 | 1 << ADPS2;
	_delay_us(200);
	return;
}
int volt_to_cm(int value){			//SHARP 2Y0A21 적외선 거리센서
	int cm = 0;
	cm = 23.7 / (value/100.0 - 0.19);
	return cm;
}
int volt_to_temperature(int value){   
	//int temp= 0;
	//temp = 2.5 * value + 1.5;
	return 0;
}

/*
 * Timer.c
 *
 * Created: 2019-04-10 오전 11:04:01
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Dot_matrix.h"
#include "FND4digit.h"
#include "Timer.h"

extern char dotmatrix_row[8];
extern char JEONG[8];
extern const char KYOUNG[8];
extern const char YOON[8];
extern char name[3][8];
extern char FND4digit_digit[4];
extern char FND[4];

volatile char start_flag, lap_flag, clear_flag, time_flag;
volatile int msec;
volatile char i, sec, min;

ISR(TIMER0_COMPA_vect){
	
	if(start_flag)msec++;
	if(msec >= 1000){
		msec = 0;
		sec++;
		if(sec >= 60){
			sec = 0;
			min++;
			if(min >= 60)min = 0;
		}
		//FND_clock(sec, min);
	}
	if(!(msec%10)){
		if(lap_flag)time_flag = 1;
	}
	if(clear_flag){
		clear_flag = 0;
		//time_flag = 1;
		FND_update_time(msec, sec);
		msec = 0;
		sec = 0;
		min = 0;
	}
	i++;
	if(i>=4)i=0;
	FND_COM_PORT &= 0b11110000;
	FND_COM_PORT |= FND4digit_digit[i];
	FND_DATA_PORT = FND[i];
	//if(!(msec%500))PORTB ^= 1<<PORTB5;
}

int Timer_main(void){
	char long_key_flag=1; 
	//DDRB |= 1<<PORTB5;
	DDRB &= ~(1<<PORTB4 | 1<<PORTB5);
	FND4digit_init();
	FND_update_value(0);
	Timer0_init();
	sei();
	while(1){
		if(time_flag){
			time_flag = 0;
			FND_update_time(msec, sec);
		}
		if(long_key_flag){
			if(!(PINB & 0b00010000)){
				_delay_us(1);
				if(!(PINB & 0b00010000)){
					start_flag = 1;
					if(lap_flag)lap_flag = 0;
					else lap_flag = 1;
					long_key_flag = 0;
				}
			}
			else if(!(PINB & 0b00100000)){
				_delay_us(1);
				if(!(PINB & 0b00100000)){
					start_flag = 0;
					lap_flag = 0;
					clear_flag = 1;
					long_key_flag = 0;
				}
			}
		}
		else {
			if((PINB & 0b00010000) && (PINB & 0b00100000)){
				long_key_flag = 1;
			}
		}
	}
	return 0;
}
void Timer0_init(void){
	TCCR0A |= 1 << WGM01;            //CTC Mode
	TCCR0B |= 1 << CS00 | 1 << CS01; //64분주
	OCR0A = 249;					 // 1ms 주기
	TIMSK0 |= 1 << OCIE0A;           //OC0A 비교 매치 인터럽트 활성화
	return;
}
void Timer0_HCSR06_init(void){
	TCCR0A |= 1 << WGM01;            //CTC Mode
	TCCR0B |= 1 << CS02 | 1 << CS00; //1024분주
	OCR0A = 255;					
	return;
}
/*
 * FND4digit.c
 *
 * Created: 2019-04-04 오후 4:01:34
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "FND4digit.h"


char FND4digit_font[10] = {
	~(1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_d | 1 << FND_e | 1 << FND_f ),
	~(1 << FND_c | 1<< FND_b),
	~(1 << FND_a | 1 << FND_b | 1 << FND_d | 1 << FND_e | 1 << FND_g),
	~(1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_d | 1 << FND_g),
	~(1 << FND_b | 1 << FND_c | 1 << FND_f | 1 << FND_g),
	~(1 << FND_a | 1 << FND_c | 1 << FND_d | 1 << FND_f | 1 << FND_g),
	~(1 << FND_c | 1 << FND_d | 1 << FND_e | 1 << FND_f | 1 << FND_g),
	~(1 << FND_a | 1 << FND_b | 1 << FND_c ),
	~(1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_d | 1 << FND_e | 1 << FND_f | 1 << FND_g),
	~(1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_f | 1 << FND_g)
};

char FND4digit_digit[4] = {1 << digit1, 1 << digit2, 1 << digit3, 1 << digit4};
char FND[4];

void FND4digit_main(void){
	
	unsigned int number = 5000;
	char sec=0, min=0;
	int msec=0;
	char long_key_flag=1, start_flag=0, lap_flag=0;
	
	FND4digit_init();
	DDRB &= 0b11001111;
	FND_update_time(msec, sec);
	while(1){
		if(long_key_flag){
			if(!(PINB & 0b00010000)){
				if(!start_flag)start_flag=1;
				if(lap_flag)lap_flag=0;
				else lap_flag=1;
				long_key_flag = 0;
			}
			else if(!(PINB & 0b00100000)){
				FND_update_time(msec, sec);
				msec = 0;
				sec = 0;
				start_flag = 0;
				lap_flag=0;
				long_key_flag = 0;
			}
		}
		else {
			if((PINB & 0b00010000) && (PINB & 0b00100000)){
				long_key_flag = 1;
			}
		}
		if(start_flag){
			msec = msec + 8;
			if(msec >= 1000){
				msec=0;
				sec++;
				if(sec >= 60){
					sec=0;
					min++;
					if(min >= 60){
						min = 0;
					}
				}
			}
			if(lap_flag)FND_update_time(msec, sec);
		}
		for(int i=0;i<4;i++){
			FND_COM_PORT = FND4digit_digit[i];
			FND_DATA_PORT = FND[i];
			_delay_ms(2);
		}
	
	}
}
void FND_update_value(int number){
	FND[0] = FND4digit_font[number%10];
	FND[1] = FND4digit_font[number/10%10];
	FND[2] = FND4digit_font[number/100%10];
	FND[3] = FND4digit_font[number/1000%10];
	return;
}
void FND_update_time(int msec, char sec){
	FND[0] = FND4digit_font[msec/10%10];
	FND[1] = FND4digit_font[msec/100%10];
	FND[2] = FND4digit_font[sec%10] & ~(1 << FND_p);
	FND[3] = FND4digit_font[sec/10%10];
	return;
}
void FND_clock(char sec, char min){
	FND[0] = FND4digit_font[sec%10];
	FND[1] = FND4digit_font[sec/10%10];
	FND[2] = FND4digit_font[min%10] & ~(1 << FND_p);
	FND[3] = FND4digit_font[min/10%10];
	return;
}
void FND4digit_init(void){
	FND_COM_DDR |= 0b00001111;
	FND_COM_PORT &= 0b11110000;
	FND_DATA_DDR |= 0b11111111;
	FND_DATA_PORT |= 0b11111111;
	return;
}
void FND4digit_test(void){
	for(int j=0;j<4;j++){
		FND_COM_PORT = FND4digit_digit[j];
		for(int i=0;i<10;i++){
			FND_DATA_PORT = FND4digit_font[i];
			_delay_ms(500);
		}
	}
	
	return;
}
/*
 * FND.c
 *
 * Created: 2019-04-04 오전 11:57:20
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "FND.h"

char FND_font[10] = {
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

void FND_main(){
	
	FND_init();
	//FND_PORT = FND_PORT & ~(1 << FND_c); 
	//FND_PORT &= ~(1 << FND_c); 
	while(1){
		FND_test();
	}
}
void FND_init(void){
	FND_DDR = 0b11111111;
	FND_PORT = 0b11111111;
	return;
}
void FND_test(void){
	
	for(int i=0;i<10;i++){
		FND_PORT = FND_font[i];
		_delay_ms(500);
	}
	return;
}
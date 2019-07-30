/*
 * Dot_matrix_74595.c
 *
 * Created: 2019-07-30 오전 10:00:24
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Dot_matrix_74595.h"
#include "Timer.h"

extern char JEONG[8];
extern const char KYOUNG[8];
extern const char YOON[8];

uint8_t dotmatrix[8];			//가상의 DotMatrix
uint8_t dotmatrixdata[8];		//데이터 조작을 위한 임시 데이터


int Dot_matrix_74595_main(void){
	
	Dotmatrix_init_74595();
	Timer0_init();
	sei();
	
	while(1){
		for(int i=0;i<8;i++){
			dotmatrix[i] = JEONG[i];
		}
		_delay_ms(1000);
		for(int i=0;i<8;i++){
			dotmatrix[i] = KYOUNG[i];
		}
		_delay_ms(1000);
		for(int i=0;i<8;i++){
			dotmatrix[i] = YOON[i];
		}
		_delay_ms(1000);
		
	}
}
void Dotmatrix_init_74595(void){
	
	Dotmatrix_74595_DDR |= 1 << RClk | 1 << SRClk | 1 << SER;
	Dotmatrix_74595_PORT |= 1 << RClk;
	for(int i=0;i<8;i++){
		dotmatrix[i] = 0xff;
	}
	return;
}
void Dotmatrix_74595_out(uint8_t data, uint8_t row){
	Dotmatrix_74595_PORT &= ~(1 << RClk);
	for(int i=0;i<8;i++){
		Dotmatrix_74595_PORT &= ~(1 << SRClk);
		Dotmatrix_74595_PORT &= ~(1 << SER);
		Dotmatrix_74595_PORT |= ((data>>i) & 1) << SER;
		Dotmatrix_74595_PORT |= 1 << SRClk;
	}
	for(int i=0;i<8;i++){
		Dotmatrix_74595_PORT &= ~(1 << SRClk);
		Dotmatrix_74595_PORT &= ~(1 << SER);
		Dotmatrix_74595_PORT |= ((row>>i) & 1) << SER;
		Dotmatrix_74595_PORT |= 1 << SRClk;
	}
	Dotmatrix_74595_PORT |= 1 << RClk;
	return;
}
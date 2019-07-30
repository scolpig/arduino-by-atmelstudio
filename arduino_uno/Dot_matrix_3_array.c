/*
 * Dot_matrix_3_array.c
 *
 * Created: 2019-07-29 오후 1:36:24
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Dot_matrix_3_array.h"
#include "Timer.h"

extern char JEONG[8];
extern const char KYOUNG[8];
extern const char YOON[8];

uint32_t dotmatrix3ary[8];			//가상의 DotMatrix
uint32_t dotmatrix3arydata[8];		//데이터 조작을 위한 임시 데이터
						

int DotmatrixArry_main(void){
	
	Dotmatrix_init_shiftR();
	
	for(int i=0;i<8;i++){
		dotmatrix3arydata[i] = 0xffffffff;
		dotmatrix3arydata[i] = (dotmatrix3arydata[i]<<8) | JEONG[i];
		
		dotmatrix3arydata[i] = (dotmatrix3arydata[i]<<8) | KYOUNG[i];
		
		dotmatrix3arydata[i] = (dotmatrix3arydata[i]<<8) | YOON[i];
		
	}
	for(int i=0;i<8;i++){
		dotmatrix3ary[i] = 0x01000000 << i | dotmatrix3arydata[i];
	}
	
	Timer0_init();
	sei();
	
	while(1){
		Dotmatrix_left_countinue();
		/*Dotmatrix_flow_left_out();
		Dotmatrix_flow_left_in();
		Dotmatrix_flow_right_out();
		Dotmatrix_flow_right_in();*/
		
		//Dotmatrix_shift_out(1);
		/*for(int i=0;i<8;i++){
			Dotmatrix_shift_out(dotmatrix[i]);
			_delay_ms(2);
		}*/
	}
}
void Dotmatrix_left_countinue(void){
	for(int j=0;j<24;j++){
		for(int i=0;i<8;i++){
			dotmatrix3ary[i] =	(0x01000000 << i) | ((~(~dotmatrix3arydata[i] << j) & 0x00ffffff) & 
							(~(~dotmatrix3arydata[i] >> (24-j)) & 0x00ffffff));
		}
		_delay_ms(100);
	}
}
void Dotmatrix_flow_left_out(void){
	for(int j=0;j<24;j++){
		for(int i=0;i<8;i++){
			dotmatrix3ary[i] = (0x01000000 << i) | ((~(~dotmatrix3arydata[i] << j) & 0x00ffffff));
		}
		_delay_ms(100);
	}
}
void Dotmatrix_flow_left_in(void){
	for(int j=0;j<24;j++){
		for(int i=0;i<8;i++){
			dotmatrix3ary[i] = (0x01000000 << i) | ((~(~dotmatrix3arydata[i] >> (23-j)) & 0x00ffffff));
		}
		_delay_ms(100);
	}
}
void Dotmatrix_flow_right_out(void){
	for(int j=0;j<24;j++){
		for(int i=0;i<8;i++){
			dotmatrix3ary[i] = (0x01000000 << i) | ((~(~dotmatrix3arydata[i] >> j) & 0x00ffffff));
		}
		_delay_ms(100);
	}
}
void Dotmatrix_flow_right_in(void){
	for(int j=0;j<24;j++){
		for(int i=0;i<8;i++){
			dotmatrix3ary[i] = (0x01000000 << i) | ((~(~dotmatrix3arydata[i] << (23-j)) & 0x00ffffff));
		}
		_delay_ms(100);
	}
}
void Dotmatrix_init_shiftR(void){
	
	Dotmatrix_shiftR_DDR |= 1 << RClk | 1 << SRClk | 1 << SER;
	Dotmatrix_shiftR_PORT |= 1 << RClk;
	for(int i=0;i<8;i++){
		dotmatrix3ary[i] = 0;
	}
	return;
}
void Dotmatrix_shift_out(uint32_t data){
	Dotmatrix_shiftR_PORT &= ~(1 << RClk);
	for(int i=0;i<32;i++){
		Dotmatrix_shiftR_PORT &= ~(1 << SRClk);
		Dotmatrix_shiftR_PORT &= ~(1 << SER);
		Dotmatrix_shiftR_PORT |= ((data>>i) & 1) << SER;
		Dotmatrix_shiftR_PORT |= 1 << SRClk;
	}
	Dotmatrix_shiftR_PORT |= 1 << RClk;
	return;
}
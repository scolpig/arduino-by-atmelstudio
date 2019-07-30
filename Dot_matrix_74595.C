#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "Dot_matrix74595.h"
#include "Timer.h"

extern char JEONG[8];
extern const char KYOUNG[8];
extern const char YOON[8];

uint8_t dotmatrix[8];			//가상의 DotMatrix
uint8_t dotmatrixdata[8];		//데이터 조작을 위한 임시 데이터


int DotmatrixArry_main(void){
	
	while(1){
		
	}
}
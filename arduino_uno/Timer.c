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

extern char dotmatrix_row[8];
extern char JEONG[8];
extern const char KYOUNG[8];
extern const char YOON[8];
extern char name[3][8];
extern char FND4digit_digit[4];
extern char FND[4];

ISR(TIMER0_COMPA_vect){
	static int msec = 0;
	static char i = 0;
	msec++;
	i++;
	if(i>=4)i=0;
	FND_COM_PORT = FND4digit_digit[i];
	FND_DATA_PORT = FND[i];
	if(!(msec%500))PORTB ^= 1<<PORTB5;
}

int Timer_main(void){
	int msec = 0;
	char sec = 0;
	DDRB |= 1<<PORTB5;
	FND4digit_init();
	FND_update_value(1234);
	Timer0_init();
	sei();
	while(1){
		_delay_ms(1);
		msec++;
		if(msec >= 1000){
			msec = 0;
			sec++;
		}
		FND_update_time(msec, sec);
		/*dotmatrix_flow_buffer(name, 3);
		for(int i=0;i<3;i++){
			dotmatrix_update(name[i]);
			_delay_ms(500);
		}*/
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
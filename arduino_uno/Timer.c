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
#include <avr/eeprom.h>
#include "FND4digit.h"
#include "Timer.h"
#include "DHT11.h"

extern char dotmatrix_row[8];
extern char JEONG[8];
extern const char KYOUNG[8];
extern const char YOON[8];
extern uint32_t dotmatrix3ary[8];
extern uint8_t dotmatrix[8];
extern char name[3][8];
extern char FND4digit_digit[4];
extern char FND[4];
extern char FND4digit_font[10];

extern void Dotmatrix_shift_out(uint32_t data);
extern void Dotmatrix_74595_out(uint8_t data, uint8_t row);
volatile char start_flag=1, lap_flag, clear_flag, time_flag, countdown_flag;
volatile char speakout_flag;
volatile int msec;
volatile char i, sec, min, cook_sec, cook_min;

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
	/*** FND에 시간 출력
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
	}*/
	/***** FND 출력 
	i++;
	if(i>=4)i=0;
	FND_COM_PORT &= 0b00001111;
	FND_shift_out(FND[i]);
	FND_COM_PORT |= FND4digit_digit[i];*/
	
	/*  /// ** Dot Matrix 3개 Array 출력 
	i++;
	if(i>7)i=0;
	Dotmatrix_shift_out(dotmatrix3ary[i]);
	*/
	
	i++;
	if(i>7)i=0;
	Dotmatrix_74595_out(dotmatrix[i], 1<<i);
		
	if(!(msec%500))PORTB ^= 1<<PORTB5;	// On Board Led Toggle
}

int Timer_main(void){
	int red=0, blue=0;
	char green = 0;
	char tmpr = 0, old_tmpr = 0;
	char count = 0;
	char red_up_down_flag = 1;
	char blue_up_down_flag = 1;
	char green_up_down_flag = 1;
	Timer1_init_fast_PWM_outA_SurvoMotor();
	Timer2_init_fast_PWM_outA();
	Timer0_init();
	FND4digit_init_shiftR();
	DHT11_init();
	sei();
	char byA;
	//byA = 180;
	//eeprom_update_byte((uint8_t*)46, byA);
	OCR1A = 160;
	FND_update_value(OCR1A);
	_delay_ms(2000);
	byA = eeprom_read_byte((const uint8_t*)46);
	
	
	while(1){
		count++;
		if(count >=200){
			count = 0;
			old_tmpr = tmpr;
			tmpr = getTemperature();
			if(tmpr != 255){
				FND_update_value(tmpr);
				OCR1A = tmpr * 8 / 11 + 142;
			}
			else {
				FND_update_value(old_tmpr + 1000);
				tmpr = old_tmpr;
			}
		}
		if(green_up_down_flag){
			green += 4;
			if(green >= 150)green_up_down_flag = 0;
		}
		else {
			green -= 4;
			if(green <= 0)green_up_down_flag = 1;
		}
		if(red_up_down_flag){
			red++;
			if(red >= 250)red_up_down_flag = 0;
		}
		else {
			red--;
			if(red <= 0)red_up_down_flag = 1;
		}
		if(blue_up_down_flag){
			blue += 2;
			if(blue >= 150)blue_up_down_flag = 0;
		}
		else {
			blue -= 2;
			if(blue <= 0)blue_up_down_flag = 1;
		}
		//OCR1A = 180;
		//OCR1B = blue;
		//OCR2A = green;
		OCR1A = byA;
		FND_update_value(OCR1A);
		
		_delay_ms(30);
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
void Timer1_init_CTC_outA(void){
	DDRB |= 1 << PORTB1;
	TCCR1A |= 1 << COM1A0;				//CTC Mode
	TCCR1B |= 1 << WGM12 | 1 << CS11;	//8분주
	OCR1A = 0;							// 소리 끄기
	return;
}
void Timer1_init_fast_PWM_outA(void){
	DDRB |= 1 << PORTB1 | 1 << PORTB2;
	TCCR1A |= 1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0 | 1 << WGM11;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS10;
	
	OCR1A = 0;
	OCR1B = 0;
	ICR1 = 255;
}
void Timer2_init_fast_PWM_outA(void){
	DDRB |= 1 << PORTB3;
	TCCR2A |= 1 << COM2A1 | 1 << COM2A0 | 1 << WGM21 | 1 << WGM20;
	TCCR2B |= 1 << CS20;

	OCR2A = 0;
}
void Timer1_init_fast_PWM_outA_SurvoMotor(void){
	DDRB |= 1 << PORTB1 | 1 << PORTB2;
	TCCR1A |= 1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0 | 1 << WGM11;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS12;
	
	OCR1A = 0;
	OCR1B = 0;
	ICR1 = 255;
}
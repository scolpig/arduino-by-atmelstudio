/*
 * Uart.c
 *
 * Created: 2019-04-16 오전 10:09:13
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>

void TX0_char(char data);
void UART0_init(unsigned long baud);
void TX0_string(char *string);

int Uart_main(void){
	
	char i, long_key_flag = 0;
	
	FILE* fpStdio = fdevopen(TX0_char, NULL);
	
	UCSR0B |= 1 << RXCIE0 | 1 << RXEN0 | 1 << TXEN0;
	UCSR0C |= 1 << UCSZ00 | 1 << UCSZ01;
	
	UBRR0H = (F_CPU/16/9600-1)>>8;
	UBRR0L = (F_CPU/16/9600-1) & 0xFF;
	i = UDR0;
	_delay_ms(1);
	
	while(1){
		
		if(long_key_flag){
			if(!(PINB & 0b00010000)){
				TX0_char('1');
				long_key_flag = 0;
			}
			else if(!(PINB & 0b00100000)){
				TX0_char('2');
				long_key_flag = 0;
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
void TX0_char(char data){
	while(!(UCSR0A & 1 << UDRE0));
	UDR0 = data;
}
void TX0_string(char *string){
	while(*string){
		TX0_char(*string);
		string++;
	}
	return;
}
void TX0_4Digit(int data){
	TX0_char('0' + data/1000%10);
	TX0_char('0' + data/100%10);
	TX0_char('0' + data/10%10);
	TX0_char('0' + data%10);
	return;
}
void UART0_init(unsigned long baud){
	FILE* fpStdio = fdevopen(TX0_char, NULL);
	char i;
	UCSR0B |= 1 << RXCIE0 | 1 << RXEN0 | 1 << TXEN0; //송신, 수신, 수신 인터럽트 활성화
	UCSR0C |= 1 << UCSZ00 | 1 << UCSZ01;			 //8비트 통신
	
	UBRR0H = (F_CPU/16/baud-1) >> 8;
	UBRR0L = (F_CPU/16/baud-1) & 0xFF;
	i = UDR0;
	_delay_ms(1);
	return;
}
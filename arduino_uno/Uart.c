/*
 * Uart.c
 *
 * Created: 2019-04-16 오전 10:09:13
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "Uart.h"

#define BUFFER_MAX 50
#define COMMAND_MAX 10

volatile char RX_data;
volatile char RX_flag, RX_cmd_count ;

char buffer[COMMAND_MAX][BUFFER_MAX];

ISR(USART_RX_vect){
	static char idx = 0, buf_idx=0;
	RX_data = UDR0;
	if(idx < BUFFER_MAX && RX_cmd_count <= COMMAND_MAX){
		if(RX_data == '\n'){
			buffer[buf_idx][idx] = '\0';
			idx = 0;
			RX_cmd_count++;
						
			buf_idx++;
			buf_idx = buf_idx % COMMAND_MAX;
		}
		else buffer[buf_idx][idx++] = RX_data;
	}
	TX0_char(RX_data);
	RX_flag = 1;
}

int Uart_main(void){
	
	char i, long_key_flag = 0;
	char cmd_idx = 0;
	UART0_init(9600);
	_delay_ms(1);
	DDRB |= 1 << PORTB2 | 1 << PORTB3 | 1 << PORTB4 | 1 << PORTB5;
	PORTB &= ~(1 << PORTB2 | 1 << PORTB3 | 1 << PORTB4 | 1 << PORTB5);
	sei();
	
	while(1){
		
		if(RX_cmd_count){
			RX_cmd_count--;
			if(!strcmp(buffer[cmd_idx],"led on")){
				PORTB |= 1 << PORTB5;
			}
			else if(!strcmp(buffer[cmd_idx],"led off")){
				PORTB &= ~(1 << PORTB5);
			}
			else if(!strcmp(buffer[cmd_idx],"led toggle")){
				PORTB ^= 1 << PORTB5;
			}
			else if(!strcmp(buffer[cmd_idx],"light toggle")){
				PORTB ^= 1 << PORTB2;
			}
			else if(!strcmp(buffer[cmd_idx],"fan toggle")){
				PORTB ^= 1 << PORTB3;
			}
			else if(!strcmp(buffer[cmd_idx],"blind toggle")){
				PORTB ^= 1 << PORTB4;
			}
			else if(!strcmp(buffer[cmd_idx],"valve toggle")){
				PORTB ^= 1 << PORTB5;
			}
			//_delay_ms(1000);
			cmd_idx++;
			cmd_idx = cmd_idx % COMMAND_MAX;
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

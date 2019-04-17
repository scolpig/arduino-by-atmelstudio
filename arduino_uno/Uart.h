/*
 * Uart.h
 *
 * Created: 2019-04-17 오전 9:49:29
 *  Author: scolpig
 */ 


#ifndef UART_H_
#define UART_H_

void UART0_init(unsigned long baud);
void TX0_char(char data);
void TX0_string(char *string);
void TX0_4Digit(int data);

#endif /* UART_H_ */
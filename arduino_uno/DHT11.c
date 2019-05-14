/*
 * DHT11.c
 *
 * Created: 2019-04-22 오후 3:59:57
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Uart.h"
#include "DHT11.h"

int DHT11_main(void){
	char RH_integral = 0 ,RH_decimal = 0, Tmpr_integral= 0, Tmpr_decimal = 0;
	DHT11_init();
	UART0_init(9600);
	
	while(1){
		
		DHT11_trigger();
		DHT11_data_input();
		dumi_read();
		RH_integral = DHT11_rx_byte();
		RH_decimal = DHT11_rx_byte();
		Tmpr_integral = DHT11_rx_byte();
		Tmpr_decimal = DHT11_rx_byte();
		DHT11_rx_byte();
		DHT11_data_output();
		_delay_ms(1500);
		
		printf("RH : %d.%d       ", RH_integral, RH_decimal);
		printf("Temperature : %d.%d \n", Tmpr_integral, Tmpr_decimal);
	}
	return 0;
}
char getTemperature(void){
	char RH_integral = 0 ,RH_decimal = 0, Tmpr_integral= 0, Tmpr_decimal = 0;
	DHT11_trigger();
	DHT11_data_input();
	dumi_read();
	RH_integral = DHT11_rx_byte();
	RH_decimal = DHT11_rx_byte();
	Tmpr_integral = DHT11_rx_byte();
	Tmpr_decimal = DHT11_rx_byte();
	DHT11_rx_byte();
	DHT11_data_output();
	//_delay_ms(1500);			//호출 후 1.5초 후에 재호출 가능
	return Tmpr_integral;
}
char getHumi(void){
	char RH_integral = 0 ,RH_decimal = 0, Tmpr_integral= 0, Tmpr_decimal = 0;
	DHT11_trigger();
	DHT11_data_input();
	dumi_read();
	RH_integral = DHT11_rx_byte();
	RH_decimal = DHT11_rx_byte();
	Tmpr_integral = DHT11_rx_byte();
	Tmpr_decimal = DHT11_rx_byte();
	DHT11_rx_byte();
	DHT11_data_output();
	DHT11_data_PORT |= 1 << DHT11_datapin;
	//_delay_ms(1500);			//호출 후 1.5초 후에 재호출 가능
	return RH_integral;
}
char DHT11_rx_byte(void){
	char data = 0;
	int count = 0;
	for(int i=0;i<8;i++){
		while(!(DHT11_data_PIN & (1 << DHT11_datapin))){
			_delay_us(1);
			count++;
			if(count >= 200)break;
		}
		if(count >= 200)break;
		count = 0;
		_delay_us(30);
		data <<= 1;
		if(DHT11_data_PIN & (1 << DHT11_datapin)){
			data |= 0b00000001;
		}
		while(DHT11_data_PIN & (1 << DHT11_datapin)){
			_delay_us(1);
			count++;
			if(count >= 2000)break;
		}
		if(count >= 200)break;
		count = 0;
	}
	if(count >= 200)return 255;
	return data;
}
void DHT11_data_output(void){
	DHT11_data_DDR |= 1 << DHT11_datapin;
	DHT11_data_PORT |= 1 << DHT11_datapin;
	return;
}
void DHT11_data_input(void){
	DHT11_data_DDR &= ~(1 << DHT11_datapin);
	return;
}
void DHT11_init(void){
	DHT11_data_DDR |= 1 << DHT11_datapin;
	DHT11_data_PORT |= 1 << DHT11_datapin;
	_delay_ms(1500);
	return;
}
void dumi_read(void){
	int count = 0;
	while(DHT11_data_PIN & (1 << DHT11_datapin))
	{
		_delay_us(1);
		count++;
		if(count >= 200)break;
	}
	count = 0;
	while(!(DHT11_data_PIN & (1 << DHT11_datapin))){
		_delay_us(1);
		count++;
		if(count >= 200)break;
	}
	count = 0;
	while(DHT11_data_PIN & (1 << DHT11_datapin)){
		_delay_us(1);
		count++;
		if(count >= 200)break;
	}
	return;
}
void DHT11_trigger(void){
	DHT11_data_PORT &= ~(1 << DHT11_datapin);
	_delay_ms(20);
	DHT11_data_PORT |= 1 << DHT11_datapin;
	_delay_us(5);
	return;
}


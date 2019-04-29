/*
 * measure.c
 *
 * Created: 2019-04-24 오후 2:15:27
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Keypad.h"
#include "DHT11.h"
#include "Uart.h"
#include "ADC.h"

int measure_main(void){
	
	char long_key_flag = 0;
	char RH_integral=0, RH_decimal=0, Tmpr_integral=0, Tmpr_decimal=0;
	int value=0;
	
	Keypad_init();
	UART0_init(9600);
	DHT11_init();
	ADC_init();
	
	while(1){
		if(long_key_flag){
			if(Keyscan() != 'A'){
				//TX0_char(Keyscan());
				if(Keyscan() == 'B'){
					DHT11_trigger();
					DHT11_data_input();
					dumi_read();
					RH_integral = DHT11_rx_byte();
					RH_decimal = DHT11_rx_byte();
					Tmpr_integral = DHT11_rx_byte();
					Tmpr_decimal = DHT11_rx_byte();
					DHT11_rx_byte();
					DHT11_data_output();
					printf("RH : %d.%d%% \n", RH_integral, RH_decimal);
					_delay_ms(1500);
					long_key_flag = 0;
				}
				else if(Keyscan() == 'C'){
					DHT11_trigger();
					DHT11_data_input();
					dumi_read();
					RH_integral = DHT11_rx_byte();
					RH_decimal = DHT11_rx_byte();
					Tmpr_integral = DHT11_rx_byte();
					Tmpr_decimal = DHT11_rx_byte();
					DHT11_rx_byte();
					DHT11_data_output();
					printf("Temperature : %d.%d", Tmpr_integral, Tmpr_decimal);
					TX0_char(39);
					TX0_char('C');
					TX0_char('\n');
					_delay_ms(1500);
					long_key_flag = 0;
				}
				else if(Keyscan() == 'D'){
					value = ADC_converting_value(0);
					printf("Potentiometer : %d.%d%dV \n", value/100%10, value/10%10, value%10);
					long_key_flag = 0;
				}
				else if(Keyscan() == 'E'){
					value = ADC_converting_value(1);
					printf("CDS value : %d.%d%dV \n", value/100%10, value/10%10, value%10);
					long_key_flag = 0;
				}
				else if(Keyscan() == 'F'){
					value = ADC_converting_value(2);
					printf("Distance : %d.%d%dV \n", value/100%10, value/10%10, value%10);
					long_key_flag = 0;
				}
			}
		}
		else {
			if(Keyscan() == 'A'){
				long_key_flag = 1;
			}
		}
	}
	return 0;
}

/*
 * DHT11.h
 *
 * Created: 2019-04-23 오후 4:19:25
 *  Author: scolpig
 */ 


#ifndef DHT11_H_
#define DHT11_H_

#define DHT11_data_DDR DDRB
#define DHT11_data_PORT PORTB
#define DHT11_data_PIN PINB
#define DHT11_datapin PORTB4

char DHT11_rx_byte(void);
void DHT11_data_output(void);
void DHT11_data_input(void);
void DHT11_init(void);
void dumi_read(void);
void DHT11_trigger(void);
char getTemperature(void);		//호출 후 1.5초 후에 재호출 가능
char getHumi(void);				//호출 후 1.5초 후에 재호출 가능

#endif /* DHT11_H_ */
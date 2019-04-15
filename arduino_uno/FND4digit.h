/*
 * FND4digit.h
 *
 * Created: 2019-04-05 오후 2:52:45
 *  Author: scolpig
 */ 


#ifndef FND4DIGIT_H_
#define FND4DIGIT_H_

#define FND_DATA_DDR DDRD
#define FND_DATA_PORT PORTD
#define FND_COM_DDR DDRB
#define FND_COM_PORT PORTB
#define FND_g 0
#define FND_c 1
#define FND_p 2
#define FND_d 3
#define FND_e 4
#define FND_a 5
#define FND_f 6
#define FND_b 7
#define digit4 0
#define digit3 2
#define digit2 1
#define digit1 3

void FND4digit_init(void);
void FND4digit_test(void);
void FND_update_value(int number);
void FND_update_time(int msec, char sec);
void FND_clock(char sec, char min);

#endif /* FND4DIGIT_H_ */
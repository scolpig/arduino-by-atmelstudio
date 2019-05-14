/*
 * FND4digit.h
 *
 * Created: 2019-04-05 오후 2:52:45
 *  Author: scolpig
 */ 


#ifndef FND4DIGIT_H_
#define FND4DIGIT_H_

#define FND_DATA_DDR DDRC
#define FND_DATA_PORT PORTC
#define FND_COM_DDR DDRD
#define FND_COM_PORT PORTD
#define FND_b 0
#define FND_f 1
#define FND_a 2
#define FND_e 3
#define FND_d 4
#define FND_p 5
#define FND_c 6
#define FND_g 7
#define digit4 6
#define digit3 5
#define digit2 4
#define digit1 7
#define RClk PORTC4
#define SRClk PORTC5
#define SER PORTC3

void FND4digit_init(void);
void FND4digit_test(void);
void FND_update_value(int number);
void FND_update_time(int msec, char sec);
void FND_clock(char sec, char min);
void FND4digit_init_shiftR(void);
void FND_shift_out(char data);
void FND4digit_shiftR_test(void);

#endif /* FND4DIGIT_H_ */
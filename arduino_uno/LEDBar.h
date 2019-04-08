/*
 * LEDBar.h
 *
 * Created: 2019-04-04 오전 10:41:53
 *  Author: scolpig
 */ 


#ifndef LEDBAR_H_
#define LEDBAR_H_
#define LEDBar_DDR DDRD
#define LEDBar_PORT PORTD

void Ledbar_init(void);
void Led_up_down(void);
void Led_on_up(void);
void Led_on_down(void);
void Led_off_up(void);
void Led_off_down(void);
void Led_toggle_center(void);

#endif /* LEDBAR_H_ */
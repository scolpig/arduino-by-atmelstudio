/*
 * HC_SR04.h
 *
 * Created: 2019-04-22 오후 2:53:04
 *  Author: scolpig
 */ 


#ifndef HC_SR04_H_
#define HC_SR04_H_

#define Trg_DDR DDRB
#define Trg_pinnum 4
#define Trg_PORT PORTB

void HC_SR04_init(void);
void HC_SR04_trigger(void);
char time_to_cm(char time);
char cm_to_hight(char cm);

#endif /* HC_SR04_H_ */
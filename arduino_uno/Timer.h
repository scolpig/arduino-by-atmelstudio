﻿/*
 * Timer.h
 *
 * Created: 2019-04-15 오후 3:36:21
 *  Author: scolpig
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void Timer0_init(void);
void Timer0_HCSR06_init(void);
void Timer1_init_CTC_outA(void);
void Timer1_init_fast_PWM_outA(void);
void Timer2_init_fast_PWM_outA(void);
void Timer1_init_fast_PWM_outA_SurvoMotor(void);

#endif /* TIMER_H_ */
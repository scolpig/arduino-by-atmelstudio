﻿/*
 * Speaker.c
 *
 * Created: 2019-04-29 오후 3:17:38
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Timer.h"
#include "Speaker.h"

int doremi[] = {DO_07, RE_07, MI_07, FA_07, SO_07, LA_07 , SI_07};
int He_Pirate[] = 
{
	RE_04, RE_04, RE_04, RE_04,
	RE_04, RE_04, RE_04, LA_03, DO_04,
	RE_04, RE_04, RE_04, MI_04,
	FA_04, FA_04, FA_04, SO_04,
	MI_04, MI_04, RE_04, DO_04,
	DO_04, RE_04, 0, LA_03, DO_04,
	RE_04, RE_04, RE_04, MI_04,
	FA_04, FA_04, FA_04, SO_04,
	MI_04, MI_04, RE_04, DO_04,
	RE_04, 0, 0, LA_03, DO_04,
	RE_04, RE_04, RE_04, FA_04,
	SO_04, SO_04, SO_04, LA_04,
	LA_04s, LA_04s, LA_04, SO_04,
	
	LA_04, RE_04, 0, RE_04, MI_04,
	FA_04, FA_04, SO_04,
	LA_04, RE_04, 0, RE_04, FA_04,
	MI_04, MI_04, FA_04, RE_04,
	MI_04, 0, 0, LA_04, DO_07,
	RE_07, RE_07, RE_07, MI_07,
	FA_07, FA_07, FA_07, SO_07,
	MI_07, MI_07, RE_07, DO_07,
	DO_07, RE_07, 0, LA_04, DO_07,
	RE_07, RE_07, RE_07, MI_07,
	FA_07, FA_07, FA_07, SO_07,
	MI_07, MI_07, RE_07, DO_07,
	RE_07, 0, 0, LA_04, DO_07,
	RE_07, RE_07, RE_07, FA_07,
	SO_07, SO_07, SO_07, LA_07,
	LA_07s, LA_07s, LA_07, SO_07,
	LA_07, RE_07, 0, RE_07, MI_07,
	FA_07, FA_07, SO_07,
	LA_07, RE_07, 0, RE_07, FA_07,
	MI_07, MI_07, RE_07, DO_07,
	RE_07, RE_07, MI_07,
	
	FA_07, FA_07, FA_07, SO_07,
	LA_07, FA_07, 0, 0, FA_07, RE_07,
	LA_04, 0, 0, 0,
	LA_04s, 0, 0, SO_07, RE_07,
	LA_04s, 0, 0, 0,
	MI_07, MI_07, RE_07,
	FA_04, 0, FA_04, SO_04,
	LA_04, LA_04, LA_04,
	LA_04s, LA_04,0 , 0,
	SO_04, SO_04, SO_04,
	SO_04, LA_04, 0, 0,
	LA_04, LA_04, LA_04,
	LA_04s, LA_04, 0, 0,
	SO_04, FA_04, MI_04,
	RE_04, 0, 0, RE_04, MI_04,
	FA_04, SO_04, LA_04,
	SO_04, FA_04, MI_04,
	FA_04, SO_04, LA_04,
	SO_04, 0, 0, FA_04, SO_04,
	LA_04, 0, 0, SO_04, FA_04,
	MI_04, FA_04, MI_04,
	RE_04, 0, 0, MI_04, DO_04,
	RE_04, 0, 0, RE_07, MI_07,
	
	FA_07, 0, 0, MI_07, FA_07,
	SO_07, FA_07, SO_07,
	LA_07, SO_07, FA_07,
	RE_07, 0, 0, RE_07, MI_07,
	FA_07, SO_07, LA_07,
	LA_07s, RE_07, SO_07,
	FA_07, 0, 0, SO_07, MI_07,
	RE_07, 0, 0, MI_07, DO_07s,
	LA_07, 0, 0, LA_07s, 0, 0,
	LA_07, LA_07, LA_07,
	LA_07, SO_07, 0, 0,
	SO_07, 0, 0,
	FA_07, 0, 0,
	FA_07, SO_07, MI_07,
	RE_07, RE_07, MI_07, FA_07,
	LA_07, RE_07, MI_07, FA_07,
	LA_07s, RE_07, MI_07, FA_07,
	LA_07, LA_07, DO_06,
	LA_07, SO_07, 0, 0,
	SO_07, 0, 0,
	FA_07, 0, 0,
	FA_07, SO_07, MI_07,
	RE_07, 0, 0,
	RE_04, '/0'
};
int He_Pirate_Beat[] = 
{
	BEAT_1_4, BEAT_1_8, BEAT_1_4, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_16, BEAT_1_16, BEAT_1_16,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_2,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_2, BEAT_1_8, BEAT_1_4,
	BEAT_1
};
int school_bell_tune[] =				//학교종
{
	SO_07, SO_07, LA_07, LA_07, SO_07, SO_07, MI_07,
	SO_07, SO_07, MI_07, MI_07, RE_07,
	SO_07, SO_07, LA_07, LA_07, SO_07, SO_07, MI_07,
	SO_07, MI_07, RE_07, MI_07, DO_07, '/0'
};
int school_bell_beat[] = {
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1
};
int Elise_Tune[] =						//엘리제를 위하여
{
	MI_06, RE_06s, MI_06, RE_06s, MI_06, SI_05, RE_06, DO_06, LA_05, 0,
	DO_05, MI_05, LA_05, SI_05, 0, MI_05, SO_05s, SI_05, DO_06, 0,
	MI_05, MI_06, RE_06s, MI_06, RE_06s, MI_06, SI_05, RE_06, DO_06, LA_05, 0,
	DO_05, MI_05, LA_05, SI_05, 0, MI_05, DO_06, SI_05, LA_05,
	MI_06, RE_06s, MI_06, RE_06s, MI_06, SI_05, RE_06, DO_06, LA_05, 0,
	DO_05, MI_05, LA_05, SI_05, 0, MI_05, SO_05s, SI_05, DO_06, 0,
	MI_05, MI_06, RE_06s, MI_06, RE_06s, MI_06, SI_05, RE_06, DO_06, LA_05, 0,
	DO_05, MI_05, LA_05, SI_05, 0, MI_05, DO_06, SI_05, LA_05, 0,
	SI_05, DO_06, RE_06, MI_06, 0, SO_05, FA_06, MI_06, RE_06, 0, FA_05, MI_06, RE_06, DO_06, 0,
	MI_05, RE_06, DO_06, SI_05, 0, MI_05, MI_06, MI_03,
	RE_06s, MI_06, RE_06s, MI_06, RE_06, MI_06, RE_05s, MI_06, SI_05, RE_05, DO_06, LA_05, 0,
	DO_05, MI_05, LA_05, SI_05, 0, MI_05, SO_05s, SI_05, DO_06, 0,
	MI_05, MI_06, RE_06s, MI_06, RE_06s, MI_06, SI_05, RE_06, DO_06, LA_05, 0, DO_05, MI_05, LA_05, SI_05, 0,
	RE_05, DO_06, SI_05, LA_05,'/0'
};
const int Elise_Beats[] = {BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_2,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_2, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8};
int GrandFa_Tune[] =					//할아버지의 낡은 시계
{
	SO_05, DO_06, SI_05, DO_06, RE_06, DO_06, RE_06, MI_06, FA_06, MI_06, LA_05, RE_06, RE_06, DO_06, DO_06, DO_06, SI_05, LA_05, SI_05, DO_06, 0,
	SO_05, DO_06, SI_05, DO_06, RE_06, DO_06, RE_06, MI_06, FA_06, MI_06, LA_05, RE_06, RE_06, DO_06, DO_06, DO_06, SI_05, LA_05, SI_05, DO_06, 0,
	DO_06, MI_06, SO_06, MI_06, RE_06, DO_06, SI_05, DO_06, RE_06, DO_06, SI_05, LA_05, SO_05, DO_06, MI_06, SO_06, MI_06, RE_06, DO_06, SI_05, DO_06, RE_06,
	SO_05, DO_06, RE_06, MI_06, FA_06, MI_06, LA_05, RE_06, RE_06, DO_06, DO_06, DO_06, SI_05, LA_05, SI_05, DO_06, '/0'
};
const int GrandFa_Beats[] = 
{
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_2, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_2, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4,
	BEAT_1_4, BEAT_1_2, BEAT_1_2, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_2
};
int mountain_rabbit[] =					//산토끼
{
	LA_05,FA_05,FA_05,LA_05,FA_05,RE_05, 0,
	MI_05,FA_05,MI_05,RE_05,FA_05,LA_05,0,
	RE_06,0,LA_05,DO_06,LA_05,DO_06,LA_05,FA_05,0,
	LA_05,MI_05,SO_05,FA_05,MI_05,RE_05, '/0'
};				
int mountain_rabbit_beat[] = 
{
	BEAT_1_2,BEAT_1_4,BEAT_1_4,
	BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,
	BEAT_1_2,BEAT_1_4,BEAT_1_4,
	BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,
	BEAT_1_4,BEAT_1_32,BEAT_1_4,BEAT_1_4,BEAT_1_4,
	BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,
	BEAT_1_2,BEAT_1_4,BEAT_1_4,
	BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4		
};
int month_tune[] =						//할아버지의 11개월
{					
	SO_05,LA_05,0,DO_06,0,SI_05,0,LA_05,SO_05,LA_05,0,MI_05,SO_05,LA_05,0,DO_06,0,SI_05,0,RE_06,SO_05s,
	LA_05,DO_06,RE_06,MI_06,RE_06,SO_06,FA_06,SO_05,DO_06,RE_06,MI_06,RE_06,FA_06,MI_06,DO_06,SI_05,LA_05,RE_06,SO_05s,SO_05s,FA_05s,
	SO_05,LA_05,0,DO_06,0,SI_05,0,LA_05,SO_05,LA_05,0,MI_05,SO_05,LA_05,0,DO_06,0,SI_05,0,RE_06,SO_05s,
	LA_05,DO_06,RE_06,MI_06, RE_06,SO_06,FA_06, SO_05,DO_06,RE_06,MI_06, RE_06,FA_06,MI_06 ,RE_06,MI_06,RE_06,SO_05s,RE_06,DO_06,
	DO_06,DO_06,DO_06s,DO_06s,RE_06,RE_06,DO_06s,DO_06s,MI_06,MI_06,RE_06,RE_06,DO_06s,DO_06s,RE_06,RE_06,RE_06,RE_06,DO_06s,DO_06s,SI_05,SI_05,DO_06,DO_06,
	SI_05,LA_05,SI_05,LA_05,LA_05,MI_05,FA_05,SO_05,LA_05,FA_05,LA_05,RE_06,DO_06,SO_05,LA_05,SI_05,SO_05,SI_05,MI_06,RE_06,MI_06,RE_06,DO_06,MI_06,SO_05,
	SO_06,FA_06s,FA_06,FA_06s,MI_06,MI_06,RE_06,MI_06,DO_06,DO_06,DO_06s,DO_06s,RE_06,RE_06,DO_06s,DO_06s,MI_06,MI_06,RE_06,RE_06,DO_06s,DO_06s,RE_06,RE_06,
	RE_06,RE_06,DO_06,DO_06,SI_05,SI_05,DO_06,DO_06,SI_05,LA_05,SI_05,LA_05,LA_05,MI_05,FA_05,LA_05,DO_06,MI_06,RE_06,MI_06,FA_06,
	SO_06,FA_06s,FA_06,MI_06,DO_06s,RE_06,MI_06,DO_06,DO_06,SO_05s,RE_06,DO_06,'/0'
};					
int month_beat[] = {
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,
};
int airplane_tune[] =					//종이 비행기
{
	MI_05, RE_05, DO_05, RE_05, MI_05, MI_05, MI_05,
	RE_05, RE_05, RE_05, MI_05, MI_05, MI_05,
	MI_05, RE_05, DO_05, RE_05, MI_05, MI_05, MI_05,
	RE_05, RE_05, MI_05, RE_05, DO_05, '/0'
};
int airplane_beat[] = {
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1
};
int tiger_tune[] =						//산중호걸
{
	DO_06, SO_05, MI_05, RE_05, MI_05, RE_05, MI_05, DO_05,
	SO_05, DO_05, MI_05, SO_05, MI_05, RE_05, MI_05, RE_05, MI_05, DO_05,
	DO_06, DO_06, SO_05, SO_05, MI_05, RE_05, MI_05, RE_05, MI_05, DO_05,
	SO_05, DO_05, MI_05, SO_05, MI_05, RE_05, DO_05,
	LA_05, LA_05, LA_05, LA_05, LA_05, LA_05,
	LA_05, DO_06, DO_06, LA_05, SO_05, LA_05, SO_05,
	DO_06, SO_05, MI_05, RE_05, MI_05, RE_05, MI_05, DO_05,
	SO_05, DO_05, MI_05, SO_05, MI_05, RE_05, DO_05, '/0'
};
int tiger_beat[] = {
	BEAT_1_2, BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_2, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_2,
	BEAT_1_2, BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1
};	
int PONO_tune[] =						//벼랑위의 포뇨
{
	DO_06,LA_05,FA_05,DO_05,DO_05,DO_05,RE_05,FA_05,SI_05,RE_06,DO_06,LA_05,SI_05,SO_05,SO_05,SI_05,LA_05,FA_05,FA_05,LA_05,
	SO_05,RE_05,MI_05,FA_05,SO_05,DO_06,LA_05,FA_05,DO_05,DO_05,DO_05,RE_05,FA_05,SI_05,RE_06,DO_06,LA_05,
	SI_05,SO_05,SO_05,SI_05,LA_05,FA_05,LA_05,SO_05,DO_05,FA_05,FA_05,DO_05,FA_05,SO_05,SO_05,DO_05,SO_05,LA_05,
	LA_05,FA_05,FA_05,LA_05,SI_05,DO_06,RE_06,DO_06,LA_05,FA_05,SO_05,FA_05,DO_05,FA_05,SO_05,SO_05,DO_05,SO_05,LA_05,
	
	LA_05,FA_05,FA_05,LA_05,SI_05,DO_06,RE_06,DO_06,SO_05,MI_05,FA_05,0,SO_05,SO_05,SO_05,FA_05,SO_05,LA_05,DO_05,SO_05,
	0,SO_05,SO_05,LA_05,SO_05,FA_05,RE_05,DO_05,LA_05,0,FA_05,FA_05,FA_05,FA_05,RE_06,DO_06,0,RE_05,RE_05,RE_05,RE_05,DO_06,SI_05,0,
	
	0,LA_05,SI_05,DO_06,FA_05,FA_05,SO_05,LA_05,SO_05,0,DO_05,FA_05,SO_05,RE_06,DO_06,LA_05,FA_05,DO_05,DO_05,DO_05,
	RE_05,FA_05,SI_05,RE_06,DO_06,LA_05,SI_05,SO_05,SO_05,SI_05,LA_05,FA_05,FA_05,LA_05,SO_05,RE_05,MI_05,FA_05,SO_05,
	DO_06,LA_05,FA_05,DO_05,DO_05,DO_05,RE_05,FA_05,SI_05,RE_06,DO_06,LA_05,SI_05,SO_05,SO_05,SI_05,LA_05,FA_05,LA_05,SO_05,DO_05,FA_05,'/0'
};
int PONO_beat[] = 
{
	BEAT_1_4,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_2,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_2,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_2,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_2,
	
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_2,BEAT_1_2,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_4,BEAT_1_2,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,
	
	BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_2,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_4,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_2,
	BEAT_1_4,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_8,BEAT_1_8,BEAT_1_4,BEAT_1_2
};
int insect_bell_tone[] =				//개똥벌레
{
	MI_05, MI_05, MI_05, RE_05, MI_05, RE_05, DO_05, 0, DO_05s, DO_05s, SI_05, MI_05, LA_05, 0,					//아무리 기어봐도 어쩔수없네
	LA_05,0, SO_05,  FA_05, MI_05, RE_05, DO_05, 0, DO_05,0, RE_05, RE_05, SO_05,	0,						//저기 개똥무덤이 내 집인걸
	
	
	MI_05, FA_05, MI_05, LA_05,0, SI_05, DO_05s, SI_05, MI_05,0, LA_05, LA_05, SO_05, FA_05, MI_05, 0,				//가지마라 가지마라 가지말아라
	RE_05, MI_05, FA_05, SO_05,0, DO_05s,0, SI_05,0, LA_05, DO_05s, DO_05s, SI_05, LA_05, SO_05,	0,				//나를위해 한번만 노래해주렴
	SO_05, DO_05s, SI_05, DO_05s, SI_05, LA_05,0, LA_05, LA_05, LA_05,0, SO_05, LA_05, FA_05, MI_05, 0,				//나나나나나나 쓰라린가슴안고
	DO_05, DO_05, 0, RE_05,0, RE_05,0, SO_05, MI_05, DO_05,0, LA_04, DO_05, SI_04, DO_05, RE_05, DO_05, '/0'						//오늘밤도 그렇게 울다 잠이든다
};
int insect_bell_beat[] =
{
	BEAT_1_2, BEAT_1_2, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1, BEAT_1_4, BEAT_1_2, BEAT_1_2, BEAT_1_2, BEAT_1_2, BEAT_1, BEAT_1_4,
	BEAT_1_2, BEAT_1_8, BEAT_1_2, BEAT_1_2, BEAT_1, BEAT_1_4, BEAT_1_2 ,BEAT_1_4, BEAT_1_2,BEAT_1_16, BEAT_1_4, BEAT_1_2, BEAT_1,BEAT_1_4,
	
	
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2, BEAT_1_8, BEAT_1_4, BEAT_1, BEAT_1_2, BEAT_1_2, BEAT_1, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,BEAT_1_8, BEAT_1_2,BEAT_1_16, BEAT_1_2,BEAT_1_16, BEAT_1_2, BEAT_1_2, BEAT_1_2, BEAT_1_2, BEAT_1_2, BEAT_1, BEAT_1_4,
	BEAT_1_2, BEAT_1, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1,BEAT_1_4, BEAT_1_4, BEAT_1_2, BEAT_1_4,BEAT_1_16, BEAT_1_4, BEAT_1_4,BEAT_1_4,BEAT_1_2, BEAT_1_4,
	BEAT_1_2, BEAT_1_2, BEAT_1_8, BEAT_1_2,BEAT_1_16, BEAT_1_2,BEAT_1_16, BEAT_1_2, BEAT_1_2,BEAT_1_2, BEAT_1_4, BEAT_1_4, BEAT_1, BEAT_1_4, BEAT_1_4, BEAT_1_2, BEAT_1_2
};
int husuabi_bell_tune[] =				//허수아비 아저씨
{
	DO_05, RE_05, MI_05, FA_05, SO_05, SO_05, LA_05, LA_05, SO_05,
	LA_05, DO_06, SI_05, LA_05, SO_05, FA_05, MI_05, RE_05, DO_05, 0,
	DO_06, DO_06, DO_06, DO_06, SO_05, 0,  DO_06, DO_06, DO_06, DO_06, SO_05,0,
	DO_06, SI_05, LA_05, SO_05, FA_05, MI_05, SO_05, RE_05, 0,
	DO_05, RE_05, MI_05, FA_05, SO_05, SO_05, LA_05, LA_05, SO_05,
	LA_05, DO_06, SI_05, LA_05, SO_05, FA_05, MI_05, RE_05, DO_05, 0, '/0'
};
int husuabi_bell_beat[] = {
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4
};
int school_bell_tune2[] =				//왈츠
{
	SO_05, SO_05s, DO_05s, SO_05, SO_05s, DO_05s, SO_05, SO_05s, MI_05, SO_05, SO_05s, DO_05s, SO_05, SO_05s, MI_05, DO_05s, LA_05, DO_05s, FA_05s, LA_05, DO_05s, MI_05, LA_05, DO_05s,
	MI_05, LA_05, DO_05s, MI_05, LA_05, DO_05s, RE_05s, DO_05s, DO_05, DO_05s, LA_05, DO_05, DO_05s, SO_05s, DO_05, DO_05s, FA_05s, DO_05, DO_05s, MI_05, DO_05, DO_05s, MI_05, DO_05, DO_05s, RE_05s, MI_05,
	DO_05s, SO_05, SO_05s, LA_05, LA_05s, SI_05, DO_05, DO_05s, RE_05, RE_05s, MI_05, FA_05, FA_05s, SO_05, SO_05s, DO_05s, SO_05, SO_05s, DO_05s, SO_05, SO_05s,
	SO_05, SO_05s, DO_05s, SO_05, SO_05s, DO_05s, SO_05, SO_05s, MI_05, SO_05, SO_05s, DO_05s, SO_05, SO_05s, MI_05, DO_05s, LA_05, DO_05s, FA_05s, LA_05, DO_05s, MI_05, LA_05, DO_05s,
	MI_05, LA_05, DO_05s, MI_05, LA_05, DO_05s, RE_05s, DO_05s, DO_05, DO_05s, LA_05, DO_05, DO_05s, SO_05s, DO_05, DO_05s, FA_05s, DO_05, DO_05s, MI_05, DO_05, DO_05s, MI_05, DO_05, DO_05s, RE_05s, MI_05,
	DO_05s, SO_05, SO_05s, LA_05, LA_05s, SI_05, DO_05, DO_05s, RE_05, RE_05s, MI_05, FA_05, FA_05s, SO_05, SO_05s, DO_05s, SO_05, SO_05s, DO_05s, SO_05, SO_05s,
	MI_06, SO_06, SO_06s, DO_06s, SO_06, SO_06s, MI_06, DO_06s, LA_05, DO_06s, FA_06s, LA_06, DO_06s, MI_06, LA_06, DO_06s, MI_06, LA_06, DO_06s, MI_06, LA_06, DO_06s, MI_06, LA_06, DO_06s, RE_06s, DO_06s,
	DO_06, DO_06s, LA_06, DO_06, DO_06s, SO_06s, DO_06, DO_06s, FA_06s, DO_06, DO_06s, MI_06, DO_06, DO_06s, RE_06s, MI_06, DO_06s, '/0'
};
int school_bell_beat2[] = {
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,BEAT_1_8,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
	BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16, BEAT_1_16,BEAT_1_16,BEAT_1_16,
BEAT_1_16,BEAT_1_16,BEAT_1_16,BEAT_1_16     };

int Speaker_main(void){
	
	Timer1_init_CTC_outA();
	
	while(1){
		//siren(3);
		//_delay_ms(1000);
		Music_Player(school_bell_tune2, school_bell_tune2);
		/*for(int i=0;i<24;i++){
			OCR0A = F_CPU / 2 / 64 / school_bell_tune[i];
			delay_ms(school_bell_beat[i]);
			OCR0A = 0;
			_delay_ms(20);
		}*/
	}
	return 0;
}
void Music_Player(int *tune, int *beat){
	
	while(*tune != '/0'){
		if(*tune)OCR1A = F_CPU / 2 / 8 / *tune;
		else OCR1A = 0;
		delay_ms(*beat);
		tune++;
		beat++;
		OCR1A = 0;
		_delay_ms(10);
	}
	return;
}
void delay_ms(int ms){
	while(ms--)_delay_ms(1);
}
void beep(char repeat){
	for(int i=0;i<repeat;i++){
		OCR1A = 500;
		_delay_ms(200);
		OCR1A = 0;
		_delay_ms(200);
	}
	return;
}
void siren(char repeat){
	
	OCR1A = 900;
	for(int j=0;j<repeat;j++){
		for(int i=0;i<100;i++){
			OCR1A += 10;
			_delay_ms(20);
		}
		for(int i=0;i<100;i++){
			OCR1A -= 10;
			_delay_ms(20);
		}
	}
	return;
}

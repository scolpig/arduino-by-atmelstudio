/*
 * arduino_uno.c
 *
 * Created: 2019-04-03 오후 2:03:18
 * Author : scolpig
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "FND4digit.h"

extern int HC_SR04_main(void);

int main(void)
{
    HC_SR04_main();
	
    while (1) 
    {
		
    }
}


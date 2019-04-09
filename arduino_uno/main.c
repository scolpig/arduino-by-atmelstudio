/*
 * arduino_uno.c
 *
 * Created: 2019-04-03 오후 2:03:18
 * Author : scolpig
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "LEDBar.h"
#include "FND.h"

extern int Dot_matrix_main(void);

int main(void)
{
    Dot_matrix_main();
	
    while (1) 
    {
		FND_test();
    }
}


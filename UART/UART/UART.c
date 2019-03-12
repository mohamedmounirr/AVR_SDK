/*
 * UART.c
 *
 * Created: 3/12/2019 1:31:39 PM
 *  Author: AG PC
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART_RX.h"
#define F_CPU 8000000UL
int main(void)
{
	LCD_init();
	UART_RX_init  ();
    
	sei();
    while(1)
    {
		start();
        //TODO:: Please write your application code 
    }
}
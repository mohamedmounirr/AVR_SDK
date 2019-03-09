/*
 * LCD.c
 *
 * Created: 3/9/2019 5:45:58 PM
 *  Author: AG PC
 */ 


#include <avr/io.h>
#include "LCD.h"
#include <util/delay.h>
int main(void)
{
	init_LCD  ();
	LCD_goto_xy( 1 , 1);
	LCD_PRINT  ( " Hallo There ");
	_delay_ms(1000);
	LCD_goto_xy( 1 , 2);
	LCD_PRINT  ( "Mohamed with you :)");
	_delay_ms(1000);
	LCD_goto_xy( 1 , 3);
	LCD_PRINT  ( " How it's going ");
	_delay_ms(1000);
	LCD_goto_xy( 1 , 4);
	LCD_PRINT  ( "I hope that you'r ok");
	_delay_ms(1000);
	LCD_CLEAR();
	_delay_ms(2000);
	deinit_LCD  ();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}
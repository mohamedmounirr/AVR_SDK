/*
 * LCD_INTERFACE.c
 *
 * Created: 3/9/2019 5:47:30 PM
 *  Author: AG PC
 */ 
#include "common.h"
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>


#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2


tenum_TF lcdcommand( uint_8 cmmd)
{
	tenum_TF ret_val = TRUE ;
	 if( cmmd != 0)
	 {
		 LCD_DPORT = cmmd ;
		 LCD_CPORT &= ~(1<< LCD_RS);
		 LCD_CPORT &= ~(1<< LCD_RW);
		 LCD_CPORT |=  (1<< LCD_EN);
		 _delay_us(1);
		 LCD_CPORT &= ~(1<< LCD_EN);
		 _delay_us(100); //if there is anthor caller in the next line 
	 }
	 else
	 {
		 ret_val = FALSE ;

	 }
	
	return ret_val ;
}
tenum_TF lcddata   ( uint_8 data)
{
	tenum_TF ret_val = TRUE ;
	if( data != 0)
	{
		LCD_DPORT = data ;
		LCD_CPORT |=  ( 1<<LCD_RS );
		LCD_CPORT &= ~( 1<<LCD_RW );
		LCD_CPORT |=  ( 1<<LCD_EN );
		_delay_us(1);
		LCD_CPORT &= ~(1<< LCD_EN);
		_delay_us(100);
		
	}
	else
	{
		ret_val = FALSE ;

	}
	
	return ret_val ;
	
}
void init_LCD  ()
{
	LCD_DDDRA = 0xFF ; 
	LCD_CDDRB = 0xFF ;
	LCD_CPORT &= ~(1<< LCD_EN);
	_delay_us(2000);
	lcdcommand(0x38);
	lcdcommand(0x0E);
	lcdcommand(0x01);
	_delay_us(2000);
	lcdcommand(0x06);
	
}
void LCD_goto_xy( uint_8 x , uint_8 y)
{
	uint_8 firstcharadd[] = { 0x80 , 0xC0 , 0x94 , 0xD4 };
    lcdcommand( firstcharadd[y-1] + x - 1 ) ;
	_delay_us(100);
	
}
tenum_TF LCD_PRINT  ( uint_8 * str_DIS_data)
{
	tenum_TF ret_val = TRUE ;
	if ( str_DIS_data != NULL)
	{
		uint_8 i = 0 ; 
		while ( str_DIS_data[i] != 0)
		{
			lcddata(str_DIS_data[i]);
			i++ ;
	
		}
	}
	else
	{
		ret_val = FALSE ;
	}
	return ret_val ;
}
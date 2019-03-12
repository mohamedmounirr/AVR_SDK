/*
 * LCD.c
 *
 * Created: 3/12/2019 3:57:21 PM
 *  Author: AG PC
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "../common.h"

/* PORTS */
#define LCD_DPORT PORTA
#define LCD_DDDRA DDRA
#define LCD_DPINA PINA
#define LCD_CPORT PORTB
#define LCD_CDDRB DDRB
#define LCD_CPINB PINB
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
		_delay_us(100);
	}
	else
	{
		ret_val = FALSE ;

	}
	
	return ret_val ;
}

void LCD_goto_xy( uint_8 x , uint_8 y)
{
	uint_8 firstcharadd[] = { 0x80 , 0xC0 , 0x94 , 0xD4 };
	lcdcommand( firstcharadd[y-1] + x - 1 ) ;
	_delay_us(100);
	
}

void LCD_CLEAR  ()
{
	lcdcommand( 0x01);
	LCD_goto_xy(0 , 0 );
	
}

void init_LCD_HALL  ()
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
	LCD_goto_xy(0 , 0 ) ;
}


tenum_TF lcddata   ( uint_8 data)
{
	tenum_TF ret_val = TRUE ;
	if( data != 0)
	{
		LCD_DPORT = (data -'0');
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

tenum_TF LCD_PRINT_HALL ( uint_8 str_DIS_data)
{
	tenum_TF ret_val = TRUE ;
	static uint_8 counter = 0 ;
	if ( str_DIS_data != 0 )
	{
		//uint_8 i = 0 ;
		/*while ( str_DIS_data[i] != 0)
		{
			lcddata(str_DIS_data[i]);
			i++ ;
			
		}*/
		lcddata( str_DIS_data );
		if (counter > 96)
		{
			LCD_CLEAR  () ;
			counter = 0 ;
		}
		counter++; 
	}
	else
	{
		ret_val = FALSE ;
	}
	
	return ret_val ;
}

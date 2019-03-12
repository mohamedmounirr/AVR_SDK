/*
 * UART_RX.c
 *
 * Created: 3/12/2019 2:03:53 PM
 *  Author: AG PC
 */ 
#include "common.h"
#include "UART_HALL/UART_HALl.h"
#include "LCD__HALL/LCD_HALL.h"


 
uint_8 g_UART_recieved_data ;
void UART_RX_init  ()
{  
	
	UART_init_RX_HALL( );
	
}

void LCD_init()
{
	init_LCD_HALL();
}

tenum_TF LCD_PRINT  ( uint_8 str_DIS_data )
{
	tenum_TF ret_val = TRUE ;
	if ( str_DIS_data != 0) 
	{
	  LCD_PRINT_HALL ( str_DIS_data );
	}
	else
	{
		ret_val = FALSE ;
	}
	return ret_val ;
}
void start()
{ 
	 g_UART_recieved_data  = HALL_dispatch() ;
	 LCD_PRINT( g_UART_recieved_data);
}
/*
 * HALL_COMM.c
 *
 * Created: 7/12/2019 3:39:14 PM
 *  Author: AG PC
 */ 
#include "common.h"
#include "../UART_HALL/Error_HalL.h"
#include "../UART_HALL/UART_HALL.h"
#include "UART_COMM.h"
#include <util/delay.h>
#include <avr/io.h>

volatile static uint_8 counter = 0 ; 
str_data_info *g_obj ; 
volatile uint_8 TX_flag = 0 ;


void interrupt_flag_()
{
	TX_flag = 1 ;
    
}

int_s8   USART_COMM_TX_init  ( str_data_info *obj ) 
{
	int_s8 ret_val = DONE ; 
	if ( obj->ptr_data != NULL && obj->ptr_data != 0)
	{
		g_obj = obj ;
		USART_TX_init  ( interrupt_flag_);
	}
	else
	{
		ret_val = INVALID_C_PRAMERTER ;
	}
	
	return ret_val;
}


int_s8 send_comm_dispatcher()
{
    int_s8 ret_val = DONE ;
    if ( g_obj->ptr_data != NULL && g_obj->NU_OF_BYTES != 0 && counter < g_obj->NU_OF_BYTES )
    {
		if ( TX_flag == 1 )
		{
			 ret_val = USART_Transmit( *(g_obj->ptr_data + counter ) ) ;
			 if (ret_val == DONE)
			 {
				 counter++;
				 TX_flag = 0 ;
				 
			 }
			 else
			 {
				 ret_val = TRANSIMIT_FAILED ;
			 }
		}
		else
		{
			ret_val = TRANSIMIT_INPROGRESS;
		}
		
	  
    }
    else if ( g_obj->NU_OF_BYTES == counter )
    {
		ret_val = TRANSIMIT_COMPLETED ;
    }
	else
    {
	    ret_val = INVALID_C_PRAMERTER ;
    }
    
    return ret_val;
}

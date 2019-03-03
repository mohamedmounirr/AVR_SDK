/*
 * s_clock.c
 *
 * Created: 2/26/2019 2:01:13 PM
 *  Author: AG PC
 */ 
#include "common.h"
#include "s_clock.h"
#include <avr/interrupt.h>
#include <avr/io.h>

static uint_16 pattarn_seven_seg_num[]={ 0x03f , 0x06 , 0x05b , 0x4f , 0x66 , 0x6d , 0x7D , 0X7 , 0Xff , 0X6f };
static uint_8 limit = 0  ;
volatile static uint_8 clock_counter = 0 ;
volatile static uint_8 min = 0 , sec1 = 0  ;
volatile static uint_8 flag_if_stop = 0 ;
ISR ( TIMER1_COMPA_vect)
{
	clock_counter++;
}
typedef struct
{
	tenum_port_base_t port_Base_min ;
	tenum_port_base_t port_Base_sec1;
	tenum_port_base_t port_Base_sec2;
	
}tstr_part_base;

static tstr_part_base ga_port_base_buffer[0] ;
tenum_errors_type init_ports  ( tenum_port_base_t port_typemin , tenum_port_base_t port_typesec1 , tenum_port_base_t port_typesec2 )
{
	tenum_errors_type ret_val = NO_ERRORS;
	if( (port_typemin < PORT_MAX && port_typemin > PORT_MIN ) && (port_typesec1 < PORT_MAX && port_typesec1 >PORT_MIN ) && (port_typesec2 < PORT_MAX && port_typesec2 >PORT_MIN ) )
	{
		if( limit == 0 )
		{
			
			*((volatile uint_8 *) port_typemin  + 1) = 0XFF ;
			*((volatile uint_8 *) port_typesec1 + 1) = 0XFF ;
			*((volatile uint_8 *) port_typesec2 + 1) = 0XFF ;
			ga_port_base_buffer[0].port_Base_sec2 = port_typesec2 ;
			ga_port_base_buffer[0].port_Base_sec1 = port_typesec1 ;
			ga_port_base_buffer[0].port_Base_min  = port_typemin ;
			limit = 1 ;
		}
		else
		{
			ret_val = JUST_THREE_PORTS;
		}

	}
	else
	{
		ret_val = INVALID_PARAMTER;
	}



	return ret_val ;
}
tenum_errors_type start_clock ()
{
	tenum_errors_type ret_val = NO_ERRORS;
	if(limit == 1 )
	{
		
		//TCCR1A = 0X8D   ;
		TCCR1B = 0X0D ;
		OCR1A  = 0X3E8  ;
		TIMSK |= (1<<4);
		//TIMSK |= (1<<2);
		sei();
		
		PORTC = pattarn_seven_seg_num[min] ;
		PORTD = pattarn_seven_seg_num[sec1] ;
		PORTB = pattarn_seven_seg_num[clock_counter] ;
		
		
		while( flag_if_stop  == 0 )
		{
			if( (TIFR &(1<<4)) == 0)
			{
				
				*(( volatile uint_8 *)ga_port_base_buffer[0].port_Base_sec2 +2) = pattarn_seven_seg_num[clock_counter] ;
				if ( clock_counter > 9 )
				{
					
					sec1++;
					*(( volatile uint_8 *)ga_port_base_buffer[0].port_Base_sec1 +2 ) = pattarn_seven_seg_num[sec1] ;
					clock_counter = 0 ;
				}
				if ( sec1 == 6 && clock_counter > 0)
				{
					min++ ;
					if (min > 9)
					{
						min = 0 ;
					}
					sec1 = 0 ;
					*(( volatile uint_8 *)ga_port_base_buffer[0].port_Base_sec1 +2 ) = pattarn_seven_seg_num[sec1] ;
					clock_counter = 0 ;
					*(( volatile uint_8 *)ga_port_base_buffer[0].port_Base_min +2 ) = pattarn_seven_seg_num[min] ;
				}
				if ( flag_if_stop == 1)
				{
					break ;
				}
				
			}
		}
	}
	
	else
	{
		ret_val = INVALID_PARAMTER;
	}



	return ret_val ;
}

tenum_errors_type stop_clock  ()
{
	tenum_errors_type ret_val = NO_ERRORS ;
	
	if ( flag_if_stop == 0 )
	{
		flag_if_stop = 1 ;
		TIMSK &= ~(1<<4);
		PORTB = pattarn_seven_seg_num[clock_counter] ;
		PORTD = pattarn_seven_seg_num[sec1] ;
		PORTC = pattarn_seven_seg_num[min] ;
		
	}
	
	
	return ret_val ;
}

tenum_errors_type deinit_ports()
{
	tenum_errors_type ret_val = NO_ERRORS ;
	
	if  ( (ga_port_base_buffer[0].port_Base_min != 0) && (ga_port_base_buffer[0].port_Base_sec1 != 0) && (ga_port_base_buffer[0].port_Base_sec2 != 0)  )
	{
		
		*(( volatile uint_8 *)ga_port_base_buffer[0].port_Base_min +2 )    = 0X00 ;
		*(( volatile uint_8 *)ga_port_base_buffer[0].port_Base_sec1 +2 )   = 0X00 ;
		*(( volatile uint_8 *)ga_port_base_buffer[0].port_Base_sec2 +2)    = 0X00 ;
		ga_port_base_buffer[0].port_Base_min = 0 ;
		ga_port_base_buffer[0].port_Base_sec1= 0 ;
		ga_port_base_buffer[0].port_Base_sec2= 0 ;
	}
	else
	{
		ret_val = INVALID_PARAMTER ;
	}
	
	
	return ret_val ;
}
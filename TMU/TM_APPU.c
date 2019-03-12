/*
 * TMU.c
 *
 * Created: 7/2/2019 9:42:17 PM
 *  Author: AG PC
 */ 


#include <avr/io.h>
#include "common.h"
#include "TMU.h"
#define F_CPU 1000000UL
static uint_16 pattarn_seven_seg_num[]={ 0x03f , 0x06 , 0x05b , 0x4f , 0x66 , 0x6d , 0x7D , 0X7 , 0Xff , 0X6f };
static uint_8 secound1_counter = 1 ; 
static uint_8 secound2_counter = 1 ;
static uint_8 minutes_counter  = 1 ;	
void secound_1 ()
{
	if ( secound1_counter <= 9 )
	{
		PORTB = pattarn_seven_seg_num[secound1_counter];
		secound1_counter++;
	}
	else
	{
		secound1_counter = 0 ;
		PORTB = pattarn_seven_seg_num[0];
	}
	
}	
void secound_2()
{
	if ( secound2_counter <= 9 )
	{
		PORTD = pattarn_seven_seg_num[secound2_counter];
		secound2_counter++;
	}
	else
	{
		secound2_counter = 0 ;
	}
	
}
void minutes()
{
	if ( minutes_counter <= 9 )
	{
		PORTD = pattarn_seven_seg_num[minutes_counter];
		minutes_counter++ ;
	}
	else
	{
		minutes_counter = 0 ;
	}
}

int main(void)
{
   str_timer_info obj1 ; 
   str_timer_info obj3 ; 
   str_timer_info obj2 ; 
   DDRC = 0xff ; 
   DDRD = 0xff ;
   DDRB = 0xff ;
   timer_init( RES_1024 );
   timer_start(&obj1 ,  3 , secound_1 , SYNC );

    while(1)
    {
       timer_dispatch();
	   
		if ( secound1_counter == 0 )
		{
		   timer_start(&obj2 ,  3 , secound_2 , SYNC );
		   stop_timer(&obj1);
		}
		if ( secound2_counter == 0 )
		{
			timer_start(&obj3 ,  3 , secound_1 , SYNC );
			PORTD = pattarn_seven_seg_num[0];
			stop_timer(&obj2);
		}
		 
    }
}
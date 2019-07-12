/*
 * Key_pad.c
 *
 * Created: 7/11/2019 6:28:49 PM
 *  Author: AG PC
 */ 
#include "common.h"
#include "Error_Hal.h"
#include "KeyPad_Hall.h"
#include <avr/io.h>
#include <avr/delay.h>

int_s8 Keypad_scan_Hal();
uint_8 keypad_get_key();

tenum_base_port g_Keypad_Port ; 
static const uint_8 arr_keypad[4][3]= {  '1' , '2' , '3',
                                         '4' , '5' , '6',
                                         '7' , '8' , '9',
                                         '*' , '0' , '#'};
volatile static uint_8  row_of_array ;   								 
volatile int_s8 key_gotten ; 
void (*cb_fun)(uint_8 pressed_key); 
 
							 
int_s8 KeyPad_init_Hal( tenum_base_port Keypad_Port , void (*cb)( uint_8 pressed_key ) )
{
	int_s8 ret_val = OK ;
	if ( ( Keypad_Port == BASE_A | Keypad_Port == BASE_B | Keypad_Port == BASE_C | Keypad_Port == BASE_D) && cb != NULL )
	{
		g_Keypad_Port = Keypad_Port ;
		cb_fun = cb ;
		*((volatile uint_8*)Keypad_Port+1) = 0xf0;  /* first four pins as output and anther 3 as input*/
		*((volatile uint_8*)Keypad_Port+2) = 0x0f;
		
	}
	else
	{
		ret_val = INVALID_ARG ;
	}
	
	return ret_val ;
}
void Keypad_dispatch_Hal()
{  
	uint_8 received ; 
	
	received = Keypad_scan_Hal();
	if ( received == OK )
	{
		key_gotten = keypad_get_key();
		cb_fun( arr_keypad[row_of_array][key_gotten - 4] );
	}	
}

int_s8 Keypad_scan_Hal()
{
	int_s8 ret_val = NON_OK; 
	uint_8 counter = 0 ;
	*((volatile uint_8*)g_Keypad_Port+2) = 0x0f;
	while( counter < 4 )
	{
		if ( !(*((volatile uint_8*)g_Keypad_Port) & ( 1<< counter) ))
		{ 
			ret_val = OK;
			row_of_array = counter ;
			break; 
		}
		else
		{
			counter++ ;
		}
		
	}
	
	 return ret_val ; 
}

uint_8 keypad_get_key()
{
	uint_8 counter = 4 , flag = 0 ; 
	uint_8 ret_val ; 
	while( counter <= 6 )
	{
		
		switch(counter)
		{
			case 4 : *((volatile uint_8*)g_Keypad_Port+2) = 0x6f ;
			break;
			case 5 : *((volatile uint_8*)g_Keypad_Port+2) = 0x5f ;
			break;
			case 6 : *((volatile uint_8*)g_Keypad_Port+2) = 0x3f ;
			break;
		}
		if ( !(*((volatile uint_8*)g_Keypad_Port) & (1<<row_of_array)) )
		{
			while( flag == 0 )
			{
				if ( (*((volatile uint_8*)g_Keypad_Port) & (1<<row_of_array)) )
				{
					ret_val = counter ; 
					flag = 1 ;
				}
			}
			break;
		}
		counter++;

	}
	
	return ret_val ; 
}
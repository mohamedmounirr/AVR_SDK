/*
 * simple_clock.c
 *
 * Created: 2/14/2019 8:38:18 PM
 *  Author: AG PC
 */ 


#include <avr/io.h>
#include "common.h"
#include "s_clock.h"



int main(void)
{ 
	
	 init_ports  (PORT_C , PORT_D , PORT_B) ;
	 //deinit_ports() ;
	 start_clock ( );
	 stop_clock  ( );
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}
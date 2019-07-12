/*
 * KeyPad.h
 *
 * Created: 7/11/2019 6:29:02 PM
 *  Author: AG PC
 */ 

/* 3 * 4 keypad*/

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "common.h"
#include "Error_Hal.h"
#include <avr/io.h>

typedef enum
{ 
	BASE_D = 0x30, 
	BASE_C = 0x33,
	BASE_B = 0x36,
	BASE_A = 0x39,
}tenum_base_port;
 
int_s8 KeyPad_init_Hal( tenum_base_port base_port , void (*cb)( uint_8 pressed_key ) );
void Keypad_dispatch_Hal();



#endif /* KEYPAD_H_ */
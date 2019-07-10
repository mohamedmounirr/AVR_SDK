/*
 * LCD.h
 *
 * Created: 3/9/2019 5:47:42 PM
 *  Author: AG PC
 */ 
#include "common.h"
#include <avr/io.h>

#ifndef LCD_H_
#define LCD_H_

#define LCD_DPORT PORTA
#define LCD_DDDRA DDRA
#define LCD_DPINA PINA
#define LCD_CPORT PORTB
#define LCD_CDDRB DDRB
#define LCD_CPINB PINB
tenum_TF lcdcommand( uint_8 cmmd); 
tenum_TF lcddata   ( uint_8 data);
void init_LCD  ();
void LCD_goto_xy( uint_8 x , uint_8 y);
tenum_TF LCD_PRINT  ( uint_8 * str_DIS_data);




#endif /* LCD_H_ */
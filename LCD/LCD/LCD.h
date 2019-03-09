/*
 * LCD.h
 *
 * Created: 3/9/2019 5:47:42 PM
 *  Author: AG PC
 */ 
#include "common.h"

#ifndef LCD_H_
#define LCD_H_

tenum_TF lcdcommand ( uint_8 cmmd); 
tenum_TF lcddata    ( uint_8 data);
void init_LCD    ();
void LCD_goto_xy    ( uint_8 x , uint_8 y);
tenum_TF LCD_PRINT  (  char * str_DIS_data);
void LCD_CLEAR   ();
void deinit_LCD  ();





#endif /* LCD_H_ */
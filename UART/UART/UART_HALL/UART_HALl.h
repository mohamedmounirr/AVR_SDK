/*
 * UART_HALl.h
 *
 * Created: 3/12/2019 2:24:53 PM
 *  Author: AG PC
 */ 


#ifndef UART_HALL_H_
#define UART_HALL_H_
#include "../common.h"

void UART_init_RX_HALL();
uint_8 HALL_dispatch() ;
//uint_8 UART_DATA_RECIEVED() ;
//tenum_TF call_back_fun_HALL( void (*cb_fun)(uint_8 *str_DIS_data) );

#endif /* UART_HALL_H_ */
/*
 * UART_HALL.h
 *
 * Created: 7/9/2019 11:56:17 PM
 *  Author: AG PC
 */ 


#ifndef UART_HALL_H_
#define UART_HALL_H_
#include "common.h"

void   USART_RX_init    ( );
void   USART_TX_init    ( );
void USART_Transmit( uint_8 data );
unsigned char USART_Receive ();





#endif /* UART_HALL_H_ */
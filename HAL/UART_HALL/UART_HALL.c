/*
 * UART_HALL.c
 *
 * Created: 7/9/2019 11:55:58 PM
 *  Author: AG PC
 */ 
#include "common.h"
#include "Error_Hall.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* UCSRA REG */
#define  RXC  7
#define  TXC  6
#define  UDRE 5 //ALREADY_TO_RECIEVE_NEW_DATA
#define  FE   4 //FRAME_ERROR
#define  DOR  3 //DATA_OVER_RUN
#define  PE   2
#define  U2X  1
#define  MPCM 0
/* UCSRB REG */
#define  RXCIE  7
#define  TXCIE  6
#define  UDRIE  5
#define  RXEN   4
#define  TXEN   3
#define  UCSZ2  2
#define  RXB8   1
#define  TXB8   0
/* UCSRC REG */
#define  URSEL  7
#define  UMSEL  6
#define  UMP1   5
#define  UMP0   4
#define  USBS   3
#define  UCSZ1  2
#define  UCSZ0  1
#define  UCPOL  0

#define  HIGH 1
#define  LOW  0

void USART_RX_init  ()
{
	UCSRB |= ( HIGH << RXCIE ) | ( HIGH << RXEN ) ;
	UCSRC |= ( HIGH << URSEL) | ( HIGH << UCSZ1)  | ( HIGH << UCSZ0) ;
	UBRRH = 0x00;
	UBRRL  = 0x33 ;
	
	
	
}
void   USART_TX_init  ()
{
	UCSRB |= ( HIGH << TXCIE ) | ( TXEN ) ;
	UCSRC |= ( HIGH << URSEL) | ( HIGH << UCSZ1)  | ( HIGH << UCSZ0) ;
	UBRRL  = 0x33 ;
}
void USART_Transmit( uint_8 data )
{
	while( !(UCSRA & (1 << UDRE)) );
	
	UDR = data ;
}
unsigned char USART_Receive ()
{
		while ( !(UCSRA & ( HIGH << RXC )) );
		
		return UDR ;
	
	return 0;
}

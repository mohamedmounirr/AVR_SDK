/*
 * UART_HALL.c
 *
 * Created: 3/12/2019 2:25:40 PM
 *  Author: AG PC
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../common.h"

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
//tenum_TF LCD_PRINT  ( uint_8 str_DIS_data ) ;
//uint_8 *ptr_call_back_fun ;
uint_8 flag = 0 ;

ISR(USART_RXC_vect)
{
	//while ( !(UCSRA & ( HIGH << RXC )) );
	flag = 1 ;
	
}

void UART_init_RX_HALL()
{
	//UCSRA |= ( HIGH << RXC ) | ( LOW << TXC ) | ( LOW << UDRE ) | ( LOW << FE ) | ( LOW << DOR ) | ( LOW << PE ) | ( LOW << U2X ) | ( LOW << MPCM ) ; //UCSRA
	UCSRB |= ( HIGH << RXCIE) | ( HIGH << RXEN )  | ( LOW << UCSZ2 ) ;
	UCSRC |= ( HIGH << URSEL) | ( HIGH << UCSZ1)  | ( HIGH << UCSZ0) ;
	UBRRH = 0x00 ; 
	UBRRL = 0x33 ;
	
}
uint_8 HALL_dispatch()
{
	if (flag == 1)
	{
		while ( !(UCSRA & ( HIGH << RXC )) );
		
		return UDR ;
	}
	return 0;
}
/*tenum_TF call_back_fun_HALL( void (*cb_fun)(uint_8 *str_DIS_data) )
{
	tenum_TF ret_val = TRUE ;
	if ( cb_fun != NULL )
	{
		ptr_call_back_fun = cb_fun ;
	}
	else
	{
		ret_val = FALSE ;
	}
	
	return ret_val ;
}
*/
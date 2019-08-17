/*
 * I2C_HAL.c
 *
 * Created: 7/16/2019 5:25:12 PM
 *  Author: AG PC
 */ 

#include "common.h"
#include "I2C_HAL.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "../LCD/LCD_HALL.h"

#define F_CPU 8000000UL
#define F_scl 1000000UL
#define prescaler 1
#define TWBR_val ((((F_CPU / F_scl) / prescaler ) - 16 ) / 2 )


#define I2C_Busy (!(TWCR & (1<< TWINT)))
tenum_status g_status ;

ISR(TWI_vect)
{
	/*DDRC = 0XFF; 
	PORTC = 0XFF;*/
	switch(TW_STATUS)
	{
		case TW_SR_DATA_ACK:
		// received data from master, call the receive callback	
		g_CallBackRecieve(TWDR);
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_ST_SLA_ACK:
		// master is requesting data, call the request callback
		g_CallBackTX();
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_ST_DATA_ACK:
		// master is requesting data, call the request callback
		g_CallBackTX();
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_BUS_ERROR:
		// some sort of erroneous state, prepare TWI to be readdressed
		TWCR = 0;
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		default:
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		
		break;
	}
}

void I2C_Init ( tenum_status status)
{
	TWBR =(uint_8)TWBR_val; 
	g_status = status ; 
	TWSR  = 0x00 ; 
	//TWAR  = 0x10;
	TWCR |= ( 1 << TWIE) | (1<<TWEA) | (1<< TWINT) | ( 1<< TWEN )  ;  // Enable TWI
	
}
void I2C_Start()
{
	/* TWINT MUST BE CLEARED FIRST BY SET IR TO 1 
	   ENABLE TWI
	   SET START BIT TWSTA 
	*/
	TWCR |= ( 1<<TWINT ) | ( 1<< TWSTA ) | ( 1<< TWEN ) ;
	/*
	  waiting to finish these operation 
	*/
	
	//while( I2C_Busy ) ; 
	
	//TWCR &= ~( 1<< TWSTA);
}
void I2C_stop ()
{
	/* TWINT MUST BE CLEARED FIRST BY SET IR TO 1 
	   ENABLE TWI
	   SET STOP BIT TWSTA 
	*/
	TWCR |= ( 1<<TWINT ) | ( 1<< TWEN ) | ( 1<< TWSTO );

}
void I2C_write( uint_8 Data)
{
	TWDR = Data ; 
	/* TWINT MUST BE CLEARED FIRST BY SET IR TO 1 
	   ENABLE TWI
	*/
	TWCR |= ( 1<<TWINT ) | ( 1<< TWEN ) ;
	//while( I2C_Busy ) ;
	
}
void I2C_TXWithInterrupt(uint_8 Data )
{
	TWDR = Data ; 
	/* TWINT MUST BE CLEARED FIRST BY SET IR TO 1 
	   ENABLE TWI
	*/
	TWCR |= ( 1<<TWINT ) | ( 1<< TWEN ) | ( 1<< TWIE )  ;
   // while( I2C_Busy ) ;
}
uint_8 I2C_ReadWithAck()
{
	/* TWINT MUST BE CLEARED FIRST BY SET IR TO 1 
	   ENABLE TWI
	   ACK IS SET BY SET TWEA
	*/
	TWCR |= ( 1<<TWINT ) | ( 1<< TWEN ) | ( 1<< TWEA ) ;
	
	//while( I2C_Busy ) ;
	
	return TWDR ;
}
uint_8 I2C_ReadWithAckAndInterrupt()
{
	/* TWINT MUST BE CLEARED FIRST BY SET IR TO 1 
	   ENABLE TWI
	   ACK IS SET BY SET TWEA
	   INTERRUPR ENABLE BY SET TWIE
	*/
	TWCR |= ( 1<<TWINT ) | ( 1<< TWEN ) | ( 1<< TWIE ) | ( 1<< TWEA );
	
	//while( I2C_Busy ) ;
	
	return TWDR ;
	
}
void AsignCallBackRx_TX(void (*CallBackRecieve)() , void (*CallBackTX)() )
{
	g_CallBackRecieve = CallBackRecieve ;
	g_CallBackTX      = CallBackTX ;  
	
}

uint_8 I2C_GetStatus()
{
	uint_8 status ; 
	status = TWSR & 0xF6 ; 
	/*
	 get first 5bits
	 
	*/
	return status ;
	
}
void I2C_disableInterrupt()
{
	TWCR &= ~( 1<<TWIE) ; 
	
}
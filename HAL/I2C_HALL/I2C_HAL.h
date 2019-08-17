/*
 * I2C_HAL.h
 *
 * Created: 7/16/2019 5:25:26 PM
 *  Author: AG PC
 */ 


#ifndef I2C_HAL_H_
#define I2C_HAL_H_
#include "common.h"

void (*g_CallBackRecieve)() ;
void (*g_CallBackTX)() ;

typedef enum
{
	TX_STATUS, 
	RX_STATUS, 
}tenum_status;

void I2C_Init ( tenum_status status );
void I2C_Start();
void I2C_stop ();
void I2C_write( uint_8 Data);
void I2C_TXWithInterrupt(uint_8 Data );
uint_8 I2C_ReadWithAck();
uint_8 I2C_ReadWithAckAndInterrupt();
void AsignCallBackRx_TX(void (*CallBackRecieve)() , void (*CallBackTX)() );
uint_8 I2C_GetStatus();
void I2C_disableInterrupt();





#endif /* I2C_HAL_H_ */
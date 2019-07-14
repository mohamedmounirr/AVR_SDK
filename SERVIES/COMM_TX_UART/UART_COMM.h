/*
 * HALL_COMM.h
 *
 * Created: 7/12/2019 3:39:02 PM
 *  Author: AG PC
 */ 


#ifndef HALL_COMM_H_
#define HALL_COMM_H_
#include "common.h"


/*typedef struct
{
	uint_32 DATA ;
}str_dtype_of_data;
*/
#define   string  

typedef struct  
{ 
	uint_8 *ptr_data    ;
	uint_32 NU_OF_BYTES ;

	
}str_data_info;

int_s8   USART_COMM_TX_init  ( str_data_info *obj );
int_s8   send_comm_dispatcher();

#endif /* HALL_COMM_H_ */
/*
 * TMU.h
 *
 * Created: 7/2/2019 9:43:09 PM
 *  Author: AG PC
 */ 


#ifndef TMU_H_
#define TMU_H_
#define MAX_OBJ 3 

#include "common.h"

typedef enum
{
	ONE_SHOT = 2 ,
	SYNC ,
}timer_type;

typedef struct
{
	uint_8 time ;
	timer_type t_type;
	void (*cb)() ;
	uint_8 rem_time ;
	
}str_timer_info;

typedef enum
{
	NO_PRESCALER = 4,
	RES_8 ,
	RES_64 ,
	RES_256 ,
	RES_1024 ,
	
}tenum_timer_res;


tenum_bool timer_init( tenum_timer_res timer_res );

tenum_bool timer_start( str_timer_info *str_obj , uint_8 time , void(*cb)() , timer_type t_type );

void timer_dispatch();

tenum_bool stop_timer( str_timer_info *str_obj );

tenum_bool timer_deinit( str_timer_info *str_obj );




#endif /* TMU_H_ */
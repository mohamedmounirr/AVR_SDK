/*
 * s_clock.h
 *
 * Created: 2/14/2019 8:39:32 PM
 *  Author: AG PC
 */ 


#ifndef S_CLOCK_H_
#define S_CLOCK_H_

typedef enum
{
	NO_ERRORS = 2 ,
	INVALID_PARAMTER ,
	JUST_THREE_PORTS ,
	ALREADY_STOPPED,
}tenum_errors_type;

typedef enum
{
	PORT_MIN = 0X29,
	PORT_A = 0X39 ,
	PORT_B = 0X36 ,
	PORT_C = 0X33 ,
	PORT_D = 0X30 ,
	PORT_MAX = 0X3A ,
	
}tenum_port_base_t;

tenum_errors_type init_ports  ( tenum_port_base_t port_type ,tenum_port_base_t port_typesec1 , tenum_port_base_t port_typesec2) ;
tenum_errors_type start_clock () ;
tenum_errors_type stop_clock  () ;
tenum_errors_type deinit_ports() ;



#endif /* S_CLOCK_H_ */
#ifndef __CALC_H__
#define __CALC_H__

typedef enum status 
{
	SUCCESS, 
	MATH_ERR, 
	SYNTAX_ERR, 
	ALLOC_ERR
} status_t;

typedef enum state
{
	WAIT_4_NUM,
	WAIT_4_OP,
	ERROR
} state_t;

typedef struct calc calc_t;

status_t Calc(const char *equation, double *result);

#endif




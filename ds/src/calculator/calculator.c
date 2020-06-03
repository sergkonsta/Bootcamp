
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      27.05.2020               **
**  Reviewer:  Hanna					**
**  Status:    Sent						**
*****************************************/
#include <stdlib.h>	/*for malloc, strtod*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for strlen*/
#include <math.h>	/*for power*/

#include "calculator.h"
#include "stack.h"

#define NUM_OF_EVENTS 256
#define NUM_OF_STATES 2

#define UNUSED(X) (void)(X)

typedef enum state
{
	WAIT_4_NUM,
	WAIT_4_OP,
	ERROR,
	CALC
} state_t;

struct calc
{
	stack_t *stk_nums;
	stack_t *stk_operations;
};

typedef struct lut_elem
{
	state_t next_state;
	status_t (*act_func)(char **equation, calc_t *equation_elems);
} lut_elem_t;

static lut_elem_t lut[NUM_OF_STATES][NUM_OF_EVENTS];

static status_t CalcInit(calc_t **calc, size_t stack_capacity);
static void DefineLUT(void);
static status_t StoreNum(char **equation, calc_t *equation_elems);
static status_t StoreOp(char **equation, calc_t *equation_elems);
static status_t CalcEquation(char **equation, calc_t *equation_elems);
static status_t SyntaxError(char **equation, calc_t *equation_elems);
static status_t DoNothing(char **equation, calc_t *equation_elems);
static void CalcDestroy(calc_t *calc);

/*----------------------------------------------------------------------------*/
/*main Buisiness logic of the calculator*/
status_t Calc(char *equation, double *result)
{
	calc_t *calc = NULL;
	
	size_t equation_length = 0;
	
	status_t status = 0;	
	
	state_t curr_state = WAIT_4_NUM;
	state_t next_state = ERROR;
	
	assert(NULL != result);
	assert(NULL != equation);
	
	equation_length = strlen((const char *)equation);
	
	/*initializes calculator struct*/
	status = CalcInit(&calc, equation_length);
	if(SUCCESS != status)
	{
		return (status);
	}

	/*build the equation in the system*/
	while(CALC != curr_state && SUCCESS == status)
	{
		/*saves next state and activates act_func of current char and state*/
		next_state = lut[curr_state][(unsigned char)*equation].next_state;	
		
		status = lut[curr_state][(unsigned char)*equation].act_func(&equation, calc);
		if(SUCCESS != status)
		{
			CalcDestroy(calc);	
			return (status);
		}
		
		curr_state = next_state;	
	}

	/*calculate remaining equation*/
	while(1 != StackIsEmpty(calc->stk_operations))
	{
		status = CalcEquation(&equation, calc);
		if(SUCCESS != status)
		{
			CalcDestroy(calc);	
			return (status);
		}
	}
	
	/*save result for user*/
	*result = (double)(long)StackPeek(calc->stk_nums);

	CalcDestroy(calc);	
	
	return (status);
}


/*----------------------------------------------------------------------------*/
/* creates calculator and 2 stacks and LUT for state machine*/
static status_t CalcInit(calc_t **calc, size_t stack_capacity)
{
	assert(stack_capacity > 0);
	
	/*create calc struct*/
	*calc = (calc_t *)malloc( sizeof(calc_t) );
	if(NULL == *calc)
	{
		return (ALLOC_ERR);
	}
	
	/*create first stack*/
	(*calc)->stk_nums = StackCreate(stack_capacity);
	if(NULL == (*calc)->stk_nums)
	{
		free(*calc);
		return (ALLOC_ERR);
	}
	
	/*create second stack*/
	(*calc)->stk_operations = StackCreate(stack_capacity);
	if(NULL == (*calc)->stk_operations)
	{
		StackDestroy((*calc)->stk_nums);
		free(*calc);
		return (ALLOC_ERR);
	}
	
	DefineLUT();
	
	return (SUCCESS);
}


/*----------------------------------------------------------------------------*/
/*destroys stacks and calc*/
static void CalcDestroy(calc_t *calc)
{
	assert(NULL != calc);
	
	StackDestroy(calc->stk_nums);	
	StackDestroy(calc->stk_operations);	
	free(calc);	

	calc = NULL;
	
	return;
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*---------------------       action funcs      ------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/



/*store num func, returns status */
static status_t StoreNum(char **equation, calc_t *equation_elems)
{
	double num = 0.0;
	
	assert(NULL != equation);
	assert(NULL != *equation);
	assert(NULL != equation_elems);
	assert(NULL != equation_elems->stk_nums);
				
	/*get double trasverse the string to the char after number*/
	num = strtod(*equation, equation);
	
	/*push to stack*/
	StackPush(equation_elems->stk_nums, (void *)(long)num);
	
	return (SUCCESS);
}


/*----------------------------------------------------------------------------*/
/*store op func, returns status */
static status_t StoreOp(char **equation, calc_t *equation_elems)
{
	char operation = '\0';

	status_t status = SUCCESS;
	
	assert(NULL != equation);
	assert(NULL != *equation);
	assert(NULL != equation_elems);
	assert(NULL != equation_elems->stk_operations);
		
	/*get operation from sting and iterate 1 char up the equation*/
	operation = **equation;
	++*equation;
		
	/*calculate what already in stack if possible 
	  (current and last operation are + or -)*/
	if('-' == operation || '+' == operation)
	{
		while(1 != StackIsEmpty(equation_elems->stk_operations) &&		
			('^' == (char)(long)StackPeek(equation_elems->stk_operations)	||
			 ')' == (char)(long)StackPeek(equation_elems->stk_operations) 	|| 
			 '-' == (char)(long)StackPeek(equation_elems->stk_operations) 	|| 
			 '+' == (char)(long)StackPeek(equation_elems->stk_operations)	||
			 '/' == (char)(long)StackPeek(equation_elems->stk_operations)	||
			 '*' == (char)(long)StackPeek(equation_elems->stk_operations))  )
		{	
			status = CalcEquation(equation, equation_elems); 
			if(SUCCESS != status)
			{
				return (status);
			}	
		}
		
	}
	
	/*calculate what already in stack if possible 
	  (current and last operation are / or *)*/
	else if('/' == operation || '*' == operation)
	{		
		while(1 != StackIsEmpty(equation_elems->stk_operations) &&			  
			('^' == (char)(long)StackPeek(equation_elems->stk_operations)	||
			 ')' == (char)(long)StackPeek(equation_elems->stk_operations)	|| 
			 '/' == (char)(long)StackPeek(equation_elems->stk_operations)	|| 
			 '*' == (char)(long)StackPeek(equation_elems->stk_operations))	)
		{
			status = CalcEquation(equation, equation_elems); 
			if(SUCCESS != status)
			{
				return (status);
			}
		}
	}
	
	/*  pushes all other i.e: '(', ')', '^'  */
	StackPush(equation_elems->stk_operations, (void *)(long)operation);
	
	return (SUCCESS);	
}


/*----------------------------------------------------------------------------*/
/*calculate equation func (handles parantheses)*/
static status_t CalcEquation(char **equation, calc_t *equation_elems)
{
	double result = 0;
	
	double num_1 = 0;
	double num_2 = 0;
	
	char operation = '\0';
	
	int parantheses_flag = 0;
	
	status_t status = SUCCESS;
	
	assert(NULL != equation);
	assert(NULL != *equation);
	assert(NULL != equation_elems);
	assert(NULL != equation_elems->stk_nums);
	assert(NULL != equation_elems->stk_operations);

	/*handle parantheses first if they exist*/
	if(')' == (char)(long)StackPeek(equation_elems->stk_operations) )
	{
		++parantheses_flag;			
	
		/* pops ')' */
		StackPop(equation_elems->stk_operations);			
	}		
	
	/*pop and calculate sub expression*/
	operation = (char)(long)StackPeek(equation_elems->stk_operations);
	StackPop(equation_elems->stk_operations);
	
	num_1 = (double)(long)StackPeek(equation_elems->stk_nums);
	StackPop(equation_elems->stk_nums);
			
	num_2 = (double)(long)StackPeek(equation_elems->stk_nums);
	StackPop(equation_elems->stk_nums);
		
	if('+' == operation)
	{
		result = num_1 + num_2;
		status = SUCCESS; 
	}	
	
	else if('-' == operation)
	{
		result = num_2 - num_1;
		status = SUCCESS; 
	}	
	
	else if('*' == operation)
	{
		result = num_1 * num_2;
		status = SUCCESS; 
	}
	
	else if('/' == operation)
	{
		if(0 == num_1)
		{
			return (MATH_ERR);
		}
		
		result = num_2 / num_1;
		status = SUCCESS; 
	}
	
	else if('^' == operation)
	{
		result = pow(num_2, num_1);
		status = SUCCESS; 
	}
	
	else 
	{
		return (SYNTAX_ERR);
	}	
	
	/* pops parantheses if when needed and return temp to equation*/
	if(  1 != StackIsEmpty(equation_elems->stk_operations) &&
		'(' == (char)(long)StackPeek(equation_elems->stk_operations) &&
	     0 < parantheses_flag )
	{
		--parantheses_flag;
		
		/*pops '('*/
		StackPop(equation_elems->stk_operations);
	}

	/* pushes back result */
	StackPush(equation_elems->stk_nums, (void *)(long)result);
	
	return (status);
}


/*----------------------------------------------------------------------------*/
/*read next num func*/
static status_t SyntaxError(char **equation, calc_t *equation_elems)
{
	UNUSED(equation);
	UNUSED(equation_elems);
	
	return (SYNTAX_ERR);
}


/*----------------------------------------------------------------------------*/
/*does nothing*/
static status_t DoNothing(char **equation, calc_t *equation_elems)
{
	UNUSED(equation);
	UNUSED(equation_elems);
	
	return (SUCCESS);
}


/*----------------------------------------------------------------------------*/
/*-------------------       LUT definition      ------------------------------*/
/*----------------------------------------------------------------------------*/

/*defines table for state machine*/
static void DefineLUT(void)
{
	int i = 0;
	
	/*all cases*/
	while(i < 256)
	{ 
		lut[WAIT_4_OP][i].next_state = 	ERROR; 
		lut[WAIT_4_OP][i].act_func = 	DoNothing;
		lut[WAIT_4_NUM][i].next_state = ERROR; 
		lut[WAIT_4_NUM][i].act_func = 	DoNothing;
	
		++i;
	}
	
	/* '\0' case */
	lut[WAIT_4_OP][0].next_state = 	CALC;
	lut[WAIT_4_OP][0].act_func = 	CalcEquation;
	lut[WAIT_4_NUM][0].next_state = ERROR;
	lut[WAIT_4_NUM][0].act_func = 	SyntaxError;

	/*space case*/
	lut[WAIT_4_OP][32].next_state = 	WAIT_4_OP;
	lut[WAIT_4_OP][32].act_func = 		NULL		/*act_func to ignore space*/;
	lut[WAIT_4_NUM][32].next_state = 	WAIT_4_NUM; 
	lut[WAIT_4_NUM][32].act_func = 		NULL		/*act_func to ignore space*/;

	/* + case */
	lut[WAIT_4_OP]['+'].next_state = 	WAIT_4_NUM;
	lut[WAIT_4_OP]['+'].act_func = 		StoreOp;
	lut[WAIT_4_NUM]['+'].next_state = 	ERROR; 
	lut[WAIT_4_NUM]['+'].act_func =		SyntaxError;
	
	/* - case */
	lut[WAIT_4_OP]['-'].next_state = 	WAIT_4_NUM;
	lut[WAIT_4_OP]['-'].act_func = 		StoreOp;
	lut[WAIT_4_NUM]['-'].next_state = 	ERROR; 
	lut[WAIT_4_NUM]['-'].act_func =		SyntaxError;
	
	/* * case */
	lut[WAIT_4_OP]['*'].next_state = 	WAIT_4_NUM;
	lut[WAIT_4_OP]['*'].act_func = 		StoreOp;
	lut[WAIT_4_NUM]['*'].next_state = 	ERROR; 
	lut[WAIT_4_NUM]['*'].act_func =		SyntaxError;
	
	/* / case */
	lut[WAIT_4_OP]['/'].next_state = 	WAIT_4_NUM;
	lut[WAIT_4_OP]['/'].act_func = 		StoreOp;
	lut[WAIT_4_NUM]['/'].next_state = 	ERROR; 
	lut[WAIT_4_NUM]['/'].act_func =		SyntaxError;
	
	/* ^ case */
	lut[WAIT_4_OP]['^'].next_state = 	WAIT_4_NUM;
	lut[WAIT_4_OP]['^'].act_func = 		StoreOp;
	lut[WAIT_4_NUM]['^'].next_state = 	ERROR; 
	lut[WAIT_4_NUM]['^'].act_func =		SyntaxError;
	
	/* ( case */
	lut[WAIT_4_OP]['('].next_state = 	ERROR;
	lut[WAIT_4_OP]['('].act_func = 		SyntaxError;
	lut[WAIT_4_NUM]['('].next_state = 	WAIT_4_NUM; 
	lut[WAIT_4_NUM]['('].act_func =		StoreOp; 
	
	/* ) case */
	lut[WAIT_4_OP][')'].next_state = 	WAIT_4_OP;
	lut[WAIT_4_OP][')'].act_func = 		StoreOp;
	lut[WAIT_4_NUM][')'].next_state = 	ERROR; 
	lut[WAIT_4_NUM][')'].act_func =		SyntaxError;
	
	/*0 - 9 numbers*/
	i = 0;
	while(i < 10)
	{ 
		lut[WAIT_4_OP][48 + i].next_state = 	ERROR; 
		lut[WAIT_4_OP][48 + i].act_func = 		SyntaxError;
		lut[WAIT_4_NUM][48 + i].next_state = 	WAIT_4_OP; 
		lut[WAIT_4_NUM][48 + i].act_func = 	StoreNum;
	
		++i;
	}
}







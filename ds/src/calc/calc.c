
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      27.05.2020               **
**  Reviewer:  Hanna					**
**  Status:    ????						**
*****************************************/
#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for strlen*/

#include "calc.h"
#include "stack.h"

#define NUM_OF_EVENTS 256
#define NUM_OF_STATES 2

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

static status_t CalcInit(calc_t *calc, size_t stack_capacity);

static void DefineLUT(void);
/*----------------------------------------------------------------------------*/

status_t Calc(const char *equation, double *result)
{
	calc_t *calc = NULL;
	
	/*initializes calculator struct*/
	if(ALLOC_ERR == CalcInit(calc, strlen(equation)))
	{
		return (ALLOC_ERR);
	}


	return (SUCCESS);
}


/*----------------------------------------------------------------------------*/
static status_t CalcInit(calc_t *calc, size_t stack_capacity)
{
	assert(stack_capacity > 0);
	
	/*create calc struct*/
	calc = (calc_t *)malloc( sizeof(calc_t) );
	if(NULL == calc)
	{
		return (ALLOC_ERR);
	}
	
	/*create first stack*/
	calc->stk_nums = StackCreate(stack_capacity);
	if(NULL == calc->stk_nums)
	{
		free(calc);
		return (ALLOC_ERR);
	}
	
	/*create second stack*/
	calc->stk_operations = StackCreate(stack_capacity);
	if(NULL == calc->stk_operations)
	{
		StackDestroy(calc->stk_nums);
		free(calc);
		return (ALLOC_ERR);
	}
	
	DefineLUT();



	return (SUCCESS);
}

/*LUT definition*/
static void DefineLUT(void)
{
	/*LUT definition - for now only for: 4 + 5 and '\0', space*/
	lut[WAIT_4_OP][0].next_state = WAIT_4_NUM;	/*next state is calc*/
	lut[WAIT_4_OP][0].act_func = NULL	/*act_func to calc stored equation*/;
	lut[WAIT_4_NUM][0].next_state = ERROR; 
	lut[WAIT_4_NUM][0].act_func = NULL	/*act_func for syntax error*/;

	/*space case*/
	lut[WAIT_4_OP][32].next_state = WAIT_4_OP	/*next state is calc*/; 
	lut[WAIT_4_OP][32].act_func = NULL	/*act_func to ignore space*/;
	lut[WAIT_4_NUM][32].next_state = WAIT_4_NUM; 
	lut[WAIT_4_NUM][32].act_func = NULL	/*act_func to ignore space*/;

	lut[WAIT_4_OP]['+'].next_state = WAIT_4_NUM	/*next state is calc*/; 
	lut[WAIT_4_OP]['+'].act_func = NULL			/*save op 2 stack_of_ops and read next input*/;
	lut[WAIT_4_NUM]['+'].next_state = ERROR; 
	lut[WAIT_4_NUM]['+'].act_func = NULL		/*act_func for syntax error*/;

	lut[WAIT_4_OP]['4'].next_state = ERROR	/*next state is calc*/; 
	lut[WAIT_4_OP]['4'].act_func = NULL		/*act_func for syntax error*/;
	lut[WAIT_4_NUM]['4'].next_state = WAIT_4_OP; 
	lut[WAIT_4_NUM]['4'].act_func = NULL;/*save number 2 stack_of_numbers and read next input*/

	lut[WAIT_4_OP]['5'].next_state = ERROR	/*next state is calc*/; 
	lut[WAIT_4_OP]['5'].act_func = NULL		/*act_func for syntax error*/;
	lut[WAIT_4_NUM]['5'].next_state = WAIT_4_OP; 
	lut[WAIT_4_NUM]['5'].act_func = NULL; /*save number 2 stack_of_numbers and read next input*/

}

/*store num func*/
/*store op func*/
/*read next num func*/
/*calculate equation func*/












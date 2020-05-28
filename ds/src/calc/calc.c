
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      27.05.2020               **
**  Reviewer:  Hanna					**
**  Status:    ????						**
*****************************************/


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

static lut_elem_t lut[NUM_OF_STATES][NUM_OF_EVENTS] = {ERROR};

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

static void DefineLUT(void)
{
	/*LUT definition - for now only for: 4 + 5 */
	lut[WAIT_4_OP]['+']	= {};
	lut[WAIT_4_NUM]['+'] = {};

	lut[WAIT_4_OP]['4']	= {ERROR, /*act_func for syntax error*/};
	lut[WAIT_4_NUM]['4'] = {WAIT_4_OP, /*save number 2 stack_of_numbers*/};
	
	lut[WAIT_4_OP]['5']	= {ERROR, /*act_func for syntax error*/};
	lut[WAIT_4_NUM]['5'] = {WAIT_4_OP, /*save number 2 stack_of_numbers*/};
}


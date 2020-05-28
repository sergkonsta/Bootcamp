
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

#define UNUSED(X) (void)(X)

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
static status_t StoreNum(char **equation, calc_t *equation_elems);
static status_t StoreOp(char **equation, calc_t *equation_elems);
static status_t CalcEquation(char **equation, calc_t *equation_elems);
static status_t SyntaxError(char **equation, calc_t *equation_elems);

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

	/*


	BUISINESS LOGIC
	/*gets first char and goes to table - inside act_func the rest of the char is recieved with strtod*/

	*/
	
	return (SUCCESS);
}

/*LUT definition*/
static void DefineLUT(void)
{
	/*LUT definition - for now only for: 4 + 5 and '\0', space*/
	
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
	lut[WAIT_4_OP]['+'].next_state = 	WAIT_4_NUM	/*next state is calc*/; 
	lut[WAIT_4_OP]['+'].act_func = 		StoreOp;
	lut[WAIT_4_NUM]['+'].next_state = 	ERROR; 
	lut[WAIT_4_NUM]['+'].act_func =		SyntaxError;
	
	/* number 4 case */
	lut[WAIT_4_OP]['4'].next_state = 	ERROR		/*next state is calc*/; 
	lut[WAIT_4_OP]['4'].act_func = 		SyntaxError;
	lut[WAIT_4_NUM]['4'].next_state = 	WAIT_4_OP; 
	lut[WAIT_4_NUM]['4'].act_func = 	StoreNum;
	
 	/* number 5 case */
	lut[WAIT_4_OP]['5'].next_state = 	ERROR		/*next state is calc*/; 
	lut[WAIT_4_OP]['5'].act_func = 		SyntaxError;
	lut[WAIT_4_NUM]['5'].next_state = 	WAIT_4_OP; 
	lut[WAIT_4_NUM]['5'].act_func = 	StoreNum;

}

/*store num func, return next char/s */
static status_t StoreNum(char **equation, calc_t *equation_elems)
{
	assert(NULL != equation_elems);
	assert(NULL != equation);

	/*push to stack*/
	StackPush();
	
	/*get next num*/

	/*return status*/
}

/*store op func, return next char/s */
static status_t StoreOp(char **equation, calc_t *equation_elems)
{

}

/*calculate equation func*/
static status_t CalcEquation(char **equation, calc_t *equation_elems)
{

}

/*read next num func*/
static status_t SyntaxError(char **equation, calc_t *equation_elems)
{
	UNUSED(equation);
	UNUSED(equation_elems);
	
	return (SYNTAX_ERR);
}








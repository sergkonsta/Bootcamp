/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      07.04.2020               **
**  Reviewer:  Eliran					**
**  Status:    in progress				**
*****************************************/
#include <stddef.h>		/*for size_t*/
#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/


#include "stack.h"

struct stack		
	{	
	void **base_element;	
	size_t capacity;	
	size_t size;	
	};

stack_t *StackCreate(size_t capacity)
{	
	/*creating the stack struct*/
	stack_t *stack_ptr = (stack_t *)malloc(sizeof(stack_t));
	if(NULL == stack_ptr)
	{
		return (NULL);
	}
	
	/*assert reasonable input from user*/
	assert(0 < capacity);
		
	/*initializing members: size & capacity*/
	stack_ptr->capacity = capacity; 
	stack_ptr->size = 0;
	
	/*initializing member that points to the stack array*/
	
	stack_ptr->base_element = (void**)malloc(sizeof(void *) * stack_ptr->capacity);
	if(NULL == stack_ptr->base_element)
	{
		free(stack_ptr);
		stack_ptr = NULL;
		return (NULL);
	}
	
	return (stack_ptr);
}


/*----------------------------------------------------------------------------*/
/*frees allocated memory and rmeoves dangaling pointers*/
void StackDestroy(stack_t *s_ptr)
{
	assert(NULL != s_ptr);
	
	free(s_ptr->base_element);
	
	s_ptr->base_element = NULL;
	
	free(s_ptr);
	
	s_ptr = NULL;
	
	return;	
}


/*----------------------------------------------------------------------------*/

void StackPush(stack_t *s_ptr, void *element)
{
	assert(NULL != s_ptr);
	assert(s_ptr->size < s_ptr->capacity);
	
	*(s_ptr->base_element + s_ptr->size) = element; 
	++s_ptr->size;
	
	return;
}


/*----------------------------------------------------------------------------*/

void StackPop(stack_t *s_ptr)
{
	assert(NULL != s_ptr);
	assert(0 != s_ptr->size);
	
	--s_ptr->size;
		
	return;
}


/*----------------------------------------------------------------------------*/
void *StackPeek(stack_t *s_ptr)
{		
	assert(NULL != s_ptr);
	assert(0 != s_ptr->size);
	
	return *(s_ptr->base_element + (s_ptr->size - 1));
}


/*----------------------------------------------------------------------------*/

size_t StackSize(stack_t *s_ptr)
{
	assert(NULL != s_ptr);
	
	return (s_ptr->size);
}


/*----------------------------------------------------------------------------*/
/*returns 0 when empty*/
int StackIsEmpty(stack_t *s_ptr)
{
	assert(NULL != s_ptr);
	
	return (0 == s_ptr->size);
}


/*----------------------------------------------------------------------------*/
size_t StackCapacity(stack_t *s_ptr)
{
	assert(NULL != s_ptr);
	
	return (s_ptr->capacity);
}



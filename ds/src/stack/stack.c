#include "stack.h"

stack_t *StackCreate(size_t capacity)
{
	void *tmp = NULL;
	
	/*creating the stack struct for global access*/
	stack_t *stack_struct = (stack_t *)malloc(sizeof(stack_t));
	
	/*initializing members: size & capacity*/
	stack_struct->capacity = capacity; 
	stack_struct->size = 0;
	
	/*initializing member that points to the stack array*/
	tmp = malloc(sizeof(void *) * stack_struct->capacity);
	stack_struct->base_element = &tmp;	

	return stack_struct;
}

#include <stddef.h>		/*for size_t*/
#include <assert.h>		/*for assert*/
#include <stdio.h>		/*for printf*/

#include "stack.h"

struct stack		
	{	
	void **base_element;	
	size_t capacity;	
	size_t size;	
	};

static void PrintStatus(stack_t *stk, int num);

int main()
{
	int i = 1; 
	char ch = 'S';
	size_t s_t = 1000;
	void *a = &i;
	void *b = &ch;
	void *c = &s_t;
	
	stack_t *stk1 = StackCreate(3);
	PrintStatus(stk1,1);
	
	StackPush(stk1, a);
	PrintStatus(stk1,1);
	
	printf("peek at stack 1: %d\n",*(int *)StackPeek(stk1));

	StackPush(stk1, b);
	PrintStatus(stk1,1);				
	printf("peek at stack 1: %c\n",*(char *)StackPeek(stk1));
		
	StackPush(stk1, c);
	PrintStatus(stk1,1);				
	printf("peek at stack 1: %ld\n",*(size_t *)StackPeek(stk1));

	StackDestroy(stk1);
	
	return 1;
}


static void PrintStatus(stack_t *stk, int num)
{
	printf("\nstack %d:\nsize: %ld,\ncapacity: %ld,\nis empty: %d.\n\n"
			,num
			,(size_t)StackSize(stk)
			,(size_t)StackCapacity(stk)
			,(int)StackIsEmpty(stk));
			
	return;	
}

































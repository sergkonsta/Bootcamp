/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      02.06.2020               **
**  Reviewer:  Ohad Shafry				**
**  Status:    Sent						**
*****************************************/

#include <stddef.h>	/*for size_t*/
#include <stdio.h>	/*for printf*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for strlen*/
#include <stdlib.h>	/*for calloc*/


#include "recursion.h"






/*fibonacci funcs*/
static int FibTailRec(int elem_index, int a, int b);

/*strings funcs*/
static size_t StrLenTailRecursive(const char *str, size_t length);

static int StrnCmpTailRecursive(const char *str1, const char *str2, size_t n);

/*flip slist*/
static slist_iter_t FlipListTailRecursive(slist_iter_t curr, slist_iter_t prev);

/*recursive stack sorting using 2 recursive funcs*/
static void SortedInsert(stack_t *stk, void *element);
static int StackCmp(stack_t *stk, void *element);

/*----------------------------------------------------------------------------*/
/*----------------  	          Fibonacci					  ----------------*/
/*----------------------------------------------------------------------------*/

/*wrapper for tail-recursion*/
int FibonacciRecursive(int elem_index)
{
	return ( FibTailRec(elem_index, 0, 1) );	
}

static int FibTailRec(int elem_index, int a, int b)
{
	if(0 == elem_index)
	{
		return (a);
	}
	
	if(1 == elem_index)
	{
		return (b);
	}
		
	return ( FibTailRec(elem_index - 1, b, a + b) );
}

 int FibNotTailRec(int element_index)
{
	assert(element_index >= 0);
	
	if (0 == element_index)
	{
		return (0);	
	}
	
	else if (1 == element_index)
	{
		return (1);
	}

	return (FibNotTailRec(element_index - 1) +
		FibNotTailRec(element_index -2));
}

int FibonacciIterative(int elem_index)
{		
	size_t i = 0;
	
	int result[3] = {0, 1, 0};
	
	for(i = 2; i < (size_t)elem_index; i++)
	{
		result[2] = result[1] + result[0];
		result[0] = result[1];
		result[1] = result[2];
	}
	
	return (result[1] + result[0]);
}



/*----------------------------------------------------------------------------*/
/*----------------  	          Strings					  ----------------*/
/*----------------------------------------------------------------------------*/

/*wrapper for tail recursion*/
size_t StrLenRecursive(const char *str)
{
	assert(NULL != str);
	
	return (StrLenTailRecursive(str, 0));
}

static size_t StrLenTailRecursive(const char *str, size_t length)
{
	assert(NULL != str);
	
	/*stop if str ended*/
	if('\0' == *str)
	{
		return (length);
	}
	
	return ( StrLenTailRecursive(str + 1, length + 1) );
}


/*----------------------------------------------------------------------------*/
int StrCmpTailRecursive(const char *str1, const char *str2)
{	
	assert(NULL != str1);
	assert(NULL != str2);
	
	/*stop if strings unequal*/
	if(0 != (*str1 - *str2))
	{
		return (*str1 - *str2);
	}

	/*stop if strings ended and equal*/
	if('\0' == *str1)
	{
		return (0);
	}
	
	/*keep going*/	
	return ( StrCmpTailRecursive(str1 + 1, str2 + 1) );
}


/*----------------------------------------------------------------------------*/
static int StrnCmpTailRecursive(const char *str1, const char *str2, size_t n)
{	
	assert(NULL != str1);
	assert(NULL != str2);
	
	/*stop if strings unequal*/
	if(0 != (*str1 - *str2))
	{
		return (*str1 - *str2);
	}

	/*stop if strings ended and equal*/
	if('\0' == *str1 || 0 == n)
	{
		return (0);
	}
	
	/*keep going*/	
	return ( StrnCmpTailRecursive(str1 + 1, str2 + 1, n - 1) );
}

/*----------------------------------------------------------------------------*/
/*wrapper for dest return*/
char *StrCpyRecursive(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	StrCpyTailRecursive	(dest, src);
	
	return (dest);
}

char *StrCpyTailRecursive(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	/*stop when src ends*/	
	if('\0' == *src)
	{
		*dest = *src;
		return (0);
	}

	*dest = *src;
	
	StrCpyTailRecursive(dest + 1, src + 1);
	
	return ( dest );
}


/*----------------------------------------------------------------------------*/
char *StrCatRecursive(char *dest, const char *src)
{
	size_t end_of_dest = 0;
	
	assert(NULL != dest);
	assert(NULL != src);	

	end_of_dest = StrLenRecursive(dest);
	
	StrCpyRecursive(dest + end_of_dest, src);
	
	return (dest);
}


/*----------------------------------------------------------------------------*/
char *StrStrRecursive(const char *haystack, const char *needle)
{
	assert(haystack);
	assert(needle);

	/*stop if haystack ended*/
	if('\0' == *haystack)
	{
		return (NULL);
	}
	
	/*stop if needle found*/
	if( 0 == StrnCmpTailRecursive(haystack, needle, StrLenRecursive(needle) - 1) )
	{
		return ((char *)haystack);
	}
	
	return ( StrStrRecursive(haystack + 1, needle) );
}




/*----------------------------------------------------------------------------*/
/*----------------  	       Flip SList					  ----------------*/
/*----------------------------------------------------------------------------*/

/*wrapper*/
slist_iter_t FlipList(slist_iter_t node)
{
	/*call tail recursive with head and prev = NULL*/
	return ( FlipListTailRecursive(node, NULL) );
}

/*flip next pointers until end of list is reached*/
static slist_iter_t FlipListTailRecursive(slist_iter_t curr, slist_iter_t prev)
{
	slist_iter_t next_tmp = NULL;

	assert(NULL != curr);
	
	/*stop when end of list is reached*/
	if(NULL == curr->next)
	{
		curr->next = prev;
		return (curr);
	}
	
	/*point this node to previous node*/
	next_tmp = curr->next;
	curr->next = prev; 
		
	return ( FlipListTailRecursive(next_tmp, curr) );	
}



/*----------------------------------------------------------------------------*/
/*----------------  	       Stack Sort					  ----------------*/
/*----------------------------------------------------------------------------*/
/*based on 2 recursive funcs*/

stack_t *SortStack(stack_t *stk)
{
	void *temp = NULL;	
	
	assert(NULL != stk);
	
	if(0 == StackIsEmpty(stk))
	{
		temp = StackPeek(stk);
		StackPop(stk);
		
		SortStack(stk);
		
		SortedInsert(stk, temp);
	}

	return (stk);
}

static void SortedInsert(stack_t *stk, void *element)
{
	void *temp = NULL;
	
	assert(NULL != stk);
	
	if(StackIsEmpty(stk) || (StackCmp(stk, element) < 0) )
	{
		StackPush(stk, element);
	}
	
	else
	{
		temp = StackPeek(stk);
		StackPop(stk);
		
		SortedInsert(stk, element);
		
		StackPush(stk,temp);
	}
	
	return;
}

static int StackCmp(stack_t *stk, void *element)
{
	int stack_int = 0;
	int element_int = 0;
	
	assert(NULL != stk);
	
	stack_int = *(int *)StackPeek(stk);
	element_int = *(int *)element;

	return (stack_int - element_int);
}



#include <stddef.h>	/*for size_t*/
#include <stdio.h>	/*for printf*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for strlen*/
#include <stdlib.h>	/*for calloc*/


#include "recursion.h"

/*test funcs*/
static void FibTest();
static void StringTest();
static void FlipCheck();
static void StackSortCheck();

/*----------------------------------------------------------------------------*/
/*----------------  	          Main						  ----------------*/
/*----------------------------------------------------------------------------*/




int main ()
{
	FibTest();
	
	StringTest();
	
	FlipCheck();
	
	StackSortCheck();
	
	printf("\n\nIf no errors printed - you are good!\n\n");	
	return (0);
}






/*----------------------------------------------------------------------------*/
/*----------------  	           Tests					  ----------------*/
/*----------------------------------------------------------------------------*/


/*----------------------------Fibonacci check---------------------------------*/
static void FibTest()
{

	int result = 0;

	result = FibonacciIterative(10);
	if(55 != result)
	{
		printf("\n Error in %d.\n",__LINE__);
	}
	
	result = FibonacciRecursive(10);
	if(55 != result)
	{
		printf("\n Error in %d.\n",__LINE__);
	}
	
}


/*----------------------------Fibonacci check---------------------------------*/

static void StringTest()
{
	const char* test_string = "abc defg!";
	
	char str1[50] = "abcdefgh";
	char str2[50] = "abcdegh";
	char str3[50] = "ab cdegh";
	char str4[50] = "ab cdefgh";
	char str5[50] = "abcd";
	char str6[50] = "abcdefgh";
	char str7[50] = "abcdefgh";
	char str8[50] = "abcd";
	
	const char src1[] = "abcdefgh";
	const char src2[] = "abcdegh";
	const char src3[] = "ab cdegh";
	char dest1[20] = "";
	char dest2[20] = "";
	char dest3[20] = "";
	
	char cat1[20] = "12345";
	char cat2[20] = "6789";
	
	char haystack[20] = "hello my name is";
	char needle1[20] = "my ";
	char needle2[20] = "m y";
	/*--------------------StrLen check---------------------------------*/
	if(StrLenRecursive(test_string) != strlen(test_string))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	
	/*--------------------StrCmpTailRecursive check---------------------------------*/
	if(StrCmpTailRecursive(str1, str2) != strcmp(str1, str2))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if(StrCmpTailRecursive(str3, str4) != strcmp(str3, str4))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( !(StrCmpTailRecursive(str5, str6) < 0) )
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( !(StrCmpTailRecursive(str7, str8) > 0) )
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( !(StrCmpTailRecursive("abcd er", "abcd er") == 0) )
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	
	/*--------------------StrCpyRecursive check---------------------------------*/
	/*check return value*/
	if( dest1 != StrCpyRecursive(dest1, src1))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( dest2 != StrCpyRecursive(dest2, src2))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( dest3 != StrCpyRecursive(dest3, src3))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}

	/*check dest string*/
	if( StrCmpTailRecursive(dest1, src1) != 0)
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( StrCmpTailRecursive(dest2, src2) != 0)
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( StrCmpTailRecursive(dest3, src3) != 0)
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	
	/*--------------------StrCatRecursive check-------------------------------*/
	if( cat1 != StrCatRecursive(cat1, cat2))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( StrCmpTailRecursive(cat1, "123456789") != 0)
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	/*--------------------StrStrRecursive check-------------------------------*/
	if( strstr(haystack, needle1) != StrStrRecursive(haystack, needle1))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
	if( strstr(haystack, needle2) != StrStrRecursive(haystack, needle2))
	{
		printf("\n Error in %d.\n",__LINE__);			
	}
}



/*----------------------------Flip	    check---------------------------------*/
static void FlipCheck()
{
	size_t i = 0;

	int sorted_test_arr[] = {5, 4, 3, 2, 1};
	
	slist_t *slist = SListCreate();
	
	slist_iter_t iter = SListBegin(slist);

	iter = SListInsert(iter, (void *)1);	
	iter = SListInsert(iter, (void *)2);	
	iter = SListInsert(iter, (void *)3);
	iter = SListInsert(iter, (void *)4);
	iter = SListInsert(iter, (void *)5);	

	iter = SListBegin(slist);
	
	FlipList(SListBegin(slist));
	
	iter = SListNext(SListEnd(slist));

	for(i = 0; i < 5; i++)
	{
		if(sorted_test_arr[i] != (int)(long)SListGetData(iter))
		{
			printf("\n Error in %d.\n",__LINE__);					
		}		
	
		iter = SListNext(iter);
	}
	
	FlipList(SListEnd(slist));
	SListDestroy(slist);
}


/*----------------------------Stack Sortcheck---------------------------------*/
/*roy ruach test*/
static void StackSortCheck()
{

	int arr[] = {10, 30, 20, 40, 60, 50};
	int sorted_test_arr[] = {60, 50, 40, 30, 20, 10};
	
	stack_t *stack = StackCreate(sizeof(arr)/sizeof(arr[0]));
	size_t i = 0;
	
	/* create stack with numbers */
	for (i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{
		StackPush(stack, (void *)&arr[i]);
	}
	
	/* pop all elements */
	for (i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{		
		StackPop(stack);
	}
	
	/* re-insert elements*/
	for (i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{
		StackPush(stack, (void *)&arr[i]);
	}
	
	SortStack(stack);

	/* pop check */
	for (i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{
		if(sorted_test_arr[i] != *(int *)StackPeek(stack))
		{
			printf("\n Error in %d.\n",__LINE__);					
		}
		
		StackPop(stack);
	}

	StackDestroy(stack);
}




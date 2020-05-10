
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#include "fsa.h"

#define INIT_RUNS -100

/*Macors for printig test status result*/
#define FAIL(text)	(printf("****** ERROR in %s ******\n",text))
#define OK(text) 	(printf("Status: OK. Test: %s \n",text))
#define UNUSED(id) (void)id

/* test ints */
static void TestInt(int in_int, int expected, char *text)
{
	if ( expected == in_int )
	{
		printf("\033[1;32m");
		printf("Status: OK. Test: %s. val=%d\n",text,in_int);
		printf("\033[0m");
	}
	else 
	{
		printf("\033[1;31m");		
		printf("** FAIL ** FAIL ** FAIL ** Test: %s. val=%d\n",text,in_int);
		printf("\033[0m");
	}
	
	return;
}


static void TestRelese()
{
	int i = 0;
	size_t suggest = 0;
	
	fsa_t *pool_1 = NULL;

	void *malloc_100 = NULL;
	void *alloc_1 = NULL;	
	void *alloc_2 = NULL;	
	void *alloc_3 = NULL;	
	void *alloc_4 = NULL;	

	void *malloc_1000 = NULL;


	puts("Test Release Compile");
		
	suggest = FSASuggestSize(0,0);
	TestInt(suggest, 24, "sizeof fsa_t: 24");
	suggest	= FSASuggestSize(1, 10);
	TestInt(suggest, 48, "fsa_t + 1 block of 10: 48");
	suggest	= FSASuggestSize(2, 2);
	TestInt(suggest, 56, " sizeof fsa_t + 2 blocks of 2: 56");
	suggest	= FSASuggestSize(1, 0);
	TestInt(suggest, 32, " sizeof fsa_t + 1 blocks of 0: 32");

	puts("init 72,2");
	malloc_100 = malloc(FSASuggestSize(72,2));
	pool_1 = FSAInit(malloc_100,72,2);
	TestInt(FSACountFree(pool_1), 3, " Count FSAInit(72,2) is 3");

	puts("alloc 1");
	alloc_1 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 2, " Count FSAInit(72,2) after 1 alloc is 2");
	puts("alloc 2");
	alloc_2 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 1, " Count FSAInit(72,2) after 2 alloc is 1");
	puts("alloc 3");
	alloc_3 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 0, " Count FSAInit(72,2) after 3 alloc is 0");
	TestInt(!alloc_3, 0, "ptr from alloc is not NULL");
	puts("alloc 4");
	alloc_4 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 0, " Count FSAInit(72,2) after 4 alloc is 0");
	TestInt((long)alloc_4, 0, "ptr from alloc is NULL after alloc from full pool");

	puts("free first alloc");
	FSAFree(alloc_1);
	TestInt(FSACountFree(pool_1), 1, " Count FSAInit(72,2) after 1 free ");
	puts("alloc again");
	alloc_1 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 0, " Count FSAInit(72,2) alloc again ");
	puts("free all 3 allocs");
	FSAFree(alloc_1);
	FSAFree(alloc_2);
	FSAFree(alloc_3);
	TestInt(FSACountFree(pool_1), 3, " Count FSAInit(72,2) free all ");
	puts("alloc 1");
	alloc_1 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 2, " Count FSAInit(72,2) after 1 alloc is 2");
	puts("alloc 2");
	alloc_2 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 1, " Count FSAInit(72,2) after 2 alloc is 1");
	puts("alloc 3");
	alloc_3 = FSAAlloc(pool_1);
	TestInt(FSACountFree(pool_1), 0, " Count FSAInit(72,2) after 3 alloc is 0");
	TestInt(!alloc_3, 0, "ptr from alloc is not NULL");
	puts("alloc 4");
	TestInt(FSACountFree(pool_1), 0, " Count FSAInit(72,2) after 4 alloc is 0");
	TestInt((long)alloc_4, 0, "ptr from alloc is NULL after alloc from full pool");
	free(malloc_100);
	
	suggest = FSASuggestSize(100,8);
	printf("malloc  FSASuggestSize(100,8) %lu \n",suggest);
	malloc_1000 = malloc(suggest);
	pool_1 = FSAInit(malloc_1000,suggest,8);
	TestInt(FSACountFree(pool_1), 100, " Count FSAInit(FSASuggestSize(100,8),8) ");
	
	i = 0;
	while (alloc_1)
	{
		alloc_1 = FSAAlloc(pool_1);
		++i;
	}
	TestInt(i, 101, "Number off allocs untill return is null should be 100+1");
	TestInt(FSACountFree(pool_1), 0, " Count after 100 allocs");

	free(malloc_1000);

	
}

static void TestDebug()
{
	size_t suggest = 0;
	void *malloc_100 = NULL;

	fsa_t *pool_1 = NULL;

	void *alloc_1 = NULL;
	void *alloc_2 = NULL;
	void *alloc_3 = NULL;

	puts("Test Debug Compile ");
	puts(" Get suggest size for 2 blocks of 2 ");
	printf(" size is : %lu \n ", FSASuggestSize(2,2));

	puts("malloc the size");
	malloc_100 = malloc(FSASuggestSize(2,2));
	puts("init pool of 2 blocks of 2");
	pool_1 = FSAInit(malloc_100,FSASuggestSize(2,2),2);
	TestInt(FSACountFree(pool_1), 2, " Count FSAInit(72,2) is 2");

	alloc_1 = FSAAlloc(pool_1);
	TestInt(!alloc_1, 0, "ptr from alloc not NULL after alloc");
	alloc_2 = FSAAlloc(pool_1);
	TestInt(!alloc_2, 0, "ptr from alloc not NULL after alloc");
	TestInt(FSACountFree(pool_1), 0, " pool is full count is 0");
	puts("free 1 block");
	FSAFree(alloc_1);
	TestInt(FSACountFree(pool_1), 1, " Count is 1");
	puts("free 1 block");
	FSAFree(alloc_2);
	TestInt(FSACountFree(pool_1), 2, " Count is 2");
	alloc_1 = FSAAlloc(pool_1);
	TestInt(!alloc_1, 0, "ptr from alloc not NULL after alloc");
	alloc_2 = FSAAlloc(pool_1);
	TestInt(!alloc_2, 0, "ptr from alloc not NULL after alloc");


	free(malloc_100);
}	

int main()
{
	/*in debug add magic number to meta*/
	#ifndef NDEBUG
	TestDebug();	
	#else
	TestRelese();	
	#endif

	return 0;
}

#include <stddef.h>		/*for size_t*/
#include <assert.h>		/*for assert*/
#include <stdio.h>		/*for printf*/

#include "dynamic_vector.h"

struct vector 
{
	void **base;
	size_t capacity;
	size_t size;
};

static void PrintStatus(vector_t *vec, int num);


/*----------------------------------------------------------------------------*/

int main()
{
	int fail_flag = 0;
	
	int i = 1; 
	char ch = 'S';
	size_t s_t = 1000;

	void *a = &i;
	void *b = &ch;
	void *c = &s_t;
	
	vector_t *vec1 = DynVecCreate(3);
	
	DynVecSetValue(vec1, 0, a);
	DynVecSetValue(vec1, 1, b);
	fail_flag = DynVecAppend(vec1, c);
	if(1 == fail_flag)
	{
		printf("\nfailed on line %d!!!\n\n",__LINE__);
	}
	
	printf("\nvalue of index: %d is: %d\n\n",0,*(int *)DynVecGetValue(vec1,0));
	printf("\nvalue of index: %d is: %c\n\n",1,*(char *)DynVecGetValue(vec1,1));
	printf("\nvalue of index: %d is: %ld\n\n",2,*(size_t *)DynVecGetValue(vec1,2));
	PrintStatus(vec1, 1);
	
	fail_flag = DynVecAppend(vec1, a);
	if(1 == fail_flag)
	{
		printf("\nfailed on line %d!!!\n\n",__LINE__);
	}
	
	fail_flag = DynVecAppend(vec1, b);
	if(1 == fail_flag)
	{
		printf("\nfailed on line %d!!!\n\n",__LINE__);
	}
	
	printf("\nvalue of index: %d is: %d\n\n",3,*(int *)DynVecGetValue(vec1,3));
	printf("\nvalue of index: %d is: %c\n\n",4,*(char *)DynVecGetValue(vec1,4));
	PrintStatus(vec1, 1);
		
	DynVecRemoveEnd(vec1);	
	
	printf("\nvalue of index: %d is: %d\n\n",3,*(int *)DynVecGetValue(vec1,3));
	printf("\nvalue of index: %d is: %c\n\n",4,*(char *)DynVecGetValue(vec1,4));
	PrintStatus(vec1, 1);
	
	fail_flag = DynVecShrinkToFit(vec1);
	if(1 == fail_flag)
	{
		printf("\nfailed on line %d!!!\n\n",__LINE__);
	}
		
	PrintStatus(vec1, 1);
	
	DynVecDestroy(vec1);
	
	return 0;
}


/*----------------------------------------------------------------------------*/

static void PrintStatus(vector_t *vec, int num)
{
	printf("\ndynamic vector %d:\nsize: %ld,\ncapacity: %ld.\n\n"
			,num
			,(size_t)DynVecSize(vec)
			,(size_t)DynVecCapacity(vec));

			
	return;	
}


































#include <assert.h>
#include <stdio.h>
 
#include "avl.h"

#define UNUSED(X) (void)(X)

int Cmp(const void *data_1, const void *data_2);
static int IncrementSizetByOneImp(void *arg, void *num);


		
int main()
{
	size_t nodes_amount = 0;
	
	avl_t *avl = AVLCreate(Cmp);
		
	AVLInsert(avl, (void *)50);
	AVLInsert(avl, (void *)40);
	AVLInsert(avl, (void *)60);
	AVLInsert(avl, (void *)30);
	AVLInsert(avl, (void *)70);
	AVLInsert(avl, (void *)55);
		
	if(6 != AVLSize(avl))
	{
		printf("\nErr in line %d\n",__LINE__);
	}
	
	if((void *)55 != AVLFind(avl, (void *)55))
	{
		printf("\nErr in line %d\n",__LINE__);
	}
	
	if((void *)NULL != AVLFind(avl, (void *)12))
	{
		printf("\nErr in line %d\n",__LINE__);
	}
	
	if(0 != AVLForEach(avl, IncrementSizetByOneImp, &nodes_amount))
	{
		printf("\nErr in line %d\n",__LINE__);
	}
	if(6 != nodes_amount)
	{
		printf("\nErr in line %d\n",__LINE__);
	}
	
	
	AVLRemove(avl, (void *)50);
	if(5 != AVLSize(avl))
	{
		printf("\nErr in line %d\n",__LINE__);
	}
	
	AVLDestroy(avl);
	return (0);
}







static int IncrementSizetByOneImp(void *arg, void *num)
{
	assert(NULL != num);
	UNUSED(arg);
	
	++*(size_t *)num;
	
	return (0);
}

int Cmp(const void *data_1, const void *data_2)
{
	int num_1 = *(int *)&data_1;
	int num_2 = *(int *)&data_2;

	return (num_1 - num_2);
}

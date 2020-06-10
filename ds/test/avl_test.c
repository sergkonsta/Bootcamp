#include <stdio.h>

#include "avl.h"


#define ERROR (printf("error in line %d\n", __LINE__));
#define UNUSED(x) (void)(x)

/*------------------------------------------------------------------*/
static int Compare(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

static int PrintAVL(void *data, void *param)
{	
	printf("key: %d  hight: %lu\n", *(int *)data, (size_t)param);
	
	return 0;
} 

/*-----------------------------------------------------------------*/

int main()
{
	avl_t *avl = AVLCreate(Compare);
	avl_t *avl2 = AVLCreate(Compare);
	
	int d8 = 8;
	int d4 = 4;
	int d7 = 7;
	int d5 = 5;
	int d1 = 1;
	int d9 = 9;
	int d2 = 2;
	int d3 = 3;
	int d6 = 6;
	
	int d10 = 10;
	int d11 = 11;
	int d12 = 12;
	int d13 = 13;
/*-------------------------------------------------------------------*/
	AVLInsert(avl, &d4);
	AVLInsert(avl, &d3);
	AVLInsert(avl, &d2);
	AVLInsert(avl, &d6);
	AVLInsert(avl, &d9);
	AVLInsert(avl, &d1);
	AVLInsert(avl, &d7);
	AVLInsert(avl, &d5);
	AVLInsert(avl, &d8);
	
	if(9 != AVLSize(avl))
	{
		ERROR
	}
	
	AVLForEach(avl, PrintAVL, NULL);
	printf("----------------------------------------------------------\n");
	
	if(3 != AVLHeight(avl))
	{
		ERROR
		printf("root hight: %lu\n", AVLHeight(avl));
	}
/*---------------------------------------------------------------------------*/
	
	AVLRemove(avl, &d3);
	AVLRemove(avl, &d6);
	
	if(2 != AVLHeight(avl))
	{
		ERROR
		printf("root hight: %lu\n", AVLHeight(avl));
	}
/*-----------------------------------------------------------------------------*/
	AVLRemove(avl, &d8);
	
	if(2 != AVLHeight(avl))
	{
		ERROR
		printf("root hight: %lu\n", AVLHeight(avl));
	}
	
	if(6 != AVLSize(avl))
	{
		ERROR
	}
/*-------------------------------------------------------------------------------*/
	AVLInsert(avl, &d3);
	
	if(NULL == AVLFind(avl, &d3))
	{
		ERROR
	}
/*---------------------------------------------------------------------------------*/
	AVLInsert(avl2, &d10);
	AVLInsert(avl2, &d11);
	AVLInsert(avl2, &d12);
	AVLInsert(avl2, &d13);

	AVLForEach(avl2, PrintAVL, NULL);
	
	AVLDestroy(avl);
	AVLDestroy(avl2);
	

return 0;
}




#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/
#include <stdio.h>

#include "sorted_list.h"
#include "dlist.h"

#define UNUSED(x) (void)(x)

static int IsBefore(const void *data1, const void *data2);
static int IsEqual(const void *arg_1, const void *arg_2);

/*from dlist.c*/
int IncrementSizetByOne(void *arg, void *num);

sort_list_iter_t CreateIter(sort_list_t *list);

int main()
{
	/*fo for each test*/
	size_t num_of_nodes = 0;
	void *tmp = (void *)&num_of_nodes;
	
	
	sort_list_t *list_1 = SortListCreate(IsBefore);
	sort_list_t *list_2 = SortListCreate(IsBefore);
	
	sort_list_iter_t iter_1 = CreateIter(list_1);
	sort_list_iter_t iter_2 = CreateIter(list_1);
	sort_list_iter_t iter_3 = CreateIter(list_1);
	sort_list_iter_t iter_4 = CreateIter(list_1);

	

/*----------------------------------------------------------------------------*/
/*fill list 1 with data*/
	SortListInsert(list_1, (void *)1);
	SortListInsert(list_1, (void *)10);
	SortListInsert(list_1, (void *)9);
	iter_4 = SortListInsert(list_1, (void *)8);
	SortListInsert(list_1, (void *)6);
	SortListInsert(list_1, (void *)0);
	SortListInsert(list_1, (void *)5);
	iter_3 = SortListInsert(list_1, (void *)3);
	SortListInsert(list_1, (void *)2);
	
/*----------------------------------------------------------------------------*/
/*fill list 2 with data*/
	SortListInsert(list_2, (void *)5);
	SortListInsert(list_2, (void *)12);
	SortListInsert(list_2, (void *)13);
	SortListInsert(list_2, (void *)17);
	SortListInsert(list_2, (void *)10);
	SortListInsert(list_2, (void *)11);
	SortListInsert(list_2, (void *)12);
	SortListInsert(list_2, (void *)111);
	
/*----------------------------------------------------------------------------*/
/*prints both lists*/	
	iter_1 = SortListBegin(list_1);
	printf("\n\n\nlist 1:\n");
	while(1 != SortListIsIterEqual( SortListEnd(list_1), iter_1) )
	{
		printf("%d, ",(int)SortListGetData(iter_1));
		iter_1 = SortListNext(iter_1);
	}
	printf("\nlist 2:\n");
	iter_1 = SortListBegin(list_2);
	while(1 != SortListIsIterEqual( SortListEnd(list_2), iter_1) )
	{
		printf("%d, ",(int)SortListGetData(iter_1));
		iter_1 = SortListNext(iter_1);
	}

	
	/*-----------------SortListFindIf test------------------------------------*/	
	iter_2 = SortListFindIf(SortListBegin(list_1), SortListEnd(list_1), 
							IsEqual, (void *)3);
							
	if(1 != SortListIsIterEqual(iter_2, iter_3))
	{
		printf("\n problem at line: %d\n",__LINE__);
	}
	
	/*------------------------------SortListFind test - -----------------------
	return pointer to the node before which the param should be placed-------*/
	iter_2 = SortListFind(list_1, SortListBegin(list_1), SortListPrev(SortListEnd(list_1)), 
						 (void *)7);
							
	if(1 != SortListIsIterEqual(iter_2, iter_4))
	{
		printf("\n problem at line: %d\n",__LINE__);
	}
	
	iter_2 = SortListFind(list_1, SortListBegin(list_1), SortListPrev(SortListEnd(list_1)), 
						 (void *)999);
							
	if(1 != SortListIsIterEqual(iter_2, SortListPrev(SortListEnd(list_1))))
	{
		printf("\n problem at line: %d\n",__LINE__);
	}
	
	/*------------- Merge Test --------------------------------------------*/	
	SortListMerge(list_1, list_2);
	
	if(0 != SortListCount(list_2))
	{
		printf("\n problem at line: %d\n",__LINE__);
	}	
	if(17 != SortListCount(list_1))
	{
		printf("\n problem at line: %d\n",__LINE__);
	}
	
	iter_1 = SortListBegin(list_1);
	printf("\n\n\nmerged list:\n");
	while(1 != SortListIsIterEqual( SortListEnd(list_1), iter_1) )
	{
		printf("%d, ",(int)SortListGetData(iter_1));
		iter_1 = SortListNext(iter_1);
	}
	
	/*------------- For Each Test --------------------------------------------*/
	SortListForEach(SortListBegin(list_1), SortListEnd(list_1), 
				 IncrementSizetByOne, tmp);		
	if(17 != num_of_nodes)
	{
		printf("\n problem at line: %d\n",__LINE__);
	}			
				
					
/*----------------------------------------------------------------------------*/	
	printf("\n\n\n\n");	
	SortListDestroy(list_1);
	SortListDestroy(list_2);

	return 1;
}



/*----------------------------------------------------------------------------*/
/*								HELPERS										  */
/*----------------------------------------------------------------------------*/

static int IsBefore(const void *data1, const void *data2)
{	
	return (!!(data1 < data2));
}


/*----------------------------------------------------------------------------*/
/*
O(1)
returns 1 if arg_1 == arg_2
*/  
static int IsEqual(const void *arg_1, const void *arg_2)
{	
	return (!!(arg_1 == arg_2));
}






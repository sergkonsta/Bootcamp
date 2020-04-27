


#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/
#include <stdio.h>

#include "sorted_list.h"
#include "dlist.h"

#define UNUSED(x) (void)(x)

static int IsBefore(const void *data1, const void *data2);
static int IsEqual(const void *arg_1, const void *arg_2);


sort_list_iter_t CreateIter(sort_list_t *list);

int main()
{
	
	
	sort_list_t *list_1 = SortListCreate(IsBefore);
	
	sort_list_iter_t iter_1 = CreateIter(list_1);
	sort_list_iter_t iter_2 = CreateIter(list_1);
	sort_list_iter_t iter_3 = CreateIter(list_1);
	sort_list_iter_t iter_4 = CreateIter(list_1);

	
	

	
	

/*----------------------------------------------------------------------------*/
	SortListInsert(list_1, (void *)1);
	SortListInsert(list_1, (void *)10);
	SortListInsert(list_1, (void *)9);
	iter_4 = SortListInsert(list_1, (void *)8);
	SortListInsert(list_1, (void *)6);
	SortListInsert(list_1, (void *)5);
	iter_3 = SortListInsert(list_1, (void *)3);
	SortListInsert(list_1, (void *)2);

	
	iter_1 = SortListBegin(list_1);
	while(1 != SortListIsIterEqual( SortListEnd(list_1), iter_1) )
	{
		printf("%d, ",(int)SortListGetData(iter_1));
		iter_1 = SortListNext(iter_1);
	}
	
	
	SortListPopFront(list_1);
	SortListPopBack(list_1);
		
	
	/*-----------------SortListFindIf test------------------------------------*/	
	iter_2 = SortListFindIf(SortListBegin(list_1), SortListEnd(list_1), 
							IsEqual, (void *)3);
							
	if(1 != SortListIsIterEqual(iter_2, iter_3))
	{
		printf("\n problem at line: %d\n",__LINE__);
	}
	
	/*------------------------------SortListFind test - -----------------------
	return pointer to the node before which the param should be placed-------*/
	iter_2 = SortListFind(list_1, SortListBegin(list_1), SortListEnd(list_1), 
						 (void *)7);
							
	if(1 != SortListIsIterEqual(iter_2, iter_4))
	{
		printf("\n problem at line: %d\n",__LINE__);
	}
	
	
	/*------------- For Each Test --------------------------------------------*/

	/*------------- Merge Test --------------------------------------------*/			
				
				
					
/*----------------------------------------------------------------------------*/	
	
	SortListDestroy(list_1);

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





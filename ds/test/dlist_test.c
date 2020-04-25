#include <stdio.h>	/*for printf*/

#include "dlist.h"

static int IsEqual(const void *arg_1, const void *arg_2);

int main()
{		
	size_t counter = 0;
	
	dlist_t *dlist_1 = NULL;
	dlist_t *dlist_2 = NULL;
	dlist_t *multi_find_dlist = NULL;
	
	dlist_iter_t iter = NULL;
	
	dlist_iter_t find_iter_temp_1 = NULL;
	dlist_iter_t find_iter_temp_2 = NULL;
	dlist_iter_t find_iter_temp_3 = NULL;
	dlist_iter_t find_iter_temp_4 = NULL;
	
	dlist_iter_t splice_iter_from = NULL;
	dlist_iter_t splice_iter_to = NULL;
	dlist_iter_t splice_iter_where = NULL;
	
	dlist_1 = DListCreate();
	dlist_2 = DListCreate();
	multi_find_dlist = DListCreate();
	
	/*empty test*/
	if(1 != DListIsEmpty(dlist_1))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	
	/* creates dlist_1 : 1-2-3-4-5-6-7 */		
	DListInsert(DListBegin(dlist_1), (void *)4);
	DListPushFront(dlist_1, (void *)3);
	DListInsert(DListNext(DListPushBack(dlist_1, (void *)5)), (void *)6);
	DListInsert(DListPrev(DListNext(DListBegin(dlist_1))),(void *)2);
	DListInsert(DListBegin(dlist_1), (void *)1);
	DListPushBack(dlist_1, (void *)7);
	
	/* creates dlist_2 : 1-2-3-4-5-6-7 */	
	counter = 0;
	while(7 != counter)
	{
		DListInsert(DListBegin(dlist_2), (void *)17);	
		++counter;
	}	
	iter = DListBegin(dlist_2);
	DListSetData(iter, (void *)1);	
	iter = DListNext(iter);
	splice_iter_from = iter;
	DListSetData(splice_iter_from, (void *)2);	
	iter = DListNext(iter);
	DListSetData(iter, (void *)3);	
	iter = DListNext(iter);
	splice_iter_to = iter;
	DListSetData(iter, (void *)4);
	iter = DListNext(iter);
	DListSetData(iter, (void *)5);
	iter = DListNext(iter);
	find_iter_temp_1 = iter;
	splice_iter_where = iter;
	DListSetData(find_iter_temp_1, (void *)6);
	iter = DListNext(iter);
	DListSetData(iter, (void *)7);
		
	/*count check*/
	if(7 != DListCount(dlist_1))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	if(7 != DListCount(dlist_2))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	
	/*pops from back from each list*/
	DListPopBack(dlist_1);
	DListPopBack(dlist_2);
	
	/*count check*/
	if(6 != DListCount(dlist_1))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	if(6 != DListCount(dlist_2))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	
	if(	DListGetData(DListNext(DListBegin(dlist_1))) != 			
		DListGetData(DListNext(DListBegin(dlist_2))))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	
	/*find data = 6 in dlist_2 hwich will be in - iter is saved in find_iter_tmp*/
	if(	find_iter_temp_1 != DListFind(DListBegin(dlist_2), DListEnd(dlist_2),
		IsEqual, (void *)6))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	
	/*adds 3 nodes with value 6 to dlist_2 for 'multi find'*/	
	find_iter_temp_2 = DListPushBack(dlist_2, (void *)6);
	find_iter_temp_3 = DListPushBack(dlist_2, (void *)6);
	find_iter_temp_4 = DListPushBack(dlist_2, (void *)6);
	
	
	
	
/*----------------------------------------------------------------------------*/	
	/*multi find test for success*/
	if(0 != DListMultiFind(	DListBegin(dlist_2), DListEnd(dlist_2), 
					IsEqual, (void *)6, multi_find_dlist))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	/*checks multilist outlist: 'multi_find_dlist' in any order*/
	while(1 != DListIsEmpty(multi_find_dlist))
	{
		if( find_iter_temp_1 != DListGetData(DListBegin(multi_find_dlist)) &&
			find_iter_temp_2 != DListGetData(DListBegin(multi_find_dlist)) &&
			find_iter_temp_3 != DListGetData(DListBegin(multi_find_dlist)) &&
			find_iter_temp_4 != DListGetData(DListBegin(multi_find_dlist)) )
		{
			printf("\nproblem in line: %d\n",__LINE__);
		}
		
		DListRemove(DListBegin(multi_find_dlist));
	}
	
	




/*----------------------------------------------------------------------------*/		
	/*make dlist 1 & 2 equal again*/
	while(DListCount(dlist_1) != DListCount(dlist_2))
	{
		DListPopBack(dlist_2);
	}
	if(DListCount(dlist_1) != DListCount(dlist_2))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}
	
	
	
/*----------------------------------------------------------------------------*/	
	/*splice test*/
	
	DListSplice(splice_iter_from, splice_iter_to, splice_iter_where);
	
	if((void *)1 != DListGetData(DListBegin(dlist_2)))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}	
	DListRemove(DListBegin(dlist_2));
	
	if((void *)4 != DListGetData(DListBegin(dlist_2)))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}	
	DListRemove(DListBegin(dlist_2));
	
	if((void *)5 != DListGetData(DListBegin(dlist_2)))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}	
	DListRemove(DListBegin(dlist_2));
	
	if((void *)2 != DListGetData(DListBegin(dlist_2)))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}	
	DListRemove(DListBegin(dlist_2));
	
	if((void *)3 != DListGetData(DListBegin(dlist_2)))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}	
	DListRemove(DListBegin(dlist_2));
	
	if((void *)6 != DListGetData(DListBegin(dlist_2)))
	{
		printf("\nproblem in line: %d\n",__LINE__);
	}	
	DListRemove(DListBegin(dlist_2));
	
	printf("\n\n\n\nIF NO ERRORS PRINTED - HOORAY!\n\n\n\n");	
		
		
	DListDestroy(dlist_1);	
	DListDestroy(dlist_2);
	DListDestroy(multi_find_dlist);
	return (1);
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




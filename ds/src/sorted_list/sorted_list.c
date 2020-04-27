
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      26.04.2020               **
**  Reviewer:  Eden						**
**  Status:    Sent						**
*****************************************/		

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "sorted_list.h"
#include "dlist.h"

#define UNUSED(x) (void)(x)

struct sort_list
{
	dlist_t *dlist;
	int (*is_before)(const void *data1, const void *data2);
};

sort_list_iter_t CreateIter(sort_list_t *list);

/*----------------------------------------------------------------------------*/
/*
O(1) 
Create sorted list. 
return pointer to list or NULL if fails.
*/
sort_list_t *SortListCreate	
			(int (*is_before)(const void *data1, const void *data2))
{
	sort_list_t *list = NULL;
	
	assert(NULL != is_before);
	
	/*reserve space for  list struct*/
	list = (sort_list_t *)malloc(sizeof(sort_list_t));
	
	/*assign the user's comparison func to the sorted list*/
	list->is_before = is_before;
	
	/*create dlist and if fails: free & put NULL in return value*/
	list->dlist = DListCreate();
	if(NULL == list->dlist)
	{
		free(list);
		list = NULL;
	}
	
	return (list);
}
	
/*----------------------------------------------------------------------------*/	
/*
O(n) 
Destroy sorted list
*/
void SortListDestroy(sort_list_t *list)
{
	DListDestroy(list->dlist);
	list->dlist = NULL;
	
	list->is_before = NULL;
	
	free(list);
	list = NULL;
	
	return;
}


/*----------------------------------------------------------------------------*/	
/*
O(1)
first valid node (or End if empty) 
*/
sort_list_iter_t SortListBegin(sort_list_t *list)
{
	sort_list_iter_t iter = {NULL};
	
	assert(NULL != list);
	
	iter = CreateIter(list);
	iter.iter = DListBegin(list->dlist);
	
	return(iter);
}


/*----------------------------------------------------------------------------*/	
/*
O(1)
return End of list
*/
sort_list_iter_t SortListEnd(sort_list_t *list)
{
	sort_list_iter_t iter = {NULL};
	
	assert(NULL != list);
	
	iter = CreateIter(list);
	iter.iter = DListEnd(list->dlist);
	
	return(iter);
}

/*----------------------------------------------------------------------------*/	
/*
O(1)
Return next itertator . Iter given MUST BE DIFFERENT then End 
*/
sort_list_iter_t SortListNext(sort_list_iter_t iter)
{
	assert(NULL != iter.iter);
	assert(NULL != iter.list);
	
	iter.iter = DListNext(iter.iter);
	
	return(iter);
}


/*----------------------------------------------------------------------------*/	
/*
O(1)
Return previous itertator . Iter given MUST BE DIFFERENT then Begin 
*/
sort_list_iter_t SortListPrev(sort_list_iter_t iter)
{
	assert(NULL != iter.iter);
	assert(NULL != iter.list);
	
	iter.iter = DListPrev(iter.iter);
	
	return(iter);
}


/*----------------------------------------------------------------------------*/	
/* 
O(n) 
Success: Retrun iter to inserted data. 
Fail: retun End 
*/
sort_list_iter_t SortListInsert(sort_list_t *list, void *data)
{
	sort_list_iter_t where = {NULL};
	
	assert(NULL != list);
	
	where = CreateIter(list);	
	
	where.iter = DListInsert( 
							SortListFind(	list, SortListBegin(list), 
											SortListEnd(list), 	data).iter, 
							data );
	
	return(where);
}


/*----------------------------------------------------------------------------*/
/* 
O(1) 
Return iter to next node 
*/
sort_list_iter_t SortListRemove(sort_list_iter_t iter)
{
	assert(NULL != iter.iter);
	assert(NULL != iter.list);

	iter.iter = DListRemove(iter.iter);

	return ( iter );
}


/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the iterator of next node after pop. 
*/
sort_list_iter_t SortListPopFront(sort_list_t *list)
{
	sort_list_iter_t iter = {NULL}; 

	assert(NULL != list);
	
	iter = CreateIter(list);
	
	iter.iter = DListPopFront(list->dlist);
	
	return (iter);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the iterator of new last element after pop. 
*/
sort_list_iter_t SortListPopBack(sort_list_t *list)
{
	sort_list_iter_t iter = {NULL}; 

	assert(NULL != list);
	
	iter = CreateIter(list);
	
	iter.iter = DListPopBack(list->dlist);
	
	return (iter);
}


/*----------------------------------------------------------------------------*/
/* 
O(n) 
Count of valid nodes in list 
*/
size_t SortListCount(const sort_list_t *list)
{
	assert(NULL != list);
	
	return ( DListCount(list->dlist) );
}


/*----------------------------------------------------------------------------*/
/* 
O(1) 
Return True if list is empty 
*/
int SortListIsEmpty(const sort_list_t *list)
{
	assert(NULL != list);
	
	return ( DListIsEmpty(list->dlist) );
}


/*----------------------------------------------------------------------------*/
/* 
O(1) 
Return TRUE if two iterators are the same 
*/
int SortListIsIterEqual(sort_list_iter_t iter_1, sort_list_iter_t iter_2)
{
	return ( DListIsIterEqual(iter_1.iter, iter_2.iter) );
}


/*----------------------------------------------------------------------------*/
/*
O(1) 
Return void pointer to data
*/
void *SortListGetData(sort_list_iter_t iter)
{
	return ( DListGetData(iter.iter) );
}


/*----------------------------------------------------------------------------*/
/*
O(n) 	
Search Range "from"-"to"(exclusive)
Returns iter to first node found  according to is_before (places ind list struct),
	that param should be before him.
Return "to" if not found.
"from" and "to" must be from same list. 
*/
sort_list_iter_t SortListFind(	const sort_list_t *list, sort_list_iter_t from, 
								sort_list_iter_t to, const void *param)
{
	sort_list_iter_t from_temp = from;
		
	assert(from.list == to.list);
		
	while(	(0 == list->is_before(param, SortListGetData(from_temp))) && 
			(0 == SortListIsIterEqual(from_temp, to)))
	{
		from_temp = SortListNext(from_temp);
	}
	
	return (from_temp);
}



/*----------------------------------------------------------------------------*/
/*
O(n) 
Search Range "from"-"to"(exclusive)
Return first node found by is_equal.
Return "to" if not found.
"from" and "to" must be from same list. 
*/
sort_list_iter_t SortListFindIf
						(sort_list_iter_t from, 
						sort_list_iter_t to,
						int(*is_equal)(const void *data, const void *param), 
						const void *param)
{
	assert(from.list == to.list);
	
	to.iter = DListFind(from.iter, to.iter, is_equal, param);
	
	return (to);
}	


/*----------------------------------------------------------------------------*/
/*
O(n)
Apply action_func on every node in Range "from"-"to"(exclusive).
If status returned from action_func != 0, stop and return status.
When done return last status returned by action_func.
action_func must not change original order of sorted data.
*/
int SortListForEach(sort_list_iter_t from, 
					sort_list_iter_t to,
					int(*action_func)(void *data, void *arg), 
					void *arg)
{
	assert(from.list == to.list);		
	
	return (DListForEach(from.iter, to.iter, action_func, arg));
}

/*----------------------------------------------------------------------------*/
/*
O(n + m)  
Merge two sorted-lists into one. Return pointer to dest.
after merge source_list is empty(source list is not destroyed.) 
*/
sort_list_t *SortListMerge(sort_list_t *dest_list, sort_list_t *source_list)
{
	while(0 == SortListIsEmpty(source_list))
	{
		SortListInsert(dest_list, SortListGetData(SortListBegin(source_list)));
		SortListRemove( SortListBegin(source_list) );
	}
	
	return (dest_list);
}


/*----------------------------------------------------------------------------*/
/*creates iterator*/
sort_list_iter_t CreateIter(sort_list_t *list)
{
	sort_list_iter_t iter = {NULL};
	dlist_iter_t dlist_iter = NULL;
	
	assert(NULL != list);	
	
	iter.iter = dlist_iter;
		
	#ifndef NDEBUG
	iter.list = list;
	#endif /* NDEBUG */
	
	return (iter);
}









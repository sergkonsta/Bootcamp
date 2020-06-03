
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      26.04.2020               **
**  Reviewer:  Eden						**
**  Status:    Approved					**
*****************************************/		

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "sorted_list.h"
#include "dlist.h"

#define UNUSED(x) (void)(x)

struct sort_list
{
	dlist_t *dlist;
	int (*cmp_func)(const void *data1, const void *data2);
};

sort_list_iter_t CreateIter(sort_list_t *list);

/*----------------------------------------------------------------------------*/
/*
O(1) 
Create sorted list. 
return pointer to list or NULL if fails.
*/
sort_list_t *SortListCreate	
			(int (*cmp_func)(const void *data1, const void *data2))
{
	sort_list_t *list = NULL;
	
	assert(NULL != cmp_func);
	
	/*reserve space for  list struct*/
	list = (sort_list_t *)malloc(sizeof(sort_list_t));
	if(NULL == list)
	{
		return (NULL);
	}
	
	/*assign the user's comparison func to the sorted list*/
	list->cmp_func = cmp_func;
	
	/*create dlist and if fails: free & put NULL in return value*/
	list->dlist = DListCreate();
	if(NULL == list->dlist)
	{
		free(list);
		list = NULL;

		return (NULL);
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
	assert(NULL != list);
	assert(NULL != list->dlist);
	
	DListDestroy(list->dlist);
	list->dlist = NULL;
	
	list->cmp_func = NULL;
	
	free(list);
	
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
	assert(NULL != list->dlist);
		
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
	assert(NULL != list->dlist);
	
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
	assert(NULL != list->dlist);
	
	where = CreateIter(list);	
	
	where.iter = DListInsert( 
	SortListFind(list, SortListBegin(list), SortListEnd(list), data).iter, data);
	
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
void *SortListPopFront(sort_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->dlist);

	return (DListPopFront(list->dlist));
}


/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the iterator of new last element after pop. 
*/
void *SortListPopBack(sort_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->dlist);

	return (DListPopBack(list->dlist));
}


/*----------------------------------------------------------------------------*/
/* 
O(n) 
Count of valid nodes in list 
*/
size_t SortListCount(const sort_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->dlist);
	
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
	assert(NULL != list->dlist);
	
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
Returns iter to the first node 'higher' in order than param (according to users)
compare function.
"from" and "to" must be from same list. 
*/
sort_list_iter_t SortListFind(	const sort_list_t *list, sort_list_iter_t from, 
								sort_list_iter_t to, const void *param)
{
	sort_list_iter_t from_temp = from;
		
	assert(from.list == to.list);
	assert(NULL != list);
	assert(NULL != list->dlist);
	
	/*iterate until you find node with data higher than 'param' 
		(and while range didn't end)*/
	while(	(0 <= list->cmp_func(param, SortListGetData(from_temp))) && 
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
Return first node found by cmp_func.
Return "to" if not found.
"from" and "to" must be from same list. 
*/
sort_list_iter_t SortListFindIf
						(sort_list_iter_t from, 
						sort_list_iter_t to,
						int(*cmp_func)(const void *data, const void *param), 
						const void *param)
{
	assert(from.list == to.list);
	assert(NULL != cmp_func);
	
	to.iter = DListFind(from.iter, to.iter, cmp_func, param);
	
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
	assert(NULL != action_func);
	
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
	sort_list_iter_t src_iter = SortListBegin(source_list);
	sort_list_iter_t dest_iter = SortListBegin(dest_list);
	
	assert(NULL != dest_list);
	assert(NULL != source_list);
	assert(NULL != source_list->dlist);
	assert(NULL != dest_list->dlist);
	
	
	while(1 != SortListIsEmpty(source_list))
	{
		/*find (in dest) where to put first node (from src)*/
		dest_iter = SortListFind(dest_list, dest_iter, 
							 SortListEnd(dest_list), SortListGetData(src_iter));
	
		/*splice 1 node into before des_t iter*/
		DListSplice(src_iter.iter, SortListNext(src_iter).iter, dest_iter.iter);

		/*move to next node (new first node) in source*/
		src_iter = SortListBegin(source_list);
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
	assert(NULL != list->dlist);	
	
	iter.iter = dlist_iter;
		
	#ifndef NDEBUG
	iter.list = list;
	#endif /* NDEBUG */
	
	return (iter);
}










/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      22.04.2020               **
**  Reviewer:  Irina					**
**  Status:    ????						**
*****************************************/		

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "dlist.h"

#define UNUSED(x) (void)(x)

int IsEqual(const void *arg_1, const void *arg_2);
int IncrementSizetByOne(void *arg, void *num);

struct node
{
	void *data;
	struct node *next;
	struct node *prev;	
};

struct dlist
{
	struct node head;
	struct node tail;
};

/*
Complexity - O(1)

Creates the dlist

Return:
on success:	 returns pointer to the list, 
on fail:	 returns NULL 
*/

dlist_t *DListCreate(void)
{
	dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if(NULL == dlist)
	{
		return (NULL);
	}
	
	/*initialize head dummy*/
	dlist->head.data = dlist;
	dlist->head.next = &dlist->tail;
	dlist->head.prev = NULL;
	
	/*initialize tail dummy*/
	dlist->tail.data = dlist;
	dlist->tail.next = NULL;
	dlist->tail.prev = &dlist->head;
	
	return (dlist);
}



/*----------------------------------------------------------------------------*/
/*
O(n)
Destroys the dlist. 

Algorithm:

-until head dummy points to tail dummy:
	--call remove node func			
	
-put nulls in main dlist struct (head & tail dummies) 
-free main dlist dtruct
*/

void DListDestroy(dlist_t *dlist)
{
	assert(NULL != dlist);
		
	while(dlist->head.next != &dlist->tail)
	{
		DListRemove(dlist->head.next);
	}
	
	dlist->head.data = NULL;
	dlist->tail.data = NULL;
	
	free(dlist);
	
	return;
}



/*----------------------------------------------------------------------------*/
/*
O(1)
Returns first valid node or tail (if empty)
*/ 

dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert(NULL != dlist);
	
	return (dlist->head.next);
}



/*----------------------------------------------------------------------------*/
/*
O(1)
Returns tail
*/

dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(NULL != dlist);

	return (const dlist_iter_t)(&dlist->tail);
}



/*----------------------------------------------------------------------------*/
/*
O(1) 
Returns the next node 
*/ 

dlist_iter_t DListNext(const dlist_iter_t iter)
{
	assert(NULL != iter);
	assert(NULL != iter->next);	
	
	return (iter->next);
}



/*----------------------------------------------------------------------------*/
/*
O(1) 
Returns the previous node 
*/ 

dlist_iter_t DListPrev(const dlist_iter_t iter)
{
	assert(NULL != iter);
	assert(NULL != iter->prev->prev);	
		
	return (iter->prev);
}



/*----------------------------------------------------------------------------*/
/*
O(n)
Returns number of nodes in the list 
*/
size_t DListCount(const dlist_t *dlist)	
{
	size_t num_of_nodes = 0;
	void *tmp = (void *)&num_of_nodes;
	
	assert(NULL != dlist);

	DListForEach(DListBegin(dlist), DListEnd(dlist), IncrementSizetByOne, tmp);

	return (num_of_nodes);
}



/*----------------------------------------------------------------------------*/
/*
O(n)
Returns the status of last foreach action function. 
Stops after first failure. 
Returns 0 for success, else failure 
*/  

int DListForEach(dlist_iter_t from, dlist_iter_t to, 
					int(*action_func)(void*data, void *arg), void *param)
{
	size_t result = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	
	while(0 == DListIsIterEqual(from, to))
	{
		result += action_func(from->data, param);
		from = from->next;
	}

	return (result);
}



/*----------------------------------------------------------------------------*/
/*
O(1)
Returns 1 (true) if iterators are equal, else returns 0 (false) 
*/

int DListIsIterEqual(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	return !!(iter1 == iter2);
}



/*----------------------------------------------------------------------------*/
/*
Amortized O(1)
Insert before node pointed to by 'where' with data 
If success returns iterator of the inserted node,
on fail returns END.
*/ 

dlist_iter_t DListInsert(dlist_iter_t where, void *data)
{
	struct node *new_node = NULL;
	
	assert(NULL != where);
	
	new_node = (struct node *)malloc(sizeof(struct node));
	if(NULL == new_node)
	{
		/*until you reach the tail dummy*/
		while(NULL != where->next)
		{
			where = DListNext(where);
		}
		
		return (where);
	}	
	
	new_node->data = data;
	new_node->next = where;
	new_node->prev = where->prev;
	
	where->prev->next = new_node;
	where->prev = new_node;
	
	return (new_node);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
Removes given node and returns the next node. 
*/

dlist_iter_t DListRemove(dlist_iter_t who)
{
	dlist_iter_t return_node = NULL;

	assert(NULL != who);
	
	return_node = who->next;
	
	who->prev->next = who->next;
	who->next->prev = who->prev;
	
	who->data = NULL;
	free(who);	
	
	/*in case return_node points to dummy*/
	if(NULL == return_node->next)
	{
		return_node = return_node->prev;
	}
	
	return (return_node);
}	



/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the iterator of element pushed in first element.
If failure, returns the END. 
*/

dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);
	
	return (DListInsert(dlist->head.next, data));
}



/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the iterator of element pushed in last element.
If failure, returns the END. 
*/

dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);
	
	return (DListInsert(&dlist->tail, data));
}



/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the iterator of next node after pop. 
*/

dlist_iter_t DListPopFront(dlist_t *dlist)
{
	assert(NULL != dlist);
	
	return (DListRemove(dlist->head.next));
}



/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the iterator of new last element after pop. 
*/

dlist_iter_t DListPopBack(dlist_t *dlist)
{
	assert(NULL != dlist);
	
	return (DListRemove(dlist->tail.prev));
}




/*----------------------------------------------------------------------------*/
/*
O(1)
Returns the data of the node
*/

void *DListGetData(const dlist_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->data);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
Sets data of the node 
*/

void DListSetData(dlist_iter_t iter, void *data)
{
	assert(NULL != iter);
	
	iter->data = data;
	
	return;
}

/*----------------------------------------------------------------------------*/
/*
O(1)
Returns 1 (true) if list is empty, else returns 0 (false) 
*/

int DListIsEmpty(const dlist_t *dlist)
{
	assert(NULL != dlist);
	
	return (DListIsIterEqual(dlist->head.next, (const dlist_iter_t)&dlist->tail));
}



/*----------------------------------------------------------------------------*/
/*
O(n)
If param is in the range (from (included), to(not included)), return
iterator to the first found node. 
If failed, returns to (the first element outside of the range).
*/

dlist_iter_t DListFind(	const dlist_iter_t from, const dlist_iter_t to, 
						int(*is_equal)(const void *data, const void *param), 
						const void *param)
{
	dlist_iter_t temp_from = from;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_equal);
	
	while(	0 == DListIsIterEqual(temp_from, to) && 
			0 == IsEqual(temp_from->data, param))
	{		
		temp_from = temp_from->next;
	}

	return (temp_from);
}


/*----------------------------------------------------------------------------*/
/*
O(n)
finds all params in the range (from (included), to(not included)), 
places their adresses inside outlist and returns:

success: 0
fail: else
*/
int DListMultiFind(	const dlist_iter_t from, const dlist_iter_t to, 
					int(*is_equal)(const void *data, const void *param), 
					const void *param, dlist_t *outlist)
{
	dlist_iter_t status_iter = NULL;
	dlist_iter_t temp_from = from;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_equal);
	assert(NULL != outlist);
	
	/*global range loop && as long as insert doesnt fail*/
	while(0 == DListIsIterEqual(temp_from, to) && status_iter != &outlist->tail)
	{		
		/*in case a match found*/
		if(1 == IsEqual(temp_from->data, param))
		{
			/*store dress to the param in outlist*/
			status_iter = DListInsert(DListBegin(outlist), (void *)temp_from);
		}
		
		temp_from = temp_from->next;
	}

	/*returns 0 as long as insert to outlist hasn't failed*/
	return (!(&outlist->tail != status_iter));
}
						
					

/*----------------------------------------------------------------------------*/
/*
O(1)
moves:
the nodes in the range: 'from' (including) - 'to' (not including)

to:
be located before 'where' (in a new list or in same list). 

Where must not be in range. 
Returns "where".
*/   

dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	dlist_iter_t to_prev_temp = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != where);
	
	to_prev_temp = to->prev;
	
	from->prev->next = to;
	to->prev->next = where;
	where->prev->next = from;
	to->prev = from->prev;
	from->prev = where->prev;
	where->prev = to_prev_temp;
	
	return (where);
}





/*----------------------------------------------------------------------------*/
/*
O(1)
increments (size_t)var that num points to by 1
*/  

int IncrementSizetByOne(void *arg, void *num)
{
	assert(NULL != num);
	UNUSED(arg);
	
	++*(size_t *)num;
	
	return (0);
}



/*----------------------------------------------------------------------------*/
/*
O(1)
returns 1 if arg_1 == arg_2
*/  

int IsEqual(const void *arg_1, const void *arg_2)
{	
	return (!!(arg_1 == arg_2));
}




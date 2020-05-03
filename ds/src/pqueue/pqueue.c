
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      28.04.2020               **
**  Reviewer:  Yael						**
**  Status:    Approved					**
*****************************************/	

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "sorted_list.h"
#include "pqueue.h"

struct pq
{
	sort_list_t *pq;
};


/*----------------------------------------------------------------------------*/
/* 
O(1)
return NULL if fails 
*/
pq_t *PQCreate( int(*compare)(const void *data1, const void *data2) )
{
	pq_t *pq = NULL;
		
	assert(NULL != compare);
	
	pq = (pq_t *)malloc(sizeof(pq_t));
	if(NULL == pq)
	{
		return (NULL);
	}
	
	pq->pq = SortListCreate(compare);
	if(NULL == pq->pq)
	{
		return (NULL);
	}
	
	return (pq);
}
 
 
/*----------------------------------------------------------------------------*/
/* 
O(n) 
*/
void PQDestroy(pq_t *pque)
{
	assert(NULL != pque);
	
	SortListDestroy(pque->pq);
	
	pque->pq = NULL;
	
	free(pque);
	pque = NULL;
	
	return;	
}


/*----------------------------------------------------------------------------*/
/* 
O(n)
add element according to compare function, 
add after all same priorities 
returns 0 on success
else on fail
*/
int	PQEnq(pq_t *pque, void *data)
{	
	assert(NULL != pque);
	assert(NULL != data);

	/*if insert failed - return 1*/
	return ( SortListIsIterEqual(SortListEnd(pque->pq),
								 SortListInsert(pque->pq, data)));
}


/*----------------------------------------------------------------------------*/
/* 
O(1)
return data on success
fail: undefined
*/
void *PQDeq(pq_t *pque)
{
	assert(NULL != pque);	
	
	return (SortListPopFront(pque->pq));	
}	


/*----------------------------------------------------------------------------*/
/*
O(1)
returns data in top element 
must not be empty
*/
void *PQPeek(const pq_t *pque)
{
	assert(NULL != pque);
	assert(1 != QPIsEmpty(pque));
	
	return (SortListGetData( SortListBegin(pque->pq) ));
}


/*----------------------------------------------------------------------------*/
/*
O(n)
returns size of queue
*/
size_t PQSize(const pq_t *pque)
{
	assert(NULL != pque);
	
	return ( SortListCount(pque->pq) );
}


/*----------------------------------------------------------------------------*/
/*
O(1)
return 1 for empty
0 for non empty
*/
int PQIsEmpty(const pq_t *pque)
{
	assert(NULL != pque);
	
	return ( 0 == PQSize(pque) );
}



/*----------------------------------------------------------------------------*/
/* 
O(n) 
empties the queue - removes all
*/
void PQClear(pq_t *pque)
{
	assert(NULL != pque);
	
	while(1 != PQIsEmpty(pque))
	{
		PQDeq(pque);	
	}
	
	return;
}
 


/*----------------------------------------------------------------------------*/
/* 
erases a spcific data
return first data found, 
return NULL if data not found 
*/
void *PQErase(pq_t *pque, 
		int(*is_match)(const void *data, const void *param), const void *param)
{
	sort_list_iter_t iter = {0};
	
	/* hold pointer to return */
	void *ret = NULL;

	assert(NULL != pque);
	assert(NULL != param);
	assert(NULL != is_match);

	/* find element to remove */
	iter = SortListFindIf(	SortListBegin(pque->pq), 
							SortListEnd(pque->pq), 
							is_match, 
							param);

	/* if element not found */
	if (1 == SortListIsIterEqual(iter, SortListEnd(pque->pq)))
	{
		return NULL;
	}
	
	ret = SortListGetData(iter);

	SortListRemove(iter);

	return ret;

	
}


















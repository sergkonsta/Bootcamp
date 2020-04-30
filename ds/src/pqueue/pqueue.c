
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      28.04.2020               **
**  Reviewer:  Yael						**
**  Status:    ?						**
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
	assert(NULL != pque->pq);
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
	void *ret = NULL;
	
	assert(NULL != pque);
	assert(NULL != pque->pq);
	
	/*hold data to return*/
	ret = PQPeek(pque);
	
	/*removes from */
	SortListPopFront(pque->pq);
	
	return (ret);	
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
	assert(NULL != pque->pq);
	
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
	assert(NULL != pque->pq);
	
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
	assert(NULL != pque->pq);
	
	return ( 0 == PQSize(pque) );
}



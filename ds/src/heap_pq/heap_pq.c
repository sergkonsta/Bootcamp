/*
Project:	Heap Priority Queue
Developer:	Sergey Konstantinovsky
Date:		14/06/2020
*/

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "heap_pq.h"
#include "heap.h"

struct heap_pq
{
	heap_t *pq;
};


/*----------------------------------------------------------------------------*/
/* 
O(1)
return NULL if fails 
*/
heap_pq_t *HPQCreate( int(*compare)(const void *data1, const void *data2) )
{
	heap_pq_t *pq = NULL;
		
	assert(NULL != compare);
	
	pq = (heap_pq_t *)malloc(sizeof(heap_pq_t));
	if(NULL == pq)
	{
		return (NULL);
	}
	
	pq->pq = HeapCreate(compare);
	if(NULL == pq->pq)
	{
		free(pq);
		pq = NULL;
		return (NULL);
	}
	
	return (pq);
}
 
 
/*----------------------------------------------------------------------------*/
/* 
O(n) 
*/
void HPQDestroy(heap_pq_t *pque)
{
	assert(NULL != pque);
	
	HeapDestroy(pque->pq);
	
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
int	HPQEnq(heap_pq_t *pque, void *data)
{	
	assert(NULL != pque);
	assert(NULL != data);

	/*if insert failed - return 1*/
	return ( HeapPush(pque->pq, data) );
}


/*----------------------------------------------------------------------------*/
/* 
O(1)
return data on success
fail: undefined
*/
void *HPQDeq(heap_pq_t *pque)
{
	void * data = NULL;
	
	assert(NULL != pque);	
	
	data = HeapPeek(pque->pq);
	
	HeapPop(pque->pq);
	
	return (data);	
}	


/*----------------------------------------------------------------------------*/
/*
O(1)
returns data in top element 
must not be empty
*/
void *HPQPeek(const heap_pq_t *pque)
{
	assert(NULL != pque);
	assert(1 != HPQIsEmpty(pque));
	
	return (HeapPeek(pque->pq));
}


/*----------------------------------------------------------------------------*/
/*
O(n)
returns size of queue
*/
size_t HPQSize(const heap_pq_t *pque)
{
	assert(NULL != pque);
	
	return ( HeapSize(pque->pq) );
}


/*----------------------------------------------------------------------------*/
/*
O(1)
return 1 for empty
0 for non empty
*/
int HPQIsEmpty(const heap_pq_t *pque)
{
	assert(NULL != pque);
	
	return ( 0 == HPQSize(pque) );
}



/*----------------------------------------------------------------------------*/
/* 
O(n) 
empties the queue - removes all
*/
void HPQClear(heap_pq_t *pque)
{
	assert(NULL != pque);
	
	while(1 != HPQIsEmpty(pque))
	{
		HPQDeq(pque);	
	}
	
	return;
}
 


/*----------------------------------------------------------------------------*/
/* 
O(n)
erases a spcific data
return first data found, 
return NULL if data not found 
*/
void *HPQErase(heap_pq_t *pque, 
		int(*is_match)(const void *data, const void *param), void *param)
{
	assert(NULL != pque);
	assert(NULL != param);
	assert(NULL != is_match);

	/* find element to remove */
	return HeapRemove(pque->pq, is_match, param);
}



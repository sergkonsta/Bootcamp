#ifndef __OL87_HEAP_PQUEUE_H__
#define __OL87_HEAP_PQUEUE_H__

#include <stddef.h>

typedef struct heap_pq heap_pq_t;


/* 
O(1)
return NULL if fails 

data_1 is data inside the PQ
data_2 is data recieved
*/
heap_pq_t *HPQCreate( int(*compare)(const void *data1, const void *data2) );
 
 
/* 
O(n) 
*/
void HPQDestroy(heap_pq_t *pque); 


/* 
O(n)
add element according to compare function, 
add after all same priorities in the end of the queue (end of list)
returns 0 on success
else on fail
*/
int	HPQEnq(heap_pq_t *pque, void *data); 


/* 
O(1)
removes data rom the head of the queue (begin of list)
return data on success
fail: undefined
*/
void *HPQDeq(heap_pq_t *pque);	


/*
O(1)
returns data in top element (in the begin of list)
must not be empty
*/
void *HPQPeek(const heap_pq_t *pque);	


/*
O(n)
returns size of queue
*/
size_t HPQSize(const heap_pq_t *pque);	


/*
O(1)
return 1 for empty
0 for non empty
*/
int HPQIsEmpty(const heap_pq_t *pque);	


/* 
O(n) 
empties the queue - removes all
*/
void HPQClear(heap_pq_t *pque); 


/* 
O(n)
erases a spcific data
return first data found, 
return NULL if data not found 
*/
void *HPQErase(heap_pq_t *pque, 
		int(*is_match)(const void *data, const void *param), void *param);

#endif /* Closing OL87 queue header file */

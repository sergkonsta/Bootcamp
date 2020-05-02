#ifndef __OL87_PQUEUE_H__
#define __OL87_PQUEUE_H__

#include <stddef.h>

typedef struct pq pq_t;

/*
change everywhere the is_before to: (in soretd list as well)

typedef int (*is_before_func)(const void *data1, const void *data2,								 const void *param);
*/


/* 
O(1)
return NULL if fails 
*/
pq_t *PQCreate( int(*compare)(const void *data1, const void *data2) );
 
 
/* 
O(n) 
*/
void PQDestroy(pq_t *pque); 


/* 
O(n)
add element according to compare function, 
add after all same priorities in the end of the queue (end of list)
returns 0 on success
else on fail
*/
int	PQEnq(pq_t *pque, void *data); 


/* 
O(1)
removes data rom the head of the queue (begin of list)
return data on success
fail: undefined
*/
void *PQDeq(pq_t *pque);	


/*
O(1)
returns data in top element (in the begin of list)
must not be empty
*/
void *PQPeek(const pq_t *pque);	


/*
O(n)
returns size of queue
*/
size_t PQSize(const pq_t *pque);	


/*
O(1)
return 1 for empty
0 for non empty
*/
int PQIsEmpty(const pq_t *pque);	


/* 
O(n) 
empties the queue - removes all
*/
void PQClear(pq_t *pque); 


/* 
erases a spcific data
return first data found, 
return NULL if data not found 
*/
void *PQErase(pq_t *pque, 
		int(*is_match)(const void *data, const void *param), const void *param);

#endif /* Closing OL87 queue header file */

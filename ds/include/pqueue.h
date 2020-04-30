#ifndef __OL87_PQUEUE_H__
#define __OL87_PQUEUE_H__

#include <stddef.h>

typedef struct pqueue pqueue_t;

/* 
O(n)
return NULL if fails 
*/
pqueue_t *PQueueCreate((int)(*compare)(const void *data1, const void *data2));
 
/* 
O(n) 
*/
void PQueueDestroy(pqueue_t *pque); 

/* 
O(n)
add element according to compare function, add after all same priorities 
*/
int	PQueueEnq(pqueue_t *pque, void *data); 
/* return data O(1) */
void *PQueueDeq(queue_t *pque);	
/*O(1)*/
void *PQueuePeek(const pqueue_t *pque);	

/*O(n)*/
size_t PQueueSize(const pqueue_t *pque);	
/*O(1)*/
int PQueueIsEmpty(const pqueue_t *pque);	

/* O(n) */
void PQueueClear(pqueue_t *pque); 

/* return first data found, return NULL if data not found */
void *PQueueErase(pqueue_t *pque, 
		(int)(*is_match)(void *data, const void *param), const void *param);

#endif /* Closing OL87 queue header file */

#infndef __OL87_QUEUE_H__
#define __OL87_QUEUE_H__

#include "slist.h"

typedef struct queue queue_t;

/*
struct queue
{
	struct slist *queue;
};
*/

queue_t *QueueCreate(void); /* O(1) */
void QueueDestroy(queue_t *que); O(n)

int	QueueEnq(queue_t *que, void *data); O(n)
void QueueDeq(queue_t *que);	O(1)
void *QueuePeek(const queue_t *que);	O(1)

size_t QueueSize(const queue_t *que);	O(n)

int QueueIsEmpty(const queue_t *que);	O(1)

queue_t *QueueAppend(queue_t *dest, queue_t *src); O(1)!!!!


#endif /* Closing OL87 queue header file */

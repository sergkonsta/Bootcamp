#ifndef __OL87_QUEUE_H__
#define __OL87_QUEUE_H__

#include <stddef.h>

#include "slist.h"

/*based on slist.h - compile together with slist source file*/

typedef struct queue queue_t;

queue_t *QueueCreate(void); 							/* O(1) */
void QueueDestroy(queue_t *que); 						/* O(n) */


int	QueueEnq(queue_t *que, void *data); 				/* O(1) */
void QueueDeq(queue_t *que);							/* O(1) */
void *QueuePeek(const queue_t *que);					/* O(1) */

size_t QueueSize(const queue_t *que);					/* O(n) */

int QueueIsEmpty(const queue_t *que);					/* O(1) */

/*doesnt free src! returns empty src*/
queue_t *QueueAppend(queue_t *dest, queue_t *src);		/* O(1) */


#endif /* __OL87_QUEUE_H__ */


/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      19.04.2020               **
**  Reviewer:  ????						**
**  Status:    ????						**
*****************************************/	
#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "queue.h"


struct queue
{
	struct slist *queue;
};

/*----------------------------------------------------------------------------*/
/* O(1) */
queue_t *QueueCreate(void)
{	
	queue_t *new_queue = NULL;

	slist_t *new_list = SListCreate();
	if(NULL == new_list)
	{
		return (NULL);
	}
	
	new_queue = (queue_t *)malloc(sizeof(queue_t));
	if(NULL == new_queue)
	{
		free(new_list);
		new_list = NULL;
		return(NULL);
	}
	
	new_queue->queue = new_list;
	
	return (new_queue);
}


/*----------------------------------------------------------------------------*/
/* O(n) */
void QueueDestroy(queue_t *que)
{
	assert(NULL != que);
	assert(NULL != que->queue);
	
	SListDestroy(que->queue);
	
	que->queue = NULL;
	
	free(que);

	return;
}						


/*----------------------------------------------------------------------------*/
/* O(1) */
/*insert the data into the end of list 
		and then return:
						 0 for success
						 1 for failed SListInsert */

int	QueueEnq(queue_t *que, void *data)
{
	assert(NULL != que);
	assert(NULL != que->queue);
		
	return (!SListInsert(SListEnd(que->queue), data));	
}				


/*----------------------------------------------------------------------------*/
/* O(1) */
void QueueDeq(queue_t *que)
{
	assert(NULL != que);
	assert(NULL != que->queue);
	assert(0 != QueueSize(que));
	
	/*removes the data from the begining of queue*/
	SListRemove(SListBegin(que->queue));
	
	return;
}


/*----------------------------------------------------------------------------*/
/* O(1) */
void *QueuePeek(const queue_t *que)
{
	assert(NULL != que);
	assert(NULL != que->queue);
	assert(0 != QueueSize(que));
		
	return(SListGetData(SListBegin(que->queue)));
}					


/*----------------------------------------------------------------------------*/
/* O(n) */
size_t QueueSize(const queue_t *que)
{
	assert(NULL != que);
	assert(NULL != que->queue);
	
	return(SListCount(que->queue));
}		


/*----------------------------------------------------------------------------*/
/* O(1) */
int QueueIsEmpty(const queue_t *que)
{
	assert(NULL != que);
	assert(NULL != que->queue);
	
	return (SListBegin(que->queue) == SListEnd(que->queue));
}				


/*----------------------------------------------------------------------------*/
/* O(1) */
/*doesnt free src! returns empty src.*/
queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	dest->queue = SListAppendList(dest->queue, src->queue);
	
	return(dest);
}	



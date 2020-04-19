
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      18.04.2020               **
**  Reviewer:  Eden						**
**  Status:    SENT						**
*****************************************/		

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "slist.h"

struct slist_node
{
  void *data;
  struct slist_node *next;
};

struct slist
{
	struct slist_node *head;
	struct slist_node *tail;
};

slist_t *SListCreate(void)
{
	struct slist_node *dummy = NULL;
	
	slist_t *new_list = (slist_t *)malloc(sizeof(slist_t));	
	if(NULL == new_list)
	{
		return (NULL);
	}

	/*create dummy node*/
	dummy = (struct slist_node *)malloc(sizeof(struct slist_node));	
	if(NULL == dummy)
	{
		free(new_list);
		new_list = NULL;
		return (NULL);
	}
	
	/*point slist head and tail to dummy*/
	new_list->head = dummy;
	new_list->tail = dummy;
	
	/*hold tail address int dummy data*/
	dummy->data = new_list;
	dummy->next = NULL;
	
	return (new_list);
}


/*----------------------------------------------------------------------------*/

void SListDestroy(slist_t *slist)
{
	struct slist_node *temp = NULL;
	
	assert(NULL != slist);
	
	/*free all nodes*/
	while(NULL != slist->head)
	{
		temp = slist->head;
		slist->head = slist->head->next; 
	
		temp->data = NULL;
		temp->next = NULL;
		free(temp);
		temp = NULL;
	}
	
	/*frees head and temp pointers*/
	slist->head = NULL;
	slist->tail = NULL;
	free(slist);	
		
	return;
}

/*----------------------------------------------------------------------------*/

slist_iter_t SListBegin(const slist_t *slist)
{
	assert(NULL != slist);
	
	return(slist->head);
}


/*----------------------------------------------------------------------------*/

slist_iter_t SListEnd(const slist_t *slist)
{
	assert(NULL != slist);
	
	return(slist->tail);
}


/*----------------------------------------------------------------------------*/

slist_iter_t SListNext(const slist_iter_t iterator)
{
	assert(NULL != iterator);
	
	/*makes sure not pointing to dummy at the end*/
	assert(iterator->data != iterator);
		
	return(iterator->next);
}


/*----------------------------------------------------------------------------*/

slist_iter_t SListInsert(slist_iter_t iterator, void *data)
{
	struct slist_node *new_node = NULL;
	slist_t *slist = (slist_t *)iterator->data;

	assert(NULL != iterator);
	
	/*new node allocation*/
	new_node =  (struct slist_node *)malloc(sizeof(struct slist_node));
	assert(NULL != new_node);
	if(NULL == new_node)
	{
		return NULL;
	}
		
	/*move from old node to new node, including tail*/
	new_node->data = iterator->data;
	new_node->next = iterator->next;
	
	/*insert new data and link new node to the list*/
	iterator->data = data;
	iterator->next = new_node;
	
	/*first insert head and tail seperation*/
	if(slist->head->next == NULL)
	{
		slist->head = iterator;
	}

	slist->tail = new_node;
			
	return (new_node);
}


/*----------------------------------------------------------------------------*/

slist_iter_t SListRemove(slist_iter_t iterator)
{
	struct slist_node *temp_free = iterator->next; 
	
	assert(NULL != iterator);
	
	/*return iter if it points to dummy at the end*/
	if(iterator->data == iterator)
	{
		return (iterator);
	}
		
	iterator->data = iterator->next->data; 
	
	iterator->next = iterator->next->next;
	
	free(temp_free);
	
	return (iterator);
}


/*----------------------------------------------------------------------------*/

void* SListGetData(const slist_iter_t iterator)
{
	assert(NULL != iterator);
	/*makes sure not pointing to dummy at the end*/
	assert(iterator->data != iterator);
	
	return (iterator->data);
}


/*----------------------------------------------------------------------------*/

void SListSetData(slist_iter_t iterator, void *data)
{
	assert(NULL != iterator);
	/*makes sure not pointing to dummy at the end*/
	assert(iterator->data != iterator);

	iterator->data = data;

	return;
}


/*----------------------------------------------------------------------------*/

size_t SListCount(const slist_t *slist)
{
	size_t node_counter = 0;
	slist_iter_t iter = slist->head; 
	
	assert(NULL != slist);
	
	while(NULL != iter->next)
	{
		++node_counter;
		iter = iter->next;
	}
	
	return (node_counter);
}


/*----------------------------------------------------------------------------*/
/*return 1 for equality*/
int SListIsIterEqual(const slist_iter_t iter1, const slist_iter_t iter2)
{
	return !!(iter1 == iter2);
}


/*----------------------------------------------------------------------------*/

slist_iter_t SListFind(slist_iter_t from, slist_iter_t to,
						int (*is_equal)(void *data, void *param), void *param)
{
	/*make sure 'from' comes before 'to' in the list*/
	slist_iter_t order_tester = to;
	while(NULL != order_tester->data)
	{
		assert(1 != SListIsIterEqual(order_tester, from));
		order_tester = order_tester->next;
	}
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_equal);
	
	while(1 != SListIsIterEqual(from, to) && 1 != is_equal(from->data, param))
	{
		from = from->next;
	}	
	
	return (from);
}

/*----------------------------------------------------------------------------*/
/*return 0 on success*/
int SListForEach(slist_iter_t from, slist_iter_t to,
				 int(*action_func)(void *data, void *arg), void *param)
{
	int result = 0;
	
	/*make sure 'from' comes before 'to' in the list*/
	slist_iter_t order_tester = to;
	while(NULL != order_tester->data)
	{
		assert(1 != SListIsIterEqual(order_tester, from));
		order_tester = order_tester->next;
	}
		
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	
	while(0 == SListIsIterEqual(from, to))
	{
		result += action_func(from->data, param);
		from = from->next;
	}
	
	return (!result);
}


/*----------------------------------------------------------------------------*/

slist_t *SListAppendList(slist_t *dest, slist_t *src)
{
	/*moving src head node to dest tail (dummy) node*/
	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	
	/*updates dest tail node*/	
	dest->tail = src->tail;

	/*src head and tail point to former src->head node*/
	src->tail = src->head;
	src->head->data = NULL;
	src->head->next = NULL;
	
	return (dest);
}

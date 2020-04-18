
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
	dummy->data = (void *)new_list;
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
	if(slist->head == slist->tail)
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
	
	/*makes sure not pointing to dummy at the end*/
	assert(iterator->data != iterator);
		
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
	size_t c = 0;
	slist_iter_t iter = slist->head; 
	
	assert(NULL != slist);
	
	while(NULL != iter->next)
	{
		++c;
		iter = iter->next;
	}
	
	return (c);
}


/*----------------------------------------------------------------------------*/
/*return 0 for equality*/
int SListIsIterEqual(const slist_iter_t iter1, const slist_iter_t iter2)
{
	return !(iter1 == iter2);
}


/*----------------------------------------------------------------------------*/

slist_iter_t SListFind(slist_iter_t from, slist_iter_t to,
						int (*is_equal)(void *data, void *param), void *param)
{
	while(0 != SListIsIterEqual(from, to) && 0 != is_equal(from->data, param))
	{
		from = from->next;
	}	
	
	return (from);
}

/*----------------------------------------------------------------------------*/

int SListForEach(slist_iter_t from, slist_iter_t to,
				 int(*action_func)(void *data, void *arg), void *param)
{
	int result = 0;
	
	while(0 != SListIsIterEqual(from, to))
	{
		result += action_func(from->data, param);
		from = from->next;
	}
	
	return (result);
}


/*----------------------------------------------------------------------------*/













#ifndef __OL87_SLIST__H__
#define __OL87_SLIST__H__

#include <stddef.h>

typedef struct slist_node* slist_iter_t;

typedef struct slist slist_t;

slist_t *SListCreate(void);
void SListDestroy(slist_t *slist);

/*place iterator in the beginning of list*/
slist_iter_t SListBegin(const slist_t *slist);

/*place iterator in the end of list*/
slist_iter_t SListEnd(const slist_t *slist);

/*move iterator to the next node*/
slist_iter_t SListNext(const slist_iter_t iterator);

/*returns iter to inserted node*/
slist_iter_t SListInsert(slist_iter_t iterator, void *data); 

/*return iter to next node after removed node*/
slist_iter_t SListRemove(slist_iter_t iterator);

void* SListGetData(const slist_iter_t iterator);
void SListSetData(slist_iter_t iterator, void *data);

size_t SListCount(const slist_t *slist);

/*return 1 (true) for equality*/
int SListIsIterEqual(const slist_iter_t iter1, const slist_iter_t iter2); 

/*	returns iter to found node.
	if not found, returns iter 'to'*/
slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, int (*is_equal)(void *data, void *param), void *param);	

/*returns 0 for success*/
int SListForEach(slist_iter_t from, slist_iter_t to, int(*action_func)(void *data, void *arg), void *param);

/*	appends src list to dst list, doesn't free src list
	return iter to head of dest*/
slist_t *SListAppendList(slist_t *dest, slist_t *src);

#endif /* __OL87_SLIST__H__*/







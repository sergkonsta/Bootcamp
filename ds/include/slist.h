#ifndef __OL87_SLIST__H__
#define __OL87_SLIST__H__


typedef struct slist_node* slist_iter_t;
/*
struct slist_node
{
  void *data;
  element_t *next;
};
typedef struct slist
{
	struct slist_node *head;
	struct slist_node *tail;
} slist_t;
*/


slist_t *SListCreate(void);
void SListDestroy(slist_t *slist);

slist_iter_t SListBegin(const slist_t *slist);
slist_iter_t SListEnd(const slist_t *slist);
slist_iter_t SListNext(const slist_iter_t iterator);

slist_iter_t SListInsert(slist_iter_t iterator, void *data); 
slist_iter_t SListRemove(slist_iter_t iterator);

slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, int (*is_equal)(void *data, void *param), void *param);	
int SListForeach(slist_iter_t from, slist_iter_t to,  int(*action_func)(void *data, void *arg), void *param); 

void* SListGetData(const slist_iter_t iterator);
void SListSetData(slist_iter_t iterator, void *data);

size_t SListCount(const slist_t *slist);

int SListIsIterEqual(const slist_iter_t iter1, const slist_iter_t iter2); 

#endif /* __OL87_SLIST__H__*/







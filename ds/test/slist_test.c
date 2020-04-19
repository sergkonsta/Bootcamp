#include <stdio.h>		/*printf*/

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

/*return 0 for equality*/
int IsEqual(void *data_1, void *data_2)
{
	return (!(data_1 == data_2));
}

int main()
{
	slist_t *slist1 = SListCreate();
	slist_t *slist2 = SListCreate();

	slist_iter_t iter1 = SListBegin(slist1);
	slist_iter_t iter2 = SListBegin(slist2);



	iter1 = SListInsert(iter1, (void *)1);	
	
	iter1 = SListInsert(iter1, (void *)2);	
	
	iter1 = SListInsert(iter1, (void *)3);
	
	iter1 = SListInsert(iter1, (void *)4);
	
	iter1 = SListInsert(iter1, (void *)5);	
	
	
	iter2 = SListInsert(iter2, (void *)6);	
	
	iter2 = SListInsert(iter2, (void *)7);	
	
	iter2 = SListInsert(iter2, (void *)8);
	
	iter2 = SListInsert(iter2, (void *)9);
	
	iter2 = SListInsert(iter2, (void *)10);	

	SListAppendList(slist1, slist2);
	
	iter1 = SListBegin(slist1);
	
	while(NULL != iter1->next)
	{
		printf("%d, ",*(int *)&iter1->data);
		iter1 = iter1->next;
	}
	
	printf("\nlist count: %ld.\n",SListCount(slist1));
	
	SListDestroy(slist1);
	SListDestroy(slist2);
	
	return 0;
}

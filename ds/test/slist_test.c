#include <stdio.h>		/*printf*/

#include "slist.h"

struct slist_node
{
  void *data;
  struct slist_node *next;
};

/*return 0 for equality*/
int IsEqual(void *data_1, void *data_2)
{
	return (!(data_1 == data_2));
}

int main()
{
	slist_t *slist = SListCreate();

	slist_iter_t iterator = slist->head;
	slist_iter_t iter_end = NULL;


	iterator = SListInsert(iterator, (void *)1);	
	
	iterator = SListInsert(iterator, (void *)2);	
	
	iterator = SListInsert(iterator, (void *)3);
	
	iterator = SListInsert(iterator, (void *)4);
	
	iterator = SListInsert(iterator, (void *)5);	
	
	
	iterator = SListBegin(slist);
	iter_end = SListEnd(slist);
	
	SListForEach(iterator, iter_end, (int)SListSetData, (void*)7);
	
	printf("iterator data returned from find is: %d", *(int *)iterator);
	
	
	printf("\nlist count: %ld.\n",SListCount(slist));
	
	SListDestroy(slist);
	
	return 0;
}

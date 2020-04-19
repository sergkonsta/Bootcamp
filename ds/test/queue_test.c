#include <stdio.h>

#include "queue.h"
#include "slist.h"


struct queue
{
	struct slist *queue;
};

int main()
{
	
	queue_t *que_1 = QueueCreate();
	queue_t *que_2 = QueueCreate();

	printf("\nque_1 size at start: %ld\n",QueueSize(que_1));
	printf("\nque_1 IsEmpty result: %d\n",QueueIsEmpty(que_1));

	printf("\nAdding 7 items to que_1......\n");
	QueueEnq(que_1, (void *)1);
	QueueEnq(que_1, (void *)2);
	QueueEnq(que_1, (void *)3);	
	QueueEnq(que_1, (void *)4);
	QueueEnq(que_1, (void *)5);
	QueueEnq(que_1, (void *)6);
	QueueEnq(que_1, (void *)7);
	
	printf("\nque_1 size before remove: %ld\n",QueueSize(que_1));	
	QueueDeq(que_1);
	printf("\nque_1 size after remove: %ld\n",QueueSize(que_1));

	printf("\nAdding 9 items to que_2......\n");
	QueueEnq(que_2, (void *)101);
	QueueEnq(que_2, (void *)102);
	QueueEnq(que_2, (void *)103);
	QueueEnq(que_2, (void *)104);
	QueueEnq(que_2, (void *)105);
	QueueEnq(que_2, (void *)106);
	QueueEnq(que_2, (void *)107);
	QueueEnq(que_2, (void *)108);
	QueueEnq(que_2, (void *)109);
	
	printf("\nque_2 size before remove: %ld\n",QueueSize(que_2));
	QueueDeq(que_2);
	printf("\nque_2 size after remove: %ld\n",QueueSize(que_2));

	printf("\npeek at que_1: %d\n",(int)QueuePeek(que_1));
	printf("\npeek at que_2: %d\n",(int)QueuePeek(que_2));
	
	
	que_1 = QueueAppend(que_1, que_2);
	printf("\nque_1 size after append: %ld\n",QueueSize(que_1));
	printf("\nque_2 size after append: %ld\n",QueueSize(que_2));	
	printf("\npeek at que_1: %d\n",(int)QueuePeek(que_1));	
	
	QueueDestroy(que_1);
	QueueDestroy(que_2);
	

	return 0;
}

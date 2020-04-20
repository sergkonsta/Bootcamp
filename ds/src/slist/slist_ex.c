
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      18.04.2020               **
**  Reviewer:  Eden						**
**  Status:    SENT						**
*****************************************/		
#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/
#include <assert.h>		/*for assert*/


typedef struct node
{
	void *data; 
	struct node *next;
} node_t;

size_t SListCount(const node_t *head);


/*reverses the order of a given slist*/
node_t *Flip(node_t *head)
{
	node_t *curr = head;
    node_t *next = NULL;
    node_t *prev = NULL;
   
   	assert(NULL != head);
   
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    
    return head;
}
/*tells wether a given slist has loop*/
int HasLoop(const node_t *head)
{
	assert(NULL != head);
	
	const node_t *one_step_p = head;
	const node_t *two_step_p = head; 

	assert(NULL != head);

	while (NULL != one_step_p && NULL != two_step_p && NULL != two_step_p->next)
	{ 
		one_step_p = one_step_p->next; 
		two_step_p = two_step_p->next->next; 
		
		if (one_step_p == two_step_p)
		{ 
			printf("Found Loop"); 
			
			return 1; 
		} 
	} 
	
	return 0; 
}

/*returns a pointer to a first node mutual to both lists if any*/
node_t *FindIntersection(node_t *head_1, node_t *head_2)
{ 
	size_t c1 = SListCount(head_1); 
	size_t c2 = SListCount(head_2); 
	size_t diff = 0; 
	size_t i = 0;

	node_t *temp = NULL;

	assert(NULL != head_1);
	assert(NULL != head_2);

	/*find difference in lengths*/
	if (c1 >= c2) 
	{ 
		diff = c1 - c2; 
	} 
	
	/*swap pointers if needed*/
	else if(c2 > c1)
	{ 
		diff = c2 - c1; 
		temp = head_1;
		head_1 = head_2;
		head_2 = temp;
	}

	/*iterate through the longer list until lists are equal in length*/
	for (i = 0; i < diff; i++) 
	{ 
		head_1 = head_1->next; 
	} 

	/*iterate through rest of the lists and return common node if found*/
	while (head_1 != NULL) 
	{ 
		if (head_1 == head_2) 
		{
			return head_1; 
		}

		head_1 = head_1->next; 
		head_2 = head_2->next; 
	} 

	return NULL;
} 

size_t SListCount(const node_t *head)
{
	size_t c = 0;
	
	assert(NULL != head);
	
	while(NULL != head->next)
	{
		++c;
		head = head->next;
	}
	
	return (c);
}

int main()
{
	node_t *iter;
	
	node_t *node6 = (node_t *)malloc(sizeof(node_t));
	node_t *node5 = (node_t *)malloc(sizeof(node_t));
	node_t *node4 = (node_t *)malloc(sizeof(node_t));	
	node_t *node3 = (node_t *)malloc(sizeof(node_t));
	node_t *node2 = (node_t *)malloc(sizeof(node_t));
	node_t *node1 = (node_t *)malloc(sizeof(node_t));
	
	node_t *node61 = (node_t *)malloc(sizeof(node_t));
	node_t *node51 = (node_t *)malloc(sizeof(node_t));
	node_t *node41 = (node_t *)malloc(sizeof(node_t));	
	
	node1->data = (void *)1;	
	node2->data = (void *)2;
	node3->data = (void *)3;
	node4->data = (void *)4;
	node5->data = (void *)5;
	node6->data = (void *)6;
	
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = NULL;
		
	node61->data = (void *)1;	
	node51->data = (void *)2;
	node41->data = (void *)3;
		
	node61->next = node51;
	node51->next = node41;
	node41->next = node2;
	
	
	/*
	iter = node1; 	
	printf("\n\n the list is:\n");
	while(NULL != iter)
	{
		printf("%d, ",*(int *)&iter->data);
		iter = iter->next;
	}
	
	iter = Flip(node1);
	
	printf("\n\n the list is:\n");
	while(NULL != iter)
	{
		printf("%d, ",*(int *)&iter->data);
		iter = iter->next;
	}
	*/
	
	/*HasLoop(node1);*/
	
	iter = FindIntersection(node61, node1);
	printf("\n%d\n",*(int *)&iter->data);
	
	
	free(node61);
	free(node51);
	free(node41);
	free(node6);
	free(node5);
	free(node4);
	free(node3);
	free(node2);
	free(node1);
	
	return 0;
}



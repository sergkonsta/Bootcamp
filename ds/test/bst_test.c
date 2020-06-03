
#include <assert.h>
#include <stdio.h>
 
#include "bst.h"

#define UNUSED(X) (void)(X)

int Cmp(const void *data_1, const void *data_2);
static void BuildTreeNTestSize(bst_t *tree);
static int IncrementSizetByOne(void *arg, void *num);
static int ForEach(	bst_iter_t from, bst_iter_t to,  
				int(*action_func)(void *data, void *arg), void *param);
static size_t TestSize(bst_t *bst);				
static void TestForEach(bst_t *tree);
static void NextTest(bst_t *tree);
static void PrevTest(bst_t *tree);
		
int main()
{
	bst_t *tree = BSTCreate(Cmp);
	
	BuildTreeNTestSize(tree);
	
	TestForEach(tree);
	
	NextTest(tree);
	
	PrevTest(tree);
	
	
	
	
	
	BSTRemove( BSTFind(tree, (void *)37) );
	BSTRemove( BSTFind(tree, (void *)30) );
	BSTRemove( BSTFind(tree, (void *)35) );
	BSTRemove( BSTFind(tree, (void *)10) );
		
	BSTDestroy(tree);
	return (0);
}

int Cmp(const void *data_1, const void *data_2)
{
	int num_1 = *(int *)&data_1;
	int num_2 = *(int *)&data_2;

	return (num_1 - num_2);
}
/*----------------------------------------------------------------------------*/
/*									
									|STUB|
								    /
								|60|
								/  \	
							|10|	|70|
						    /  \
						 |1|    |25|
						 	   /	\
						   |20|		 |30|
						   				 \
						   				 |35|
						   				/	 \
						   			|33|	  |37|

*/
static void BuildTreeNTestSize(bst_t *tree)
{
	if(1 != BSTIsEmpty(tree))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if(0 != BSTSize(tree))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	BSTInsert(tree, (void *)60);	
	BSTInsert(tree, (void *)10);
	BSTInsert(tree, (void *)70);
	BSTInsert(tree, (void *)25);
	BSTInsert(tree, (void *)1 );
	BSTInsert(tree, (void *)30);
	BSTInsert(tree, (void *)35);
	BSTInsert(tree, (void *)20);
	BSTInsert(tree, (void *)33);
	BSTInsert(tree, (void *)37);
		
	if(0 != BSTIsEmpty(tree))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if(10 != BSTSize(tree))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
}

static void NextTest(bst_t *tree)
{
	/*if((void *)NULL != BSTGetData( BSTNext( BSTEnd(tree) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}*/
	
	if((void *)33 != BSTGetData( BSTNext( BSTFind(tree, (void *)30) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if((void *)10 != BSTGetData( BSTNext( BSTFind(tree, (void *)1) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if((void *)60 != BSTGetData( BSTNext( BSTFind(tree, (void *)37) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if(NULL != BSTGetData( BSTNext( BSTFind(tree, (void *)70) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
}

static void PrevTest(bst_t *tree)
{

	if((void *)70 != BSTGetData( BSTPrev( BSTEnd(tree) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if((void *)33 != BSTGetData( BSTPrev( BSTFind(tree, (void *)35) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if((void *)37 != BSTGetData( BSTPrev( BSTFind(tree, (void *)60) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if((void *)25 != BSTGetData( BSTPrev( BSTFind(tree, (void *)30) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if((void *)NULL != BSTGetData( BSTPrev( BSTFind(tree, (void *)1) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
	
	if((void *)30 != BSTGetData( BSTPrev( BSTFind(tree, (void *)33) ) ))
	{
		printf("\nproblem on line: %d",__LINE__);
	}
}

static void TestForEach(bst_t *tree)
{
	assert(NULL != tree);
	TestSize(tree);
}

/*----------------------------------------------------------------------------*/

static int IncrementSizetByOne(void *arg, void *num)
{
	assert(NULL != num);
	UNUSED(arg);
	
	++*(size_t *)num;
	
	return (0);
}

static int ForEach(	bst_iter_t from, bst_iter_t to,  
				int(*action_func)(void *data, void *arg), void *param)
{
	int result = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	
	while(0 == BSTIsIterEqual(from, to))
	{
		result += action_func(BSTGetData(from), param);
		from = BSTNext(from);
	}

	return (result);
}

static size_t TestSize(bst_t *bst)
{
	size_t num_of_nodes = 0;
	void *tmp = (void *)&num_of_nodes;
	
	assert(NULL != bst);

	ForEach(BSTBegin(bst), BSTEnd(bst), IncrementSizetByOne, tmp);

	if(10 != num_of_nodes)
	{
		printf("\nproblem on line: %d",__LINE__);
	}

	return (num_of_nodes);
}


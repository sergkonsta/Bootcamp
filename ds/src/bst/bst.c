
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      24.05.2020               **
**  Reviewer:  Eden Ben Zion			**
**  Status:    ????						**
*****************************************/
#include <assert.h>		/*for asserts*/
#include <stdlib.h>		/*for malloc */

#include "bst.h"

#define UNUSED(X) (void)(X)

enum child {LEFT, RIGHT};

typedef struct bst_node
{
    void *data;
    struct bst_node *parent;
    struct bst_node *children[2];
} bst_node_t;

struct bst
{
	bst_node_t stub;
	
	int (*compare)(const void *data_1, const void *data_2);	
};

static bst_iter_t FindParent(bst_t *bst, void *data);
static int WhereTo(bst_t *bst, const void *input, const void *data);
static bst_iter_t FindMax(bst_iter_t node);
static bst_iter_t FindMin(bst_iter_t node);
int IncrementSizetByOne(void *arg, void *num);

/*----------------------------------------------------------------------------*/
/*
O(1)

function: 				creates stub (bst struct)

returns on success: 	pointer to tree structure
		on failure:		NULL
*/
bst_t *BSTCreate(int (*cmp_func)(const void *data_1, const void *data_2))
{
	struct bst *bst = NULL;
	
	assert(NULL != cmp_func);
	
	bst = (bst_t *)malloc(sizeof(bst_t));
	if(NULL == bst)
	{
		return NULL;
	}
	
	bst->stub.data = NULL; /*need a way to make sure its always highest*/
	bst->stub.parent = NULL;
	bst->stub.children[LEFT] = NULL;
	bst->stub.children[RIGHT] = NULL;
	bst->compare = cmp_func;
		
	return (bst);
}


/*----------------------------------------------------------------------------*/
/*
O(n)

function: 				destroys BST

returns on success: 	void
		on failure:		void
*/
void BSTDestroy(bst_t *bst)
{
	assert(NULL != bst);
	
	/*remove nodes until tree is empty*/
	while(1 != BSTIsEmpty(bst))
	{
		BSTRemove( BSTBegin(bst) );
	}
	
	bst->compare = NULL;
	
	free(bst);
	
	return;	
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				Inserts new node in to tree, in-order algorithm

returns on success: 	iter to inserted node / NULL if node exists
		on failure:		stub
*/
bst_iter_t BSTInsert(bst_t *bst, void *input)
{
	bst_node_t *new_node = NULL;
	bst_iter_t parent_2_be = NULL;
	
	assert(NULL != bst);
	
	/*finds future parent of new_node*/
	parent_2_be = FindParent(bst, input);
	if(NULL == parent_2_be)
	{
		return (NULL);
	}
	
	/*if input does't exist in tree - create node*/
	new_node = (bst_node_t *)malloc( sizeof(bst_node_t) );
	if(NULL == new_node)
	{
		return (&bst->stub);
	}
	
	/*initialize new_node*/
	new_node->data = input;
	new_node->parent = parent_2_be;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;	
			
	/*connect parent to new_node, if stub always connect to LEFT*/
	
	parent_2_be->children[parent_2_be->data && 
						  WhereTo(bst, input, parent_2_be->data) ] = new_node;
	
	return (new_node);	
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				removes node from tree

returns on success: 	iter to inserted node / NULL if node already exists
		on failure:		stub
*/
void *BSTRemove(bst_iter_t iter)
{
	void *ret = NULL;
	
	bst_iter_t node_2_remove = NULL;
	bst_iter_t node_2_reconnect = NULL;
	
	int child_side = 0;
	
	assert(NULL != iter);
	
	ret = iter->data;
		
	/*node 2 remove has no children*/
	if(NULL == iter->children[LEFT] && NULL == iter->children[RIGHT])
	{
		node_2_remove = iter;
		node_2_reconnect = NULL;		
	}
	
	/**/
	if(NULL == iter->children[LEFT] && NULL != iter->children[RIGHT])
	{
		node_2_remove = FindMin(iter->children[RIGHT]);
		iter->data = node_2_remove->data;
		node_2_reconnect = node_2_remove->children[RIGHT];
	}
	
	if(NULL != iter->children[LEFT] && NULL == iter->children[RIGHT])
	{
		node_2_remove = FindMax(iter->children[LEFT]);
		iter->data = node_2_remove->data;
		node_2_reconnect = node_2_remove->children[LEFT];
	}
	
	if(NULL != iter->children[LEFT] && NULL != iter->children[RIGHT])
	{
		node_2_remove = FindMax(iter->children[LEFT]);
		iter->data = node_2_remove->data;
		node_2_reconnect = node_2_remove->children[LEFT];
	}	
{
	
	/*check what child is the node 2 remove*/
	child_side = BSTIsIterEqual(node_2_remove, node_2_remove->parent->children[RIGHT]);
	
	/*reconnext parent to new next node, and new next node to parent*/
	node_2_remove->parent->children[child_side] = node_2_reconnect;
	if(NULL != node_2_reconnect)
	{
		node_2_reconnect->parent = iter;
	}
	
	/*nullify node to be removed*/
	node_2_remove->parent = NULL;
	node_2_remove->data = NULL;
	node_2_remove->children[LEFT] = NULL;
	node_2_remove->children[RIGHT] = NULL;	
	
	free(node_2_remove);
	
	return (ret);
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				finds node with specific data

returns on success: 	iter to found node / stub if node doesn't exists
		on failure:		---
*/
bst_iter_t BSTFind(bst_t *bst, void *data)
{	
	bst_iter_t node = NULL;
	
	assert(NULL != bst);
	assert(1 != BSTIsEmpty(bst));
			
	/*find parent of needed node*/
	node = FindParent(bst, data);
	
	/*if data not found in tree*/
	if(1 == BSTIsIterEqual(node, &bst->stub))
	{
		return (&bst->stub);
	}
	
	/*continue 1 more step*/
	node = node->children[ WhereTo(bst, data, node->data) ];
	
	return (node);
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				returns amount of nodes in the tree

returns on success: 	amount of nodes
*/
size_t BSTSize(bst_t *bst)
{
	size_t num_of_nodes = 0;
	void *tmp = (void *)&num_of_nodes;
	
	assert(NULL != bst);

	BSTForEach(BSTBegin(bst), BSTEnd(bst), IncrementSizetByOne, tmp);

	return (num_of_nodes);
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				checks if bst is empty

returns on success: 	-> 1 if bst is empty
						-> 0 if bst isn't empty
*/
int BSTIsEmpty(bst_t *bst)
{
	assert(NULL != bst);
	
	return ( NULL == bst->stub.children[LEFT] );
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				returns first element in 'in-order' trasverse 
						according to users cmp_func

returns on success: 	-> iter to first element
*/
bst_iter_t BSTBegin(bst_t *bst)
{
	assert(NULL != bst);
	
	return ( FindMin(&bst->stub) );
}

/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				returns last element in 'in-order' trasverse 
						according to users cmp_func

returns on success: 	-> iter to stub
*/
bst_iter_t BSTEnd(bst_t *bst)
{
	assert(NULL != bst);
	
	return (&bst->stub);
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				trasverses to the next node in order.

returns on success: 	-> next node in order, returns stub if reached the end
*/
bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_iter_t next = NULL;
	
	int child_side = 0;
	
	assert(NULL != iter);
	
	/*check what child is the iter*/
	child_side = BSTIsIterEqual(iter, iter->parent->children[RIGHT]);
	
	/*if iter is stub*/
	if(NULL == iter->parent)
	{
		next = iter;
	}
	
	/*iter has right children*/
	else if(NULL != iter->children[RIGHT])
	{
		next = FindMin( iter->children[RIGHT] );
	}
	
	/*iter has no right children & iter is left child*/
	else if(LEFT == child_side)
	{
		next = iter->parent;
	}
	
	/*iter has no right child & iter is right child*/
	else if(RIGHT == child_side)
	{				
		/*goes up the tree until iter becomes left child*/
		while(LEFT != child_side)
		{
			iter = iter->parent;
			child_side = BSTIsIterEqual(iter, iter->parent->children[RIGHT]);
		}
		
		next = (iter->parent);
	}	
	
	return (next);
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				trasverses to the prev node in order.

returns on success: 	-> prev node in order, returns null after the first elem
*/
bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t prev = NULL;
	
	int child_side = 0;
	
	assert(NULL != iter);
	
	/*check what child is the iter*/
	child_side = BSTIsIterEqual(iter, iter->parent->children[RIGHT]);
	
	/*iter has left child*/
	if(NULL != iter->children[LEFT])
	{
		prev = FindMax( iter->children[LEFT] );
	}
	
	/*iter has no left children & iter is right child*/
	else if(RIGHT == child_side)
	{
		prev = iter->parent;
	}
	
	/*iter has no left child & iter is left child*/
	else if(RIGHT == child_side)
	{				
		/*goes up the tree until iter becomes right child and didn't reach stub*/
		while(RIGHT != child_side && NULL != iter->parent)
		{
			iter = iter->parent;
			child_side = BSTIsIterEqual(iter, iter->parent->children[RIGHT]);
		}
		
		prev = (iter->parent);
	}	
	
	return (prev);
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				gets node data

returns on success: 	-> data, or null if at stub
*/
void *BSTGetData(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->data);
}


/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				checks if iterators are equal (NULLs too)

returns on success: 	-> 1 for equality, 0 if not equal.
*/
int BSTIsIterEqual(bst_iter_t iter_1, bst_iter_t iter_2)
{
	return (iter_1 == iter_2);
}


/*----------------------------------------------------------------------------*/
/*
O(n)

function: 				applies action func on each node in the range 
						from - to (not including)

returns on success: 	-> 1 for equality, 0 if not equal.
*/
int BSTForEach(	bst_iter_t from, bst_iter_t to,  
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

/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				Finds parent of data while applying cmp_func at each node

returns on success: 	-> iter to closest node with 'data' (including stub)
						->NULL in case data already exists				
*/
static bst_iter_t FindParent(bst_t *bst, void *data)
{
	int side = 0;
	bst_iter_t node = NULL;
	
	assert(NULL != bst);
	
	if(1 == BSTIsEmpty(bst))
	{
		return (&bst->stub);
	}
			
	node = bst->stub.children[LEFT];	
	
	/*while data hasn't been found in tree*/	
	while(0 != bst->compare(node->data, data))
	{		
		side = WhereTo(bst, data, node->data);
		
		/*if data not found in tree the current node will be the parent*/
		if(NULL == node->children[side])
		{
			return (node);
		}
		
		node = node->children[side];
	}
	
	return (NULL);
}

/*----------------------------------------------------------------------------*/
/*
tells which child the data needs to be placed at (uses cmp_func )

returns:	0(LEFT) if input is smaller than data
			1(RIGHT) if larger
			
ignores equality
*/
static int WhereTo(bst_t *bst, const void *input, const void *data)
{
	int ret = LEFT;
	
	assert(NULL != bst);
	
	if(0 < bst->compare(input, data))
	{
		ret = RIGHT;
	}
	
	return ret;	
}

/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				Finds highest value of data in sub-tree

returns on success: 	-> iter to node with highest 'data' (including self)				
*/
static bst_iter_t FindMax(bst_iter_t node)
{
	assert(NULL != node);
	
	while(NULL != node->children[RIGHT])
	{
		node = node->children[RIGHT];
	}
	
	return (node);
}

/*----------------------------------------------------------------------------*/
/*
O(?)

function: 				Finds lowest value of data in sub-tree

returns on success: 	-> iter to node with lowest 'data' (including self)
*/
static bst_iter_t FindMin(bst_iter_t node)
{
	assert(NULL != node);
	
	while(NULL != node->children[LEFT])
	{
		node = node->children[LEFT];
	}
	
	return (node);
}

/*----------------------------------------------------------------------------*/
/*
O(1)
increments (size_t)var that num points to by 1
*/  

int IncrementSizetByOne(void *arg, void *num)
{
	assert(NULL != num);
	UNUSED(arg);
	
	++*(size_t *)num;
	
	return (0);
}



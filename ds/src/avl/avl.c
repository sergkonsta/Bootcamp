
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      03.06.2020               **
**  Reviewer:  Jenia Edelshtein			**
**  Status:    In Progress				**
*****************************************/
#include <assert.h>
#include <stdlib.h>	/*for malloc*/

#include "avl.h"


/*----------------------------------------------------------------------------*/

typedef enum child {LEFT, RIGHT, NUM_OF_CHILDREN};

typedef struct avl_node
{
    void *key;
    size_t node_height;
    struct avl_node *children[NUM_OF_CHILDREN];
} avl_node_t;

struct avl
{
	avl_node_t *root;
	cmp_func_t cmp_func;	
};

/*static avl_node_t root = {NULL, 0, {NULL, NULL}};*/

/*----------------------------------------------------------------------------*/

static void PostOrderDestroyImp(avl_node_t *node);

static int NodeInsertImp(avl_node_t *node, cmp_func_t cmp_func, void *input_key);
static avl_node_t *CreateNodeImp(void *input_key);
void *RemoveImp(avl_t *avl, avl_node_t *node, const void *key_to_remove);

size_t SizePreOrderImp(avl_node_t *node);

avl_node_t *FindImp(const avl_t *avl, avl_node_t *node, const void *key);
avl_node_t *FindParentImp(const avl_t *avl, avl_node_t *node, const void *key);

int ForEachImp(avl_node_t *node, action_func_t action_func, void *act_func_arg);

static int IsLeaf(avl_node_t *node);
static int HasLeft(avl_node_t *node);
static int HasRight(avl_node_t *node);
static void RemoveLeaf(avl_node_t *node);
enum child UseCmpImp(avl_node_t *node, cmp_func_t cmp_func, const void *input_key);
static avl_node_t *FindMaxImp(avl_node_t *node);
static avl_node_t *FindMinImp(avl_node_t *node);
static int GetHeightImp(avl_node_t *node);


/*------------------------------------------------------------------------------
O(1)
creates avl struct
on success: returns pointer to avl 
on fail: NULL
udefined behaviour: cmp_fun == NULL
*/
avl_t *AVLCreate(cmp_func_t cmp_func)
{
	avl_t *avl = {NULL};
	
	assert(NULL != cmp_func);
	
	avl = (avl_t *)malloc( sizeof(avl_t) );
	if(NULL == avl)
	{
		return (NULL);
	}
	
	avl->root = NULL;
	avl->cmp_func = cmp_func;
	
	return (avl);
}



/*------------------------------------------------------------------------------
O(n)
destroy avl (post order)
on success: destroys avl
on fail: ---
udefined behaviour: avl == NULL

post order means - from leaves up, 
meaning do the function only when a leaf is reached on every subtree starting from left

remove always rotates to balance the tree
*/
void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	PostOrderDestroyImp(avl->root);
		
	avl->cmp_func = NULL;
		
	free(avl);
	
	return;
}

static void PostOrderDestroyImp(avl_node_t *node)
{	
	if (NULL == node)
	{
		return;
	}

	PostOrderDestroyImp(node->children[LEFT]);
	PostOrderDestroyImp(node->children[RIGHT]);
	
	free(node);
}

/*------------------------------------------------------------------------------ 
O(log n)
inserts new node with input data 
on success: returns 0
on fail: returns non zero
udefined behaviour: avl == NULL, input key already exists in the tree
*/

/*not balancing at first stage*/
    
int AVLInsert(avl_t *avl, void *input_key)
{
	assert(NULL != avl);
	assert(NULL != avl->cmp_func);
	
	/*create root*/
	if(1 == AVLIsEmpty(avl))
	{
		avl->root = CreateNodeImp(input_key);
	}
	
	/*create and insert child*/
	else if(1 == NodeInsertImp(avl->root, avl->cmp_func, input_key) )
	{
		return (1);
	}
	
	/*call Balance()*/
	
	return (0);
}


/*recursively inserts new node and update its branch height*/
static int NodeInsertImp(avl_node_t *node, cmp_func_t cmp_func, void *input_key)
{
	/*check to what branch input_key should go to*/
	enum child where_2_go = UseCmpImp(node, cmp_func, input_key);
	
	/*if no child there - create one*/
	if(NULL == node->children[where_2_go])
	{
		node->children[where_2_go] = CreateNodeImp(input_key);
		if(NULL == node->children[where_2_go])
		{
			return (1);
		}
	}
	
	else
	{
		NodeInsertImp(node->children[where_2_go], cmp_func, input_key);	
	}
	
	return (0);
}
	

/*
creates new node:
returns node adress on success, NULL on fail.
*/
static avl_node_t *CreateNodeImp(void *input_key)
{
	avl_node_t *node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(NULL == node)
	{
		return (NULL);
	}

	node->key = input_key;
	node->node_height = 1; 
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	
	return (node);
}

/*------------------------------------------------------------------------------ 
O(log n)
on success: returns key for succesfull removal, NULL if key not found
on fail: ---
udefined behaviour: avl == NULL
*/

/*not balancing at first stage*/

void *AVLRemove(avl_t *avl, const void *key_to_remove)
{
	assert(NULL != avl);
	
	return RemoveImp(avl, avl->root, key_to_remove);
}

void *RemoveImp(avl_t *avl, avl_node_t *node, const void *key_to_remove)
{
	avl_node_t *replacement = NULL;
	avl_node_t *parent = NULL;
	
	/*find node to be removed*/
	avl_node_t *node_2_remove = FindImp(avl, avl->root, key_to_remove);
	if(NULL == node_2_remove)
	{
		return (NULL);
	}
	
	/*node has only right child & possible sub-tree*/
	if(0 == HasLeft(node_2_remove) && 1 == HasRight(node_2_remove))
	{
		replacement = FindMinImp(node_2_remove->children[RIGHT]);
		node_2_remove->key = replacement->key;
	}	
	
	/*node has only left child & possible sub-tree*/
	else if(1 == HasLeft(node_2_remove) && 0 == HasRight(node_2_remove))
	{
		replacement = FindMaxImp(node_2_remove->children[LEFT]);
		node_2_remove->key = replacement->key;
	}
	
	/*got 2 children & possible sub-trees*/
	else if(1 == HasLeft(node_2_remove) && 1 == HasRight(node_2_remove))
	{
		replacement = FindMaxImp(node_2_remove->children[LEFT]);
		node_2_remove->key = replacement->key;
	}

	/*reconnect rest of tree (make the replacement a leaf)*/
	if(0 == IsLeaf(replacement))
	{
		if(HasRight(replacement))
		{
			node_2_remove->children[RIGHT] = replacement->children[RIGHT];
		}
		
		else
		{
			node_2_remove->children[LEFT] = replacement->children[LEFT];
		}
	}
	
	/*replacement is leaf*/
	else
	{
		/*nullify parents child*/
		parent = FindParentImp(avl, node_2_remove, replacement->key);
		
		parent->children[0] = NULL;	
	}
				
	/*remove node*/
	RemoveLeaf(replacement);	
		
	/*Balance*/			
}


/*------------------------------------------------------------------------------
O(1)
on success: returns height of root
on fail: ---
udefined behaviour: avl == NULL
*/
size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);	
	
	return (avl->root->node_height);
}


/*------------------------------------------------------------------------------
O(n)
on success: return size of tree (amount of nodes) (pre-order)
on fail: ---
udefined behaviour: avl == NULL

	pre-order means that i will count every time i go deeper into the Rec, 
	starting from the root and going left
*/	
size_t AVLSize(const avl_t *avl)
{		
	size_t result = 0;
	
	assert(NULL != avl);
	
	if(0 == AVLIsEmpty(avl))
	{
		result = SizePreOrderImp(avl->root);		
	}
	
	return (result);
}

size_t SizePreOrderImp(avl_node_t *node)
{	
	if (NULL == node)
	{
		return 0;
	}

	return( 1 + 
			SizePreOrderImp(node->children[LEFT]) + 
			SizePreOrderImp(node->children[RIGHT])	);
}
		

/*------------------------------------------------------------------------------ 
O(1)
on success: 1 if tree is empty, 0 if tree not empty
on fail: ---
udefined behaviour: avl == NULL
*/
int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == avl->root);
}


/*------------------------------------------------------------------------------ 
O(log n)
finds specific key in tree 
on success: return key if found 
			not found return NULL
on fail: ---
udefined behaviour: avl == NULL
*/ 
void *AVLFind(const avl_t *avl, const void *key)
{
	avl_node_t *node_found = NULL;

	assert(NULL != avl);
	
	node_found = FindImp(avl, avl->root, key);
	
	if(NULL != node_found)
	{
		return (node_found->key);
	}
	
	else 
	{
		return(NULL);
	}
}


avl_node_t *FindImp(const avl_t *avl, avl_node_t *node, const void *key)
{
	enum child where_2_go = 0;
	
	if(key == node->key)
	{
		return (node);
	}
	
	where_2_go = UseCmpImp(node, avl->cmp_func, key);
	
	if(NULL != node->children[where_2_go])
	{
		return (FindImp(avl, node->children[where_2_go], key));
	}
	
	else
	{
		return (NULL);
	}	
}	

avl_node_t *FindParentImp(const avl_t *avl, avl_node_t *node, const void *key)
{
	enum child where_2_go = 0;
		
	if(node->children[LEFT]->key == key || node->children[LEFT]->key == key )
	{
		return (node);
	}
	
	where_2_go = UseCmpImp(node, avl->cmp_func, key);
			
	if(NULL != node->children[where_2_go])
	{
		return (FindImp(avl, node->children[where_2_go], key));
	}
	
	else
	{
		return (NULL);
	}	
}		
	
/*------------------------------------------------------------------------------
O(n)
applies in-order action_func on every node.
on success: returns 0
on fail: returns first non 0, trasverse stops at first failure.
udefined behaviour: user must apply only linear transformations
					avl == NULL
					action_func == NULL
					
	in-order means go to leftmost leaf in left subtree use act_func,
	ascend to root, use act_func 
	go to right child and use act_func
	ascend to roots parent.........................
*/ 
int AVLForEach(avl_t *avl, action_func_t action_func, void *act_func_arg)
{
	assert(NULL != avl);
	assert(NULL != action_func);
	
	return (ForEachImp(avl->root, action_func, act_func_arg));	
}

	

int ForEachImp(avl_node_t *node, action_func_t action_func, void *act_func_arg)
{	
	int status = 1;
	
	if (NULL == node)
	{
		return 0;
	}

	if(	(ForEachImp(node->children[LEFT],action_func, act_func_arg)) || 
		(status = action_func(node->key, act_func_arg)) || 
		(ForEachImp(node->children[RIGHT],action_func, act_func_arg)) )
	{
		return status;
	}

	return 0;
}



/*----------------------------------------------------------------------------*/
/*----------------------		    HELPERS  			----------------------*/
/*----------------------------------------------------------------------------*/

static int IsLeaf(avl_node_t *node)
{
	assert(NULL != node);
	
	return(0 == HasRight(node) && 0 == HasLeft(node));
}

static int HasLeft(avl_node_t *node)
{
	assert(NULL != node);
	
	return(NULL != node->children[LEFT]);
}

static int HasRight(avl_node_t *node)
{
	assert(NULL != node);
	
	return(NULL != node->children[RIGHT]);
}

static void RemoveLeaf(avl_node_t *node)
{
	assert(NULL != node);
	
	node->key = NULL;
	node->node_height = 0;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	
	free(node);
	
	return;
}

enum child UseCmpImp(avl_node_t *node, cmp_func_t cmp_func, const void *input_key)
{
	if(0 > cmp_func(input_key, node->key))
	{
		return (LEFT);
	}	
	
	return (RIGHT);	
}

static avl_node_t *FindMaxImp(avl_node_t *node)
{
	assert(NULL != node);
	
	if(1 == HasRight(node))
	{
		return(FindMaxImp(node->children[RIGHT]));
	}
		
	return (node);
}


static avl_node_t *FindMinImp(avl_node_t *node)
{
	assert(NULL != node);
	
	if(1 == HasLeft(node))
	{
		return(FindMinImp(node->children[LEFT]));
	}
		
	return (node);
}

static int GetHeightImp(avl_node_t *node) 
{
	if(NULL == node)
	{
		return (0);
	}
	
	return (node->node_height);
}










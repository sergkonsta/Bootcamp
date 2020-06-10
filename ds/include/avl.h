#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>

/*should return 0 for equality;  < 0 for key_2 > key_1;  > 0 for key_1 > key_2*/
typedef int (*cmp_func_t)(const void *key_1, const void *key_2);

/* should return 0 for success, non 0 for failure */
typedef int (*action_func_t)(void *key, void *act_func_arg);

typedef struct avl avl_t;


/*
O(1)
creates avl struct
on success: returns pointer to avl 
on fail: NULL
udefined behaviour: cmp_fun == NULL
*/
avl_t *AVLCreate(cmp_func_t cmp_func);


/*
O(n)
destroy avl (post order)
on success: destroys avl
on fail: ---
udefined behaviour: avl == NULL
*/
void AVLDestroy(avl_t *avl);


/* 
O(log n)
inserts new node with input data 
on success: returns 0
on fail: returns non zero
udefined behaviour: avl == NULL, inpu_t key already exists in the tree
*/

/*not balancing at first stage*/

int AVLInsert(avl_t *avl, void *input_key);

/* 
O(log n)
on success: returns key for succesfull removal, NULL if key not found
on fail: ---
udefined behaviour: avl == NULL
*/

/*not balancing at first stage*/

void *AVLRemove(avl_t *avl, const void *key_to_remove);

/*
O(1)
on success: returns height of root
on fail: ---
udefined behaviour: avl == NULL
*/
size_t AVLHeight(const avl_t *avl);

/*
O(n)
on success: return size of tree (amount of nodes) (pre-order)
on fail: ---
udefined behaviour:
*/
size_t AVLSize(const avl_t *avl);

/* 
O(1)
on success: 1 if tree is empty, 0 if tree not empty
on fail: ---
udefined behaviour: avl == NULL
*/
int AVLIsEmpty(const avl_t *avl);

/* 
O(log n)
finds specific key in tree 
on success: return key if found 
			not found return NULL
on fail: ---
udefined behaviour: avl == NULL
*/ 
void *AVLFind(const avl_t *avl, const void *key);

/*
O(n)
applies in-order action_func on every node.
on success: returns 0
on fail: returns first non 0, trasverse stops at first failure.
udefined behaviour: user must apply only linear transformations
					avl == NULL
					action_func == NULL
*/ 
int AVLForEach(avl_t *avl, action_func_t action_func, void *act_func_arg); 


#endif



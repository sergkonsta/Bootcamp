#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>

typedef struct bst bst_t;

typedef struct bst_node *bst_iter_t;

bst_t *BSTCreate(int (*cmp_func)(const void *data1, const void *data2));

void BSTDestroy(bst_t *bst);

/* returns iter to new node on success, returns stub when failed*/
bst_iter_t BSTInsert(bst_t *bst, void *input);

/* retruns data of removed node*/
void *BSTRemove(bst_iter_t iter);

/* retruns iterator to data, if not found returns stub*/ 
bst_iter_t BSTFind(bst_t *bst, void *data);

/*returns amount of elements in the tree*/
size_t BSTSize(const bst_t *bst);

/* returns 1 if bst is empty */
int BSTIsEmpty(const bst_t *bst);

/* returns minimal element*/
bst_iter_t BSTBegin(bst_t *bst);

/*returns stub */
bst_iter_t BSTEnd(bst_t *bst);

bst_iter_t BSTNext(bst_iter_t iter);
bst_iter_t BSTPrev(bst_iter_t iter);

void *BSTGetData(bst_iter_t iter);

/* returns 1 if iters are equal */
int BSTIsIterEqual(bst_iter_t iter_1, bst_iter_t iter_2);

/*retruns success of action function */ 
int BSTForEach(bst_iter_t from, bst_iter_t to, int(*action_func)(void *data, void *arg), void *param); 

#endif



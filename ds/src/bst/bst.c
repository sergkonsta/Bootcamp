
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      24.05.2020               **
**  Reviewer:  Eden Ben Zion			**
**  Status:    ????						**
*****************************************/

#include "bst.h"

enum child {RIGHT, LEFT};

typedef struct bst_node
{
    void *data;
    struct bst_node *parent;
    struct bst_node *children[2];
} bst_node_t;

struct bst
{
	bst_node_t stub;
	
	int (*compar)(const void *, const void *);	
};

/*----------------------------------------------------------------------------*/

bst_t *BSTCreate(int (*cmp_func)(const void *data1, const void *data2));
void BSTDestroy(bst_t *bst);

/* returns iter to new node on success, returns stub when failed*/
bst_iter_t BSTInsert(bst_t *bst, void *input);

/* retruns data of removed node*/
void *BSTRemove(bst_iter_t iter);

/* retruns iterator to data, if not found returns stub*/ 
bst_iter_t BSTFind(bst_t *bst, void *data);

/*return size*/
size_t BSTSize(bst_t *bst);

/* returns 1 if bst is empty */
int BSTIsEmpty(bst_t *bst);

/* returns minimal element*/
bst_iter_t BSTBegin(bst_t *bst);

/*returns stub */
bst_iter_t BSTEnd(bst_t *bst);

bst_iter_t BSTNext(bst_iter_t iter);
bst_iter_t BSTPrev(bst_iter_t iter);

void* BSTGetData(bst_iter_t iter);

/* returns 1 if iters are equal */
int BSTIsIterEqual(bst_iter_t iter_1, bst_iter_t iter_2);

/*retruns success of action function */ 
int BSTForeach(bst_iter_t from, bst_iter_t to,  int(*action_func)(void *data, void *arg), void *param);

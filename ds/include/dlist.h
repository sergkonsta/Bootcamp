#ifndef __OL87_DLIST__H__
#define __OL87_DLIST__H__

#include <stddef.h>	/*for size_t*/

/*
struct dlist_node
{
	void *data;
	struct dlist_node *prev;
	node dlist_node *next;
};

struct dlist
{
	struct dlist_node head;
	struct dlist_node tail;
};
*/

typedef struct dlist dlist_t;

typedef dlist_node* dlist_iter_t;


/*o(1)*//* Creates the dlist. If success, returns the list, else returns NULL */
dlist_t *DListCreate(void);

/*o(n)*//* Destroys the dlist. */
void DListDestroy(dlist_t *dlist);

/*o(1)*//* Returns first valid node or END (if empty).*/ 
dlist_iter_t DListBegin(const dlist_t *dlist);

/*o(1)*/ //* Returns END.*/
dlist_iter_t DListEnd(const dlist_t *dlist);

/* o(1) */ /* Returns the next node */ 
dlist_iter_t DListNext(const dlist_iter_t iter);

/* o(1) */	/* Returns the previous node */ 
dlist_iter_t DListPrev(const dlist_iter_t iter);

/*Amortized o(1)*/ /* Insert before. If success returns iterator of the inserted
node, else returns END.*/ 
dlist_iter_t DListInsert(dlist_iter_t where, void *data);	

/*o(1)*/ /* Removes given node and returns the next node. */
dlist_iter_t DListRemove(dlist_iter_t who);			

/*o(1)*/ /* Returns the iterator of element pushed in first element.
If failure, returns the END. */
dlist_iter_t PushFront(dlist_t *dlist, void *data)

/*o(1)*/ /* Returns the iterator of element pushed in last element.
If failure, returns the END. */
dlist_iter_t PushBack(dlist_t *dlist, void *data)

/*o(1)*/ /* Returns the iterator of next node after pop. */
dlist_iter_t PopFront(dlist_t *dlist)

/*o(1)*/ /* Returns the iterator of new last element after pop. */
dlist_iter_t PopBack(dlist_t *dlist)

/*o(n)*/ /* If param is in the range (from (included), to(not included)), return
iterator to the first found node. If failed, returns to (the first element 
outside of the range).*/
dlist_iter_t DListFind(const dlist_iter_t from, const dlist_iter_t to, int 
(*is_equal)(const void *data, const void *param), const void *param);

/*o(n)*/ /* Returns the status of last foreach action function. Stops after first
failure. Returns 0 for success, else failure */  
int DListForeach(dlist_iter_t from, dlist_iter_t to, int(*action_func)(void
*data, void *arg), void *param);

/*o(1)*/ /* Returns the data of the node*/
void *DListGetData(const dlist_iter_t iterator);

/*o(1)*/ /* Sets data of the node */
void DListSetData(dlist_iter_t iterator, void *data);

/*o(n)*/ /* Returns number of nodes in the list */
size_t DListCount(const dlist_t *dlist);	

/*o(1)*//* Returns 1 (true) if list is empty, else returns 0 (false) */
int DListIsEmpty(const dlist_t *dlist);

/*o(1)*//* Returns 1 (true) if iterators are equal, else returns 0 (false) */
int DListIsIterEqual(const dlist_iter_t iter1, const dlist_iter_t iter2); 

/*o(1)*/ /* Moves nodes in range "from (included) - to (to not included) before
"where" iterator (in a new list or in same list). Where must not be in range. 
Returns "where".*/   
dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where);


#endif /* __OL87_DLIST__H__*/

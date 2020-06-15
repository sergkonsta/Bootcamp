#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>

/*
should return 0 for equality, 
			  < 0 for key_2 > key_1
			  > 0 for key_1 > key_2
*/
typedef int (*cmp_func_t)(const void *key_1, const void *key_2);

typedef struct heap heap_t;

/*
O(1)
Init dyn_size - MACRO in C file.
creates heap struct
on success: returns pointer to heap 
on fail: NULL
unspecified behaviour: cmp_fun == NULL
*/
heap_t *HeapCreate(cmp_func_t cmp_func);


/*
O(1)
destroy heap
on success: destroys heap
on fail: ---
unspecified behaviour: heap == NULL
*/
void HeapDestroy(heap_t *heap);


/* 
O(log n)
inserts new node with input data 
on success: returns 0
on fail: returns non zero
unspecified behaviour: heap == NULL, inpu_t key already exists in the tree
*/
int HeapPush(heap_t *heap, void *data);


/* 
O(log n)
pops root of heap 
on success: ----
unspecified behaviour: heap == NULL, Pop empty tree
*/
void HeapPop(heap_t *heap);

/* 
O(n)
on success: returns data for succesfull removal, NULL if param not found
on fail: ---
unspecified behaviour: heap == NULL
*/
void *HeapRemove(heap_t *heap, int (*is_match)(const void *data, const void *param), void *param);

/*
O(1)
on success: returns root key
on fail: ---
undefined behaviour: heap == NULL, peek empty tree
*/
void *HeapPeek(const heap_t *heap);

/*
O(1)
on success: return size of tree (amount of nodes) 
on fail: ---
undefined behaviour:
*/
size_t HeapSize(const heap_t *heap);

/* 
O(1)
on success: 1 if tree is empty, 0 if heap not empty
on fail: ---
undefined behaviour: heap == NULL
*/
int HeapIsEmpty(const heap_t *heap);


#endif




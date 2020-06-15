
/*****************************************
**				HEAP DS					**
**										**
**  Developer: Sergey Konstantinovsky   **
**  Date:      14.06.2020               **
**  Reviewer:  Alon						**
**  Status:    ?????					**
*****************************************/	
#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/

#include "heap.h"
#include "dynamic_vector.h"

/*size of heap*/
#define DYNAMIC_VECTOR_SIZE (1000)

/*root location in dynamic vector*/
#define ROOT_INDEX 			(0)

/*index of the parent node - ONE BASED ARRAY*/
#define PARENT(i) 			((i - 1) / 2)

/*index of the left child node*/
#define LEFT_CHILD(i) 		(2*i + 1)

/*index of the right child node*/
#define RIGHT_CHILD(i) 		(2*i + 2)

struct heap
{
	vector_t *vector; 
	cmp_func_t cmp_func;  
};

static void HeapifyUpImp(heap_t *heap, size_t index);
static void HeapifyDownImp(heap_t *heap, size_t index);
static void SwapTwoElments(heap_t *heap, size_t index1, size_t index2);

/*----------------------------------------------------------------------------*/
/*
O(1)
Init dyn_size - MACRO in C file.
creates heap struct
on success: returns pointer to heap 
on fail: NULL
unspecified behaviour: cmp_fun == NULL
*/
heap_t *HeapCreate(cmp_func_t cmp_func)
{
	heap_t *heap = NULL;
	
	assert (NULL != cmp_func);
	
	/*create heap struct*/
	heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		return NULL;
	}
	
	/*create dynamic vector struct*/
	heap->vector = DynVecCreate(DYNAMIC_VECTOR_SIZE);
	if (NULL == heap->vector)
	{
		free (heap);
		return NULL;
	}
	
	/*store users pointer to compare function*/
	heap->cmp_func = cmp_func;
	
	return heap;
}


/*----------------------------------------------------------------------------*/
/*
O(1)
destroy heap
on success: destroys heap
on fail: ---
unspecified behaviour: heap == NULL
*/
void HeapDestroy(heap_t *heap)
{
	assert (NULL != heap);
	
	DynVecDestroy(heap->vector);
	
	heap->cmp_func = NULL;
	
	free (heap);
}


/*----------------------------------------------------------------------------*/
/* 
O(log n)
inserts new node with input data 
on success: returns 0
on fail: returns non zero
unspecified behaviour: heap == NULL, input key already exists in the tree
*/
int HeapPush(heap_t *heap, void *data)
{
	assert (NULL != heap);

	/*inserts data*/
	if (1 == DynVecAppend(heap->vector, data))
	{
		return 1;
	}
	
	/*heapifies if needed*/
	HeapifyUpImp(heap, DynVecSize(heap->vector) - 1);		
				
	return 0;			
}


/*----------------------------------------------------------------------------*/
/* 
O(log n)
pops root of heap 
on success: ----
unspecified behaviour: heap == NULL, Pop empty tree
*/
void HeapPop(heap_t *heap)
{
	assert (NULL != heap);
	assert (1 != HeapIsEmpty(heap));

	/*swap root with last node*/
	if (1 < HeapSize(heap))
	{
		SwapTwoElments(heap, ROOT_INDEX, HeapSize(heap) - 1);
	}

	/*removes last node (old root)*/
	DynVecRemoveEnd(heap->vector);
	
	/*heapifies*/
	if (HeapSize(heap) > 1)
	{
		HeapifyDownImp(heap, ROOT_INDEX);
	}

	return;
}


/*----------------------------------------------------------------------------*/
/* 
O(log n)
heapifies the heap
recieves: heap, index of node to heapify, size of data for swap

	heapify up algorithm:
		-> get value from parent
		-> compare them
		-> swap node data with parent data if node data is larger than parent data
		-> keep going until you reached the root or heap is ordered

	heapify down algorithm:
		-> get value from left child
		-> get value from right child
		-> compare them
		-> swap node with the child of higher value according to cmp_func
		-> check if node is heap now
*/

static void HeapifyUpImp(heap_t *heap, size_t index)
{
	/*stop if reached root or no need to heapify*/
	if  (ROOT_INDEX == index || 0 < heap->cmp_func(DynVecGetValue(heap->vector, PARENT(index)), 
									 	  DynVecGetValue(heap->vector, index)))	  
	{
		return;
	}
	
	/*swaps 2 datas*/
	SwapTwoElments(heap, PARENT(index), index);
	
	HeapifyUpImp(heap, PARENT(index));
}



static void HeapifyDownImp(heap_t *heap, size_t index)
{
	void *data_parent = NULL;
	void *data_left = NULL;
	void *data_right = NULL;
	size_t index_2_swap = 0;
	
	assert (NULL != heap);
	
	while (RIGHT_CHILD(index) < HeapSize(heap) &&
		   LEFT_CHILD(index) < HeapSize(heap))
	{	
		/*get all datas*/
		data_parent = DynVecGetValue(heap->vector,index); 
		data_left = DynVecGetValue(heap->vector, LEFT_CHILD(index));
		data_right = DynVecGetValue(heap->vector, RIGHT_CHILD(index));	
			
		/*checks what child to swap with & update index of node*/
		if (0 > heap->cmp_func(data_left, data_right))
		{
			index_2_swap = RIGHT_CHILD(index);
		}
		
		else
		{
			index_2_swap =  LEFT_CHILD(index);
		}
		
		/*performs swap if childs data higher than parents*/		
		if (0 < heap->cmp_func(DynVecGetValue(heap->vector, index_2_swap), data_parent))
		{
			SwapTwoElments(heap, index_2_swap, index);
			index = index_2_swap;		
		}				
		
		else
		{
			break;
		}
	}
	
	return;
}


/*----------------------------------------------------------------------------*/
/* 
O(n)
on success: returns data for succesfull removal, NULL if param not found
on fail: ---
unspecified behaviour: heap == NULL

	algorithm:
		-> iterate the vector to find param
		-> if end of vector reached
			- return NULL
		-> if param found
			- swap it with last data in vector
			- heapify up
			- heapify down
			-return data found
*/
void *HeapRemove(heap_t *heap, int (*is_match)(const void *data, const void *param), void *param)
{
	size_t index = 0;
	size_t heap_size = 0;
	void *data_2_remove = NULL;
	
	assert (NULL != heap);
	
	heap_size = HeapSize(heap);
	
	for (index = ROOT_INDEX;
		 index < heap_size && 1 != is_match(DynVecGetValue(heap->vector, index), param);
		 index++)
	{}
	
	if (index == heap_size)
	{
		return NULL;
	} 
	
	/*hold data to return*/
	data_2_remove = DynVecGetValue(heap->vector, index);
	
	/*swap found data with last in vector*/
	SwapTwoElments(heap, index, heap_size - 1);
	
	/*removes last node (old root)*/
	DynVecRemoveEnd(heap->vector);
	
	HeapifyUpImp(heap, index);
	HeapifyDownImp(heap, index);
	
	return data_2_remove;
}


/*----------------------------------------------------------------------------*/
/*
O(1)
on success: returns root key
on fail: ---
undefined behaviour: heap == NULL, peek empty tree
*/
void *HeapPeek(const heap_t *heap)
{
	assert (NULL != heap);
	assert (1 != HeapIsEmpty(heap));
	
	return DynVecGetValue(heap->vector, ROOT_INDEX);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
on success: return size of tree (amount of nodes) 
on fail: ---
undefined behaviour:
*/
size_t HeapSize(const heap_t *heap)
{
	assert (NULL != heap);
	
	return DynVecSize(heap->vector);
}


/*----------------------------------------------------------------------------*/
/* 
O(1)
on success: 1 if tree is empty, 0 if heap not empty
on fail: ---
undefined behaviour: heap == NULL
*/
int HeapIsEmpty(const heap_t *heap)
{
	assert (NULL != heap);
	
	return 0 == HeapSize(heap);
}




static void SwapTwoElments(heap_t *heap, size_t index1, size_t index2)
{
	void *temp1 = NULL;
	void *temp2 = NULL;
		
	assert(heap);
	assert(index1 < HeapSize(heap));
	assert(index2 < HeapSize(heap));
	
	temp1 = DynVecGetValue(heap->vector, index1);
	temp2 = DynVecGetValue(heap->vector, index2);
	
	DynVecSetValue(heap->vector, index1, temp2);
	DynVecSetValue(heap->vector, index2, temp1);
}


#include <stdio.h>

#include "heap.h"


#include "dynamic_vector.h"	/*for print heap*/
struct heap
{
	vector_t *vector; 
	cmp_func_t cmp_func;  
};


#define ERROR (printf("error in line %d\n", __LINE__));
#define UNUSED(x) (void)(x)


static void PrintHeap(heap_t *heap);

/*------------------------------------------------------------------*/
static int Compare(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}
/*----------------------------------------------------------------------------*/

static int num_1 = 100;
static int num_2 = 35;
static int num_3 = 45;
static int num_4 = 10;
static int num_5 = 55;
static int num_6 = 70;
static int num_7 = 20;
static int num_8 = 40;



int main()
{
	heap_t *heap = HeapCreate(Compare);
	
	HeapPush(heap, &num_1);
	PrintHeap(heap);
	
	HeapPush(heap, &num_2);
	PrintHeap(heap);
	
	HeapPush(heap, &num_3);
	PrintHeap(heap);
	
	HeapPush(heap, &num_4);
	PrintHeap(heap);
	
	HeapPush(heap, &num_5);
	PrintHeap(heap);
	
	HeapPush(heap, &num_6);
	PrintHeap(heap);
	
	HeapPush(heap, &num_7);
	PrintHeap(heap);
	
	HeapPush(heap, &num_8);
	PrintHeap(heap);
	
	HeapDestroy(heap);
	
	return 0;
}


/*----------------------------------------------------------------------------*/


static void PrintHeap(heap_t *heap)
{
	size_t i = 0;
	
	printf("\n\nheap arr is:\n");
	
	while (HeapSize(heap) != i)
	{
		printf("%d\t",*(int *)DynVecGetValue(heap->vector, i));
		++i;
	}
	
	printf("\n\n");
}



























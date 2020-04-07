#ifndef __OL87_DYNAMIC_VECTOR_H__
#define __OL87_DYNAMIC_VECTOR_H__

#include <stddef.h>		/* for size_t */


typedef struct vector vector_t;

/*
struct vector 
{
	void **base;
	size_t capacity;
	size_t size;
};*/


vector_t *DynVecCreate(size_t capacity);
void DynVecDestroy(vector_t *dyn_vec);

int DynVecShrinkToFit(vector_t *dyn_vec);

size_t DynVecCapacity(const vector_t *dyn_vec);
size_t DynVecSize(const vector_t *dyn_vec);

int DynVecAppend(vector_t *dyn_vec, void *data);
void DynVecRemoveEnd(vector_t *dyn_vec);

void *DynVecGetValue(const vector_t *dyn_vec, size_t index);
void DynVecSetValue(vector_t *dyn_vec, size_t index, void *data);

int DynVecReserve(vector_t *dyn_vec, size_t add_size);


#endif







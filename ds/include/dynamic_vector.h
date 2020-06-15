#ifndef __OL87_DYNAMIC_VECTOR_H__
#define __OL87_DYNAMIC_VECTOR_H__

#include <stddef.h>		/* for size_t */

typedef struct vector vector_t;

/*implement with 1 malloc only - struct come before the array in the memory*/
vector_t *DynVecCreate(size_t capacity);
void DynVecDestroy(vector_t *dyn_vec);

int DynVecShrinkToFit(vector_t *dyn_vec);

/* O(1) */
size_t DynVecCapacity(const vector_t *dyn_vec);

/* O(1) */
size_t DynVecSize(const vector_t *dyn_vec);

/*
inserts data to first free index, increases vector if needed
returns 0 for sucess
1 if failed
*/
int DynVecAppend(vector_t *dyn_vec, void *data);

void DynVecRemoveEnd(vector_t *dyn_vec);

void *DynVecGetValue(const vector_t *dyn_vec, size_t index);

void DynVecSetValue(vector_t *dyn_vec, size_t index, void *data);

int DynVecReserve(vector_t *dyn_vec, size_t add_size);


#endif







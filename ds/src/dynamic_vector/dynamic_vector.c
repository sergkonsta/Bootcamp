
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      07.04.2020               **
**  Reviewer:  Amir						**
**  Status:    in progress				**
*****************************************/
#include <assert.h>		/*for assert*/
#include <stdlib.h>		/*for malloc*/

#include "dynamic_vector.h"

struct vector 
{
	void **base;
	size_t capacity;
	size_t size;
};


/*----------------------------------------------------------------------------*/

vector_t *DynVecCreate(size_t capacity)
{
	/*creating the stack struct*/
	vector_t *dyn_vec = (vector_t *)malloc(sizeof(vector_t));
	if(NULL == dyn_vec)
	{
		return (NULL);
	}
	
	/*assert reasonable input from user*/
	assert(0 < capacity);
		
	/*initializing members: size & capacity*/
	dyn_vec->capacity = capacity; 
	dyn_vec->size = 0;
	
	/*initializing member that points to the stack array*/
	dyn_vec->base = (void**)malloc(sizeof(void *) * dyn_vec->capacity);
	if(NULL == dyn_vec->base)
	{
		free(dyn_vec);
		return (NULL);
	}
	
	return (dyn_vec);
}



/*----------------------------------------------------------------------------*/

void DynVecDestroy(vector_t *dyn_vec)
{	
	assert(NULL != dyn_vec);
	
	free(dyn_vec->base);
	dyn_vec->base = NULL;	

	free(dyn_vec);
	dyn_vec = NULL;
	
	return;	
}


/*----------------------------------------------------------------------------*/

int DynVecShrinkToFit(vector_t *dyn_vec)
{
	int fail_flag = 0;
	
	assert(NULL != dyn_vec);	
	
	dyn_vec->base = (void *)realloc(dyn_vec->base, dyn_vec->size * sizeof(void *));
	if(NULL == dyn_vec->base)
	{
		fail_flag = 1;
	}
	
	dyn_vec->capacity = dyn_vec->size;
	
	return (fail_flag);
}


/*----------------------------------------------------------------------------*/

size_t DynVecCapacity(const vector_t *dyn_vec)
{
	assert(NULL != dyn_vec);

	return (dyn_vec->capacity);
}


/*----------------------------------------------------------------------------*/

size_t DynVecSize(const vector_t *dyn_vec)
{
	assert(NULL != dyn_vec);

	return (dyn_vec->size);
}


/*----------------------------------------------------------------------------*/

int DynVecAppend(vector_t *dyn_vec, void *data)
{
	int fail_flag = 0;
	
	if(dyn_vec->size == dyn_vec->capacity)
	{
		fail_flag = DynVecReserve(dyn_vec, dyn_vec->capacity);	
	}
		
	dyn_vec->base[dyn_vec->size] = data;
	
	++dyn_vec->size;
	
	return (fail_flag);
}


/*----------------------------------------------------------------------------*/


void DynVecRemoveEnd(vector_t *dyn_vec)
{
	assert(NULL != dyn_vec);

	--dyn_vec->size;
	
	return;
}


/*----------------------------------------------------------------------------*/

void *DynVecGetValue(const vector_t *dyn_vec, size_t index)
{
	assert(index < dyn_vec->capacity);
	assert(NULL != dyn_vec);
			
	return (dyn_vec->base[index]);
}


/*----------------------------------------------------------------------------*/

void DynVecSetValue(vector_t *dyn_vec, size_t index, void *data)
{
	assert(index <= dyn_vec->size);
	assert(NULL != dyn_vec);
	
	dyn_vec->base[index] = data;

	/*checks if data is added at a new index*/
	if (index >= dyn_vec->size)
	{
		++dyn_vec->size;
	}
	
	return;
}


/*----------------------------------------------------------------------------*/

int DynVecReserve(vector_t *dyn_vec, size_t add_size)
{
	int fail_flag = 0;
	size_t new_size = (dyn_vec->capacity + add_size) * sizeof(void *);
	
	assert(NULL != dyn_vec);
		
	dyn_vec->base = (void *)realloc(dyn_vec->base, new_size);
	
	if(NULL == dyn_vec->base)
	{
		fail_flag = 1;		
	}
	
	dyn_vec->capacity += add_size;
	
	return (fail_flag);
}


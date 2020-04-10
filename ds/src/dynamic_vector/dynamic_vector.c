
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      07.04.2020               **
**  Reviewer:  Amir						**
**  Status:    in progress				**
*****************************************/

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
	stack_t *vec_ptr = (vector_t *)malloc(sizeof(vector_t));
	if(NULL == vec_ptr)
	{
		return NULL;
	}
	
	/*assert reasonable input from user*/
	assert(0 < capacity);
		
	/*initializing members: size & capacity*/
	vec_ptr->capacity = capacity; 
	vec_ptr->size = 0;
	
	/*initializing member that points to the stack array*/
	
	vec_ptr->base = (void**)malloc(sizeof(void *) * vec_ptr->capacity);
	if(NULL == vec_ptr->base)
	{
		free(vec_ptr);
		return NULL;
	}
	
	return stack_ptr;
}







void DynVecDestroy(vector_t *dyn_vec);

int DynVecShrinkToFit(vector_t *dyn_vec);

size_t DynVecCapacity(const vector_t *dyn_vec);
size_t DynVecSize(const vector_t *dyn_vec);

int DynVecAppend(vector_t *dyn_vec, void *data);
void DynVecRemoveEnd(vector_t *dyn_vec);

void *DynVecGetValue(const vector_t *dyn_vec, size_t index);
void DynVecSetValue(vector_t *dyn_vec, size_t index, void *data);

int DynVecReserve(vector_t *dyn_vec, size_t add_size);

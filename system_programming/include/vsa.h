#ifndef __OL87_VSA_H__
#define __OL87_VSA_H__


#include <stddef.h>	/* for size_t */

typedef struct vsa vsa_t;

/*----------------------------------------------------------------------------*/
/*
O(1) 
Function: 	initializes memory pool
Return: 	pointer to initialized memory pool / NULL if not enough memory
*/
vsa_t *VSAInit(void *mem_segment, size_t size);


/*-------------------------------------------------------------------------*/
/*
O(n) 
Function: 	allocates memory
			combines additional free blocks
Return: 	pointer to allocated memory / NULL if no memory space was found
*/
void *VSAAlloc(vsa_t *pool, size_t size_to_alloc);


/*----------------------------------------------------------------------------*/
/*
O(1) 
Function: 	frees block
Return: 	---
*/
void VSAFree(void *chunk);


/*-------------------------------------------------------------------------*/
/*
O(n) 
Function: 	finds largest free chunk of memory
		  	merges adjacent free blocks

Return: 	size_t of largest block found
			0 if none were found
*/
size_t VSALargestChunkAvailable(vsa_t *pool);

/*-------------------------------------------------------------------------*/
#endif /*  __OL87_VSA_H__ */

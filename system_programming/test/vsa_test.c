#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */

#include "vsa.h"

#define ERROR (printf("error in line %d\n", __LINE__));

int main()
{	
	void *segment = malloc(sizeof(char) * 17122);
	vsa_t *pool = VSAInit(segment, 17122);
	
	void *chunk1 = NULL;
	void *chunk2 = NULL;
	void *chunk3 = NULL;	
	void *chunk4 = NULL;		

	if(17088 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
		
	chunk1 = VSAAlloc(pool, 88);
		
	if(16984 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
		
	chunk2 = VSAAlloc(pool, 1500);
	
	if(15464 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}

	chunk3 = VSAAlloc(pool, 3246); /*12200 space left*/
	
	if(12200 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}	
	
	/*too big size test*/
	if(NULL != VSAAlloc(pool, 12201))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
	
	chunk4 = VSAAlloc(pool, 12170);	
	
	if(8 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}	
	
	VSAFree(chunk2);
	
	if(1504 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
	
	VSAFree(chunk3);
	
	if(4768 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
	
	VSAFree(chunk4);
	VSAFree(chunk1);
	
	if(17088 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
	
	free(segment);	
	return 0;
}

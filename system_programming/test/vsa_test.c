#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */

#include "vsa.h"


#define ERROR (printf("error in line %d\n", __LINE__));

int main()
{
	
	void *segment = malloc(sizeof(char) * 200);
	vsa_t *pool = VSAInit(segment, 200);

	void *chunk1 = NULL;
	void *chunk2 = NULL;
	
	size_t test = 0;
/*-------------------------------------------------------------------------*/
	if(168 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
/*-------------------------------------------------------------------------*/
	chunk1 = VSAAlloc(pool, 17);
	chunk2 = VSAAlloc(pool, 30);

	if(80 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
/*-------------------------------------------------------------------------*/
	VSAFree(chunk1);

	if(80 != VSALargestChunkAvailable(pool))
	{
		printf("%ld\n", VSALargestChunkAvailable(pool));
		ERROR
	}
/*-------------------------------------------------------------------------*/
	VSAFree(chunk2);
	
	test = VSALargestChunkAvailable(pool);
	if(168 != test)
	{
		printf("%ld\n", test);
		ERROR
	}

/*-------------------------------------------------------------------------*/
	free(segment);


return 0;
}

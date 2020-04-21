#include <stdio.h>		/*for printf*/

#include "cbuff.h"

#define BUFFER_SIZE (10)

/*
test cases: 




*/

int main()
{
	c_buff_t *cbuff = CirBufferCreate(BUFFER_SIZE);
	
	char array[5] = {'a', 'b', 'c', 'd', 'e'};
	
	printf("\nIsEmpty result: %d\n",CirBufferIsEmpty(cbuff));
	
	printf("\nwrite result: %ld\n",CirBufferWrite(cbuff, array, 3));
	
	printf("\nIsEmpty result: %d\n",CirBufferIsEmpty(cbuff));
	printf("\nFreeSpace result: %ld\n",CirBufferFreeSpace(cbuff));
	printf("\nSize result: %ld\n",CirBufferSize(cbuff));		
	
	CirBufferDestroy(cbuff);
	
	return 1;
}

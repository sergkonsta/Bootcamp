#include <stdio.h>		/*for printf*/
#include <stdlib.h>		/*for malloc*/
#include "cbuff.h"

/* minimum of 3 values*/
#define MIN2(a,b) ((a) < (b)  ? (a) : (b) )
#define MIN3(a,b,c) MIN2(MIN2(a,b),(c))

void TestCase(	size_t case_num, size_t buf_capacity, size_t dest_size,
				size_t src_size, size_t num_2_write, size_t num_2_read);

/*

TEST CASES:

	BufSize		dest	src			2write		2read
	
[		2		10		10			10			10		]	-	CASE 1
[		10		10		10			10			0		]	-	CASE 2
[		10		10		10			1			10		]	-	CASE 3
[		10		10		10			0			10		]	-	CASE 4

[		10		2		10			2			10		]	-	CASE 5
[		10		2		10			10			2		]	-	CASE 6
[		10		10		2			2			10		]	-	CASE 7
[		10		10		2			10			2		]	-	CASE 8

*/

int main()
{	
	TestCase(1,2,10,10,10,10);
	
	TestCase(2,10,10,10,10,0);
	
	TestCase(3,10,10,10,1,10);
	
	TestCase(4,10,10,10,0,10);
	
	TestCase(5,10,2,10,2,10);
	
	TestCase(6,10,2,10,10,2);
	
	TestCase(7,10,10,2,2,10);
		
	/*TestCase(8,10,10,2,10,2);*/ /*attempts to write more that src_size - !vlg!*/

	printf("\n\nIf no problems were stated - all good.\n\n");	
	return 1;
}

void TestCase(	size_t case_num, size_t buf_capacity, size_t dest_size,
				size_t src_size, size_t num_2_write, size_t num_2_read)
{
	c_buff_t *cbuff = NULL;	
	char *src = (char *)malloc(sizeof(char)*src_size);
	char *dest = (char *)malloc(sizeof(char)*dest_size);
	
	size_t tmp = 0;
	size_t min_3 = 0;
	size_t min_2 = 0;
	size_t size_counter = 0;
	
	/*		creating buffer		*/
	cbuff = CirBufferCreate(buf_capacity);
	
	if(NULL == cbuff)
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	if(1 != CirBufferIsEmpty(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	if((buf_capacity - CirBufferSize(cbuff)) != CirBufferFreeSpace(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	

	/*		writing to buffer		*/	
	min_3 = MIN3(num_2_write, src_size, CirBufferFreeSpace(cbuff));
	min_2 = MIN2(num_2_write, CirBufferFreeSpace(cbuff));
	size_counter += CirBufferWrite(cbuff, src, num_2_write);
	
	
	/*checks for case:		 num_2_write <= src_size	*/	
	/*if(min_3 != size_counter)
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}*/
	 	
	/*checks for case:		any num_2_write 	*/
	if(min_2 != size_counter)
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	 	
	if((!(num_2_write)) != CirBufferIsEmpty(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	if(size_counter != CirBufferSize(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	if((buf_capacity - size_counter) != CirBufferFreeSpace(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	

	
	/*		reading from buffer		*/	
	min_3 = MIN3(num_2_read, dest_size, CirBufferSize(cbuff));
	
	tmp = CirBufferRead(cbuff, dest, num_2_read); 		
	
	size_counter -= tmp;
	
	if(min_3 != tmp)
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
		
	if((!(size_counter)) != CirBufferIsEmpty(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	if(size_counter != CirBufferSize(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	if((buf_capacity - size_counter) != CirBufferFreeSpace(cbuff))
	{
		printf("\nproblem in line: %d, case: %ld",__LINE__,case_num);
	}
	
	CirBufferDestroy(cbuff);
	
	free(dest);
	free(src);
	
	return;
}



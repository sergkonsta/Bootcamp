

/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    ???						**
*****************************************/
#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/
#include <assert.h>		/*for assert*/
#include <string.h>		/*for original memset*/

#include "ex1.h"		/*Memlib*/


int main()
{
	char *free_test_1 = NULL;
	char *free_test_2 = NULL;
	char *test_space_1 = malloc(sizeof(char) * NUMBER_OF_PLACES);
	char *test_space_2 = malloc(sizeof(char) * NUMBER_OF_PLACES);

	if(NULL == test_space_1 || NULL == test_space_2)
	{
		return 0;
	}
	
	/*backup for mem free*/
	free_test_1 = test_space_1;
	free_test_2 = test_space_2;

	
	TestMemset(test_space_1, test_space_2);
	
	free(free_test_1);
	free(free_test_2);
	
	return 1;
}


/*prints memory before and after Memset*/
int TestMemset(char *s1, char *s2)
{
	size_t counter = 0;
	
	assert(NULL != s1 && NULL != s2);
			
	Memset((void *)s1, '$', NUMBER_OF_PLACES);	
	memset((void *)s2, '$', NUMBER_OF_PLACES);	
	
	while(0 < counter)
	{
		if(*s1 != *s2)
		{
			printf("error in Memset");
		}
		
		++s1;
		++s2;
	}

	return 1;
}


















/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    SENT						**
*****************************************/

#include "memlib.h"

int main()
{
	int i_1 = INT_FOR_ITOA;
	char *str = STR_FOR_ATOI;
	
	unsigned int base_1 = BASE_FOR_ITOA;
	unsigned int base_2 = BASE_FOR_ATOI;
	
	char *free_test_1 = NULL;
	char *free_test_2 = NULL;
	
	char *test_space_1 = malloc(sizeof(char) * SIZE_OF_MEM);
	char *test_space_2 = malloc(sizeof(char) * SIZE_OF_MEM);

	if(NULL == test_space_1 || NULL == test_space_2)
	{
		return 0;
	}
	
	/*backup for mem free*/
	free_test_1 = test_space_1;
	free_test_2 = test_space_2;
	
	/*start tests*/
	printf("Starting tests, errors will be printed below.\n\n");
	
	TestMemSet(test_space_1, test_space_2);
	ZeroMem(test_space_2);
	
	TestMemCpy(test_space_1, test_space_2);
	ZeroMem(test_space_2);
	
	TestMemMove(test_space_1, test_space_2);
	ZeroMem(test_space_2);

	TestIntToString(i_1,base_1);
	TestStringToInt(str, base_2);
	
	printf("All done,\nIf no errors were printed, you're good.\n\n");
	
	/*free mem*/
	free(free_test_1);
	free(free_test_2);
		
	return 1;
}


/*prints memory before and after Memset*/
int TestMemSet(char *s1, char *s2)
{
	size_t counter = SIZE_OF_MEM;
	
	assert(NULL != s1 && NULL != s2);
			
	MemSet((void *)s1, CHAR_TO_MEMSET, NUMBER_OF_PLACES);	
	memset((void *)s2, CHAR_TO_MEMSET, NUMBER_OF_PLACES);	
	
	while(0 < counter)
	{
		if(*s1 != *s2)
		{
			printf("error in MemSet while counter = %ld\n",counter);
		}
		
		--counter;
		++s1;
		++s2;
	}

	return 1;
}

int TestMemCpy(char *src, char *dest)
{
	size_t counter = SIZE_OF_MEM;
	
	assert(NULL != src && NULL != dest);
			
	MemCpy((void *)dest, (const void *)src, NUMBER_OF_PLACES);	
		
	while(0 < counter)
	{
		if(*src != *dest)
		{
			printf("error in MemCpy while counter = %ld\n",counter);
		}
		
		--counter;
		++src;
		++dest;
	}

	return 1;
}



int TestMemMove(char *src, char *dest)
{
	size_t counter = SIZE_OF_MEM;
	
	assert(NULL != src && NULL != dest);
			
	MemMove((void *)dest, (const void *)src, NUMBER_OF_PLACES);	
		
	while(0 < counter)
	{
		if(*src != *dest)
		{
			printf("error in MemMove\n");
		}
		
		--counter;
		++src;
		++dest;
	}

	return 1;
}


int ZeroMem(char *s)
{
	assert(NULL != s);
			
	MemSet((void *)s, '0', SIZE_OF_MEM);	
		
	return 1;
}


int TestIntToString(int i, unsigned int base)
{
	size_t digits = 0;
	char *str = NULL;
	int tmp = i;
	
	while(0 != tmp)
	{
		tmp /= 10;
		++digits;
	} 

	str = (char *)malloc((digits + SIZE_OF_NULL_TERM) * sizeof(char));
	if(NULL == str)
	{
		return 0;
	}
	
	str = IntToString(i, str, 10);


	printf("\nInt to string test:\nint is: %d\nstring is: %s\n\n",i,str);

	free(str);
	
	return 1;
}

int TestStringToInt(const char *str, unsigned int base)
{	
	printf("\nTesting for String To Int:\n");
	printf("%s in base %u is: %d\n\n",str,base, StringToInt(str, base));
	
	
	return 1;
}








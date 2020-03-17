#include <stdio.h>	/*	for printf		*/
#include <ctype.h>	/*	for to lower()  */
#include <assert.h> /*	for assert		*/
#include <string.h> /*	for strlen		*/
#include <stdlib.h> /*	for malloc		*/

#include "ex.h"




 /*Duplicates the string in lower case
  (original c function strdup() doest work well,
  returns *int instead of *char)   		     	*/
char *StrDup(char *s)
{
	char *dup_str = NULL;
	char *result = NULL;
	
	assert(NULL != s);
	
	/*malloc for string , copies pointer to its beginning*/
	result = (char*)malloc((strlen(s)+1)*sizeof(char));
	assert(NULL != result);
	dup_str = result; 
	
	/*classic strcpy() only with lowercase casting*/	
	while('\0' != *s)
	{
		*dup_str = tolower(*s);		
		s++;
		dup_str++;
	}
	*dup_str = '\0';
			
	return result;
}	



/* counts and returns indexes in array of pointers */
size_t ArrLen(char **str)
{
	size_t counter = 0;

	assert(NULL != str);
		
	while(NULL != *str)
	{
		++counter;
		++str;
	}
		
	return counter;
}



/*receives pointer to array of pointers ending with NULL
  prints the strings at the end of each pointer and then frees its alloc.*/
void PrintAndFree(char **str)
{
	char **str_copy1 = str;
	char **str_copy2 = str;
	assert(NULL != str);
	
	/*prints and then frees strings*/
	while(NULL != *str)
	{	
		printf("%s\n\n",*str);
		++str;
		free(*str_copy1);
		++str_copy1;
	}
	
	/*free 'array of pointers'*/
	free(str_copy2);
	
	return;
}



/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      17.03.2020               **
**  Reviewer:  Eliran					**
**  Status:    Approved					**
*****************************************/

/*	***** Uses multiple mallocs in order to make it less likely to fail. 	
	
	ALGORITHM:
	
	1. check length of 'array of pointers'
	
	2. malloc new 'array of pointers' & assert successful malloc
	
	3. in each index of the new 'array of pointers':
		
		-> check length of old string
		
		-> malloc new string & assert successful malloc
		
		-> link between new string and 'array of pointers'
		
		-> copy from old string to new string in lowercase
		
		-> continue for next index
		
	4. print all new strings and free them, free main array of pointers*/



void PrintEnvLow(char **env)
{
	char **new_env = NULL;
	char **new_env_start = NULL;

	assert(NULL != env);
	
	/*creates new 'array of pointer' (the +1 is for the last NULL pointer)*/
	new_env = (char**)malloc((ArrLen(env)+1) * sizeof(*env));
	assert(NULL != new_env);
	
	/*saves pointer to new array of pointers*/
	new_env_start = new_env;
	
	/*creates new strings and links them to 'array of pointers'*/
	while(NULL != *env)
	{
		*new_env = StrDup(*env);		
		++new_env;	
		++env;
	}	
	
	/*prints new Env Vars and free memmory*/
	PrintAndFree(new_env_start);
			
	return;
}


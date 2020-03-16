#include <unistd.h> /*	for *__environ	*/
#include <stdio.h>	/*	for printf		*/
#include <ctype.h>	/*for to lower() */

#include "ex.h"



/*receives pointer to array of pointers ending with NULL
  prints the strings at the end of each pointer	in lower-case */
  
void PrintEnvironmentVar(char **str)
{
	printf("\n\n The Env Var is: ");
		
	while(NULL != *str)
	{
		/*from the format: 'NAME=value' prints only EnvVar name*/
		while('=' != **str)
		{
			printf("%c",tolower(**str));
			++*str;		
		}
		
		printf("\n\n");
		
		++str;
	}
		
	return;
}

void PrintEnvLow(char **env)
{
	PrintEnvironmentVar(env);
}


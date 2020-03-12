

#include <ctype.h>         /*  for tolower() inside StrCmpCmp  */
#include <stdlib.h>        /*  for abs() ; malloc()            */
#include <string.h>        /*  for strlen(), strdup() used in StrDup     */
#include "ilrd_strings.h"


/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      11.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Approved                **
****************************************/


/*checking strings length and returningthe length in size_t*/

size_t StrLen(const char *s)
{
	size_t counter = 0;
	
	for(; *s != '\0'; counter++, s++) {}

	return counter;
}



/* comparing 2 strings and returning 0 for equality of the result of ascii char substraction: s1-s2 */

int StrCmp(const char *s1, const char *s2)
{
	while((*s1 == *s2) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	
	return (*s1 - *s2);
}



/* copying 1 string into the destination */

char *StrCpy(char *dest, const char *src)
{
	char *start = dest;		 /*save start pointer for the return*/

	while(*src != '\0')
	{
		*dest = *src;		
		src++;
		dest++;
	}

	*dest = '\0';
	
	return start;
}

/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      11.03.2020              **
**  Reviewer:  Elimelech               **
**  Status:    Approved                **
****************************************/

/* comparing 2 strings disregarding lower-case and upper-case
 differences using tolower() */

int StrCaseCmp(const char *s1, const char *s2)
{
	while((tolower(*s1) == tolower(*s2)) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	
	return (*s1 - *s2);

}


/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      12.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Sent                        **
****************************************/

/* returns the first occurance of the Char in the String
   if it can't find the char - will return a pointer to null */

char *StrChr(const char *s, int c)
{
	char *nullpointer = NULL;
	char *res = (char *)s;
	
	while(*res != '\0') 
	{
		if(*res == (char)c)
		{
			return res;
		}
		++res;
	}
	return nullpointer;
}



/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      12.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Sent                    **
****************************************/

/* returns a pointer to a new string which is a duplicate of the first one.
   uses malloc 
   
   *******     CLIENT: remember to free memory after use!!!    ********** */
   
   
char *StrDup(const char *s)
{
	size_t str_length = strlen(s);
	char *dup_str = NULL;
	char *result = NULL;
	
	dup_str = (char*)malloc((str_length+1)*sizeof(char));

	result = dup_str; 
	
	while(*s != '\0')
	{
		*dup_str = *s;
		++s;
		++dup_str;
	}
	*dup_str = '\0';
	
	return result;
}	




/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      12.03.2020              **
**  Reviewer:          **
**  Status:                        **
****************************************/

/*  */


























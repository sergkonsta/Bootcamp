
#include <assert.h>        /*  for assert() */
#include <ctype.h>         /*  for tolower() inside StrCmpCmp  */
#include <stdlib.h>        /*  for abs() ; malloc()            */
#include <string.h>        /*  for strlen(), strdup() used in StrDup     */

#include "ilrd_strings.h"


/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      12.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Approved                **
****************************************/

/* returns the first occurance of the Char in the String
   if it can't find the char - will return a pointer to null */

char *StrChr(const char *s, int c)
{
	char *nullpointer = NULL;
	const char *res = s;
	
	while(*res != '\0') 
	{
		if(*res == (const char)c)
		{
			return (char *)res;
		}
		++res;
	}
	return nullpointer;
}



/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      12.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Approved                **
****************************************/

/* returns a pointer to a new string which is a duplicate of the first one.
   uses malloc 
   
   *******     CLIENT: remember to free memory after use!!!    ********** */
   
   
char *StrDup(const char *s)
{
	size_t str_length = strlen(s);
	char *dup_str = NULL;
	char *result = NULL;
	
	result = (char*)malloc((str_length+1)*sizeof(char));
	assert(NULL != result);
	
	dup_str = result; 
	
	dup_str = StrCpy(dup_str, s);
	
	return result;
}	




/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      12.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Approved                **
****************************************/

/* the function appends src  string to dest string removing the NULL 
char and creating a new one at the end of the appended strings */

char *StrCat(char *dest, const char *src)
{
	char *dest_start = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	/* saving pointer for the return*/
	dest_start = dest;
	
	/* increment dest pointer to the '\0' place */
	while(*dest != '\0')
	{
		++dest;
	}
	
	/*adding src string to the end of des string*/
	strcpy(dest, src);

	return dest_start;
}





/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      12.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Approved                **
****************************************/

/* the function finds the first occurance of the substring needle in the string
 haystack. returns pointer to the start of needle if found. NULL if not found */
 
char *StrStr(const char *haystack, const char *needle)
{
	size_t needle_length = StrLen(needle);
	const char *location_in_haystack = haystack;

	assert(NULL != haystack);
	assert(NULL != needle);

	while(0 != strncmp(location_in_haystack, needle, needle_length))
	{
		/*looks for the first needle char in the haystack*/
		location_in_haystack = strchr(haystack, (int)*needle);  
				
		if(NULL == location_in_haystack)
		{
			return NULL;
		}
		
		haystack = location_in_haystack + 1;
	}
			
	return (char *)location_in_haystack;
}






/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      14.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    sent                    **
****************************************/

/* the function counts how many chars from the start of the str,
   all appear in the accept str                                        */

size_t StrSpn(const char *str, const char *accept)
{
	size_t result = 0;
	
	assert(NULL != accept);
	assert(NULL != str);
	
	while('\0' != *str)
	{
		if(NULL != strchr(accept, (int)*str))
		{
			++result;
			++str;
		}
		else
		{
			return result;
		}
	}
	return result;
}


#include "ilrd_strings.h"


size_t StrLen(const char *s)
{
	size_t counter = 0;
	
	for(; *s != '\0'; counter++, s++) {}

	return counter;
}

int StrCmp(const char *s1, const char *s2)
{
	while((*s1 == *s2) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	
	return (*s1 - *s2);
}

char *StrCpy(char *dest, const char *src)
{
	char *start = dest;

	while(*src != '\0')
	{
		*dest = *src;		
		src++;
		dest++;
	}
	dest = '\0';
	
	return start;
}

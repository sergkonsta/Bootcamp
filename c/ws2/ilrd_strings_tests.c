#include <string.h> /*for strcmp, strchr*/
#include <strings.h> /* for strcasecmp */
#include <stdio.h>  /* io */
#include <stdlib.h> /*  for free() */
#include "ilrd_strings.h"

void TestStrCpy()
{
	const char str1[] = "abcdefgh";
	const char str2[] = "abcdegh";
	const char str3[] = "ab cdegh";
	char str4[20] = "";
	char str5[20] = "";
	char str6[20] = "";

	StrCpy(str4, str1);
	StrCpy(str5, str2);
	StrCpy(str6, str3);

	if( StrCmp(str4, str1) == 0)
	{
		printf("Success.\n");
	}
	if( StrCmp(str5, str2) == 0)
	{
		printf("Success.\n");
	}
	if( StrCmp(str6, str3) == 0)
	{
		printf("Success.\n");
	}
}	

void TestStrCmp()
{
	char str1[50] = "abcdefgh";
	char str2[50] = "abcdegh";
	char str3[50] = "ab cdegh";
	char str4[50] = "ab cdefgh";
	char str5[50] = "abcd";
	char str6[50] = "abcdefgh";
	char str7[50] = "abcdefgh";
	char str8[50] = "abcd";

	if(strcmp(str1, str2) != StrCmp(str1, str2))
	{
		printf("Error in str 1 and 2");
	}
	if(strcmp(str3, str4) != StrCmp(str3, str4))
	{
		printf("Error in str 3 and 4");
	}
	if(strcmp(str5, str6) != StrCmp(str5, str6))
	{
		printf("Error in str 5 and 6");
	}
	if(strcmp(str7, str8) != StrCmp(str7, str8))
	{
		printf("Error in str 7 and 8");
	}
	else
	{
		printf("Success");
	}

}


void TestStrCaseCmp()
{
	char str1[6] = {'a','B','c','D','e','\0'};
	char str2[6] = {'A','b','c','d','e','\0'};
	
	printf("%s\n",str1);
	printf("%s\n",str2);

	if(strcasecmp(str1, str2) != StrCaseCmp(str1, str2))
	{
		printf("Error in str 1 and 2");
	}
	
	else
	{
		printf("Success\n");
	}

}

void TestStrLen()
{
	char serg[10] = "Hello!";
	size_t x = 0;
		
	printf("%s\n",serg);
	
	x = StrLen(&serg[0]);
	printf("%ld\n",x);
}

void TestStrChr()
{
	int c = 'z';
	char str[] = "this is my string";
	
	if (StrChr(str, c) == strchr(str, c))
	{
		printf("all good\n");
	}
	else printf("somethings wrong \n");
}

void TestStrDup()

/*testing that the new string is identical to the original one. */

{

	const char str[] = "this is my stringaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char *new_str = NULL;
	int result1 = 0;
	
	new_str = StrDup(str);
	result1 = strcmp(new_str, str);

	if(result1 == 0)
	{
		printf("\nAll good\n\n");
	}
	else 
	{
		printf("\nsomethings wrong\n\n");
	}
	
	free(new_str);
	
	return;
}


void TestStrCat()
{
	char str1[100] = "This is my first string. ";
	char str2[] = "this is my second string. ";
	
	printf("\n %s\n\n", str1);
	printf("\n %s\n\n", str2);
	
	printf("\n This is the new string: \n\n");	
	printf("\n %s\n\n", StrCat(str1, str2));
	
	return;
}

void TestStrStr()
{
	const char *strlong = "   Hello, my name is sergey konstantinovskymy n.";
	const char *str = "e";
	if(StrStr(strlong, str) == strstr(strlong, str))
	{
		printf("\nsuccess\n\n");
	}
	else 
	{
		printf("\nsomethings wrong\n\n");
	}

	return;
}

int main()
{
	TestStrStr();
	return 0;	

}

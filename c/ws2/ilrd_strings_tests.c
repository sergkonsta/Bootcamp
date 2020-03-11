#include <string.h> /* for strings */
#include <stdio.h>
#include "ilrd_strings.h"

void TestStrCpy()
{
	int a = 0, b = 0, c = 0;	

	const char str1[50] = "abcdefgh";
	const char str2[50] = "abcdegh";
	const char str3[50] = "ab cdegh";
	char str4[50];
	char str5[50];
	char str6[50];

	str4 = StrCpy(str4, str1);
	str5 = StrCpy(str5, str2);
	str6 = StrCpy(str6, str3);

	a = StrCmp(str1, str4);
	b = StrCmp(str2, str5);
	c = StrCmp(str3, str6);

	if(a == 0 && b == 0 && c == 0)
	{
		printf("Success");	
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

void TestStrLen()
{
	char serg[10] = "Hello!";
	size_t x = 0;
		
	printf("%s\n",serg);
	
	x = StrLen(&serg[0]);
	printf("%ld\n",x);
}

int main()
{
	
	TestStrCpy();
	return 0;	

}

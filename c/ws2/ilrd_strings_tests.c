#include <stdio.h>
#include "ilrd_strings.h"


void TestStrLen()
{
	char serg[10] = "Hello!";
		
	printf("%s\n",serg);
	
	size_t x = StrLen(&serg[0]);
	printf("%ld",x);
}

int main()
{

	

}

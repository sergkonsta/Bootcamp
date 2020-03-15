#include <stdio.h>
#include "ex.h"

/*tests for: even, odd, empty and 1 char string*/

void TestIsPalindrome()
{
	size_t test_counter = 0;
	
	const char *str = "!ax123  321xa!";
	test_counter += IsPalindrome(str);
	
	str = "!ax123 321xa!";
	test_counter += IsPalindrome(str);
		
	str = "";
	test_counter += IsPalindrome(str);
	
	str = "1";
	test_counter += IsPalindrome(str);
	
	str = "!ax123q 321xa!";
	test_counter += IsPalindrome(str);
	
	/*test counter should be equal to amount of not-palindromes above*/
    if(1 == test_counter)
    {
    	printf("\nsuccess!\n\n");
    }
	
	else
	{
		printf("\n somethings wrong.\n\n");
	}
	
	return;
}


/*------------------------------------------------------------------*/


void LaunchBoom7()
{
	Boom7(1457, 9);
	
	return;
}


/*------------------------------------------------------------------*/


void TestSwapIntPointers()
{
	int a = 1;
	int b = 2;
	
	int *pa = &a;
	int *pb = &b;

	printf("\nData before swap:\n\n");	
	printf("\n\n int a=%d is located at %p. A's pointer is located at %p:",a,(void*)&a,(void*)&pa);
	printf("\n\n int b=%d is located at %p. B's pointer is located at %p:",b,(void*)&b,(void*)&pb);

	SwapIntPointers(&pa, &pb);	
	
	printf("\nData after swap:\n\n");	
	printf("\n\n int a=%d is located at %p. A's pointer is located at %p:",a,(void*)&a,(void*)&pa);
	printf("\n\n int b=%d is located at %p. B's pointer is located at %p:",b,(void*)&b,(void*)&pb);

	return;
}


/*------------------------------------------------------------------*/

void TestAddStrings()
{
	char str1[] = "1294";
	char str2[] = "32";
	char str3[] = "0000";
	
	printf("\n %s \n\n",str1);
	printf("\n %s \n\n",str2);
	printf("\n %s \n\n",AddStr(str1, str2, str3));
		
	return;
}

/*------------------------------------------------------------------*/

int main()
{
	TestAddStrings();
	
	return 0;
}

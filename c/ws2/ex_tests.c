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

void LaunchBoom7()
{
	Boom7(1457, 9);
	
	return;
}

int main()
{
	LaunchBoom7();
	return 0;
}

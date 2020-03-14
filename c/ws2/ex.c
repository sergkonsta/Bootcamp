#include <string.h> 			/*for stlen()*/
#include <assert.h>				/*for asser()*/
#include <stdio.h>				/*for printf()*/

int ContainsDigit(int number, int digit)
{
	int curr_digit = 0;
	
	while(0 != number)
	{
		curr_digit = number % 10;
		
		if(curr_digit == digit)
		{
			return 1;
		}
		number /= 10;
	}
	
	return 0;
}


/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      14.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    sent                    **
****************************************/

/* Tests if the string is a palindrome and returns: 
   0 for palinfrome
   1  for not palindrome                           */


int IsPalindrome(const char *s)
{
	/*pointer to the end of the string*/
	const char *s_rev = &s[strlen(s) - 1];

	int loop_counter = strlen(s) / 2;
	
	/*checks for NULL pointer*/
	assert(NULL != s);
	
	/*empty string or 1 char string*/
	if(0 == loop_counter)
	{
		return 0;
	}
	
	/*comparing first and last string char, loops towards center of string*/
	while(0 != loop_counter) 
	{
		if(*s != *s_rev)
		{
			return 1;
		}
		
		++s;
		--s_rev;
		--loop_counter;
	}
	
	return 0;	
}	





/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      14.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    sent                    **
****************************************/

/* prints all numbers in recieved range. 
   prints BOOM instead of numbers dividable by 7 or that contain the digit 7*/
   
void Boom7(int num1, int num2)
{
	int range_min = 0;
	int range_max = 0;
	
	assert(num1 != num2);
	
	/*determines min and max number*/
	if(num1 < num2)
	{
		range_min = num1;
		range_max = num2;
	}
	
	else
	{
		range_min = num2;
		range_max = num1;
	}
	
	/*print and num check loop*/
	while(range_min != range_max)
	{
		if((0 == range_min % 7) || 1 == ContainsDigit(range_min, 7))
		{
			printf(" BOOM! ");
		}
		
		else
		{
			printf(" %d ",range_min);
		}
		
		++range_min;
	}
}
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
	


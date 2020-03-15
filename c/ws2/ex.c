#include <string.h> 			/*for stlen()*/
#include <assert.h>				/*for asser()*/
#include <stdio.h>				/*for printf() -Boom7 needs to be printed here*/ 
#include <stdlib.h>				/*for malloc()*/

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

void StrRev(char *str)
{
	int strlength = strlen(str) / 2;
	char tmp = 0;
	char *end = NULL;
	
	end = strchr(str,'\0');
	--end;
		
	while(0 != strlength)
	{
		tmp = *str;
		*str = *end;
		*end = tmp;
		
		++str;
		--end;
		--strlength;		
	}
	
	return;
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
   
   
   
   
   
   
/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      14.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    sent                    **
****************************************/

/* swaps 2 pointers to integers*/

void SwapIntPointers(int **p1, int **p2)
{
	int *tmp = NULL;
	
	assert(NULL != *p1);
	assert(NULL != *p2);
	
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	
	return;
}
   
   
   
   
/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      15.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    SENT                    **
****************************************/

/* makes string of numbers addition*/  
    
 
char *AddStr(char *str1, char *str2)
{
	int carry = 0;
	int sum = 0;
	size_t counter = 0;	
	size_t length1 = strlen(str1);
	size_t length2 = strlen(str2);
	char *res = NULL;
	char *sumstr = NULL;
		
	assert(NULL != str1);
	assert(NULL != str2);
	assert(length1 > length2);
	
	sumstr = (char *)malloc((length1 + 1) * sizeof(char));
	res = sumstr;
		
	/*reverse strings*/
	StrRev(str1); 
	StrRev(str2); 
	
	/*long addition for the parallel part of both strings*/
	while(length2 > counter)
	{
		sum = (*str1 - '0') + (*str2 - '0') + carry;
		*sumstr = (char)((sum % 10) + '0');
		carry = sum / 10;
		
		++str1;
		++str2;
		++counter;
		++sumstr;
	}
	
	/*Adds the remainder of the long string*/
	while(length1 > counter)
	{
		sum = (*str1 - '0')+ carry;
		*sumstr = (char)((sum % 10) + '0');
		carry = sum / 10;
		
		++str1;
		++counter;
		++sumstr;
	}
	
	/*adds last carry if exists and '\0' */
	if(0 != carry)
	{
		*sumstr = carry;
		++sumstr;
	}
	*sumstr = '\0';
	
	/*reverts back*/
	StrRev(res);
	
	return res;

}
   
   
   
   
   
/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      15.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    ____                    **
****************************************/

/* removes double white-spaces */  
   

   
   
   
   
   
	


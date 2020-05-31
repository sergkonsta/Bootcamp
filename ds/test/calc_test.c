
#include <stdio.h>

#include "calc.h"

int main()
{
	double result = 0.0;
	
	char str1[100] = "4+5";   
	char str2[100] = "1+2+3+4-5";
	char str3[100] = "1+2*3+5";
	char str4[100] = "2+3-1+1*2*3*5/3-1";

	
	
/*    char str2[100] = "8+83+-2^5";         Result =  0 status = SUCCESS   	  */
/*    char str3[100] = "8+83-2^";           Result =  0 status = SYNTAX_ERROR */
/*    char str4[100] = "2/0";               Result =  0 status = MATH_ERROR   */
/*    char str5[100] = "8++8((3-2)5)";      Result = 48 status = SUCCESS      */
/*    char str6[100] = "3-2)5";             Result =  0 status = SYNTAX_ERROR */
/*    char str7[100] = "(3-2)5+ 5(4+4+4";   Result =  0 status = SYNTAX_ERROR */

	printf("\n\n");
	
	if(SUCCESS != Calc(str1, &result) || 9.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str2, &result) || 5.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str3, &result) || 12.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str4, &result) || 13.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	printf("\n  %f  \n",result);
	
	printf("\nif no errors were printed - all tests are passed.\n");
	printf("\n\n");
	
	return (0);
}

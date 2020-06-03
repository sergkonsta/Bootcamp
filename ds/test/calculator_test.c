
#include <stdio.h>

#include "calculator.h"

int main()
{
	double result = 0.0;
	
	char str1[100] = "4+5";   
	char str2[100] = "1+2+3+4-5";
	char str3[100] = "1+2*3+5";
	char str4[100] = "2+3-1+1*2*3*5/3-1";
	
	char str5[100] = "1*5+(4*5)+2+2";
	char str6[100] = "(4*5)+2+2-7";
	char str7[100] = "2*5+(7-5)";
	char str8[100] = "(4*2+4-1+5)/2";
	
	char str9[100] = "2^3";
	char str10[100] = "(2^3)*2^(2/2)";
	char str11[100] = "((2^3-8)*2)+17";
	
    char str12[100] = "8+83+-2^5";       /*not ready - need to change storeop to use strtod*/ 
    char str13[100] = "8+83-2^";          
	char str14[100] = "2/0";
    char str15[100] = "8++8((3-2)5)";     /* Result = 48 status = SUCCESS      */
    char str16[100] = "3-2)5"; 
    char str17[100] = "(3-2)5+ 5(4+4+4";

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
	
	if(SUCCESS != Calc(str5, &result) || 29.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str6, &result) || 17.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str7, &result) || 12.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str8, &result) || 8.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str9, &result) || 8.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str10, &result) || 16.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str11, &result) || 17.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SUCCESS != Calc(str12, &result) || 59.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}	

	if(SYNTAX_ERR != Calc(str13, &result))
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(MATH_ERR != Calc(str14, &result))
	{
		printf("\nerror in line: %d",__LINE__);
	}
	/*
	if(SUCCESS != Calc(str15, &result) || 48.0 != result)
	{
		printf("\nerror in line: %d",__LINE__);
	}
	*/
	if(SYNTAX_ERR != Calc(str16, &result))
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	if(SYNTAX_ERR != Calc(str17, &result))
	{
		printf("\nerror in line: %d",__LINE__);
	}
	
	/*printf("\n  %f  \n",result);*/
	
	printf("\nif no errors were printed - all tests are passed.\n");
	printf("\n\n");
	
	return (0);
}

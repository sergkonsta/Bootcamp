#include <stdio.h>
#include <stdlib.h> // for abs()


float power(int n)
{
	int num = abs(n);	
	float res = 1;
	for(int i = 0; i < num; i++)
		res *= 10;

	if(0 > n)
		return (1 / res);
	
	return res;
}

void main()
{

	float x = 0;
	
	for(int i = -10; i != 10; i++)
	{
		x = power(i);
		printf("\n%f",x);
	}

}

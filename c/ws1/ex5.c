#include <stdlib.h>
#include <stdio.h>

int FlipInt(int num)
{
	int rev = 0;

	if(num < 10 && num > -10)
	{
		return num;
	}
	
	if(num == 10 || num == -10)
	{
		return (num / 10);
	}

	for(; num != 0; num /= 10)
	{
		rev = (num % 10) + (rev * 10);
	}

	return rev;
}

void main()
{
	int x = 0;

	for(int i = -99999999; i != 99999999; i++)
	{
		x = FlipInt(i);
		printf("\n%d",x);		
	}

}

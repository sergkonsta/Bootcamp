#include <stdio.h>

typedef union numbers
{
	int i;
	float f;
	double d;
} one;

typedef struct x
{
	int i;
	char c;
	double d;
	short s;
	
} two;

typedef struct card
{
	unsigned int s:2;
	unsigned int f:4;
}three;

int main()
{
	
	printf("%ld\n%ld\n%ld\n",sizeof(one),sizeof(two),sizeof(three));
	return 1;
}

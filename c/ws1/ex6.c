#include <stdio.h>

void Swap(int *a, int *b)
{

	int tmp = *a;
	*a = *b;
	*b = tmp;

	return;
}

void main()
{

	int a = 5;
	int b = 10;

	printf("Values before swap are:\n");
	printf("A = %d and located at: %p\n",a,&a);
	printf("B = %d and located at: %p\n",b,&b);
	
	Swap(&a, &b);

	printf("Values after swap are:\n");
	printf("A = %d and located at: %p\n",a,&a);
	printf("B = %d and located at: %p\n",b,&b);

}

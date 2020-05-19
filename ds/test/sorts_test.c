
#include <stdlib.h>	/*for rand*/
#include <stdio.h>	/*for printf*/

#include "sorts.h"

#define TEST_ARR_SIZE (5000)

static int ArrayIsSorted(int arr[], size_t size);
static void FillArray(int arr[], size_t size);

int main()
{
	int arr[TEST_ARR_SIZE] = {0};
	
	/*----------------  fill arr with random ints, sort and check ------------*/
	FillArray(arr, TEST_ARR_SIZE);	
	
	BubbleSort(arr, TEST_ARR_SIZE);	
	
	if(0 == ArrayIsSorted(arr,TEST_ARR_SIZE))
	{
		printf("\n\nError in Bubble sort.\n\n");
	}
	
	
	
	
	
	
	
	printf("\n\nIF NO ERRORS WERE PRINTED ---> ALL GOOD!\n\n");
	
	return 0;
}


/*----------------------------------------------------------------------------*/
/*--------------------------------HELPERS-------------------------------------*/
/*----------------------------------------------------------------------------*/


static int ArrayIsSorted(int arr[], size_t size)
{
	size_t iter = 0;
	int sorted_flag = 1;
	
	while((iter + 1) < size)
	{
		if(arr[iter] > arr[iter + 1])
		{
			sorted_flag = 0;
			break;
		}

		++iter;
	}
	
	return (sorted_flag);
}

static void FillArray(int arr[], size_t size)
{
	size_t iter = 0;
	
	while(iter < size)
	{
		arr[iter] = rand();
		++iter;
	}
	
	return;
}

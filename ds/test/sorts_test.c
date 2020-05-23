
#include <stdlib.h>	/*for rand & malloc*/
#include <stdio.h>	/*for printf*/
#include <string.h>	/*for memcpy*/
#include <time.h>	/*for clock*/

#include "sorts.h"

#define TEST_ARR_SIZE (5000)

#define MIN_RANGE (1)
#define MAX_RANGE (100)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

static int ArrayIsSorted(int arr[], size_t size);
static void FillArray(int arr[], size_t size);
static void PrintTestResult(int test_result, char *test_name);
static void FillArrayLow(int arr[], size_t size);
static int QSPartition (int *arr, int low, int high);
static void QuickSort(int *arr, int low, int high);
static void Swap(int *a, int *b);

int main()
{	
	int *arr = (int *)calloc(TEST_ARR_SIZE, sizeof(int));
	int *dup_arr = (int *)calloc(TEST_ARR_SIZE, sizeof(int));
	int *sorted_arr = (int *)calloc(TEST_ARR_SIZE, sizeof(int));

	clock_t time_tag = 0;
	clock_t time_tag_q = 0;

	/*radix simpletest case:*/
	int a[8] = {170,45,75,90,802,24,2,66};
	RadixSort(a, 8);

	/*------------------------------------------------------------------------*/
	/*							 BUBBLE SORT TEST						      */
	/*------------------------------------------------------------------------*/
	FillArray(arr, TEST_ARR_SIZE);	
	memcpy((void *)dup_arr, (const void *)arr, (sizeof(int) * TEST_ARR_SIZE));
	
	time_tag = clock();
	BubbleSort(arr, TEST_ARR_SIZE);		
	PrintTestResult( ArrayIsSorted(arr,TEST_ARR_SIZE), "bubble sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	QuickSort(dup_arr, 0, TEST_ARR_SIZE - 1);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "quick sort" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (Bubble sort time - Q-Sort time) is: ");
	printf("\n(%fs - %fs) = %fs\n",	(float)time_tag/CLOCKS_PER_SEC,
								(float)time_tag_q/CLOCKS_PER_SEC,
								(float)(time_tag - time_tag_q)/CLOCKS_PER_SEC);
	
	
	/*------------------------------------------------------------------------*/
	/*							 SELECTION SORT TEST						  */
	/*------------------------------------------------------------------------*/	
	FillArray(arr, TEST_ARR_SIZE);	
	memcpy((void *)dup_arr, (const void *)arr, (sizeof(int) * TEST_ARR_SIZE));
	
	time_tag = clock();
	SelectionSort(arr, TEST_ARR_SIZE);		
	PrintTestResult( ArrayIsSorted(arr,TEST_ARR_SIZE), "selection sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	QuickSort(dup_arr, 0, TEST_ARR_SIZE - 1);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "quick sort" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (selection sort time - Q-Sort time) is: ");
	printf("\n(%fs - %fs) = %fs\n",(float)time_tag/CLOCKS_PER_SEC,
								 (float)time_tag_q/CLOCKS_PER_SEC,
								 (float)(time_tag - time_tag_q)/CLOCKS_PER_SEC);

	/*------------------------------------------------------------------------*/
	/*							 INSERTION SORT TEST						  */
	/*------------------------------------------------------------------------*/
	FillArray(arr, TEST_ARR_SIZE);	
	memcpy((void *)dup_arr, (const void *)arr, (sizeof(int) * TEST_ARR_SIZE));
	
	time_tag = clock();
	InsertionSort(arr, TEST_ARR_SIZE);		
	PrintTestResult( ArrayIsSorted(arr,TEST_ARR_SIZE), "insertion sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	QuickSort(dup_arr, 0, TEST_ARR_SIZE - 1);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "quick sort" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (insertion sort time - Q-Sort time) is: ");
	printf("\n(%fs - %fs) = %fs\n",(float)time_tag/CLOCKS_PER_SEC,
							 	 (float)time_tag_q/CLOCKS_PER_SEC,
								 (float)(time_tag - time_tag_q)/CLOCKS_PER_SEC);
	
	
	/*------------------------------------------------------------------------*/
	/*							 COUNTING SORT TEST							  */
	/*------------------------------------------------------------------------*/
	
	FillArrayLow(arr, TEST_ARR_SIZE);	
	memcpy((void *)dup_arr, (const void *)arr, (sizeof(int) * TEST_ARR_SIZE));
	
	time_tag = clock();
	CountingSort(arr, TEST_ARR_SIZE, MIN_RANGE, MAX_RANGE, sorted_arr);		
	PrintTestResult( ArrayIsSorted(sorted_arr,TEST_ARR_SIZE), "counting sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	QuickSort(dup_arr, 0, TEST_ARR_SIZE - 1);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "quick sort" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (counting sort time - Q-Sort time) is: ");
	printf("\n(%fs - %fs) = %fs\n",(float)time_tag/CLOCKS_PER_SEC,
								   (float)time_tag_q/CLOCKS_PER_SEC,
								 (float)(time_tag - time_tag_q)/CLOCKS_PER_SEC);


	
	/*------------------------------------------------------------------------*/
	/*							 RADIX SORT TEST							  */
	/*------------------------------------------------------------------------*/
	
	FillArray(arr, TEST_ARR_SIZE);	
	memcpy((void *)dup_arr, (const void *)arr, (sizeof(int) * TEST_ARR_SIZE));
	
	time_tag = clock();
	RadixSort(arr, TEST_ARR_SIZE);		
	PrintTestResult( ArrayIsSorted(sorted_arr,TEST_ARR_SIZE), "radix sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	QuickSort(dup_arr, 0, TEST_ARR_SIZE - 1);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "quick sort" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (radix sort time - Q-Sort time) is: ");
	printf("\n(%fs - %fs) = %fs\n",(float)time_tag/CLOCKS_PER_SEC,
								   (float)time_tag_q/CLOCKS_PER_SEC,
								 (float)(time_tag - time_tag_q)/CLOCKS_PER_SEC);

	
	printf(GRN"\n\nIF NO ERRORS WERE PRINTED ---> ALL GOOD!\n\n"RESET);	
	
	free(sorted_arr);
	free(dup_arr);
	free(arr);
	
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
		arr[iter] = rand() % 9999999;
		++iter;
	}
	
	return;
}

/*fill array with number in the range 1 to 100*/
static void FillArrayLow(int arr[], size_t size)
{
	size_t iter = 0;
	
	while(iter < size)
	{
		arr[iter] = ((rand() % 99) + 1);
		++iter;
	}
	
	return;
}

static void PrintTestResult(int test_result, char *test_name)
{
	
	if(1 != test_result)
	{
		printf(RED"\n\nError in %s, line: %d.\n\n"RESET,test_name,__LINE__);	
	}
	
	return;
}


/*----------------------------------------------------------------------------*/
/*GEEKS qsort - here for time comparison testing*/

static int QSPartition (int *arr, int low, int high) 
{ 
	int pivot = arr[high];    
	int i = (low - 1);  
	int j = low;
		
	for(j = low; j <= high- 1; j++) 
	{ 
		if (arr[j] < pivot) 
		{ 
			i++;   
			Swap(&arr[i], &arr[j]); 
		} 
	} 

	Swap(&arr[i + 1], &arr[high]); 

	return (i + 1); 
} 

static void QuickSort(int *arr, int low, int high) 
{ 		
	if(low < high) 
	{ 
		int pi = QSPartition(arr, low, high); 

		QuickSort(arr, low, pi - 1); 
		QuickSort(arr, pi + 1, high); 
	} 
	
	return;
} 
/*----------------------------------------------------------------------------*/

/* int swapper */
static void Swap(int *a, int *b) 
{ 
	int temp_swap = 0;

	temp_swap = *a; 
	*a = *b; 
	*b = temp_swap; 
} 









#include <stdlib.h>	/*for rand & malloc*/
#include <stdio.h>	/*for printf*/
#include <string.h>	/*for memcpy*/
#include <time.h>	/*for clock*/

#include "sorts.h"

#define TEST_ARR_SIZE (5000)

#define ERROR (printf(RED"\n\nError in line: %d.\n\n",__LINE__))

#define MIN_RANGE (1)
#define MAX_RANGE (100)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

static int ArrayIsSorted(int arr[], size_t size);
static void FillArray(int arr[], size_t size);
static void PrintTestResult(int test_result, char *test_name);
static void FillArrayLow(int arr[], size_t size);
static int Cmp(const void*int1, const void *int2);

int main()
{	
	int *arr = (int *)calloc(TEST_ARR_SIZE, sizeof(int));
	int *dup_arr = (int *)calloc(TEST_ARR_SIZE, sizeof(int));
	int *sorted_arr = (int *)calloc(TEST_ARR_SIZE, sizeof(int));

	clock_t time_tag = 0;
	clock_t time_tag_q = 0;
	
	size_t i = 0;
	
	/*small test case*/
	/*int a[6] = {170,45,-17,170,-9,24};
	QuickSortRecursive(a, 6, sizeof(int), Cmp);		
	
	for(i = 0; i < 6; i++)
	{
		printf("\n%d",a[i]);
	}*/
	
	/*------------------------------------------------------------------------*/
	/*					ITERATIVE BINARY SEARCH TEST					      */
	/*------------------------------------------------------------------------*/
	/*fill array from 0 to TEST_ARR_SIZE*/
	for (i = 0; i < TEST_ARR_SIZE; i++)
	{
		arr[i] = i;
	}
	/*int number is index */
	if ((int)4221 != BinarySearchIter(arr, TEST_ARR_SIZE, 4221))
	{
		ERROR;
	}
	/*int number is index */
	if ((int)4221 != BinarySearchRec(arr, TEST_ARR_SIZE, 4221))
	{
		ERROR;
	}
	
	/*------------------------------------------------------------------------*/
	/*					RECURSIVE MERGE SORT TEST						      */
	/*------------------------------------------------------------------------*/
	FillArray(arr, TEST_ARR_SIZE);	
	memcpy((void *)dup_arr, (const void *)arr, (sizeof(int) * TEST_ARR_SIZE));
	
	time_tag = clock();
	MergeSortRec(arr, TEST_ARR_SIZE);		
	PrintTestResult(ArrayIsSorted(arr, TEST_ARR_SIZE), "Recursive Merge sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	qsort(dup_arr, TEST_ARR_SIZE, sizeof(int), Cmp);
	PrintTestResult(ArrayIsSorted(dup_arr, TEST_ARR_SIZE), "linux qsort time" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\n\nTime difference (Recursive Merge sort time - linux qsort time) is: ");
	printf("\n(%fs - %fs) = %fs\n",	(float)time_tag/CLOCKS_PER_SEC,
								(float)time_tag_q/CLOCKS_PER_SEC,
								(float)(time_tag - time_tag_q)/CLOCKS_PER_SEC);
	
	
	/*------------------------------------------------------------------------*/
	/*					RECURSIVE QUICK SORT TEST						      */
	/*------------------------------------------------------------------------*/
	FillArray(arr, TEST_ARR_SIZE);	
	memcpy((void *)dup_arr, (const void *)arr, (sizeof(int) * TEST_ARR_SIZE));
	
	time_tag = clock();
	QuickSortRecursive(arr, TEST_ARR_SIZE, sizeof(int), Cmp);		
	PrintTestResult(ArrayIsSorted(arr, TEST_ARR_SIZE), "Recursive Quick sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	qsort(dup_arr, TEST_ARR_SIZE, sizeof(int), Cmp);
	PrintTestResult(ArrayIsSorted(dup_arr, TEST_ARR_SIZE), "linux qsort time" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (Recursive Quick sort time - linux qsort time) is: ");
	printf("\n(%fs - %fs) = %fs\n",	(float)time_tag/CLOCKS_PER_SEC,
								(float)time_tag_q/CLOCKS_PER_SEC,
								(float)(time_tag - time_tag_q)/CLOCKS_PER_SEC);	
	
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
	qsort(dup_arr, TEST_ARR_SIZE, sizeof(int), Cmp);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "linux qsort time" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (Bubble sort time - linux qsort time) is: ");
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
	qsort(dup_arr, TEST_ARR_SIZE, sizeof(int), Cmp);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "linux qsort time" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (selection sort time - linux qsort time) is: ");
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
	qsort(dup_arr, TEST_ARR_SIZE, sizeof(int), Cmp);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "linux qsort time" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (insertion sort time - linux qsort time) is: ");
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
	qsort(dup_arr, TEST_ARR_SIZE, sizeof(int), Cmp);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "linux qsort time" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (counting sort time - linux qsort time) is: ");
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
	PrintTestResult( ArrayIsSorted(arr,TEST_ARR_SIZE), "radix sort" );
	time_tag = clock() - time_tag;
	
	time_tag_q = clock();
	qsort(dup_arr, TEST_ARR_SIZE, sizeof(int), Cmp);
	PrintTestResult( ArrayIsSorted(dup_arr,TEST_ARR_SIZE), "linux qsort time" );	
	time_tag_q = clock() - time_tag_q;	
	
	printf("\nTime difference (radix sort time - linux qsort time) is: ");
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
/*CHECKS IF ARRAY IS SORTED*/
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
			printf(RED"\n Error! unsorted number: %d \n"RESET,arr[iter]);
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
static int Cmp(const void*int1, const void *int2)
{
	return *(int *)(int1) - *(int *)(int2);
}






/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      11.06.2020               **
**  Reviewer:  Yael						**
**  Status:    sent						**
*****************************************/		
#include <assert.h>		/*for assert*/
#include <stdlib.h>		/*for calloc*/
#include <string.h>		/*for memcpy*/
#include <sys/types.h>	/*for ssize_t*/

#include "sorts.h"

#define MIN_VAL_RADIX (0)
#define MAX_VAL_RADIX (9999999)
#define RADIX_SORT_VAL (10)
#define UNUSED(X) (void)(X)

static void Swap(int *a, int *b);
static void SwapImp(void *p1, void *p2, size_t size);
static int RadixCountingSort(int *arr, size_t arr_size, int dev_factor);
static int RadixGetMaxDevFactor(int *arr, size_t arr_size);
static int BinarySearchRecImp(int *arr, size_t low_index, size_t high_index, int num_2_find);
static int MergeSortRecImp(int *arr_to_sort, size_t low_index, size_t high_index);

static int MergeCombineImp(int *arr_to_sort, size_t low_index, 
						   size_t mid_index, size_t high_index);

static void QuickSortRecursiveImp(int *arr, int low_index, int high_index,
								  int(*compare)(const void *, const void *), size_t size);
			  						   
static size_t QuickSortPivotPlaceImp(int *arr, size_t low_index, size_t high_index, 
									 int (*compare)(const void *, const void *), size_t size); 									 
/*----------------------------------------------------------------------------*/
/*iterative  & tail recursive binary search*/
/*
	algorithm:
		-> get sorted array of ints
		-> get middle index of the array
		-> compare num_2_find to number in middle index:
			->is equal - return found
			->if lower - update arr boundaries: from 0 to (last middle index - 1) 
			->if higher -update arr boundaries: from (last middle index + 1) to END
		repeat until found	
*/
int BinarySearchIter(int *arr, size_t arr_size, int num_2_find)
{
	size_t low_index = 0;
	size_t mid_index = 0;
	size_t high_index = arr_size - 1;
	
	assert(NULL != arr);
	
	while (low_index <= high_index)
	{
		mid_index = low_index + (high_index - low_index) / 2;
		
		if (num_2_find == arr[mid_index])
		{
			return (mid_index);
		}
		
		/*number_2_find is in upper half of arr*/
		else if (num_2_find > arr[mid_index])
		{
			low_index = mid_index + 1;
		}
		
		/*number_2_find is in lower half of arr*/
		else
		{
			high_index = mid_index - 1;
		}
	}
	
	/*not found*/
	return -1;
}

/*----------------------------------------------------------------------------*/
int BinarySearchRec(int *arr, size_t arr_size, int num_2_find)
{
	assert (NULL != arr);
	
	return BinarySearchRecImp(arr, 0, arr_size - 1, num_2_find);	
}

/*tail rec*/
static int BinarySearchRecImp(int *arr, size_t low_index, size_t high_index, int num_2_find)
{
	/*num_2_find is not out of bounds*/
	if (high_index >= low_index) 
	{ 
		/*update mid index*/
		int mid_index = low_index + (high_index - low_index) / 2; 

		/*num is found*/
		if (arr[mid_index] == num_2_find) 
		{	
			return mid_index; 
		}
		
		/*number_2_find is in upper half of arr*/
		if (num_2_find > arr[mid_index]) 
		{	
			return BinarySearchRecImp(arr, mid_index + 1, high_index, num_2_find); 
		}
		
		/*number_2_find is in lower half of arr*/
		return BinarySearchRecImp(arr, low_index, mid_index - 1, num_2_find); 
	} 
	
	/*not found*/
	return -1; 	
}
 
/*----------------------------------------------------------------------------*/
/*iterative  & tail recursive binary search*/
/*
	algorithm:
		-> get array of integers to sort
		
		-> stop: when size is 1
		-> int 1 = call yourself with lower half of array
		-> int 2 = call yourself with higher hlaf of array
		
		-> return: combine int1 and int2 while sorting
		
		
	combine algorithm:
		-create sub_arr_1[mid_index - low_index];
		-create sub_arr_2[high_index - mid_index];
		-check not failed
				
		-fill sub_arr_1 with nums from low to mid + 1
		-fill sub_arr_2 with nums from mid + 1 to high + 1
		
		-while (sub_arr_1 not ended && sub_arr_2 not ended)
			-fill arr_to_sort from low to high index with nums from sub arrays
			 while sorting
			 
		-fill with remaining numbers from sub array 1 or 2 if exist
		
		release sub arrays					
*/ 
int MergeSortRec(int *arr_to_sort, size_t num_elements)
{
	assert (NULL != arr_to_sort);
	
	return MergeSortRecImp(arr_to_sort, 0, num_elements - 1); 	
}

static int MergeSortRecImp(int *arr_to_sort, size_t low_index, size_t high_index)
{
	/*update mid index*/
	int mid_index = low_index + (high_index - low_index) / 2; 
	
	/*stop recursion when sub array is of 1 num*/
	if(low_index < high_index)
	{
		/*lower half*/	
		MergeSortRecImp(arr_to_sort, low_index, mid_index);
		
		/*upper half*/	
		MergeSortRecImp(arr_to_sort, mid_index + 1, high_index);
		
		/*combines back*/
		return MergeCombineImp(arr_to_sort, low_index, mid_index, high_index);	
	}
	
	return 0;
}

/*return 0 for success, 1 for failed alloc*/
static int MergeCombineImp(int *arr_to_sort, size_t low_index, 
						   size_t mid_index, size_t high_index)
{
	/*loop iters*/
	size_t i_1 = 0;
	size_t i_2 = 0;
	size_t i_sorted = low_index;
	
	/*calculating sub array sizes*/
	size_t sub_1_size = mid_index  - low_index + 1; 
    size_t sub_2_size = high_index - mid_index; 
	
	/*allocating sub arrays*/
	int *sub_arr_1 = (int *)calloc(sub_1_size, sizeof(int));
	int *sub_arr_2 = (int *)calloc(sub_2_size, sizeof(int));
	if (NULL == sub_arr_1 || NULL == sub_arr_2)
	{
		free(sub_arr_1);
		free(sub_arr_2);
		
		return 1;
	}
	
	/*fill sub arr 1*/
	for (i_1 = 0; i_1 < sub_1_size; i_1++) 
	{
		sub_arr_1[i_1] = arr_to_sort[low_index + i_1]; 
	}
	
	/*fill sub arr 2*/
	for (i_2 = 0; i_2 < sub_2_size; i_2++) 
	{
		sub_arr_2[i_2] = arr_to_sort[mid_index + 1 + i_2];	
	}
	
	/*go back to start of arrays*/
	i_1 = 0;
	i_2 = 0;
	i_sorted = low_index;
	
	/*fill original array while sorting*/	
	while (i_1 < sub_1_size && i_2 < sub_2_size) 
	{ 
		if (sub_arr_1[i_1] <= sub_arr_2[i_2]) 
		{ 
			arr_to_sort[i_sorted] = sub_arr_1[i_1]; 
			++i_1; 
		} 
	
		else 
		{ 
			arr_to_sort[i_sorted] = sub_arr_2[i_2]; 
			++i_2; 
		} 
		
		++i_sorted; 
	}
	
	/*moving all the rest if exist*/
	while (i_1 < sub_1_size) 
	{ 
		arr_to_sort[i_sorted] = sub_arr_1[i_1]; 
		++i_1; 
		++i_sorted; 
	} 

	/*moving all the rest if exist*/
	while (i_2 < sub_2_size) 
	{ 
		arr_to_sort[i_sorted] = sub_arr_2[i_2]; 
		++i_2; 
		++i_sorted; 
	} 

	free(sub_arr_1);
	free(sub_arr_2);
	
	return 0;
}



/*----------------------------------------------------------------------------*/
/*
base is array to sort, 
nmemb - amount of members, 
size - sizeof(member)
compare func works like strcmp

	algorithm:
		-> choose last element as pivot
		-> iterate the array with pivot_des and loop iterator 
		   (to find where to place the pivot):
				- if a specific element is smaller than pivot element: 
					-- increment pivod dest 
					-- swap places: arr[pivot dest] <--> arr[loop iter]

		-> when done, place pivot in its sorted position
		->return pivots index
		
		-> call yourself with array to the left of pivot
		-> call yourself with array to the right of pivot
*/

/*wrapper*/
void QuickSortRecursive(void *arr, size_t nmemb, size_t size, int(*compare)(const void *, const void *))
{ 		
	size_t low_index = 0; 
	size_t high_index = nmemb - 1;		
	
	UNUSED(size);
	
	QuickSortRecursiveImp(arr, low_index, high_index, compare, size);
}



static void QuickSortRecursiveImp(int *arr, int low_index, int high_index,
								  int(*compare)(const void *, const void *), size_t size)
{			
	if(low_index < high_index) 
	{ 
		size_t pivot_index = QuickSortPivotPlaceImp(arr, low_index, high_index, compare, size); 

		QuickSortRecursiveImp(arr, low_index, pivot_index - 1, compare, size); 
		QuickSortRecursiveImp(arr, pivot_index + 1, high_index, compare, size); 
	} 
	
	return;
} 




static size_t QuickSortPivotPlaceImp(int *arr, size_t low_index, size_t high_index, 
									 int (*compare)(const void *, const void *), size_t size) 
{ 
	/*pivot of choice*/
	size_t pivot_index = high_index;
	
	/*iters*/
	ssize_t pivot_dest = low_index - 1;  
	size_t  loop_iter  = low_index;
	
	/*find the right place for the pivot*/	
	for(; loop_iter <= high_index - 1; loop_iter++) 
	{ 
		/*sort data according to pivot*/
		if (0 > compare(&arr[loop_iter], &arr[pivot_index])) 
		{ 
			pivot_dest++;   
			SwapImp(&arr[pivot_dest], &arr[loop_iter], size); 
		} 
	} 

	SwapImp(&arr[pivot_dest + 1], &arr[high_index], size); 

	return (pivot_dest + 1); 
} 


/*-----------------------------------------------------------------------------
O(n^2)
functionality: applies a bubble sort in ascending order on ints.
return: ---
*/
void BubbleSort(int *arr, size_t arr_length)
{
	int swap_flag = 1;
	int *left = arr;
	int *right = arr + 1;

	/*until array is sorted*/
	while(0 != swap_flag)
	{
		for (swap_flag = 0, left = arr, right = arr + 1;
			right < arr + arr_length;
			++left, ++right)
		{
			if (*left > *right)
			{
				Swap(left, right);
				swap_flag = 1;
			}
		}

		/* adjust loop range */
		--arr_length;
	}
	
	return;
}

/*-----------------------------------------------------------------------------
O(n^2)
functionality: Selection sort in ascending order on ints.
return: ---
*/
void SelectionSort(int *arr, const size_t arr_length)
{
	size_t min_elem_index = 0;
	size_t iter_find = 0;
	size_t iter_place = 0;
	
	assert(NULL != arr);
	assert(arr_length > 0);
	
	/*outer loop*/
	while(iter_place < arr_length - 1)
	{
		/*restart min element with every inner loop*/
		min_elem_index = iter_place;
		
		/*inner loop - to find min element*/
		while(iter_find < arr_length)
		{			
			if(arr[iter_find] < arr[min_elem_index])
			{
				min_elem_index = iter_find;
			}
			
			++iter_find;
		}
		
		/*place min element first*/		
		Swap(&arr[min_elem_index], &arr[iter_place]);
					
		++iter_place;
		iter_find = iter_place + 1;
	}	
	
	return;
}


/*-----------------------------------------------------------------------------
O(n^2)
functionality: Insertion sort in ascending order on ints.
return: ---
*/
void InsertionSort(int *arr, const size_t arr_length)
{
    int key = 0;
    int iter_inner = 0;
    size_t iter_place = 1;
   
   	assert(NULL != arr);
	assert(arr_length > 0);
    
    while(iter_place < arr_length) 
    { 
        key = arr[iter_place]; 
        iter_inner = iter_place - 1; 
  
        /*move elements that should be before key 1 pos to the right */
        while (iter_inner >= 0 && arr[iter_inner] > key) 
        { 
            arr[iter_inner + 1] = arr[iter_inner]; 
            --iter_inner;
        } 
        
        arr[iter_inner + 1] = key;         
        ++iter_place;
    } 

	return;
}


/*-----------------------------------------------------------------------------
O(n)
functionality: counting sort.
				min max val is needed in order not to waste space on hist array.
return: ---
*/
/*	Algorithm:
	--> create histogram of ints occurances in input arr
	--> get prefix sum of the histogram to get new positions. 
	--> iterate through the input arr, for every num, place it inside the 
		sorted array the position stated in the prefix arr and decrease 
		its count by 1.
*/
int CountingSort(int *input_arr, const size_t arr_size, int min_val,
				 int max_val, int *sorted_arr)
{
	size_t iter = 0;
	size_t range = ((size_t)(max_val - min_val) + 1);
	
	int *hist = NULL;
	
	assert(NULL != input_arr);
	assert(NULL != sorted_arr);
	assert(0 < arr_size);
	
	/*alloc memory for histogram*/
	hist = (int *)calloc(range, sizeof(int));
	if(NULL == hist)
	{
		return (1);
	}
	
	/*create histogram*/
	while(iter < arr_size)
	{
		++hist[ input_arr[iter] - 1 ];
		++iter;
	}
	
	/*makes prefix sum from the histogram array*/
	for(iter = 0; iter < range - 1; iter++)
	{
		hist[iter + 1] += hist[iter];
	}
	
	/*placing the integer from the input arr, in its correct place 
	  inside the sorted array, according to the histogram*/
	for(iter = 0; iter < arr_size; iter++)
	{		
		sorted_arr[ hist[ input_arr[iter] - 1 ] -1 ] = input_arr[iter];
		
		--hist[ input_arr[iter] - 1 ];
	}	
	
	free(hist);
	
	return (0);
}

/*-----------------------------------------------------------------------------
O(n)
functionality: radix sort, based on counting sort.
return: ---
*/
int RadixSort(int *arr, size_t arr_size)
{

	/* Get max dev_factor for sort */
	int curr_dev_factor = 1;
	int max_dev_factor = RadixGetMaxDevFactor(arr, arr_size);
	int status = 0;
		
	assert(arr);
	assert(arr_size > 0);
	
	/* sort from list significant digit to most */
	while ((curr_dev_factor < max_dev_factor) && (1 != status))
	{
		status = RadixCountingSort(arr, arr_size, curr_dev_factor);
		curr_dev_factor *= RADIX_SORT_VAL;
	}

	return status;
}

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/* perform counting sort according to dev_factor
	work only with positive numbers */
static int RadixCountingSort(int *arr, size_t arr_size, int dev_factor)
{
	int hist[10] = {0};
	int *sorted_arr = NULL;	
	int tmp = 0;
	
	size_t iter = 0;
	
	assert(arr);
	assert(arr_size > 0);
	
	/*malloc for sorted arr*/
	sorted_arr = (int *)malloc(sizeof(int) * arr_size);
	if (NULL == sorted_arr)
	{
		return 1;
	}
	
	/*create histogram*/
	for(iter = 0; iter < arr_size; iter++)
	{
		++hist[ (arr[iter]/dev_factor) % RADIX_SORT_VAL ];
	}

	/*makes prefix sum from the histogram array*/
	for(iter = 1; iter < RADIX_SORT_VAL; iter++)
	{
		hist[iter] += hist[iter - 1];
	}
	
	/* 	shift hist right and insert 0 in first element*/
	tmp = hist[0];
	hist[0] = 0;

	for(iter = 1; iter < RADIX_SORT_VAL; iter++)
	{
		Swap(&tmp, &hist[iter]);
	}

	/*placing the integer from the input arr, in its correct place 
	  inside the sorted array, according to the histogram*/
	for(iter = 0; iter < arr_size; iter++)
	{
		sorted_arr[ hist[ (arr[iter] / dev_factor) % RADIX_SORT_VAL ] ] = arr[iter];
		
		++hist[ (arr[iter] / dev_factor) % RADIX_SORT_VAL ];
	}

	/* copy sorted to original arr */
	memcpy((void *)arr, (const void *)sorted_arr, (sizeof(int) * arr_size));
	
	free(sorted_arr);

	return 0;	
}

/*----------------------------------------------------------------------------*/

/* return max dev factor for  RadixCountingSort*/
static int RadixGetMaxDevFactor(int *arr, size_t arr_size)
{
	int max_dev_factor = RADIX_SORT_VAL;
	int max_num = 0;
	size_t iter = 0;

	/*find highest number*/
	while(iter < arr_size)
	{
		if (arr[iter] > max_num)
		{
			max_num = arr[iter];
		}
		
		++iter;
	}

	/*get dev factor according to number of digits in max_num*/
	while(0 != max_num / max_dev_factor)
	{
		max_dev_factor *= RADIX_SORT_VAL;
	}
	
	return (max_dev_factor);
}
   

/*----------------------------------------------------------------------------*/


  
/*----------------------------------------------------------------------------*/
/*--------------------------------HELPERS-------------------------------------*/
/*----------------------------------------------------------------------------*/

/* int swapper */
static void Swap(int *a, int *b) 
{ 
	int temp_swap = 0;
	
	assert(NULL != a);   
	assert(NULL != b);
	
	temp_swap = *a; 
	*a = *b; 
	*b = temp_swap; 
} 

static void SwapImp(void *p1, void *p2, size_t size)
{
	char temp;
	char *ptr1 = p1;
	char *ptr2 = p2;
	size_t i = 0;

	while (size != i)
	{
		temp = ptr1[i];
		ptr1[i] = ptr2[i];
		ptr2[i] = temp;
		++i;
	}

	return;	
}

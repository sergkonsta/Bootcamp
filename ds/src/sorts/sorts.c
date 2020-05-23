
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      19.05.2020               **
**  Reviewer:  Eliran Abrevaya			**
**  Status:    ???						**
*****************************************/		
#include <assert.h>	/*for assert*/
#include <stdlib.h>	/*for calloc*/
#include <string.h>	/*for memcpy*/

#include "sorts.h"

#define MIN_VAL_RADIX (0)
#define MAX_VAL_RADIX (9999999)
#define RADIX_SORT_VAL (10)

static void Swap(int *a, int *b);
static int RadixCountingSort(int *arr, size_t arr_size, int dev_factor);
static int RadixGetMaxDevFactor(int *arr, size_t arr_size);

/*-----------------------------------------------------------------------------
O(n^2)
functionality: applies a bubble sort in ascending order on ints.
return: ---
*/
void BubbleSort(int *arr, const size_t arr_length)
{
	int swap_flag = 1;
	size_t iter = 0;
	
	assert(NULL != arr);
	assert(arr_length > 1);
	
	/*until array is sorted*/
	while(0 != swap_flag)
	{
		swap_flag = 0;
		iter = 0;
		
		/*until a full pass on the array is done*/
		while((iter + 1) < arr_length)
		{
			/*swap numbers if not in order*/
			if(arr[iter] > arr[iter + 1])
			{
				Swap(&arr[iter], &arr[iter + 1]);
				swap_flag = 1;
			}
			
			++iter;
		}
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
	assert(arr_length > 1);
	
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
	assert(arr_length > 1);
    
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
	
	/*alloc memory for histogram*/
	int *hist = (int *)calloc(range, sizeof(int));
	if(NULL == hist)
	{
		return (1);
	}
	
	assert(NULL != input_arr);
	assert(NULL != sorted_arr);
	assert(2 < arr_size);
	
	/*create histogram*/
	while(iter < arr_size)
	{
		++hist[ input_arr[iter] - 1 ];
		++iter;
	}
	
	/*makes prefix sum from the histogram array*/
	iter = 0;
	while(iter < range - 1)
	{
		hist[iter + 1] += hist[iter];
		++iter;
	}
	
	/*placing the integer from the input arr, in its correct place 
	  inside the sorted array, according to the histogram*/
	iter = 0;
	while(iter < arr_size)
	{		
		sorted_arr[ hist[ input_arr[iter] - 1 ] -1 ] = input_arr[iter];
		
		--hist[ input_arr[iter] - 1 ];
		
		++iter;
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
		RadixCountingSort(arr, arr_size, curr_dev_factor);
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
	int *hist = NULL;
	int *sorted_arr = NULL;	
	int tmp = 0;
	
	size_t iter = 0;
	
	assert(arr);
	assert(arr_size > 0);
	
	/*malloc for hist*/
	hist = (int *)calloc(RADIX_SORT_VAL,sizeof(int));
	if (NULL == hist)
	{
		return 1;
	}

	/*malloc for sorted arr*/
	sorted_arr = (int *)malloc(sizeof(int)*arr_size);
	if (NULL == sorted_arr)
	{
		free(hist);
		return 1;
	}

	/*create histogram*/
	iter = 0;
	while(iter < arr_size)
	{
		++hist[ (arr[iter]/dev_factor) % RADIX_SORT_VAL ];
		++iter;
	}

	/*makes prefix sum from the histogram array*/
	iter = 1;
	while(iter < RADIX_SORT_VAL)
	{
		hist[iter] += hist[iter - 1];
		++iter;
	}
	
	/* 	shift hist right and insert 0 in first element*/
	tmp = hist[0];
	hist[0] = 0;

	iter = 1;
	while(iter < RADIX_SORT_VAL)
	{
		Swap(&tmp, &hist[iter]);
		++iter;
	}

	/*placing the integer from the input arr, in its correct place 
	  inside the sorted array, according to the histogram*/
	iter = 0;
	while(iter < arr_size)
	{
		sorted_arr[ hist[ (arr[iter] / dev_factor) % RADIX_SORT_VAL ] ] = arr[iter];
		
		++hist[ (arr[iter] / dev_factor) % RADIX_SORT_VAL ];
		
		++iter;
	}

	/* copy sorted to original arr */
	memcpy((void *)sorted_arr, (const void *)arr, (sizeof(int) * arr_size));
	
	free(hist);
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


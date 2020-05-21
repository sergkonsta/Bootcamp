
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      19.05.2020               **
**  Reviewer:  Eliran Abrevaya			**
**  Status:    ???						**
*****************************************/		
#include <assert.h>	/*for assert*/
#include <stdlib.h>	/*for calloc*/

#include "sorts.h"

static void Swap(int *a, int *b);
static int QSPartition (int arr[], int low, int high);

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
O(n^2)
functionality: Insertion sort in ascending order on ints.
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
  

/*----------------------------------------------------------------------------*/
/*GEEKS qsort - here for time comparison testing*/

static int QSPartition (int *arr, int low, int high) 
{ 
	int pivot = arr[high];    
	int i = (low - 1);  
	int j = low;
	
	assert(NULL != arr);
	
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

void QuickSort(int *arr, int low, int high) 
{ 	
	assert(NULL != arr);
	
	if(low < high) 
	{ 
		int pi = QSPartition(arr, low, high); 

		QuickSort(arr, low, pi - 1); 
		QuickSort(arr, pi + 1, high); 
	} 
	
	return;
} 


#include <stddef.h>

/*-----------------------------------------------------------------------------
O(n^2)
functionality: applies a bubble sort in ascending order on ints.
return: ---
*/
void BubbleSort(int *arr, size_t arr_length);



/*-----------------------------------------------------------------------------
O(n^2)
functionality: Selection sort in ascending order on ints.
return: ---
*/
void SelectionSort(int *arr, const size_t arr_length);



/*-----------------------------------------------------------------------------
O( )
functionality:
return: ---
*/
void InsertionSort(int *arr, const size_t arr_length);

/* positive intgers*/
/* sort arr of 5000 number val range 0 - 9,999,999*/ 
int RadixSort(int *arr, const size_t arr_size);


/* test range val 1-100, 5000 numbers - other range is undefined output*/
int CountingSort(int *input_arr, const size_t arr_size, int min_val,
				 int max_val, int *sorted_arr);


/*-----------------------------------------------------------------------------*/
/*iterative binary search

returns index where num is located, if not found - returns (-1)
*/
int BinarySearchIter(int *arr,  size_t arr_size, int num_2_find);


/*-----------------------------------------------------------------------------*/
/*recursive binary search*/
int BinarySearchRec(int *arr,  size_t arr_size, int num_2_find);

/*-----------------------------------------------------------------------------*/
/*recursive merge sort*/
int MergeSortRec(int *arr_to_sort, size_t num_elements);

/*-----------------------------------------------------------------------------*/
/*
base is array to sort, 
nmemb - amount of members, 
size - sizeof(member)
compare func works like strcmp
*/
void QuickSortRecursive(void *arr, size_t nmemb, size_t size, 
int(*compare)(const void *, const void *));



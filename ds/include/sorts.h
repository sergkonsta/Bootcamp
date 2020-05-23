
#include <stddef.h>

/*-----------------------------------------------------------------------------
O(n^2)
functionality: applies a bubble sort in ascending order on ints.
return: ---
*/
void BubbleSort(int *arr, const size_t arr_length);



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


/* test range val 1-100, 5000 numbers */
int CountingSort(int *input_arr, const size_t arr_size, int min_val,
				 int max_val, int *sorted_arr);


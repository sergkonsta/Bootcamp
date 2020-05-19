
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      19.05.2020               **
**  Reviewer:  Eliran Abrevaya			**
**  Status:    ???						**
*****************************************/		

#include "sorts.h"

static void Swap(int *a, int *b);

/*-----------------------------------------------------------------------------
O(n^2)
functionality: applies a bubble sort.
return: ---
*/
void BubbleSort(int arr[], const size_t arr_length)
{
	int swap_flag = 1;
	size_t iter = 0;
	
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
O( )
functionality:
return: ---
*/
void SelectionSort(int *arr, const size_t arr_length);



/*-----------------------------------------------------------------------------
O( )
functionality:
return: ---
*/
void InsertionSort(int *arr, const size_t arr_length);



/*----------------------------------------------------------------------------*/
/*--------------------------------HELPERS-------------------------------------*/
/*----------------------------------------------------------------------------*/

/* int swapper */
static void Swap(int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  


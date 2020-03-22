#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/
#include <assert.h>		/*for assert*/


/*Create Array of knights and assign them with '1'*/
size_t *CreateArrOfOnes(size_t num)
{
	size_t i = 0;
	size_t *arr = (size_t *)malloc(sizeof(size_t) * num);
	size_t *arr_cpy = arr;
	
	/*malloc check*/
	if(NULL == arr)
	{
		return NULL;
	}	
	
	while(i < num)
	{ 
		*arr = 1;
		++arr;
		++i;
	}
	
	return arr_cpy;
}

/*find last survivor*/
size_t FindLastKnightAndFree(size_t *arr)
{
	size_t result = 0;
	size_t *arr_cpy = arr;
	
	assert(NULL != arr);
	
	while(0 == *arr)
	{
		++arr;
	}

	/*another incremention because arrays start from index 0*/
	++arr;
	
	/*difference of adresses gives us the place in the arr*/
	result = (size_t)(arr - arr_cpy);
	
	free(arr_cpy);
	
	return result;
}


/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      19.03.2020               **
**  Reviewer:  Eliran					**
**  Status:    Sent						**
*****************************************/

/*---------------------------------------------------------------------
	ALGORITHM:
	
	1. create array according to users input, save its pointer & a copy
	   according to the knight that should start.
	
	2. loop through the array while more than 1 knight are alive
	
	3. for every knight check its status:
		
		-> if its alive and needs to be killed - kill it & adjust counters
		
		-> if its alive but shouldnt be killed - adjust 'to_kill' counter
		
	4. after only 1 left, find its place, free memmory and return
	
---------------------------------------------------------------------*/


size_t Josephus(size_t total_knights, size_t place)
{
	size_t to_kill = 0;
	size_t alive_count = total_knights;
	size_t *arr = CreateArrOfOnes(total_knights);
	
	/*place in arr from where we start the killings 
	(place - 1) because the arr index starts from 0)*/
	size_t *place_in_arr = arr + (place - 1);
	
	/*loops while there still more than 1 alive */
	while (alive_count > 1)
	{   
		/*loops while end of array not reached*/
		while((0 != total_knights - (size_t)(place_in_arr - arr)))   
		{
			/*if current knight is alive and needed to be killed - kill it*/
			if((1 == *place_in_arr) && (1 == to_kill))
			{
				*place_in_arr = 0;
				to_kill = 0;
				--alive_count;
			}
			
			/*if current knight is alive but doesnt needs to be killed*/
			else if((1 == *place_in_arr) && (0 == to_kill))
			{
				to_kill = 1;
			}
			
			/*continue to next knight*/
			++place_in_arr;
		}
		
		/*move back to the first knight in the array*/
		place_in_arr = arr;
	}
	
	/*checks and return the index of the remaining knight*/
	return (FindLastKnightAndFree(arr));

}

int main()
{
	printf("\n The remaining knights index is: %ld\n\n", Josephus(100, 3));
	
	return 0;
}


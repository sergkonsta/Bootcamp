#include <stddef.h>

struct Result{
	size_t output;
	size_t index1;
	size_t index2;
};

int IsSumFound(int *Arr, int sum, int arr_size, Result *res)
{
	int *pstart = Arr;
	int *pend = &Arr[arr_size - 1]; /*had no &*/
	
	while(*pstart < *pend)
	{
		if (*pstart + *pend > sum)
		{
			--pend;
		}
		
		else if(*pstart + *pend < sum)
		{
			++pstart;
		}
		
		else if(*pstart + *pend == sum)
		{
			res->output = 1;
			res->index1 = (size_t)(pstart - Arr);
			res->index2 = (size_t)(pend - Arr);
		}
	}
	
	return 0;
}

int main ()
{
	int Arr[6] = {0, 2, 4, 7, 8, 9};
	int arr_size = 6;
	int sum = 13;
	
	Result res = {0, 0, 0};
	
	IsSumFound(Arr, sum, arr_size,&res);
	
	printf("\n out: %d, index1: %d, index2: %d\n\n", res.output, res.index1, res.index2);
	
	
	return 0;
}

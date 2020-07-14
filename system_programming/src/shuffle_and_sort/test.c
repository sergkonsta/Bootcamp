
/*return 0 for success, 1 for failed alloc*/
static int MergeSortIter(char **arr_to_sort, size_t low_index, size_t mid_index, 
						size_t high_index)
{
	/*loop iters*/
	size_t i_1 = 0;
	size_t i_2 = 0;
	size_t i_sorted = low_index;
	
	/*calculating sub array sizes*/
	size_t sub_1_size = mid_index  - low_index + 1; 
    size_t sub_2_size = high_index - mid_index; 
	
	/*allocating sub arrays*/
	char **sub_arr_1 = (char **)calloc(sub_1_size, sizeof(char *));
	char **sub_arr_2 = (char **)calloc(sub_2_size, sizeof(char *));
	if (NULL == sub_arr_1 || NULL == sub_arr_2)
	{
		free(sub_arr_1);
		free(sub_arr_2);
		
		return 1;
	}
	
	/*fill sub arr 1*/
	for (i_1 = 0; i_1 < sub_1_size; ++i_1)
	{
		sub_arr_1[i_1] = arr_to_sort[low_index + i_1]; 
	}
	
	/*fill sub arr 2*/
	for (i_2 = 0; i_2 < sub_2_size; ++i_2)
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
		if (0 >= SortCmpFunc((void *)(&sub_arr_1[i_1]), (void *)(&sub_arr_2[i_2]))) 
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


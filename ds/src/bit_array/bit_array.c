/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      05.04.2020               **
**  Reviewer:  Eden						**
**  Status:    SENT				**
*****************************************/

#include "bit_array.h"

/*return bit_array with all bits set to 1*/
bit_arr_t BArrSetAll(bit_arr_t arr)
{
	UNUSED(arr);
	
	return 0xFFFFFFFF;
}


/*--------------------------------------------------------------------------*/
/*returns bit_array with all bits 0*/

bit_arr_t BArrResetAll(bit_arr_t arr)
{
	UNUSED(arr);
	
	return 0;
}


/*--------------------------------------------------------------------------*/
/*return value of specified bit in the */

int BArrGetVal(bit_arr_t arr, size_t bit_index)
{
	return (int)((arr >> bit_index) & 0x1);
}


/*--------------------------------------------------------------------------*/
/*sets a specific bit to 1 in the bit_array*/

bit_arr_t BArrSetOn(bit_arr_t arr, size_t bit_index)
{
	return (arr |= (0x1 << bit_index));
}


/*--------------------------------------------------------------------------*/
/*sets a specific bit to 0 in the bit_array*/

bit_arr_t BArrSetOff(bit_arr_t arr, size_t bit_index)
{
	return (arr &= ~(0x1 << bit_index));
}


/*--------------------------------------------------------------------------*/
/*sets a specific bit in the bit_array to a specific value*/
bit_arr_t BArrSetBit(bit_arr_t arr, size_t bit_index, int val_to_set)
{
	assert(0 == val_to_set && 1 == val_to_set);
	
	if(0 == val_to_set)
	{
		return (arr &= ~(0x1 << bit_index));
	}
	
	return (arr |= (0x1 << bit_index));	
}

/*--------------------------------------------------------------------------*/
/*flips the value of a specific bit in the bit_array*/
bit_arr_t BArrFlipBit(bit_arr_t arr, size_t bit_index)
{
	return (arr ^= (0x1 << bit_index));
}


/*
size_t BArrCountOn(bit_arr_t arr)
size_t BArrCountOff(bit_arr_t arr)
bit_arr_t BArrMirror(bit_arr_t arr)
bit_arr_t BArrRotR(bit_arr_t arr, size_t num_of_rot)
bit_arr_t BArrRotL(bit_arr_t arr, size_t num_of_rot)
char *BArrToString(bit_arr_t arr, char *bits_string)

*/

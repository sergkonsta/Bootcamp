/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      05.04.2020               **
**  Reviewer:  Eden						**
**  Status:    SENT				**
*****************************************/

#include "bit_array.h"

#define SIZE_OF_BARR (sizeof(bit_arr_t) * 8)

/*return bit_array with all bits set to 1*/
bit_arr_t BArrSetAll(bit_arr_t arr)
{
	UNUSED(arr);
	
	return 0xFFFFFFFFFFFFFFFF;
}


/*--------------------------------------------------------------------------*/
/*returns bit_array with all bits 0  - STATUS: APPROVED */

bit_arr_t BArrResetAll(bit_arr_t arr)
{
	UNUSED(arr);
	
	return 0;
}


/*--------------------------------------------------------------------------*/
/*return value of specified bit in the   - STATUS: APPROVED */

int BArrGetVal(bit_arr_t arr, size_t bit_index)
{
	assert(SIZE_OF_BARR > bit_index);
		
	return (int)((arr >> bit_index) & 0x1);
}


/*--------------------------------------------------------------------------*/
/*sets a specific bit to 1 in the bit_array  - STATUS: APPROVED */

bit_arr_t BArrSetOn(bit_arr_t arr, size_t bit_index)
{
	assert(SIZE_OF_BARR > bit_index);
	
	return arr |= ((bit_arr_t)0x1 << bit_index);
}


/*--------------------------------------------------------------------------*/
/*sets a specific bit to 0 in the bit_array  - STATUS: APPROVED */

bit_arr_t BArrSetOff(bit_arr_t arr, size_t bit_index)
{
	assert(SIZE_OF_BARR > bit_index);
	
	return arr &= ~((bit_arr_t)0x1 << bit_index);
}


/*--------------------------------------------------------------------------*/
/*sets a specific bit in the bit_array to a specific value  - STATUS: APPROVED*/

bit_arr_t BArrSetBit(bit_arr_t arr, size_t bit_index, int val_to_set)
{
	assert(0 == val_to_set || 1 == val_to_set);
	assert(SIZE_OF_BARR > bit_index);
	
	if(0 == val_to_set)
	{
		return BArrSetOff(arr, bit_index);
	}
	
	return BArrSetOn(arr, bit_index);	
}

/*--------------------------------------------------------------------------*/
/*flips the value of a specific bit in the bit_array  - STATUS: APPROVED */

bit_arr_t BArrFlipBit(bit_arr_t arr, size_t bit_index)
{
	assert(SIZE_OF_BARR > bit_index);
	
	return arr ^= (0x1 << bit_index);
}


/*--------------------------------------------------------------------------*/
/*counts amount of Ones in the bit_array  - STATUS: SENT */

size_t BArrCountOn(bit_arr_t arr)
{
	size_t counter = 0;
		
	while(arr > 0)
	{
		counter+= arr & 0x1;
		arr >>= 1;
	}
	
	return counter;
}

/*--------------------------------------------------------------------------*/
/*counts amount of Zeros in the bit_array deducting the amount 
	- STATUS: APPROVED)*/

size_t BArrCountOff(bit_arr_t arr)
{
	return (SIZE_OF_BARR - BArrCountOn(arr));
}



/*--------------------------------------------------------------------------*/
/*mirrors the bit_array - STATUS: mirrors one byte only!!!!!!!!!! */
bit_arr_t BArrMirror(bit_arr_t arr)
{
	bit_arr_t temp = 0;
	
	temp |= arr << 4;
	temp |= arr >> 4;
	arr = temp;
	
	temp = 0;
	temp |= (arr & 0x33) << 2;
	temp |= (arr & 0xCC) >> 2;
	arr = temp;
	
	temp = 0;
	temp |= (arr & 0x55) << 1;
	temp |= (arr & 0xAA) >> 1;
		
	return temp;
}


/*--------------------------------------------------------------------------*/
/* Rotate the array Left - STATUS: SENT */
bit_arr_t RotL(bit_arr_t arr, size_t num_to_rotate)
{ 		 
	return (arr << num_to_rotate) | (arr >> (SIZE_OF_BARR - num_to_rotate));
}


/*--------------------------------------------------------------------------*/
/* Rotate the array Right - STATUS: SENT */
bit_arr_t RotR(bit_arr_t arr, size_t num_to_rotate)
{ 	
	return (arr >> num_to_rotate) | (arr << (SIZE_OF_BARR - num_to_rotate));
}


/*--------------------------------------------------------------------------*/
/* ToString function  - STATUS: SENT */
char *ToString(bit_arr_t arr, char *bits_string)
{
	size_t index = 0;
	
	while (0 != arr) 
	{
      	bits_string[index] = (((arr & 1) == 1) ? '1' : '0');
      	++index; 
		arr >>= 1; 
	}
		
	return bits_string;
}






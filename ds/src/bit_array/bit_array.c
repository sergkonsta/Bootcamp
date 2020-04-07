/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      05.04.2020               **
**  Reviewer:  Eden						**
**  Status:    APPROVED					**
*****************************************/

#include "bit_array.h"

#define SIZE_OF_BARR (sizeof(bit_arr_t) * 8)
#define FROM_DEC_TO_ASCII (48)



/*--------------------------------------------------------------------------*/
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
	
	return arr ^= ((bit_arr_t)0x1 << bit_index);
}


/*--------------------------------------------------------------------------*/
/*counts amount of Ones in the bit_array using  Kernighan’s Algorithm
  - STATUS: APPROVED */

size_t BArrCountOn(bit_arr_t arr)
{
	size_t c = 0;

	while(arr)
	{
		arr &= (arr - 1);
		c += 1;
	}

	return c;
}

/*--------------------------------------------------------------------------*/
/*counts amount of Zeros in the bit_array deducting the amount 
	- STATUS: APPROVED)*/

size_t BArrCountOff(bit_arr_t arr)
{
	return (SIZE_OF_BARR - BArrCountOn(arr));
}



/*--------------------------------------------------------------------------*/
/*mirrors the bit_array - STATUS: APPROVED */
bit_arr_t BArrMirror(bit_arr_t arr)
{
	arr = (arr & 0xFFFFFFFF00000000) >> 32 | (arr & 0x00000000FFFFFFFF) << 32;
	arr = (arr & 0xFFFF0000FFFF0000) >> 16 | (arr & 0x0000FFFF0000FFFF) << 16;
	arr = (arr & 0xFF00FF00FF00FF00) >> 8 | (arr & 0x00FF00FF00FF00FF) << 8;	
	arr = (arr & 0xF0F0F0F0F0F0F0F0) >> 4 | (arr & 0x0F0F0F0F0F0F0F0F) << 4;
   	arr = (arr & 0xCCCCCCCCCCCCCCCC) >> 2 | (arr & 0x3333333333333333) << 2;
  	arr = (arr & 0xAAAAAAAAAAAAAAAA) >> 1 | (arr & 0x5555555555555555) << 1;
 
  	return arr;
}


/*--------------------------------------------------------------------------*/
/* Rotate the array Left - STATUS: APPROVED */
bit_arr_t BArrRotL(bit_arr_t arr, size_t num_to_rotate)
{ 		 
	return (arr << num_to_rotate) | (arr >> (SIZE_OF_BARR - num_to_rotate));
}


/*--------------------------------------------------------------------------*/
/* Rotate the array Right - STATUS: APPROVED */
bit_arr_t BArrRotR(bit_arr_t arr, size_t num_to_rotate)
{ 	
	return (arr >> num_to_rotate) | (arr << (SIZE_OF_BARR - num_to_rotate));
}


/*--------------------------------------------------------------------------*/
/* ToString function  - STATUS: APPROVED */
char *BArrToString(bit_arr_t arr, char *bits_string)
{
	size_t index = 0;
		
	while (SIZE_OF_BARR > index) 
	{
      	bits_string[index] = (char)((arr & 1) + FROM_DEC_TO_ASCII);
      	++index; 
		arr >>= 1; 
	}
			
	return StrRev(bits_string);
}

/*--------------------------------------------------------------------------*/
/*Reverses str*/
		
char *StrRev(char *str)
{
  char *p1 = NULL;
  char *p2 = NULL;

  if (! str || ! *str)
  {
  	return str;
  }
      
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
  {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
  }
  
  return str;
}

/*--------------------------------------------------------------------------*/
/* return Mirror of the array -Using Look-Up Table - STATUS: APPROVED */
bit_arr_t BArrMirrorLut(bit_arr_t arr)
{
	bit_arr_t result = 0x0;
	
	size_t c = SIZE_OF_BARR / 8;
	
	while(0 != c)
	{
		result <<= 8;
		result |= LookUpTable[arr & 0xFF];	
		arr >>= 8;
		--c;
	}

	return result;	
}

/*--------------------------------------------------------------------------*/
/* Count the bits that's on - Using Look-Up table - STATUS: APPROVED */
int BArrCountBitLut(bit_arr_t arr) 
{
	size_t i = 0;

	static size_t bit_count_array[] = {0, 1, 1, 2, 1, 2, 2, 3,
										1, 2, 2, 3, 2, 3, 3, 4};
	
  	size_t count = 0;
	
  	for (i = 0; i < sizeof(arr) * 2 ; ++i) 
	{
    	int nibble = arr & 0xFu;
    	arr >>= 4;
    	count += bit_count_array[nibble];
  	}
  	return count;
}


/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      05.04.2020               **
**  Reviewer:  Eden						**
**  Status:    APPROVED					**
*****************************************/

#include <assert.h>		/*for assert*/
#include <stdio.h>		/*for printf*/
#include <stdlib.h>
#include <string.h>		/*strcmp*/

#include "bit_array.h"

#define SIZE_OF_BARR (sizeof(bit_arr_t) * 8)
#define FROM_DEC_TO_ASCII (48)
#define UNUSED(x) (void)(x)

/*Look-Up table */
static size_t LookUpTable[256] = {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
        0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
        0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
        0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
        0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
        0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
        0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
        0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
        0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
        0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
        0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
        0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

char *StrRev(char *str);

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


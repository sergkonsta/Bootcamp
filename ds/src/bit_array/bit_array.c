/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      05.04.2020               **
**  Reviewer:  ????						**
**  Status:    in progress				**
*****************************************/

#include "bit_array.h"

bit_array_t SetAll(bit_array_t arr)
{
	UNUSED(arr);
	
	return 0xFFFFFFFF;
}

bit_array_t ResetAll(bit_array_t arr)
{
	UNUSED(arr);
	
	return 0;
}

int GetVal(bit_array_t arr, size_t bit_pos)
{
	

	return ?;
}


bit_array_t SetBit(bit_array_t arr, size_t bit_pos, int valude);
bit_array_t FlipBit(bit_array_t arr, size_t bit_pos);
bit_array_t SetOn(bit_array_t arr, size_t bit_pos);
bit_array_t SetOff(bit_array_t arr, size_t bit_pos);
size_t CountOn(bit_array_t);
size_t CountOn(bit_array_t);
bit_array_t Mirror(bit_array_t arr);
bit_array_t RotR(bit_array_t arr, size_t bit_pos);
bit_array_t RotL(bit_array_t arr, size_t bit_pos);
char *ToString(bit_array_t arr, char *bits_string);



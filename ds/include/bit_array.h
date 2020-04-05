#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#define UNUSED(x) void(x)

typedef size_t bit_array_type;

/*Bit Array functions*/

bit_array_t SetAll(bit_array_t arr);

bit_array_t ResetAll(bit_array_t arr);

int GetVal(bit_array_t arr, size_t bit_pos);

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

#endif

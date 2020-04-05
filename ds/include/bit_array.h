#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#define UNUSED(x) (void)(x)

#include <stddef.h>		/*for size_t*/
#include <assert.h>		/*for assert*/

typedef size_t bit_arr_t;

/*Bit Array functions*/

bit_arr_t BArrSetAll(bit_arr_t arr);

bit_arr_t BArrResetAll(bit_arr_t arr);

int BArrGetVal(bit_arr_t arr, size_t bit_index);

bit_arr_t BArrRotR(bit_arr_t arr, size_t num_of_rot);

bit_arr_t BArrRotL(bit_arr_t arr, size_t num_of_rot);

size_t BArrCountOn(bit_arr_t arr);

size_t BArrCountOff(bit_arr_t arr);

bit_arr_t BArrSetOn(bit_arr_t arr, size_t bit_index);

bit_arr_t BArrSetOff(bit_arr_t arr, size_t bit_index);

bit_arr_t BArrSetBit(bit_arr_t arr, size_t bit_index, int val_to_set);

bit_arr_t BArrFlipBit(bit_arr_t arr, size_t bit_index);

bit_arr_t BArrMirror(bit_arr_t arr);

char *BArrToString(bit_arr_t arr, char *bits_string);

#endif

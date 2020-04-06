#include "bit_array.h"

#define SIZE_OF_BARR (sizeof(bit_arr_t) * 8)

static bit_arr_t test_arr_1 = 0x0000000000000000;
static bit_arr_t test_arr_2 = 0xFFFFFFFFFFFFFFFF;
static bit_arr_t test_arr_3 = 0x8000000000000000;
static bit_arr_t test_arr_4 = 0x0000000000000001;
static bit_arr_t test_arr_5 = 0x1111111111111111;
static bit_arr_t test_arr_6 = 0xAAAAAAAAAAAAAAAA;

static size_t bit_index_1 =  0;
static size_t bit_index_2 =  32;
static size_t bit_index_3 =  63;


void SetAllTest()
{	
	if(	0xFFFFFFFFFFFFFFFF == BArrSetAll(test_arr_1) &&
		0xFFFFFFFFFFFFFFFF == BArrSetAll(test_arr_2) &&
		0xFFFFFFFFFFFFFFFF == BArrSetAll(test_arr_3) &&
		0xFFFFFFFFFFFFFFFF == BArrSetAll(test_arr_4) &&
		0xFFFFFFFFFFFFFFFF == BArrSetAll(test_arr_5) &&
		0xFFFFFFFFFFFFFFFF == BArrSetAll(test_arr_6) )
	{
		return;
	} 	
	
	printf("test failt on line: %d in _test.c\n\n",__LINE__);
}

void ResetAllTest()
{
	if(	0x0 == BArrResetAll(test_arr_1) &&
		0x0 == BArrResetAll(test_arr_2) &&
		0x0 == BArrResetAll(test_arr_3) &&
		0x0 == BArrResetAll(test_arr_4) &&
		0x0 == BArrResetAll(test_arr_5) &&
		0x0 == BArrResetAll(test_arr_6) )
	{
		return;
	} 	
	
	printf("test failt on line: %d in _test.c\n\n",__LINE__);
}

void SetBitTest()
{
	bit_arr_t tmp;
	
	tmp = BArrSetBit(test_arr_1, bit_index_1, 1);
	if(	0x0000000000000001 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrSetBit(test_arr_2, bit_index_2, 0);
	if(0xFFFFFFFEFFFFFFFF != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrSetBit(test_arr_3, bit_index_3, 1);
	if(0x8000000000000000 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrSetBit(test_arr_4, bit_index_1, 0);
	if(0x0000000000000000 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrSetBit(test_arr_5, bit_index_2, 1);
	if(0x1111111111111111 !=  tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrSetBit(test_arr_6, bit_index_3, 0);
	if(0x2AAAAAAAAAAAAAAA != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
}

void GetValTest()
{
	bit_arr_t tmp;
	
	tmp = BArrGetVal(test_arr_1, bit_index_1);
	if(	0 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrGetVal(test_arr_2, bit_index_2);
	if(1 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrGetVal(test_arr_3, bit_index_3);
	if(1 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrGetVal(test_arr_4, bit_index_1);
	if(1 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrGetVal(test_arr_5, bit_index_2);
	if(1 !=  tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrGetVal(test_arr_6, bit_index_3);
	if(1 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
}

void CountOnTest()
{
	bit_arr_t tmp;
	
	tmp = BArrCountOn(test_arr_1);
	if(0 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOn(test_arr_2);
	if(64 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOn(test_arr_3);
	if(1 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOn(test_arr_4);
	if(1 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOn(test_arr_5);
	if(16 !=  tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOn(test_arr_6);
	if(32 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
}

void CountOffTest()
{
	bit_arr_t tmp;
	
	tmp = BArrCountOff(test_arr_1);
	if(64 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOff(test_arr_2);
	if(0 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOff(test_arr_3);
	if(63 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOff(test_arr_4);
	if(63 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOff(test_arr_5);
	if(48 !=  tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrCountOff(test_arr_6);
	if(32 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
}

void FlipBitTest()
{
	bit_arr_t tmp;
	
	tmp = BArrFlipBit(test_arr_1, bit_index_1);
	if(0x0000000000000001 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrFlipBit(test_arr_2, bit_index_2);
	if(0xFFFFFFFEFFFFFFFF != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrFlipBit(test_arr_3, bit_index_3);
	if(0x0000000000000000 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrFlipBit(test_arr_4, bit_index_1);
	if(0x0000000000000000 != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrFlipBit(test_arr_5, bit_index_2);
	if(0x1111111011111111 !=  tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
	
	tmp = BArrFlipBit(test_arr_6, bit_index_3);
	if(0x2AAAAAAAAAAAAAAA != tmp)
	{
		printf("test failt on line: %d in _test.c\n\n",__LINE__);
	}
}

void RotLTest()
{
	
}

void RotRTest()
{
	
}

void TostringTest()
{
	
}

void SetOnTest()
{
	
}

void SetOffTest()
{
	
}

void MirrorTest()
{
	
}


int main()
{
	printf("\n\nStarting tests, errors will be printed below.\n\n");
	
	SetAllTest();
	ResetAllTest();
	SetBitTest();
	GetValTest();
	CountOnTest();
	CountOffTest();
	FlipBitTest();
	RotLTest();
	RotRTest();
	TostringTest();
	SetOnTest();
	SetOffTest();
	MirrorTest;
	
	
	printf("\n\nFinished testing.\nIf no errors prnted - all good.\n\n");
	
	return 0;
}

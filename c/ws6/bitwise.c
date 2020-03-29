
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      25.03.2020               **
**  Reviewer:  Roy						**
**  Status:    APPROVED						**
*****************************************/

#include <stdio.h>	/*for printf*/
#include <assert.h>	/*for assert*/
#include <stdbool.h>/*for bool*/

#include "bitwise.h"

/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	 - 

	multiplication by 2 is left shift once.
	so if the formula is x*(2^y), 
	we need to shift X left (y) times */
long Pow2(unsigned int x, unsigned int y)
{
	long Result = x << y;
	
	return Result;
}

/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	  	

	n is a power of 2 if only 1 bit in the number is lit:
	____________________________________
	2^4	|	2^3	|	2^2	|	2^1	|	2^0
	____|_______|_______|_______|_______
	0	|	1	|	0	|	0	|	0   
	____|_______|_______|_______|_______
	
	size of 'unsigned int' is: 4 bytes = 32bits
	
	with loop - rotate number 32 times and increment counter when but is lit
	
	w/o loop  - c */
	
int IsPow(unsigned int n)
{
	size_t bit_counter = 0;
	int result = 0;
	
	/*0 is not a power of 2*/
	if(0 == n)
	{
		return 0;
	}
		
	/*check LSB with 0x0001 mask, and shift to next LSB*/
	while(bit_counter < 32 && result > 1)
	{
		result += (n & 1);
		n = n >> 1;
		++bit_counter;
	}
	
	/*return 0 if more than 1 bit in n is lit*/
	if(1 < result)
	{
		return 0;
	}
	
	return 1;	
}

int IsPowNoLoop(unsigned int n)
{
	return((0 != n) && ~(n & (n-1))	);
}

/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	

	adds one to an int without the use of aritjmetic operators:

	-until you reach the first '0' from the LSB:
		-NOT all the '1's using XOR with 'single bit' mask
		-increment the mask to the check the next bit (LSB+1)
		
	- then NOT the '0' found  */

long AddOne(int x)
{
	int mask = 1; 
	
	assert(0 <= x);
  
    /*NOT all the '1' until the first zero*/
    while (0 != (x & mask))
    { 
        x = x ^ mask; 
        mask = mask << 1; 
    } 
  
    /* NOT the first zero */
    x = x ^ mask; 
    
    return x; 	
}



/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	
	
	-go through the array, 
	-for every number in the array check its bits for amount of '1's
	 using a mask of single bit.
	 

  */
	
void ThreeBits(const unsigned int *arr, size_t arr_size)
{
	size_t arr_counter = 0;
	size_t bit_counter = 0;
	size_t amount_ones = 0;
	size_t result = 0;
	
	unsigned int mask = 1;

	/*ARRAY LOOP*/
	while(arr_size > arr_counter)
	{	
		/*integer bits loop*/
		while(32 > bit_counter && 4 > amount_ones)
		{
			/* if the tested bit is '1', increase the counter with it*/
			amount_ones += mask & *arr;
			/*change the mask so it will check the next bit*/
			mask <<= 1;	
			/*keeps*/
			++bit_counter;
		} 
		
		if(4 > amount_ones)
		{
			++result;
		}
		
		bit_counter = 0;
		amount_ones = 0;
		++arr;
		++arr_counter;		
	}
	
	printf("\namount of Ints int the array with only 3 '1's is: %ld\n",result);
}

/*------------------------------------------------------------------------*/
/* Review status: APPROVED	

   return a mirrored variable using a loop:
   -iterating over the original byte and shifting it to ther right
    to match the 1 in the mask
   -XOR with the mask to save the bits needed
   -shift original byte right, shift mirror byte left
    */
unsigned char ByteMirrorLoop(unsigned char b)
{

	unsigned char mirror_b = 0;	
	unsigned char mask = 1;
	
	/*according to (bit amount-1)*/
	int counter = 7;	
		
	/*iterate over the whole byte,*/	
	while ((0 != b) && (0 != counter))
	{		
		if ((mask & b) != 0)
		{
			mirror_b = mirror_b ^ mask;
		}
			
		mirror_b <<= 1;		
		b >>= 1;
		--counter;
	}
			
	mirror_b |= b; 
	mirror_b <<= counter;
		
	return mirror_b;
		
	
}

/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	

	the algorithm for byte mirroring:
	divide the bits into 2 groups, switch their places
	each group divide into 2 groups and switch their places
	continue until every single char is switched. 
	
	for loop:
	amount of switches is: Log Base2 of number of bits, so for us it will be 
	Log base2 of 8 = 3
  */

unsigned char ByteMirror(unsigned char b)
{	
	unsigned char temp = 0;
	
	temp |= b << 4;
	temp |= b >> 4;
	b = temp;
	
	temp = 0;
	temp |= (b & 0x33) << 2;
	temp |= (b & 0xCC) >> 2;
	b = temp;
	
	temp = 0;
	temp |= (b & 0x55) << 1;
	temp |= (b & 0xAA) >> 1;
		
	return temp;
}

/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	

	bit number 2 and bit number 6 are both on will return true:
	-OR with mask "1101,1101" - 0xDD
	-NOT it to reach a state that if both bits were on, now all the bits are 0
	-return a converted NOT(char) to bool
  */

bool TwoAndSix(unsigned char ch)
{	
	ch = ch | 0xDD;
	ch = ~ch;
	return (bool)!ch;
}

/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	

	bit number 2 OR bit number 6 are both on will return true:
	-AND with mask "0010,0010" - 0x22
	-if at least one digit is on,
	 the number won't be zero and wont convert to false
	-return a converted (char) to bool
  */
bool TwoOrSix(unsigned char ch)
{
	ch = ch & 0x22;
	
	return (bool)ch;
}


/*------------------------------------------------------------------------*/
/*	Review status: APPROVED		

	-swap bits 3 and 5 and return new char.
	-set aside a char with the original char without digits 3 and 5:
	 using the mask: 0xE3
	-mask the old char for bit 3 with 0x04, shift left twice, add into in result
	-mask the old char for bit 5 with 0x10, shift right twice, add into result
  	-return result */
unsigned char SwapBits(unsigned char ch)
{
	unsigned char result = (ch & 0xE3);
	
	result |= (ch & 0x04) << 2;
	result |= (ch & 0x10) >> 2;

	return result;
}


/*------------------------------------------------------------------------*/
/*	Review status: APPROVED		

	-return the closest bit divisable by 16 with no remainder:
	-take all the first digits until you reach the 2^3 (4 first bits)
	 bit and turn them to zero using the mask: 0xFFFFFFF0;
	-return the new number
	  */
unsigned int ClosestNumber(unsigned int x)
{
	unsigned int mask = 0xFFFFFFF0;
			
	return (x & mask);
}


/*------------------------------------------------------------------------*/
/*	Review status: APPROVED	
	-swaps two ints	
	  */
void SwapVar(int *x, int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
	
	return;
}

/*------------------------------------------------------------------------*/
/*	 Review status: APPROVED		 
	
	iterates thorugh every bit of the integer using a rotating 1 bit mask
	for every bit lit in the int - increments amount_ones
  */
	
size_t CountSetBitsLoop(int num)
{
	size_t bit_counter = 0;
	size_t amount_ones = 0;
	
	int mask = 1;
	
	/*integer bits loop*/
	while(32 > bit_counter)
	{
		/* if the tested bit is '1', increase the counter with it*/
		if(0 != (mask & num))
		{
			++amount_ones;
		}
		
		/*change the mask so it will check the next bit*/
		mask <<= 1;	
				
		++bit_counter;
	} 
		
	return amount_ones;
}



/*------------------------------------------------------------------------*/
/*	 Review status: APPROVED		 
	
	recursive solution:
	sums all the 1 digits, while shifting right.
	recursion breaks after the remaining number is filled only with zeros
  */
size_t CountSetBits(int num) 
{
	if (num == 0)
	{
   		return 0; 
	}

	return (size_t)((num & 1) + CountSetBits(num >> 1)); 
} 




/*------------------------------------------------------------------------*/
/*	 Review status: APPROVED		 
	
	print the bits of float
	-iterate through the float number bits
	-iteration must be made using a pointer to int
	
	
  */
	
void PrintFloatBits(float fnum)
{
	/*Check bits from end to beggining because on terminait will be reversed*/
	size_t bit_counter = 32;

	int *fp = (int *)(&fnum);
	
	printf("\n");
	
	/*integer bits loop*/
	while(0 < bit_counter)
	{
		printf("%d ",(*fp >> bit_counter) & 1);
		--bit_counter;
	}
	
	printf("\n");
			
	return;
}




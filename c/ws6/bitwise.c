#include <stdio.h>	/*for printf*/
#include <math.h>	/*for pow()*/
#include <assert.h>	/*for assert*/
#include <stdbool.h>/*for bool*/

long Pow2(unsigned int x, unsigned int y);
int IsPow(unsigned int n);
long AddOne(int x);
void ThreeBits(const unsigned int *arr);
unsigned char ByteMirror(unsigned char b);
bool TwoAndSix(unsigned char ch);
bool TwoOrSix(unsigned char ch);
unsigned char SwapBits(unsigned char ch);


int main()
{
	unsigned int x = 7;
	unsigned int y = 5;
	unsigned char b = 0x13;
	const unsigned int arr[5] = {2149582848, 3758096384, 0, 4294967295, 11111};
	
	/*SwapBits check*/
	printf("\nfrom 0xA7 to: %x\n",SwapBits(0xA7));
	
	/*TwoAndSix check*/
	if(true == TwoAndSix(0x33))
	{
		printf("\ndigits 2 and 6 both on\n");
	}
	
	else
	{
		printf("\ndigits 2 and 6 aren't both on\n");
	}
	
	/*TwoOrSix check*/
	if(true == TwoOrSix(0x20))
	{
		printf("\ndigits 2 or 6 is on\n");
	}
	
	else
	{
		printf("\ndigits 2 and 6 both zero\n");
	}
	
	/*ByteMirror check*/
	printf("\nthe char is %x",b);
	printf("\nthe flipped char is %x",ByteMirror(b));
	
	/*ThreeBits check*/
	ThreeBits(arr);
	
	/*Pow2 ckeck*/
	printf("\nThe result of Pow2 with x: %d, y: %d, is: %ld\n",x,y,Pow2(x,y));
	
	/*IsPow check*/
	x = 1;
		
	printf("\nThe result of IsPow with x: %d, is: %d\n",x,IsPow(x));
	
	/*AddOne check*/
	x = 0;
	
	while(1000000 != x)
	{
		if(AddOne((int)x) != x+1)
		{
			printf("\nWRONG on: %d\n",x);
		}
		
		++x;		
	}

	return 0;
}






/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      25.03.2020               **
**  Reviewer:  Roy						**
**  Status:    SENT						**
*****************************************/

/*------------------------------------------------------------------------*/
/*	multiplication by 2 is left shift once.
	so if the formula is x*(2^y), 
	we need to shift X left (y) times */
long Pow2(unsigned int x, unsigned int y)
{
	long Result = x << y;
	
	return Result;
}

/*------------------------------------------------------------------------*/
/*	n is a power of 2 if only 1 bit in the number is lit:
	____________________________________
	2^4	|	2^3	|	2^2	|	2^1	|	2^0
	____|_______|_______|_______|_______
	0	|	1	|	0	|	0	|	0   
	____|_______|_______|_______|_______
	
	size of 'unsigned int' is: 4 bytes = 32bits
	
	with loop - rotate number 32 times and increment counter when but is lit
	
	w/o loop  - return: (	(0 != x) && ~(x & (x-1))	) */
	
int IsPow(unsigned int n)
{
	size_t counter = 0;
	int result = 0;
	
	/*0 is not a power of 2*/
	if(0 == n)
	{
		return 0;
	}
		
	/*check LSB with 0x0001 mask, and shift to next LSB*/
	while(counter < 32)
	{
		result += (n & 1);
		n = n >> 1;
		++counter;
	}
	
	/*return 0 if more than 1 bit in n is lit*/
	if(1 < result)
	{
		return 0;
	}
	
	return 1;	
}

/*------------------------------------------------------------------------*/
/*	adds one to an int without the use of aritjmetic operators:

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
/*	-go through the array, 
	-for every number in the array check its bits for amount of '1's
	 using a mask of single bit.
	 
	 ARRAY SIZE GIVEN!!!
  */
	
void ThreeBits(const unsigned int *arr)
{
	size_t arr_counter = 0;
	size_t bit_counter = 0;
	size_t amount_ones = 0;
	size_t arr_size = 5;
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
/*	the algorithm for nyte mirroring:
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
/*	bit number 2 and bit number 6 are both on will return true:
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
/*	bit number 2 OR bit number 6 are both on will return true:
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
/*	-swap bits 3 and 5 and return new char.
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











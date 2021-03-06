/*----------------------------------------------------------

INTEGER TYPES:

signed char				- 1 byte
char
short int
unsigned short int
int						- 4 bytes
unsigned int 			- 4 bytes
long int 				- 8 bytes
unsigned long it
long long int
unsigned long long int



REAL NUMBERS:

float					- 4 bytes
double
long double


--------------------------------------------------------*/

#include <stdio.h>

int main()
{
	printf("    short int is %3ld bytes \n", sizeof(short int));
	printf("          int is %3ld bytes \n", sizeof(int));
	printf("        int * is %3ld bytes \n", sizeof(int *));
	printf("     long int is %3ld bytes \n", sizeof(long int));
	printf("   long int * is %3ld bytes \n", sizeof(long int *));
	printf("   signed int is %3ld bytes \n", sizeof(signed int));
	printf(" unsigned int is %3ld bytes \n", sizeof(unsigned int));
	printf("\n");
	printf("        float is %3ld bytes \n", sizeof(float));
	printf("      float * is %3ld bytes \n", sizeof(float *));
	printf("       double is %3ld bytes \n", sizeof(double));
	printf("     double * is %3ld bytes \n", sizeof(double *));
	printf("  long double is %3ld bytes \n", sizeof(long double));
	printf("\n");
	printf("  signed char is %3ld bytes \n", sizeof(signed char));
	printf("         char is %3ld bytes \n", sizeof(char));
	printf("       char * is %3ld bytes \n", sizeof(char *));
	printf("unsigned char is %3ld bytes \n", sizeof(unsigned char));
	
	return 0;
}

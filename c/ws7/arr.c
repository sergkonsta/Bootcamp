#include <stdlib.h>
#include <stdio.h>

int main()
{
	char str[20];
	char *str2 = malloc(sizeof(*str2)*20);
	char *str3 = "whatever";
	char str4[] = "whatever";
	
	*(str2 + 3) = '4';

	str4[3] = '4';
	str[3] = '4';
	
	printf("%c %c %c %c\n",*(str2 + 3) ,*(str3 + 3) ,str4[3],str[3]);
	
	free(str2);
	
	return 1;
	
}

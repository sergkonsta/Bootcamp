#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	int i = 8;
	int j = 16;
	int k = 32;

	int *p = &j;

	FILE *fp;

	if (0 == (fp = fopen("stoopid", "r")))
	{
		printf("well, that didn\'t work!\n");

		return -1;
	}

	fscanf(fp, "%p\n", &p);

	if (fclose(fp))
	{
		printf("oh well.");
		return -1;
	} 

	printf("p points to: %d\n", *p);
	printf("p address is: %p\n", &p);
	printf("i address is: %p\n", &i);
	printf("j address is: %p\n", &j);
	printf("k address is: %p\n", &k);
				

	return 0;
}

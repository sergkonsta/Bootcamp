#include <stdio.h>
#include <stdlib.h>

char GLOBAL_STR[] = "global string";

int uninitialized;

int PrintArg(char *arg)
{
	printf("arg 2 is %s\n",arg);
}

int main(int argc, char *argv[], char **env)
{
	int first = 1;
	
	register size_t reg = 0xDEADBEEF;
	
	char *literal = "str literal";
	
	const char constish[] = "constant arr";
	
	static char statish[] = "static arr";
	
	void *mall1 = malloc(0xFF);
	void *mall2 = malloc(4096);
	
	printf(" %s\n", argv[1]);
	PrintArg(argv[2]);
	printf("load time PrintArg address: %p\n",PrintArg);
	printf("run time printf: %p\n",printf);
	printf("argv adress: %p\n",argv);
	printf("env address: %p\n",env);
	printf("env[5] address: %p\n",env[5]);
	printf("global string address: %p\n",&GLOBAL_STR);
	printf("uninitialized int address: %p\n", uninitialized);
	printf("int on stack address: %p\n",&first);
	printf("const on stack address: %p\n",constish);
	printf("static on stack: %p\n",statish);
	printf("string literal address on stack: %p\n",literal);
	printf("malloc of 0xFF: %p\n",mall1);
	printf("second malloc address: %p\n",mall2);
	
	
	return (0);
}

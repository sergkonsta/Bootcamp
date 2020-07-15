#include <stdio.h>	/* printf 			*/
#include <dlfcn.h>	/* dlsym, dlopen 	*/

#define UNUSED(X) (void)(X)

typedef void (*foo_f)();
foo_f foo = NULL;

int main(int argc, char *argv[])
{
	void *sym_adress = NULL;	

	UNUSED(argc);

	sym_adress = dlopen("./test_dl.so", RTLD_LAZY);
	if (!sym_adress)
	{
		printf("\nCannot load symbol!");
	}
	
	*(void **)&foo = dlsym(sym_adress, argv[1]);
	
	sym_adress = dlerror();
	if (sym_adress)
	{
		printf("\nCannot find foo!");
	}

	foo();
	
	return 0;
}

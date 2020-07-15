#include <stdio.h>	/* printf 			*/
#include <dlfcn.h>	/* dlsym, dlopen 	*/

#define UNUSED(X) (void)(X)

typedef void (*foo_f)();
foo_f foo = NULL;

int main(int argc, char *argv[])
{
	void *shared_lib_handle = NULL;	

	UNUSED(argc);

	shared_lib_handle = dlopen("./test_dl.so", RTLD_LAZY);
	if (!shared_lib_handle)
	{
		printf("\nCannot load shared library!");
	}
	
	*(void **)&foo = dlsym(shared_lib_handle, argv[1]);
	
	shared_lib_handle = dlerror();
	if (shared_lib_handle)
	{
		printf("\nCannot find foo!");
	}

	foo();
	
	return 0;
}

#include <stdlib.h>

#include <stdio.h>	/* printf 			*/
#include <dlfcn.h>	/* dlsym, dlopen 	*/

#define UNUSED(X) (void)(X)

typedef void (*foo_f)();
foo_f foo = NULL;

int g_serg = 2;

int main(int argc, char *argv[])
{
	void *shared_obj_handle = NULL;	
	char *error = NULL;
	
	UNUSED(argc);

	shared_obj_handle = dlopen("./test_dl.o", RTLD_LAZY);
	if (!shared_obj_handle)
	{
		printf("\nCannot load shared object!");
	}
	
	*(void **)&foo = dlsym(shared_obj_handle, argv[1]);
	
	error = dlerror();
	if (error)
	{
		printf("\nCannot find foo!");
	}

	foo();
	
	dlclose(shared_obj_handle);

	return 0;
}

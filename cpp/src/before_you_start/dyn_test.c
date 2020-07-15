#include <stdio.h>	/* printf 			*/
#include <dlfcn.h>	/* dlsym, dlopen 	*/

#define UNUSED(X) (void)(X)

typedef void (*foo_f)();
foo_f foo = NULL;

int main(int argc, char *argv[])
{
	void *shared_obj_handle = NULL;	

	UNUSED(argc);

	shared_obj_handle = dlopen("./test_dl.o", RTLD_LAZY);
	if (!shared_obj_handle)
	{
		printf("\nCannot load shared object!");
	}
	
	*(void **)&foo = dlsym(shared_obj_handle, argv[1]);
	
	shared_obj_handle = dlerror();
	if (shared_obj_handle)
	{
		printf("\nCannot find foo!");
	}

	foo();
	
	return 0;
}

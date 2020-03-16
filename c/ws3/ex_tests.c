#include <unistd.h>  		/*for **__environ*/

#include "ex.h"




int main()
{
	/* declares **env for **__environ[array of strings of Env Vars */
	char **env = NULL;
	
	env = __environ;	
	PrintEnvLow(env);

	return 0;
}

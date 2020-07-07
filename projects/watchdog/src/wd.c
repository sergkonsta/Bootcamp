#include <stdio.h>	/*for test printf!!!!!!!!!!!!!!!!!!!!!!*/

#include <sys/types.h>	/*pid_t, fork*/
#include <unistd.h>		/*pid_t, fork, !!!sleep!!!*/
#include <pthread.h>	/*pthread*/

#include "wd_utils.h"
#include "watchdog.h"

void *WDMonitorFunc(void *client_process_argv);


struct watchdog_s
{
	pid_t watchdog_pid;
};







watchdog_t *WDMMI(const char *client_path, size_t interval, 
					size_t num_of_checks, char **client_process_argv)
{
	void **retval = NULL;
	pthread_t wd_monitor_thread = 0;
	
	pthread_create(&wd_monitor_thread, 0, WDMonitorFunc, client_process_argv);
	
	pthread_join(wd_monitor_thread, retval);
	
	return NULL;
}





/* The fuction closes the given process. */
int WDDNR(watchdog_t *watchdog);




/*thread that monitors watchdog*/
void *WDMonitorFunc(void *client_process_argv)
{
	size_t i = 0;
	
	pid_t pid = 0;
	
	char **clients_argv = (char **)client_process_argv;
	
	
	/*test print func*/
	printf("\nPrinting argvs from MMI's thread:\n");
	for (i = 0; NULL != clients_argv[i]; ++i)
	{
		printf("%s ,",clients_argv[i]);
	}
	printf("\n\n");	
	
	/*fork*/
	pid = fork();
	if (-1 == pid)
	{
		return NULL; /*check if this is the desired action when fork fails*/
	}
	
	/*child case*/
	if (0 == pid)
	{
		execv(clients_argv[1], clients_argv);
	}
	
	
	/*parent case*/
	if (0 < pid)
	{
		sleep(5);
	}


	
	return NULL;
}

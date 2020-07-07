#define _XOPEN_SOURCE (600)

#include <stdio.h>	/*for test printf!!!!!!!!!!!!!!!!!!!!!!*/

#include <stdlib.h>		/*malloc*/
#include <sys/types.h>	/*pid_t, fork*/
#include <unistd.h>		/*pid_t, fork, !!!sleep!!!*/
#include <pthread.h>	/*pthread*/
#include <signal.h>		/*sigaction, sig_atomic_t*/

#include "wd_utils.h"
#include "watchdog.h"

#define UNUSED(X) (void)(X)

void *WDMonitorFunc(void *client_process_argv);
static void SigRecievedFromWatchdog(int sig);

struct watchdog_s
{
	pid_t pid;
};

extern sig_atomic_t g_do_not_revive;
extern sig_atomic_t g_sigs_recieved_from_watchdog;
extern sig_atomic_t g_sigs_recieved_from_client;



watchdog_t *WDMMI(const char *client_path, size_t interval, 
					size_t num_of_checks, char **client_process_argv)
{
	long retval = 0;

	pthread_t wd_monitor_thread = 0;
	struct sigaction usr_action = {0};
		
	watchdog_t *watchdog = (watchdog_t *)malloc(sizeof(watchdog_t));
	if (NULL == watchdog)
	{
		return NULL;
	}
	
	/*Establish the signal handler*/
	usr_action.sa_handler = SigRecievedFromWatchdog;
	sigaction(SIGUSR1, &usr_action, NULL);
	
	/*prepare to pass pointer to watchdog struct via argv[2]*/
	client_process_argv[2] = (char *)watchdog;
	client_process_argv[3] = NULL;
	 
	/*creates monitor thread*/
	pthread_create(&wd_monitor_thread, 0, WDMonitorFunc, client_process_argv);
	if (0 != wd_monitor_thread)
	{
		return NULL;
	}
	
	
	pthread_join(wd_monitor_thread, (void **)(&retval));
	watchdog->pid = retval;
	
	
	return watchdog;
}





/* The fuction closes the given process. */
int WDDNR(watchdog_t *watchdog)
{

	free(watchdog);
	
	return 0;
}




/*thread that monitors watchdog*/
void *WDMonitorFunc(void *client_process_argv)
{
	pid_t pid = 0;
	
	char **clients_argv = (char **)client_process_argv;
	watchdog_t *watchdog = (watchdog_t *)(clients_argv[2]);
	
	/*create watchdog monitor process*/
	pid = fork();
	if (-1 == pid)
	{
		return (void *)-1; /*check if this is the desired action when fork fails*/
	}
	
	/*child case - execute watchdog*/
	if (0 == pid)
	{
		execv(clients_argv[1], clients_argv);
	}
	
	
	/*parent case - waits for first signal to arrive - 
		meaning watchdog is up and running*/
	if (0 < pid)
	{
		/*update watchdog pid*/
		watchdog->pid = pid;
		
		/*wait for first signal (check toggle on global counter)*/
		
		return (void *)0;
	}


	
	return (void *)0;
}

/*increments counter of amounts of signals recieved from watchdog*/
static void SigRecievedFromWatchdog(int sig)
{
	UNUSED(sig);
	
	++g_sigs_recieved_from_watchdog;
}

/*
Project:	Watchdog
Developer:	Sergey Konstantinovsky
Date:		10/07/2020
*/

#define _POSIX_C_SOURCE 200112L  /*sem_wait requirement*/

#include <stdlib.h>		/*malloc, setenv, atoi*/
#include <sys/types.h>	/*pid_t, fork*/
#include <unistd.h>		/*pid_t, fork, execve*/
#include <pthread.h>	/*pthread*/
#include <signal.h>		/*sigaction, sig_atomic_t*/
#include <semaphore.h>	/*sem_open, sem_wait*/
#include <fcntl.h>		/*O_* ocnstants*/
#include <sys/stat.h>	/*mode constants*/
#include <assert.h>		/*assert*/

#include "wd_utils.h"
#include "watchdog.h"


static void CleanUp(watchdog_t *client);
static void *WDMonitorFunc(void *param);
static char **StoreDataInArgs(char **client_process_argv, size_t interval, size_t num_of_checks);

sem_t client_sem;

/*----------------------------------------------------------------------------*/
wd_t *WDMMI(const char *client_path, size_t interval, size_t num_of_checks,
			char **client_process_argv)
{
	pthread_t wd_monitor_thread = 0;
	
	/*init client struct*/	
	wd_t *client = (wd_t *)malloc(sizeof(wd_t));
	if (NULL == client)
	{
		return NULL;
	}
	
	assert(client_path);
	assert(interval);
	assert(num_of_checks);
	assert(client_process_argv);
	
	UNUSED(client_path);
	
	client->other_side_path = client_process_argv[1];
	client->other_side_argv = StoreDataInArgs(client_process_argv, interval, 
												num_of_checks);
	client->interval = interval;
	client->num_of_checks = num_of_checks;
	
	sem_init(&client_sem, 0, 0);
	
	/*creates monitor thread*/
	pthread_create(&wd_monitor_thread, 0, WDMonitorFunc, client);
	client->thread_2_join = wd_monitor_thread;
	
	/*wait until wd is up*/
	sem_wait(&client_sem);

	return client;
}





/*----------------------------------------------------------------------------*/
/*thread that monitors client*/
static void *WDMonitorFunc(void *param)
{
	wd_t *client = (wd_t *)param;
	
	assert(param);
	
	/*setup comm device*/
	if (SetupCommunication(client))
	{
		CleanUp(client);
		sem_post(&client_sem);
		return NULL;
	}
	
	/*watchdog is already running*/
	if (getenv(ENV_NAME))
	{
		client->other_side_pid = getppid();
		sem_post(wd_sem);
	}
	
	/*watchdog will now run*/
	else
	{	
		setenv(ENV_NAME,"1",1);

		ReviveOtherProc(client);
		
		sem_wait(wd_sem);
	}

	sem_post(&client_sem);

	StartCommunication(client); 
	
	return NULL;
}



/*----------------------------------------------------------------------------*/
/* The fuction closes the given process. */
int WDDNR(wd_t *client)
{
	assert(client);
	
	g_sched_op = SEND;
	
	kill(client->other_side_pid, SIGUSR2);
	
	pthread_join(client->thread_2_join, NULL);
	
	CleanUp(client);
	
	return 0;
}


/*----------------------------------------------------------------------------*/
static char **StoreDataInArgs(char **client_process_argv, size_t interval, 
							size_t num_of_checks)
{
	char **new_args = NULL;
	char *interval_str = NULL;
	char *check_str = NULL;
	size_t args_amount = 0;
	size_t i = 0;
	
	assert(client_process_argv);
	
	interval_str = malloc(sizeof(char) * 10);
	check_str = malloc(sizeof(char) * 10);
	if (NULL == check_str || NULL == interval_str)
	{
		free(check_str);
		free(interval_str);
		return NULL;
	}

	sprintf(interval_str,"%ld",interval);
	sprintf(check_str,"%ld",num_of_checks);

	while (*client_process_argv)
	{
		++args_amount; 
		++client_process_argv;
	}
	
	client_process_argv -= args_amount;
		
	new_args = (char **)malloc(sizeof(char *) * (args_amount + 3));
	if (NULL == new_args)
	{
		return NULL;	
	}
	
	new_args[0] = interval_str;
	new_args[1] = check_str;

	for (i = 0; i < args_amount; ++i)
	{
		new_args[i + 2] = client_process_argv[i];
	}
	new_args[args_amount + 2] = NULL;

	return new_args;
}

static void CleanUp(wd_t *client)
{
	assert(client);
	
	free(client->other_side_argv[0]);
	free(client->other_side_argv[1]);
	free(client->other_side_argv);
	
	client->other_side_argv = NULL;	
	
	free(client);
	
	client = NULL;

	sem_destroy(&client_sem);
	sem_unlink(ENV_NAME);
	
	return;
}


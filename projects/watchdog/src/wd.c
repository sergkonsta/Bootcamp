#define _XOPEN_SOURCE (600)

#include <stdio.h>		/*test ------------- printf*/



#include <stdlib.h>		/*malloc, setenv, atoi*/
#include <sys/types.h>	/*pid_t, fork*/
#include <unistd.h>		/*pid_t, fork, execve*/
#include <pthread.h>	/*pthread*/
#include <signal.h>		/*sigaction, sig_atomic_t*/
#include <string.h>		/*strcmp*/
#include <semaphore.h>	/*sem_open, sem_wait*/
#include <fcntl.h>		/*O_* ocnstants*/
#include <sys/stat.h>	/*mode constants*/

#include "wd_utils.h"
#include "watchdog.h"

#define UNUSED(X) (void)(X)

static void StoreDataInEnvs(watchdog_t *client);
static void *WDMonitorFunc(void *client_process_argv);
static void Usr1Handler(int signum);
static void Usr2Handler(int signum);
static void SetIntEnv(const char *env_var, int param);

extern sig_atomic_t g_stop;
extern sig_atomic_t g_do_not_revive;
extern sig_atomic_t g_failed_checks;

watchdog_t *WDMMI(const char *my_path, size_t interval, 
					size_t num_of_checks, char **client_process_argv)
{
	pthread_t wd_monitor_thread = 0;

	struct sigaction sig1 = {0};
	struct sigaction sig2 = {0};
	
	/*init client struct*/	
	watchdog_t *client = (watchdog_t *)malloc(sizeof(watchdog_t));
	if (NULL == client)
	{
		return NULL;
	}
	client->my_info = NULL;
	client->my_path = my_path;
	client->my_argv = client_process_argv;
	client->interval = interval;
	client->num_of_checks = num_of_checks;
	client->thread_2_join = &wd_monitor_thread;
	
	/*stores user data in env vars*/
	StoreDataInEnvs(client);
	
	/*Establish the signal handler*/
	sig1.sa_handler = Usr1Handler;
	sig2.sa_handler = Usr2Handler;
	
	/**/
	if(sigfillset(&sig1.sa_mask) || sigfillset(&sig2.sa_mask)
	|| sigdelset(&sig1.sa_mask, SIGUSR1) || sigdelset(&sig2.sa_mask, SIGUSR2)
	|| sigdelset(&sig1.sa_mask, SIGTERM) || sigdelset(&sig2.sa_mask, SIGTERM)
	|| sigdelset(&sig1.sa_mask, SIGINT) || sigdelset(&sig2.sa_mask, SIGINT) 
	|| sigaction(SIGUSR1, &sig1, NULL) || sigaction(SIGUSR2, &sig2, NULL))
	{
		printf("failed sig mmi \n");
		return NULL;
	}
	
	/*creates monitor thread*/
	pthread_create(&wd_monitor_thread, 0, WDMonitorFunc, client);

	return client;
}





/*----------------------------------------------------------------------------*/
/*thread that monitors client*/
static void *WDMonitorFunc(void *param)
{
	watchdog_t *client = (watchdog_t *)param;
	pid_t pid = 0;
	sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
	
	/*check in enviroment vars if watchdog is not running*/
	if (0 == strcmp("False" ,getenv(WD_FLAG)))
	{
		/*create client monitor process*/
		pid = fork();
		if (-1 == pid)
		{
			sem_unlink(SEM_NAME);
			free(client);
			
			return NULL;
		}
		
		/*child case - execute client*/
		if (0 == pid)
		{
			if (-1 == execv(getenv(PATH_ENV_WD), client->my_argv))
			{
				sem_unlink(SEM_NAME);
				free(client);
			
				return NULL;
			}
		}
	}	
	
	/*setup comm device*/
	client->my_info = SetupCommunication(getenv(PATH_ENV_WD), sem, 
						client->my_argv, (size_t)atoi(getenv(INT_ENV)),
						(size_t)atoi(getenv(NUM_ENV)), getpid(), pid);
	
	/*parent case - waits for first signal to arrive from watchdog*/
	sem_wait(sem);
	
	/*set env - watchdog is runing*/
	setenv(WD_FLAG, "True", 1);
	
printf("\n starting client sched\n");						
	
	/*start sending signals back*/
	StartCommunication(client->my_info);

	return NULL;

}



/*----------------------------------------------------------------------------*/
/* The fuction closes the given process. */
int WDDNR(watchdog_t *client)
{
	g_do_not_revive = 1;

	ShutDownCommunication(client->my_info);

	pthread_join(*(client->thread_2_join), NULL);

	sem_unlink(SEM_NAME);
	
	free(client);
	
	return 0;
}


/*----------------------------------------------------------------------------*/
/*increments counter of amounts of signals recieved from client*/
static void Usr1Handler(int signum)
{
	UNUSED(signum);
	g_failed_checks = 0;
}

static void Usr2Handler(int signum)
{
	UNUSED(signum);
	g_stop = 1;
}

/*----------------------------------------------------------------------------*/
static void StoreDataInEnvs(watchdog_t *client)
{
	/*create env var if runs for the first time*/
	if (NULL ==  getenv(WD_FLAG))
	{
		setenv(WD_FLAG, "False", 1);
	}
	
	/*interval*/
	SetIntEnv(INT_ENV, (int)client->interval);

	/*num_of_checks*/
	SetIntEnv(NUM_ENV, (int)client->num_of_checks);
	
	/*my_path*/
	setenv(PATH_ENV, client->my_path, 1);
	
	/*client path*/
	setenv(PATH_ENV_WD, client->my_argv[1], 1);
}

static void SetIntEnv(const char *env_var, int param)
{
	char buffer[20] = {'\0'};
	sprintf(buffer, "%d", param);
	setenv(env_var, buffer, 1);
}

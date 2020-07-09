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

static void StoreDataInEnvs(watchdog_t *watchdog);
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
	
	/*init watchdog struct*/	
	watchdog_t *watchdog = (watchdog_t *)malloc(sizeof(watchdog_t));
	if (NULL == watchdog)
	{
		return NULL;
	}
	watchdog->my_info = NULL;
	watchdog->my_path = my_path;
	watchdog->argv = (char **)client_process_argv;
	watchdog->interval = interval;
	watchdog->num_of_checks = num_of_checks;
	
	/*stores user data in env vars*/
	StoreDataInEnvs(watchdog);
	
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
	pthread_create(&wd_monitor_thread, 0, WDMonitorFunc, watchdog);
	pthread_join(wd_monitor_thread, NULL);

	return watchdog;
}





/*----------------------------------------------------------------------------*/
/*thread that monitors watchdog*/
static void *WDMonitorFunc(void *param)
{
	watchdog_t *watchdog = (watchdog_t *)param;
	pid_t pid = 0;
	sem_t *sem = sem_open(SHAREDSEM, O_CREAT, 0666, 0);
	
	/*check in enviroment vars if watchdog is already up*/
	while (0 == strcmp("False" ,getenv(WD_FLAG)))
	{
		/*create watchdog monitor process*/
		pid = fork();
		if (-1 == pid)
		{
			return (void *)-1; /*check if this is the desired action when fork fails*/
		}
		
		/*child case - execute watchdog*/
		if (0 == pid)
		{
			execv(getenv(PATH_ENV_WD), watchdog->argv);
		}
		
		/*parent case - waits for first signal to arrive - 
			meaning watchdog is up and running*/
		if (0 < pid)
		{
			/*setup comm device*/
			my_info = SetupCommunication(getenv(PATH_ENV_WD), 
								sem, (char **)client_process_argv, 
								(size_t)atoi(getenv(INT_ENV)),							
								(size_t)atoi(getenv(NUM_ENV)), getpid(), pid);
			
			/*wait for first signal from watchdog*/
			sem_wait(sem);
			
			/*set env - watchdog is runing*/
			setenv(WD_FLAG, "True", 1);
			
			/*start sending signals back*/
			StartCommunication(my_info);
			
			return (void *)0;
		}
	}
	
	/*starts sched*/
	StartCommunication(my_info);
	
	return (void *)0;
}



/*----------------------------------------------------------------------------*/
/* The fuction closes the given process. */
int WDDNR(watchdog_t *watchdog)
{
	g_do_not_revive = 1;

	ShutDownCommunication();

	sem_unlink(SEM_NAME);
	
	free(watchdog);
	
	return 0;
}


/*----------------------------------------------------------------------------*/
/*increments counter of amounts of signals recieved from watchdog*/
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
static void StoreDataInEnvs(watchdog_t *watchdog)
{
	/*create env var if runs for the first time*/
	if (NULL ==  getenv(WD_FLAG))
	{
		setenv(WD_FLAG, "False", 1);
	}
	
	/*interval*/
	SetIntEnv(INT_ENV, (int)watchdog->interval);

	/*num_of_checks*/
	SetIntEnv(NUM_ENV, (int)watchdog->num_of_checks);
	
	/*my_path*/
	setenv(PATH_ENV, watchdog->my_path, 1);
	
	/*watchdog path*/
	setenv(PATH_ENV_WD, watchdog->wd_path, 1);
}

static void SetIntEnv(const char *env_var, int param)
{
	char buffer[20] = {'\0'};
	sprintf(buffer, "%d", param);
	setenv(env_var, buffer, 1);
}

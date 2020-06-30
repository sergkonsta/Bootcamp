#define _XOPEN_SOURCE (600)

#include <stdio.h> /* printf */
#include <string.h> /* memeset */
#include <sys/types.h> /* pid_t */
#include <signal.h> /* sigprocmask sigset_t */
#include <unistd.h> /* pause */
#include <stdlib.h> /* strtol */

static sig_atomic_t is_flaged = 0;

void PongHandler(int signum)
{
	is_flaged = 1;
	(void)signum;
}

int main (int argc, char **argv)
{
	size_t i = 0;
	struct sigaction action_pong;	
	
	long loaded_pid = strtol(*(argv + 1), NULL, 10);

	memset(&action_pong, 0, sizeof(action_pong));
	sigemptyset(&action_pong.sa_mask);
	action_pong.sa_handler = PongHandler;
	sigaction(SIGUSR2, &action_pong, NULL);
	
	printf("Pong is UP. PongPID: %u, PID loaded :%u \n",getpid(), (int)loaded_pid);

	kill((int)loaded_pid, SIGUSR1);

	/* send frist signal */
	while (1)
	{
		if (is_flaged)
		{
			puts("pong recieved signal");
			++i;
			is_flaged = 0;
			sleep(1);
		}
		
		kill((int)loaded_pid, SIGUSR1);
		pause();
	}

	return 0; 
}


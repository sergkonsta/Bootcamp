#include <stdio.h>

#include <unistd.h>	/*sleep*/
#include <signal.h>

#include "watchdog.h"

					#include "wd_utils.h"
					struct comm_s
					{
					sched_t *my_sched;
					const char *other_side_path;
					sem_t *shared_sem;
					char **new_argv;
					size_t interval;
					size_t num_of_checks;
					pid_t pid;
					pid_t other_side_pid;
					};

sig_atomic_t flag = 1;

void SigHandler(int signum)
{
	(void)signum;

	flag = 0;
}

int main(int argc, char *argv[])
{
	watchdog_t *watchdog = NULL;
	
	struct sigaction sig = {0};
	sig.sa_handler = SigHandler;
	sigaction(SIGINT, &sig, NULL);
	
	
	watchdog = WDMMI(argv[0], 1, 3, argv);
	
	printf("\n started sleeping\n");
	
	sleep(10);
	
	
	WDDNR(watchdog);
	
	return 0;
}

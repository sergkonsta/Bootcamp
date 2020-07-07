#define _XOPEN_SOURCE (600)

#include <stdio.h>	/*for test printf!!!!!!!!!!!!!!!!!!!!!!*/

#include <signal.h>		/*sigaction, sig_atomic_t*/

#include "wd_utils.h"

#define UNUSED(X) (void)(X)

static void SigRecievedFromClient(int sig);

extern sig_atomic_t g_do_not_revive;
extern sig_atomic_t g_sigs_recieved_from_watchdog;
extern sig_atomic_t g_sigs_recieved_from_client;

int main()
{
	/*Establish the signal handler*/
	struct sigaction usr_action = {0};
	usr_action.sa_handler = SigRecievedFromClient;
	sigaction(SIGUSR2, &usr_action, NULL);
	
	
	return 0;
}





/*increments amounts of signals recieved from client*/
static void SigRecievedFromClient(int sig)
{
	UNUSED(sig);
	
	++g_sigs_recieved_from_client;
}

#include <stdio.h>	/*for test printf!!!!!!!!!!!!!!!!!!!!!!*/

#include <signal.h>		/*sig_atomic_t*/

#include "wd_utils.h"


sig_atomic_t g_do_not_revive = 0;
sig_atomic_t g_sigs_recieved_from_client = 0;
sig_atomic_t g_sigs_recieved_from_watchdog = 0;


void TestFunc()
{

	printf("\nI am the watchdog!\n");

	

}

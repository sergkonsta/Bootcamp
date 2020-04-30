
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      28.04.2020               **
**  Reviewer:  Irina					**
**  Status:    Sent						**
*****************************************/		

#include <unistd.h>	/*for getpid()*/
#include <time.h>	/*for time()*/

#include "uid.h"

extern ilrd_uid_t BAD_UID;

/* Creat a unique uid value and return it. If Create fail-return BAD_UID */
ilrd_uid_t UIDCreate(void)
{
	static size_t counter = 0;
	
	ilrd_uid_t uid = {0};	
	ilrd_uid_t BAD_UID = {0,0,0};
	
	/*pull process id and put into uid.pid*/
	uid.pid = getpid();
	
	/*pull time stamps and put into uid.time*/
	uid.time = time(NULL);
	
	/*inc counter*/
	++counter;
	uid.counter = counter;
	
	if(-1 == uid.time)
	{
		uid = BAD_UID;
	}
	return (uid);
}

/*----------------------------------------------------------------------------*/
/*Compare 2 uids. If uids are same return: 1, else: 0 */
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (!!(	uid1.pid	 == uid2.pid && 
				uid1.time	 == uid2.time && 
				uid1.counter == uid2.counter));
}

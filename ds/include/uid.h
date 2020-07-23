#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>	/*for pid_t*/

typedef struct 
{
   pid_t 	pid;
   time_t 	time;
   size_t 	counter;
}ilrd_uid_t;

/* hold value of invalid UID */
extern ilrd_uid_t BAD_UID;

/* Creat a unique uid value and return it. If Create fail-return BAD_UID */
ilrd_uid_t 	UIDCreate(void);

/*Compare 2 uids. If uids are same return: 1, else: 0 */
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif 

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>

#include "task.h"

typedef struct sched sched_t;

/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	creates a scheduler 
Success:	pointer to sched
fail:		NULL
*/
sched_t *SchedCreate(void);

/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	destroys
Success:	---
fail:		---
*/
void SchedDestroy(sched_t *sched);



/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	returns size of sched 
			(during runtime if there is a task running 
			will be +1 for current task)
Success:	size_t
fail:		---
*/
size_t SchedSize(const sched_t *sched);


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	checks if sched is empty
Success:	1 for empty or 0 for not empty
fail:		---
*/
int SchedIsEmpty(const sched_t *sched);


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	clears all tasks
Success:	---
fail:		---
*/
void SchedClear(sched_t *sched);




/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	removes a specific task, UID must be correct
Success:	---
fail:		---
*/
void SchedRemove(sched_t *sched, ilrd_uid_t uid);



/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	Adds new task to scheduler
Success:	UID of added task
fail:		---
*/
/* 
void *param - how many times task should repeat
interval - time to start (when calling add func- time 0) + interval
act_func - what the task should do 
act_func returns non zero int as status if task should be repeated
				zero - if should not be repeated 
*/
ilrd_uid_t SchedAddTask(sched_t *sched, int (*act_func)(void *param),
		void *param, size_t interval_in_sec);


/*stop running (should be sent to the sched via task)*/
void SchedStop(sched_t *sched);

/*returns status

return:

-1 means task failed to reEnq. put it in sched again.*/
int SchedRun(sched_t *sched);


#endif 



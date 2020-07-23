#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>
#include <time.h>

#include "uid.h"

typedef struct task task_t;

/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	creates a task according to task struct 
success:	pointer to task
fail:		NULL
*/
task_t *TaskCreate( int(*act_func)(void *param), void *param,
						size_t interval_in_sec);


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	runs act_func
success:	1 for repeat / 0 for don't repeat
fail:		---
*/
int TaskRun(task_t *task);

/*----------------------------------------------------------------------------*/
/*
O(1)
function:	frees task.
success:	---
fail:		---
*/
void TaskDestroy(task_t *task);


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	gets UID of the task
success: 	return UID of the task
fail: 		---	
*/
ilrd_uid_t TaskGetId(const task_t *task);


/*----------------------------------------------------------------------------*/
/*
O(1)
function: returns next time to run
success:
fail:
*/
size_t TaskGetNextRunTime(const task_t *task);


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	updates next run time according to interval			
success: 	---
fail:		---
*/
void TaskUpdateNextRun(task_t *task);


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	checks if task has the same UID as 'uid'
success: 	1 - is a match / 0 - no match
fail:		---
*/
int TaskIsMatch(const void *task, const void *uid);


#endif 

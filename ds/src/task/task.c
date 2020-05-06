
#include <assert.h>		/*for assert*/
#include <stdlib.h>		/*for malloc*/

#include "task.h"

typedef struct help help_struct_t;

struct help
{
	void *param_for_act_fun;
	time_t start_time;
	int is_repeat;
};

struct task
{
	ilrd_uid_t uid;
	size_t time_to_run; /*my comment: shows next time to run*/
	size_t interval_in_sec; /*first time to run and all after if repeat is on*/
	int (*act_func)(void *param); /*returns repeat or not*/
	void *param; /*		1-	(void *)param for act_fun
						2-	(size_t) time elapsed for TaskUpdateNextRun
						3-	(int)is_repeat - need to repeat?*/
};


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	creates a task according to task struct 
success:	pointer to task
fail:		NULL
*/
task_t *TaskCreate(	int (*act_func)(void *param), void *param, 
					size_t interval_in_sec)
{
	task_t *new_task = {0};

	assert(0 != interval_in_sec);
	assert(NULL != param);
	
	new_task = (task_t *)malloc( sizeof(task_t) );
	if(NULL == new_task)
	{
		return NULL;
	}
	
	/*assign unique ID for task*/
	new_task->uid = UIDCreate();
	
	/*set first time act_func will run*/
	new_task->time_to_run = interval_in_sec; 
	
	/*set repeat interval*/
	new_task->interval_in_sec = interval_in_sec;

	/*assign action func pointer and param*/
	new_task->act_func = act_func;
	new_task->param = param;
	
	return (new_task);
}



/*----------------------------------------------------------------------------*/
/*
O(1)
function:	runs act_func
success:	1 for repeat / 0 for don't repeat
fail:		--- (can't fail - Tal said)
*/
int TaskRun(task_t *task)
{
	help_struct_t *temp = (help_struct_t *)task->param;
	
	int is_repeat = temp->is_repeat;
	
	assert(NULL != task);
	
	task->act_func(temp->param_for_act_fun);	
	
	return (is_repeat);
}




/*----------------------------------------------------------------------------*/
/*
O(1)
function:	gets UID of the task
success: 	return UID of the task
fail: 		---	
*/
ilrd_uid_t TaskGetId(const task_t *task)
{
	assert(NULL != task);

	return (task->uid);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	frees task.
success:	---
fail:		---
*/
void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	free(task);	
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function: returns next time to run
success:
fail:
*/
size_t TaskGetNextRunTime (const task_t *task)
{
	assert (NULL != task);
	
	return (task->time_to_run);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	updates next run time according to interval and param
			param in this func is  elapsed time from start of event loop (Run)
success: 	---
fail:		---
*/
void TaskUpdateNextRun(task_t *task)
{
	size_t time_elapsed = (time_t)task->param;
	
	assert(NULL != task);
	
	task->time_to_run += task->interval_in_sec + time_elapsed;
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	checks if task has the same UID as 'uid'
success: 	1 - is a match / 0 - no match
fail:		---
*/
int TaskIsMatch(task_t *task, ilrd_uid_t uid)
{
	assert(NULL != task);
	
	return (UIDIsSame(task->uid,uid));
}



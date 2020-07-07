/*
Developer: Sergey Konstantinovsky
Date:      01.07.2020
Reviewer:  Irina
*/

/*
DOESN'T PROTECT USER FROM DECREMENT TO ZERO
		 	
for semaphore: link with -pthread 
*/

#include <sys/stat.h>   /*for semaphore mode constants*/
#include <fcntl.h>      /*O_CREAT*/
#include <semaphore.h>	/*sem_ops*/
#include <string.h> 	/*strcpy, strcmp*/
#include <stdio.h> 		/*printf, sscanf*/
#include <assert.h>		/*assert*/

#define DEFAULT_SEMAPHORE_NAME "/my_semaphore"
#define INPUT_STR_LEN (256)
#define BUFFER_SIZE (20)

typedef void *(*sem_action)(void *);

int g_flag = 0;

static void CleanUp(sem_t *sem, int undo_inc, int undo_dec);
static void PrintCurrVal(sem_t *sem);
static void *Decrement(void *sem);
static void *Increment(void *sem);

int main(int argc, char *argv[])
{
	char *name = DEFAULT_SEMAPHORE_NAME;
	
	int init_val = 0;
	
	sem_t *sem = NULL;

	/*user input variables*/
	char buffer[INPUT_STR_LEN];
	char action = 0;
	int num_of_actions = 1;
	char undo_str[5]= {0};

	/*undo logic variables*/
	int is_undo = 0;
	int undo_inc = 0; 
	int undo_dec = 0;
	
	/*if user presented own name*/
	if(argc > 1)
	{
		name = argv[1];
	} 

	/*create semaphore with user ang groups read write perms*/
	sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, init_val);
	if (SEM_FAILED == sem)
	{
		return -1;
	}

	/*buisiness logic*/
	while (!g_flag)
	{
		undo_str[0] = 0;
		PrintCurrVal(sem);
		printf("D <NUM> [undo] (Decrement), U <NUM> [undo] (increment), X (exit) \n");
		
		fgets(buffer, BUFFER_SIZE, stdin);
		sscanf(buffer, "%c%d%5s", &action, &num_of_actions, undo_str);

		is_undo = !(strcmp(undo_str, "undo"));

		switch (action)
		{
			case 'D':
				
				while (0 < num_of_actions)
				{
					Decrement(sem);
					undo_dec += is_undo;
					--num_of_actions;
				}
				
				break;
				
			case 'U':
				
				while (0 < num_of_actions)
				{
					Increment(sem);
					undo_inc += is_undo;
					--num_of_actions;
				}
				
				break;
				
			case 'X':
				
				CleanUp(sem, undo_inc, undo_dec);
				
				break;
			
			default:
				break;
		}
	}

	PrintCurrVal(sem);

	sem_close(sem);

	return 0;
}


/*increment semaphore*/
static void *Increment(void *sem)
{
	assert(sem);
	
	if (sem_post((sem_t *)sem))
	{
		printf("operation failed\n");
		return (void *) -1;
	}

	return (void *)0;
}

/*decrement semaphore*/
static void *Decrement(void *sem)
{
	assert(sem);
	
	if (sem_wait((sem_t *)sem))
	{
		printf("operation failed\n");
		return (void *)-1;
	}

	return (void *)0;
}

/*prints semaphore current value*/
static void PrintCurrVal(sem_t *sem)
{
	int val = 0;

	assert(sem);

	sem_getvalue(sem, &val);

	printf("semaphore current value: %d \n", val);
}

/*on exit calculate and peform 'undos'*/
static void CleanUp(sem_t *sem, int undo_inc, int undo_dec)
{
	g_flag = 1;
	
	assert(sem);
	
	while (undo_inc != undo_dec && 0 != undo_inc)
	{	
		if(undo_inc > undo_dec)
		{
			Decrement(sem);
			--undo_inc;
		}
		
		if(undo_dec > undo_inc)
		{
			Increment(sem);
			--undo_dec;
		}
	}
}


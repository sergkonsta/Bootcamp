/*
Developer: Sergey Konstantinovsky
Date:      01.07.2020
Reviewer:  Irina
*/

/*
sem_manipulation: 

user runs prog with: ./sem_manipulator.c name <--- argv[1] is name
	-> sem_open name 
		if argc == 3,
			get name from argv[1] 
		else
			wrong type of input 

wait for user input (every input performed in a new thread):

 - use getline() and create new thread and pass arg the str from getline.

 - D number [UNDO]
	-> call sem_wait
	-> if UNDO is present, terminate operation with process termination
	
 - U number [UNDO]
 	-> cal sem_post
 	-> if UNDO is present, terminate operation with process termination
 	
 - X 
 	choose which:
 	-> call sem_close ? 
 	-> call sem_unlink ?
for semaphore: link with -pthread 
*/







int main(int argc, char *argv[])
{
	return 0;
}

#include <stdlib.h> /*for exit*/
#include <stdio.h>	/*for printf, files*/
#include <unistd.h>	/*for */

enum State {Succeeded = 0, Failed = -1, append_from_start = 2}; 

enum State RemoveFile(const char *file_name);
enum State PreAppend(char *str, const char *file_name);
enum State Append(char *str, const char *file_name);
enum State Compare(const char *s1, const char *s2);

void Exit();
size_t CountRows(const char *file_name);


/*-------------------------------------------------------------------------*/

int main()
{
	char *str = "Hello!!!!!!!!!!!!!!!";
	const char *file_name = "Log.txt";
	
	printf("\n the row number is: %ld.\n",CountRows(file_name);
	
	return 1;
}

/*-------------------------------------------------------------------------*/


/*	Removes the Log file	*/
enum State RemoveFile(const char *file_name)
{
	/*check if file opens successfully*/
 	if(NULL == file_name)
 	{
 		return -1;
 	}
 	
	return(remove(file_name));
}



/*	Program Exits	*/
void Exit()
{
	exit(0);
	return;
}


/*	Function appends to the End of the file	*/
enum State Append(char *str, const char *file_name)
{
	/*create file pointer and open it in append and read mode*/
	FILE *file_pointer;
 	file_pointer = fopen(file_name, "a+");
 	
	/*writes string to the file pointer and then starts a new line*/
	fputs(str, file_pointer);
	fputc('\n',file_pointer);
	
	/*closes the file*/
	fclose(file_pointer);
	
	return 0;
}


/*Counts number of lines in the file*/
size_t CountRows(const char *file_name)
{
	size_t rows = 0;
	
	FILE *file_pointer = fopen(file_name, "r");

	/*check every char for end of line, while EOF is still zero */
	while(0 == feof(fp))
	{
		ch = fgetc(fp);

		if(ch == '\n')
		{
			++rows;
		}

	}
	
	return 0;
}


/*Function appends to the beginning of the file*/
enum State PreAppend(char *str, const char *file_name)
{
	

	return 0;
}


/* strcmp between string from user to each check*/
enum State Compare(const char *s1, const char *s2)
{
	/*	check if to append to file beggining	*/
	if('<' == *s2)
	{
		return 2;
	}
	
	/*	strcmp	*/
	while((*s1 == *s2) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	
	if ((*s1 - *s2) == 0)
	{
		return 0;
	}

	return -1;
}


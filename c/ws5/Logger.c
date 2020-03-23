#include <stdlib.h> /*for exit*/
#include <stdio.h>	/*for printf, files*/
#include <unistd.h>	/*for */

enum op {succeeded = 0, failed = -1, exit_program = 2}; 

enum op RemoveFile();
enum op PreAppend(const char *str);
enum op Append(const char *str);
enum op Compare(const char *s1, const char *s2);
enum op Exit();
size_t CountRows();

/*global string for file name - NOT GOOD*/
char file_path[100];


/*-------------------------------------------------------------------------*/

int main()
{	
	/*string for user input*/
	char str[100];
		
	/*file path and command input*/
	printf("\nPlease enter the file path\n");
	scanf("%s", file_path);
	/*printf("\n%s\n", file_path);
	printf("\nPlease enter your input\n");
	scanf("%s", str);*/
		
	PreAppend("123456");
	
	
	return 1;
}

/*-------------------------------------------------------------------------*/


/*	Removes the Log file	*/
enum op RemoveFile()
{
	if(remove(file_path) == 0)
	{
		return succeeded;
	}
	
	return failed;
}

/*-------------------------------------------------------------------------*/

/*	Program Exits	*/
enum op Exit()
{
	return exit_program;
}

/*-------------------------------------------------------------------------*/

/*	Function appends to the End of the file	*/
enum op Append(const char *str)
{
	
	/*create file pointer and open it in append and read mode*/
	FILE *file_pointer;
 	file_pointer = fopen(file_path, "a+");
 	
 	if(NULL == file_pointer)
 	{
 		return failed;
 	}

	/*writes string to the file pointer and then starts a new line*/
	fputs(str, file_pointer);
	fputc('\n',file_pointer);
	
	/*closes the file*/
	fclose(file_pointer);

	return succeeded;
}

/*-------------------------------------------------------------------------*/

/*	Counts number of lines in the file	*/
size_t CountRows()
{
	size_t rows = 0;
	char ch = 0;
	
	FILE *file_pointer = fopen(file_path, "r");
	
	/*check every char for end of line char, while file not ended */
	while(0 == feof(file_pointer))
	{
		ch = fgetc(file_pointer);
		if(ch == '\n')
		{
			rows++;
		}
	}
		
	return rows;
}

/*-------------------------------------------------------------------------*/

/*Function appends to the beginning of the file*/
enum op PreAppend(const char *str)
{
	unsigned char ch = 0;
	
	/*opening file and saving its pointer*/
	FILE *file_pointer = fopen(file_path, "r");
	
	/*opening temp file and saving its pointer*/
	FILE *temp_file_pointer = fopen("temp.txt", "w");
	
	/*copying original file to temp file, while original file not ended*/
	while(0 == feof(file_pointer))
	{
		ch = fgetc(file_pointer);
		fputc(ch, temp_file_pointer);
	}
	
	
    /**/
     
    
	/*removing temp file*/
	

	/*closing file*/
	fclose(file_pointer);
	fclose(temp_file_pointer);
	return 0;
}

/*-------------------------------------------------------------------------*/


/* strcmp between string from user to each check*/
enum op Compare(const char *s1, const char *s2)
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


#include <stdlib.h> /*for exit*/
#include <stdio.h>	/*for printf, files*/
#include <unistd.h>	/*for */
#include <string.h>	/*for strcmp*/

/*usued for error checking*/
enum op {success = 0, fail = -1, nullpointer = 1, exit_program = 2}; 

enum op CompareChar(char *str, char ch);
enum op StrCmp(char *s1, char *s2);
enum op AlwaysTrue();

enum op RemoveFile(char *file_path);
enum op PreAppend(char *str, char *file_path);
enum op Append(char *str, char *file_path);
enum op Exit();

void GetInput(char *str);
size_t CountRows(char *file_path);


/*-------------------------------------------------------------------------*/

int main()
{	
	/*strings for user input*/
	char string[256];
	char file_path[256];
			
	/*file path input*/
	printf("\nPlease enter the file path\n");
	GetInput(file_path);
	
	/*command input*/
	printf("\nPlease enter a command\n");
	GetInput(string);
		
	/*call function*/
	
	
		
	return 1;
}



/*-------------------------------------------------------------------------*/


/*gets input from user, placing '\0' when user presses 'ENTER' */
void GetInput(char *str)
{
	char ch = getc(stdin);
	size_t i = 0;
	
	while('\n' != ch)
	{
		str[i] = ch;
		ch = getc(stdin);
		++i;;
	}
	str[i] = '\0';
	
	return;
}


/*-------------------------------------------------------------------------*/


/*	Removes the Log file	*/
enum op RemoveFile(char *file_path)
{
	if(remove(file_path) == 0)
	{
		return success;
	}
	
	return fail;
}

/*-------------------------------------------------------------------------*/

/*	Program Exits	*/
enum op Exit()
{
	return exit_program;
}

/*-------------------------------------------------------------------------*/

/*	Function appends to the End of the file	*/
enum op Append(char *str, char *file_path)
{
	
	/*create file pointer and open it in append and read mode*/
	FILE *file_pointer;
 	file_pointer = fopen(file_path, "a+");
 	
 	if(NULL == file_pointer)
 	{
 		return fail;
 	}

	/*writes string to the file pointer and then starts a new line*/
	fputs(str, file_pointer);
	fputc('\n',file_pointer);
	
	/*closes the file*/
	fclose(file_pointer);

	return success;
}

/*-------------------------------------------------------------------------*/

/*	Counts number of lines in the file	*/
size_t CountRows(char *file_path)
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

/*	Function appends to the beginning of the file	*/
enum op PreAppend(char *str, char *file_path)
{
	char ch = 0;
	
	/*opening file & temp-file and initializing their pointers*/
	FILE *file_pointer = fopen(file_path, "r");
	FILE *temp_file_pointer = fopen("temp.txt", "w");
	if(NULL == file_pointer || NULL == temp_file_pointer)
	{
		return nullpointer;
	}
	
	/*copying original file to temp file, while original file not ended*/
	ch = fgetc(file_pointer); 
    while(0 == feof(file_pointer))
    { 
        fputc(ch, temp_file_pointer); 
        ch = fgetc(file_pointer); 
    } 
	
	/*closing files*/
	fclose(file_pointer);
	fclose(temp_file_pointer);
	
	/*writing new str to original (deletes old data)*/
    file_pointer = fopen(file_path, "w");
    fputs(str, file_
    pointer);
    fputc('\n', file_pointer);	
	fclose(file_pointer);
	
	/*opening original again in append mode */
    file_pointer = fopen(file_path, "a");
    temp_file_pointer = fopen("temp.txt", "r");
	
	/*appending back from temp to original*/	
	ch = fgetc(temp_file_pointer); 
    while(0 == feof(temp_file_pointer))
    { 
        fputc(ch, file_pointer); 
        ch = fgetc(temp_file_pointer); 
    } 
	
	/*closing files*/
	fclose(file_pointer);
	fclose(temp_file_pointer);
	
	/*removing temp file*/
	remove("temp.txt");
	
	return 0;
}

/*-------------------------------------------------------------------------*/

/*Compares first char of str with ch*/			
enum comp_t Compare(char *str, char ch)
{
	if(ch == *str)
	{
		return success;
	}	
	
	return fail;
}

/*compares 2 strings*/
enum op StrCmp(char *s1, char *s2)
{
	if(0 == strcmp(s1, s2))
	{
		return success;
	}
	
	return fail;
}

/*always return success*/
enum op AlwaysTrue()
{
	return success;
}

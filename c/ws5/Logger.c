#include <stdlib.h> /*for exit*/
#include <stdio.h>	/*for printf, files*/
#include <unistd.h>	/*for */
#include <string.h>	/*for strcmp*/

/*amount of tests for arr of structs*/
#define AMOUNT_OF_ACTIONS 5

#define MAX_STR_SIZE 256

/*enum used for error checking*/
enum op {success = 0, fail = -1, exit_program = 1, file_fail = 2}; 

/*defining function pointers for struct*/
typedef enum op (*compfunc)();
typedef enum op (*actionfunc)();

/*defining struct*/
typedef struct _mystruct
{
	char *input; 
	compfunc compare;
	actionfunc action;
	
} CHECK;

/*compare funcs*/
enum op CompareChar(char *s1, char *ch);
enum op StrCmp(char *s1, char *s2);
enum op AlwaysTrue();

/*action funcs*/
enum op RemoveFile(char *file_path);
enum op PreAppend(char *file_path, char *str);
enum op Exit();
enum op Append(char *file_path, char *str);
enum op CountRows(char *file_path);

/*helper funcs*/
void GetInput(char *str);

/*exit and fail flag*/
size_t g_flag_exit = 0;
size_t g_flag_file_fail = 0;

/*-------------------------------------------------------------------------*/

int main()
{	
	/*arr counter*/
	size_t arr_c = 0;
		
	/*strings for user input*/
	char input[MAX_STR_SIZE];
	char file_path[MAX_STR_SIZE];
	
	FILE *file_pointer = NULL;
	
	/*array of structs declaration*/
	CHECK array[AMOUNT_OF_ACTIONS];
		
	/*
	assignment according to: 			
	array[0] - preappend
	array[1] - remove
	array[2] - exit
	array[3] - count;			
	array[4] - append
	*/
	
	/*structs definition*/
	array[0].input = "<";
	array[0].compare = CompareChar;
	array[0].action = PreAppend;
	
	array[1].input = "-remove";
	array[1].compare = StrCmp;
	array[1].action = RemoveFile;
	
	array[2].input = "-exit";
	array[2].compare = StrCmp;
	array[2].action = Exit;
	
	array[3].input = "-count";
	array[3].compare = StrCmp;
	array[3].action = CountRows;
	
	array[4].input = NULL;
	array[4].compare = AlwaysTrue;
	array[4].action = Append;
			
	/*file path input*/
	printf("\nPlease enter the file path\n");
	GetInput(file_path);
	
	file_pointer = fopen(file_path, "w");
	fclose(file_pointer);
	
	/*general loop untill user types -exit*/	
	while(0 == g_flag_file_fail && 0 == g_flag_exit)
	{		
		/*command input*/
		printf("\nPlease enter a command\n");
		GetInput(input);
		
		/*zero arr counter*/
		arr_c = 0;
		
		/*array loop*/
		while(arr_c < AMOUNT_OF_ACTIONS)
		{	
			if(success ==  array[arr_c].compare(input, array[arr_c].input))
			{
				array[arr_c].action(file_path, input);
				break;
			}
									
			++arr_c;
		}				
	}
		
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
		++i;
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
	g_flag_exit = 1;
	return success;
}

/*-------------------------------------------------------------------------*/
/*	Function appends to the End of the file	*/
enum op Append(char *file_path, char *str)
{
	
	/*create file pointer and open it in append and read mode*/
	FILE *file_pointer;
 	file_pointer = fopen(file_path, "a+");
 	
 	if(NULL == file_pointer)
 	{
 		return file_fail;
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
enum op CountRows(char *file_path)
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
	
	printf("\nThe number of rows in the file is: %ld.\n",rows);	

	fclose(file_pointer);
	
	return success;
}


/*-------------------------------------------------------------------------*/
/*	Function appends to the beginning of the file	*/
enum op PreAppend(char *file_path, char *str)
{
	char ch = 0;
		
	/*opening file & temp-file and initializing their pointers*/
	FILE *file_pointer = fopen(file_path, "r");
	FILE *temp_file_pointer = fopen("temp.txt", "w");

    /*check if both files opened, if not, close and ret*/
	if(NULL == file_pointer || NULL == temp_file_pointer)
	{
		fclose(temp_file_pointer);
		fclose(file_pointer);
		return file_fail;
	}
	
	/*ignore first '<' char*/
	++str;
	
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
   
	/*check if file opened, if now return (before both files closed)*/
    if(NULL == file_pointer)
	{
		return file_fail;
	}
	
    fputs(str, file_pointer);
    fputc('\n', file_pointer);	
	fclose(file_pointer);
	
	/*opening original again in append mode */
    file_pointer = fopen(file_path, "a");
    temp_file_pointer = fopen("temp.txt", "r");
   
    /*check if both files opened, if not, close and ret*/
    if(NULL == file_pointer || NULL == temp_file_pointer)
	{
		fclose(temp_file_pointer);
		fclose(file_pointer);
		return file_fail;
	}
	
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
enum op CompareChar(char *str, char *ch)
{
	if(*ch == *str)
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

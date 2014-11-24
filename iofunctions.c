#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

/**
*
*NAME:  Benjamin Chi
*
*CLASS:  ICS 212
*
*DESCRIPTION:  Read/write plain text functions
*
**/

int readfile(char name[], char address[], int *yob, char telno[], char filename[], struct record **start);
int writefile(struct record **start, char filename[]);
void getSubstring(char[], char[]);
FILE *filein;
FILE *fileout;

/**
* This method reads in the records.txt file, forms records out of them,
* and inserts them into the linked list.
**/
int readfile(char name[], char address[], int *yob, char telno[], char filename[], struct record **start)
{

	/* Initialize variables */
	char line[100];
	line[0] = '\0';
	int colCount = 0;
	int intchar = 0;
	char nextchar[2];
	char yearofbirth[15];
    int counter = 0;
	
	/* Open records.txt */
	filein = fopen(filename, "r");
	
		/* The file does not exist */
		if(!filein)
			return 1;
		
		/* Load contents into struct account */
		while(intchar != -1)
		{
			/* Each column represents a field.  End the entry after the last column. */
			while(colCount < 4)
			{
			
			/* Read in the data as an int */
			intchar = fgetc(filein);
			
				/* checks for EOF */
				if(intchar == -1)
				{
					break;
				}
								
				/* Copies each character 1 at a time */
				else
				{
					/* Convert the int to a char and store it */
					nextchar[0] = (char)intchar;
					nextchar[1] = '\0';
					
					/* If a column is encountered increment the counter */
					if(nextchar[0] == '|')
						colCount++;
					
					/* If the character is a newline skip it */
					if(intchar == 10)
						continue;
					
					/* If not add it to the string line */
					else
						strcat(line, nextchar);
				}
                
                /* EOF has been reached */                
				if(intchar == -1)
					break;
			}
            
            /* Reset the column counter for the next record */
            colCount = 0;
            
            /* EOF has been reached */
			if(intchar == -1)
				break;
                        
			/* Gets the field for name */
			getSubstring(name, line);
            
			/* Gets the field for address */
			getSubstring(address, line);
			
			/* Gets the field for yob */
			getSubstring(yearofbirth, line);
			*yob = atoi(yearofbirth);
			memset(yearofbirth, 0, 15);	
            
			/* Gets the field for telno */
			line[strlen(line)-1] = 0;
            
            /* Copy the rest of the line to the phone number */
            strcpy(telno, line);
    		
    		/* Add the record to the linked list */
            addRecord(start, name, address, *yob, telno);
            
            counter++;
            
			/* Clears line */
			memset(line, 0, 100);
            
        }
		
        /* Print the number of records retrieved */
        printf("\n%d%s\n", counter, " records retrieved.");
    
		/* Success!  */
		fclose(filein);
		return 0;
}

/**
* writefile is called after the program is done.  It takes the linked list
* and writes them out to the records.txt file before exiting.  
**/
int writefile(struct record **start, char filename[])
{
	/* Initialize variables */
	char line[100];
	char yearofbirth[15];
	struct record *curr;
	curr = (*start);
	line[0] = '\0';
	
	fileout = fopen(filename, "w");

	/* Iterate through the linked list */
	while(curr != NULL)
	{
		/* Copy name to line string */
		strcat(line, curr -> name);
		strcat(line, "|");
		
		/* Copy address to line string */
		strcat(line, curr -> address);
		strcat(line, "|");
	
		/* Copy year of birth to line string */
		snprintf(yearofbirth, 5, "%d", curr -> yearofbirth);
		strcat(line, yearofbirth);
		strcat(line, "|");
	
		/* Copy telelphone number to line string */
		strcat(line, curr -> telno);
		strcat(line, "|\n");
		
		/* Copy line string to file */
		fputs(line, fileout);
		
		/* Reset the line to store the next record */
		memset(line, 0, 100);
		
		curr = curr -> next;
	}

	fclose(fileout);
    
    return 0;
}

/**
* getSubstring takes an array of chars (line) and
* cuts off the first entry signified by a pipe.
* It then puts that sub array into substring.
**/
void getSubstring(char substring[], char fullstring[])
{
	char tempstring[100];
	int position;
	
	/* Finds the first pipe in the line */
	char *result = strstr(fullstring, "|");
	position = result - fullstring;
	
	/* Copies first field into substring(name, accountno, balance) and adds a null terminator  */
	strncpy(substring, fullstring, position);
	substring[position] = '\0';
	
    
	/**
	Removes the first field of fullstring/line 
	and moves the rest of the characters to the beginning
	**/
    
	memmove(tempstring, result+1, strlen(fullstring)-position);
	memset(fullstring, 0, 100);
	strncpy(fullstring, tempstring, strlen(tempstring));
}
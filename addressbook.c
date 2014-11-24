#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addressbook.h"
#include "record.h"

/**
*
*NAME:  Benjamin Chi
*
*HOMEWORK:  3
*
*CLASS:  ICS 212
*
*DATE:  9/21/2013
*
*DESCRIPTION:  A database to store and modify records 
*
**/

void getfield(char[], char[], char[]);

int debug=0;

/**
* The main method is primarily responsible for menu 
* navigation and variable initialization.
**/
main(int argc, char *argv[])
{
	/* Set variables */
	char menunum[2];
	int menunumi = 1;
	int clear;
	char name[25];
	char address[80];
	int yearofbirth;
	int *pyearofbirth = &yearofbirth;
	char phonenum[15];
	int returnedfunc;
	struct record *start = NULL;
    int test;
    
    /* Read in the text file database of records */
    readfile(name, address, pyearofbirth, phonenum, "records.txt", &start);
    
	/* Sets debug mode to on */
	if(argc > 1)
	{
		if(!strcmp(argv[1], "debug"))
		debug = 1;
		
		else{
		printf("%s\n", "Your entry was invalid.  Debug mode not activated.");
		}
	}
	
	/* Loops through options until the user quits */
	while(menunumi != 6)
	{
		printf("\n%s\n","1. Add new record");
		printf("%s\n","2. Modify record");
		printf("%s\n","3. Print info for a record");
		printf("%s\n","4. Print info for all records");
		printf("%s\n","5. Delete a record");
		printf("%s\n","6. Quit");
		printf("Please enter a number from 1-6 to select a choice from the menu: ");
		
		/* Get menu number */
		scanf("%d", &menunumi);
		
		/* Clear the output buffer */
		fflush(stdout);
		
		if(menunumi < 6 || menunumi > 0)
		{
			switch(menunumi)
			{
			
			/* Add new record */
			case 1:
				
				/* Cleans address and uses getfield to set the variables */
                memset(address, 0, 80);
				getfield(name, address, phonenum);
				
				/* Prints the information and adds the new record to the list */
				printf("Please enter year of birth:");
				scanf("%5d", pyearofbirth);
				returnedfunc = addRecord(&start, name, address, yearofbirth, phonenum);
				
				break;
				
			/* Modify record */
			case 2:
				
				/* No records available */
				if(start == NULL)
				{
					printf("No records available to modify.\n");
				}
				
				/* Cleans address and uses getfield to set the variables */
				else{
					memset(name, 0, 25);
					memset(address, 0, 80);
					getfield(name, address, phonenum);
					returnedfunc = modifyRecord(start, name, address, phonenum);
				}
				break;
				
			/* Print info for a record */
			case 3:
								
				/* No records available */
				if(start == NULL)
				{
					printf("No records available.\n");
				}
				
				else
				{
					/* Cleans address and uses getfield to set the variables */
					memset(name, 0, 25);

					printf("Please enter name:");
				
					/* Used to clear the input buffer so the newline is not entered in the next field */
					getchar() != '\n';
				
					fgets(name, 25, stdin);
				
					/* Cuts off the newline at the end of name */
					strtok(name, "\n");
				
					returnedfunc = printRecord(start, name);
				}
				break;
			
			/* Print info for all records */
			case 4:
				printAllRecords(start);
				break;
				
			/* Delete a record */
			case 5:
			
				if(start == NULL)
				{
					printf("No records available.\n");
				}
				
				else
				{
					/* Cleans address and uses getfield to set the variables */
					memset(name, 0, 25);
					printf("Please enter name:");
				
					/* Used to clear the input buffer so the newline is not entered in the next field*/
					getchar() != '\n';
					fgets(name, 25, stdin);
	
					/* Cuts off the newline at the end of name */
					strtok(name, "\n");
				
					/*No records are in the data base */
					if(start == NULL)
						printf("No records available to delete\n");
				
					else
						returnedfunc = deleteRecord(&start, name);
				}
				break;
			}
		}
		
		/* If user input is an invalid number give an error message */	
		if(menunumi <= 0 || menunumi >= 7)
		{
			printf("%s\n","Invalid.  Please enter a number between 1 and 6");
		}
		
		/* User quits */
		if(menunumi == 6)
		{
			printf("%s\n", "Goodbye!");
		}
	}
    
    /* The program is ending so write all the records to the text file */
    writefile(&start, "records.txt");
}

/**
* This function is called when the user needs to add or modify a record.
* It only takes the name, address, and phone number.  Birthdate is added in main.
* It takes input for each field and stores them in the global variables.
* addRecord and modifyRecord are responsible for actually putting the record
* in the list.
**/
void getfield(char name[], char address[], char phonenum[])
{
	if(debug == 1)
	{
		printf("\n%s\n", "Function called: getfield()");
		printf("%s\n\n", "Arguments passed: name char[], address char[], phonenum char[]");
	}
	
	/* Enter name */
	printf("Please enter a name:");
	
	/* Used to clear the input buffer so the newline is not entered in the next field*/
	getchar() != '\n';
	fgets(name, 25, stdin);
	
	/* Cut off the newline at the end of name */
	strtok(name, "\n");
	
	/* Reads an address one char at a time */
	printf("Please enter an address.  When finished, type a '!' and press enter: ");
	
	/* A test character used to identify the '!' which marks the end of the entry */
	char testchar[2] = {'z', '\0'};

	while(testchar[0] != '!')
    {
    
    	/* Read the input in one character at a time to look for the '!' */
		testchar[0] = fgetc(stdin);

		if(testchar[0] != '!'){
        	int len = strlen(address);
			address[len] = testchar[0];
        	address[len + 1] = '\0';
        }
	}

	/* Get the phone number */
	printf("Please enter telephone #:");
	
	/* Used to clear the input buffer so the newline is not entered in the next field*/
	getchar() != '\n';
	fgets(phonenum, 15, stdin);
	
	/* Cut off the newline at the end of name */
    strtok(name, "\n");

    phonenum[strlen(phonenum)-1] = '\0';
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

struct record;

extern int debug;


/**
* addRecord takes the parameters then stores them in the record struct.
* It also builds a linked list with each record appropriately.
* The first parameter **start refers to the head of the linked list.
**/
int addRecord(struct record **start, char name[], char address[], int yearofbirth, char phonenum[])
{	
    /* If the head is empty make the new record the head */
    if((*start) -> name == NULL)
	{
		/* Create a new struct and make space for it */
		struct record *newrec;
		newrec = malloc(sizeof(*newrec));
		
		/* Set the new struct to the head of the list */
		(*start) = newrec;
		
		/* Copy all the parameters to the new struct */
		strcpy((*start) -> name, name);
		strcpy((*start) -> address, address);
		(*start) -> yearofbirth = yearofbirth;
		strcpy((*start) -> telno, phonenum);
	}
	
	/* The linked list is not empty */
	else
	{
	
		/* Make a new record that represents the head of the list */
		struct record *temp;
		temp = (*start);
		
		/* Iterate through the list until you hit the end */
		while(temp -> next != NULL)
		{
			temp = temp -> next;
		}
		
		/* Make space for new record */
		struct record *newrec;
		newrec = malloc(sizeof(*newrec));
	
		/* Make the new record the new end of the list */
		temp -> next = newrec;
	
		/* Copy all the parameters to the new struct */
		strcpy(newrec -> name, name);
		strcpy(newrec -> address, address);
		newrec -> yearofbirth = yearofbirth;
		strcpy(newrec -> telno, phonenum);
	}
    
    printf("\nRecord added successfully!\n");
    
    /* Print the parameters if debug mode is on */
	if(debug == 1)
	{
		printf("\n%s\n", "Function called: addRecord()");
		printf("Arguments passed: name= %s, address= %s, yearofbirth= %d, phonenum= %s\n", name, address, yearofbirth, phonenum);
	}
    
return 0;
}

/**
* printRecord displays the information for a particular record
**/
int printRecord(struct record *start, char name[])
{
	/* Initialize variables */
    int valid = 0;
    struct record *temp;
    temp = start;
    
    /* There are no records in the database */
    if(temp == NULL)
    {
        valid = 1;
    }
    
    /* If there are records iterate through them till the name matches */
    else
    {
        /* Iterate through records */
        while(strcmp(temp -> name, name) != 0)
        {
            temp = temp -> next;
			
			/* The end of the list has been reached and still no matches */
            if(temp == NULL)
            {
                valid = 1;
                break;
            }
        }
    }
    
    /* If the record is not in the database print an error */
    if(valid == 1)
        printf("%s\n", "Record does not exist.");
    
    /* Print record information */
    else
    {
		printf("\nRecord name: %s\n", temp -> name);
		printf("%s's address: %s\n", temp -> name, temp -> address);
		printf("%s's year of birth: %d\n", temp -> name, temp -> yearofbirth);
		printf("%s's phone#: %s\n", temp -> name, temp -> telno);
    }
    
    /* Print the parameters if debug mode is on */
	if(debug == 1)
	{
		printf("\n%s\n", "Function called: printRecord()");
		printf("Arguments passed: name= %s\n", name);
	}
	
return 0;
}

/**
* modifyRecord changes the name, address, and phone number of the
* record to the new parameters given.
**/
int modifyRecord(struct record *start, char name[], char address[], char phonenum[])
{
	/* Initialize variables */
    int valid = 0;
    struct record *temp;
    temp = start;
    
    /* Iterate through records */
    while(strcmp(temp -> name, name) != 0)
    {
    temp = temp -> next;
    
		/* The end of the list has been reached and still no matches */
        if(temp == NULL)
        {
        valid = 1;
        break;
        }
    }

    /* If the record is not in the database print an error */
    if(valid == 1)
    printf("%s\n", "Record does not exist.");
           
    /* Replace record entries with parameters*/
    else
    {
		strcpy(temp -> name, name);
		strcpy(temp -> address, address);
		strcpy(temp -> telno, phonenum);
		printf("%s\n", "Record modified successfully!");
    }

    /* Print the parameters if debug mode is on */
	if(debug == 1)
	{
		printf("\n%s\n", "Function called: modifyRecord()");
		printf("Arguments passed: name= %s, address= %s, phonenum= %s\n", name, address, phonenum);
	}

return 0;
}

/**
* printAllRecords iterates through the linked list and
* prints each record's information
**/
void printAllRecords(struct record *start)
{
	/* Initialize variables */
    int valid = 0;
    struct record *temp;
    temp = start;
    
    /* Iterate through all the records and print them out */
    while(temp != NULL){
        printf("\nRecord name: %s\n", temp -> name);
        printf("%s's address: %s\n", temp -> name, temp -> address);
        printf("%s's year of birth: %d\n", temp -> name, temp -> yearofbirth);
        printf("%s's phone#: %s\n", temp -> name, temp -> telno);
        
        temp = temp -> next;
        valid = 1;
    }
    
    /* There are no records in the database */
    if(valid == 0){
        printf("%s\n", "No records available");
    }
    
    /* Print the parameters if debug mode is on */
	if(debug == 1)
	{
		printf("\n%s\n", "Function called: printAllRecords()");
	}

}

/**
* deleteRecord removes a record that matches the name in the parameter
**/
int deleteRecord(struct record **start, char name[])
{
	/* Initialize variables */
    int valid = 0;
    int count = 0;
    
    /* Define a pointer to start’s value (what start’s pointing to) called temp */
    struct record *temp = *start;
    
    /* while start is the target record make start the next record */
    while(strcmp((*start) -> name, name) == 0){
		*start = (*start) -> next;
		
		/* Delete the record*/
		free(temp);
		temp = (*start);
	
		valid = 1;
		count++;
		
			if(temp == NULL)
			break;
    }

    /* Make a second pointer that tails behind the first */
    struct record *temp2 = temp;
    
    /* Iterates through all the records*/
    while(temp != NULL){
        
        /* If the record matches, delete it */
        if(strcmp(temp -> name, name) == 0)
        {   
            /*End of list */
            if(temp -> next == NULL)
            {
            	/* Delete temp and reset temp and temp2 */
				free(temp);
				temp = NULL;
				temp2 = NULL;
            }
            
            /*Not the end of the list*/
            else
            {
				temp2 -> next = temp -> next;
				free(temp);
				temp = temp2;
            }
            
            valid = 1;
            count++;
        }
        
        /* Make temp2 point to temp (the record that follow it) */
        else
			temp2 = temp;
        
        /* The end of the list has been reached */
        if(temp == NULL)
        	break;
        
        /* Move to next record */
        temp = temp -> next;
    }
    
    /* Print an error message if the record is missing */
    if(valid == 0)
    	printf("\n%s\n", "Record does not exist");
    
    /* Print a success message */
    else
    	printf("\n%s%d%s\n", "Success! ", count, " record(s) deleted");

    /* Print the parameters if debug mode is on */
	if(debug == 1)
	{
		printf("\n%s\n", "Function called: deleteRecord()");
		printf("Arguments passed: name= %s\n", name);
	}
    
return 0;
}
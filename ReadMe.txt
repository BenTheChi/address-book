/**
*
*AUTHOR:  Benjamin Chi
*
*CLASS:  ICS 212
*
*PROGRAM NAME:  AddressBook.c
**/

DESCRIPTION

This is a basic address book implemented in C.  It stores the records in a .txt
file when the program is not running.  If the program is started and a records.txt
file is available it will load the information to the database.  It can add, delete, 
modify, and print records. The program has a debug feature that prints the parameters 
passed to functions to help determine if information is being stored correctly.

RUNNING THE PROGRAM

1. Make sure that it is properly compiled and linked by typing 'make' to run 
the makefile.

2.  Run the executable by typing './AddressBook.c'  If you would like to run
the program in debug mode type './AddressBook.c debug' instead.

KNOWN BUGS

Entering a non digit for 'year of birth' will result in a malfunction of the
input commands.


/**
* The struct that represents a record in the address book
**/

struct record
{
	char name[25];
	char address[80];
	int yearofbirth;
	char telno[15];
	struct record* next;
};
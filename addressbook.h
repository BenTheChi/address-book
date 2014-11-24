/**
* The various functions the address book uses
**/

struct record;

int addRecord(struct record **, char[], char[], int, char[]);
int printRecord(struct record *, char[]);
int modifyRecord(struct record *, char[], char[], char[]);
void printAllRecords(struct record *);
int deleteRecord(struct record **, char[]);
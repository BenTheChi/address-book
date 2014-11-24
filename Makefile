AddressBook: addressbook.o iofunctions.o addressbookfunc.o
	cc -o AddressBook addressbook.o iofunctions.o addressbookfunc.o

addressbookfunc.o: addressbookfunc.c record.h
	cc -c addressbookfunc.c

iofunctions.o: iofunctions.c record.h
	cc -c iofunctions.c

addressbook.o: addressbook.c record.h addressbook.h
	cc -c addressbook.c
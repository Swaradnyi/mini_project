project: check.o std.o 
	cc check.o std.o -o project
check.o: check.c miniproject.h
	cc -Wall -c check.c
std.o: std.c miniproject.h 
	cc -Wall -c std.c 



all: a3p2Client1 a3p2Client2 a3p2Server

a3p2Client1: a3p2Client1.c
	gcc -o a3p2Client1 a3p2Client1.c -lpthread -l sqlite3

a3p2Client2: a3p2Client2.c
	gcc -o a3p2Client2 a3p2Client2.c -lpthread -l sqlite3

a3p2Server: a3p2Server.c 
	gcc -o a3p2Server a3p2Server.c -lpthread -l sqlite3


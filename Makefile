server: server.o
	gcc -o server server.o

server.o: server.c
	gcc -ansi -pedantic-errors -Wall -c server.c



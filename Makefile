all: program

program: program.c
	gcc -g -Wall -pedantic -o program program.c

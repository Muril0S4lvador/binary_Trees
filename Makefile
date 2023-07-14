all:
	gcc -g -o main *.c
valg: all
	valgrind ./main < input.txt
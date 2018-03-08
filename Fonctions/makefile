test: test.o cryptmath.o
	gcc -o test test.o cryptmath.o

cryptmath.o: cryptmath.c
	gcc -o cryptmath.o -c cryptmath.c 

test.o: test.c cryptmath.h
	gcc -o test.o -c test.c
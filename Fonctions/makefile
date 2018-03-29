test: test.o cryptmath.o diffie-hellman.o
	gcc -o test test.o cryptmath.o

serveur.o: serveur.c
	gcc -o serveur.o -c serveur.c

client.o: client.c
	gcc -o client.o -c client.c

diffie-hellman.o: diffie-hellman.c cryptmath.h serveur.h client.h
	gcc -o diffie-hellman.o -c diffie-hellman.c

cryptmath.o: cryptmath.c cryptmath.h
	gcc -o cryptmath.o -c cryptmath.c 

test.o: test.c cryptmath.h diffie-hellman.h serveur.h client.h
	gcc -o test.o -c test.c
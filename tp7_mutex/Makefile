All : synchronisation clean

synchronisation.o : synchronisation.c
	gcc -c synchronisation.c

synchronisation : synchronisation.o
	gcc -lpthread -o synchronisation synchronisation.o

clean:
	rm *.o
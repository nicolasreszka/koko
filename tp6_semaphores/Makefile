all : first second third clean

first.o : first.c
	gcc -c first.c

first : first.o
	gcc -o first first.o

second.o : second.c
	gcc -c second.c

second : second.o
	gcc -o second second.o

third.o : third.c
	gcc -c third.c

third : third.o
	gcc -o third third.o

clean:
	rm *.o
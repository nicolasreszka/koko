All : shm_init clean

shm_init.o : shm_init.c
	gcc -c shm_init.c

shm_init : shm_init.o
	gcc -o shm_init shm_init.o

clean:
	rm *.o
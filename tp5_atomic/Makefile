All : shm_init shm_remove clean

shm_init.o : shm_init.c
	gcc -c shm_init.c

shm_init : shm_init.o
	gcc -o shm_init shm_init.o

shm_remove.o : shm_remove.c
	gcc -c shm_remove.c

shm_remove : shm_remove.o
	gcc -o shm_remove shm_remove.o

clean:
	rm *.o
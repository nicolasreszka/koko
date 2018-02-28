All : shm_init shm_remove shm_write shm_read clean

shm_init.o : shm_init.c
	gcc -c shm_init.c

shm_init : shm_init.o
	gcc -o shm_init shm_init.o

shm_remove.o : shm_remove.c
	gcc -c shm_remove.c

shm_remove : shm_remove.o
	gcc -o shm_remove shm_remove.o

shm_write.o : shm_write.c
	gcc -c shm_write.c

shm_write : shm_write.o
	gcc -o shm_write shm_write.o

shm_read.o : shm_read.c
	gcc -c shm_read.c

shm_read : shm_read.o
	gcc -o shm_read shm_read.o

clean:
	rm *.o
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define VMAX 5
#define INCREMENT_THREAD_NUMBER 3
#define RESET_THREAD_NUMBER 1

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int x = 0;

void* increment(void* thread_number) {
	pthread_mutex_lock(&lock);

	int i = *(int*) thread_number; 
	printf("increment%d : before x=%d\n", i+1, x);
	x++;
	printf("after x=%d\n", x);

	sleep(1);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

void* reset(void* thread_number) {
	pthread_mutex_lock(&lock);

	int i = *(int*) thread_number; 
	printf("reset%d : before x=%d\n", i+1, x);
	if (x >= VMAX) {
		x = 0;
	}
	printf("after x=%d\n", x);

	sleep(1);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	int i;
	pthread_t increment_thread[INCREMENT_THREAD_NUMBER];
	pthread_t reset_thread[RESET_THREAD_NUMBER];
	
	while (1) {
		for (i = 0; i < INCREMENT_THREAD_NUMBER; i++) {
			printf("--- this is increment%d ---\n", i+1);
			pthread_create(&increment_thread[i], NULL, increment, (void*)&i);
		}
		for (i = 0; i < RESET_THREAD_NUMBER; i++) {
			printf("=== this is reset%d ===\n", i+1);
			pthread_create(&reset_thread[i], NULL, reset, (void*)&i);
		}
		pthread_join(increment_thread[0], NULL);
	}

	return EXIT_SUCCESS;
}
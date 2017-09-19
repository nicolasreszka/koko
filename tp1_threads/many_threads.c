#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/types.h"
#include "sys/syscall.h"

pid_t gettid(void) {
	return syscall(__NR_gettid);
}

void* start_routine(void *arg) {
	printf("Thread number %d :\n", *((int*) arg));
	printf("PID : %d\n", getpid());
	printf("TID : %d\n", gettid());
	printf("PTHID : %d\n", pthread_self());
}

int main(int argc, char** argv) {
	pthread_t thread;

	for (int i = 0; i < 3; i++) {
		pthread_create(&thread, NULL, start_routine, &i);
		pthread_join(thread, NULL);
	}
	sleep(10);

	return EXIT_SUCCESS;
}
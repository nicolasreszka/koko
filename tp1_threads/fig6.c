#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"

int count = 2;

void dec(void * count) {
	count--;
	printf("count = %d\n", count);
	return;
}

void inc(void * count) {
	count++;
	printf("count = %d\n", count);
	return;
}

int main(int argc, char** argv) {
	
	pthread_t th;
	pthread_t thc;
	pthread_create(&th, NULL, inc, NULL);
	pthread_create(&thc, NULL, dec, NULL);
	pthread_join(th, NULL);
	pthread_join(thc, NULL);
	
	return EXIT_SUCCESS;
}
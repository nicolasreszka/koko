#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define RMAX 5

pthread_mutex_t mutexReader = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condWriter = PTHREAD_COND_INITIALIZER;

int numberReader=0, communValue = 0;

void* routine_reader(void* arg) {
	struct timespec waitTime = {0,500000000};
	int i = *(int*)arg;

	while(1) {
		pthread_mutex_lock(&mutexReader);
		numberReader++;
		pthread_mutex_unlock(&mutexReader);
		printf("\treader %2d: val=%d\n", i, communValue);
		numberReader--;
		if(numberReader ==0) {
			pthread_cond_signal(&condWriter);
		}
		nanosleep(&waitTime, NULL);
	}
}

void* routine_writer(void* arg) {
	struct timespec waitTime = {1,123456789};
	int i = *(int*)arg;

	while(1) {
		pthread_mutex_lock(&mutexReader);
		if(numberReader != 0) {
			pthread_cond_wait(&condWriter, &mutexReader);
		}
		communValue++;
		sleep(1);
		communValue++;
		printf("writer\t%d: val=%d\n", i, communValue);
		pthread_mutex_unlock(&mutexReader);
		nanosleep(&waitTime, NULL);
	}
}


int main(void) {
	pthread_t thWriter;
	pthread_t thReader[RMAX];

	int x=1;
	int numberThread[RMAX];
	pthread_create(&thWriter, 0, routine_writer, &x);
	for(int i=0; i<RMAX; i++) {
		numberThread[i] = i;
		pthread_create(&thReader[i], 0, routine_reader, &numberThread[i]);
	}

	pthread_join(thWriter, NULL);	
	for(int i=0; i<RMAX; i++) {
		pthread_join(thReader[i], NULL);
	}



	return EXIT_SUCCESS;
}
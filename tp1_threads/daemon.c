/* "L'exemple typique du daemon" vu en TD */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

pid_t gettid(void){
	return syscall(__NR_gettid);
}

void* start_routine(void* arg){
	int x = *(int*) arg;
	printf("x = %c, PID = %d, TID = %d, PTHID = %lu\n", x, getpid(), gettid(), pthread_self());
	sleep(5);
	pthread_exit(NULL);
}

int get_one_letter(void) {
	int c, first;
	first = c = getchar();
	while(c != '\n' && c != EOF){
		c = getchar();
	}
	return(first);
}

int main(void){
	int x;
	pthread_t thread;
	
	while (1) {
		x = get_one_letter();
		pthread_create(&thread, NULL, start_routine, &x);
		pthread_join(thread, NULL);
	}
 
	return EXIT_SUCCESS;
}
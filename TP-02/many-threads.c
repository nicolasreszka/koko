#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>


pid_t gettid(void)
{
	return syscall(__NR_gettid);
}

void * start_routine(void * arg)
{

	int x = *(int*)arg;

	while(1)
	{

		printf("threadnum = %d \n PID = %d \n TID = %d \n PTHID = %lu \n",x,getpid(),gettid(),pthread_self());
		sleep(5);

	}

}

void main(void)
{
	int i,j;
	pthread_t th[3];
	for ( i=0 ; i<3 ; i++)
	{
		pthread_create(&th[i],NULL,start_routine,&i);
	}
	for ( j=0 ; j<3 ; j++)
	{
		pthread_join(th[j],NULL);
	}
}

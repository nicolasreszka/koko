#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;

void * first(void * arg)
{
	int i;
	const char name[5] = { 'f' , 'i' , 'r' , 's' , 't'};
	printf("wait : %ld\n",((struct timespec*)arg)->tv_nsec);
	while ( 1 )
	{
		pthread_mutex_lock(&m1);
		for ( i = 0 ; i < 5 ; i++)
		{
			putchar(name[i]);
			printf("debug1\n");
			nanosleep((struct timespec*)arg,NULL);
			printf("debug2\n");
			fflush(0);
		}
		putchar(' ');
		pthread_mutex_unlock(&m2);
	}

}

void * second(void * arg)
{
	int i;
	const char name[6] = { 's' , 'e' , 'c' , 'o' , 'n' , 'd'};
	while ( 1 )
	{
		pthread_mutex_lock(&m2);
		for ( i = 0 ; i < 6 ; i++)
		{
			putchar(name[i]);
			nanosleep((struct timespec*)arg,NULL);
			fflush(0);
		}
		putchar(' ');
		pthread_mutex_unlock(&m3);
	}

}

void * third(void * arg)
{
	int i;
	const char name[5] = { 't' , 'h' , 'i' , 'r' , 'd'};
	while ( 1 )
	{
		pthread_mutex_lock(&m3);
		for ( i = 0 ; i < 5 ; i++)
		{
			putchar(name[i]);
			nanosleep((struct timespec*)arg,NULL);
			fflush(0);
		}
		putchar(' ');
		pthread_mutex_unlock(&m1);
	}

}




void main(int argc,char** argv)
{
	pthread_t th[3];
	long data[3] = {strtol(argv[1],NULL,0),strtol(argv[2],NULL,0),strtol(argv[3],NULL,0)};
	
	struct timespec s1 = { 0 , data[0]*1000000 };
	struct timespec s2 = { 0 , data[1]*1000000 };
	struct timespec s3 = { 0 , data[2]*1000000 };
	pthread_mutex_lock(&m2);
	pthread_mutex_lock(&m3);
	pthread_create(&th[0],NULL,first,&s1);
	
	pthread_create(&th[1],NULL,second,&s2);
	printf("ORDRE");
	pthread_create(&th[2],NULL,third,&s3);
}
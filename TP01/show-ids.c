#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main(void)
{
	int pid;
	printf("pid = %d \n",getpid());
	printf("pgid = %d \n",getpgid(getpid()));
	printf("sid = %d \n",getsid(getpid()));
	
}
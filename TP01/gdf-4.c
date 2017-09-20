#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int pid1;
	while(1)
	{
		pid1 = fork();
		if(pid1==-1)perror("fork err");
		else if ( pid1 == 0)
		{
			printf("id : %d \n",getpid());
			break;
		}
		sleep(1);
	}
}
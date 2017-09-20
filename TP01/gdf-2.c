#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int pid1,pid2,qelq;
	pid1=fork();
	printf("id : %d \n",getpid());
	if( pid1 == -1 )
	{
		printf("erreur au fork 1");
		return -1;
	}
	else if ( pid1 == 0)
	{
		pid2=fork();
		printf("id : %d \n",getpid());
		if ( pid2 == -1 )
		{
			printf("erreur au fork 2");
			return -1;
		}
		else if ( pid2 == 0 )
		{

			scanf("%d",&qelq);

		}	
	}

	else
	{
		while(1);
	}

}
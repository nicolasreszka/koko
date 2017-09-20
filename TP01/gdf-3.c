#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int pid1,pid2;
	pid1 = fork();
	printf("pid : %d \n",pid1);
	if ( pid1 == -1 )
	{
		perror("Erreur au fork 1");
		return -1;
	}
	else if (pid1 == 0)
	{
		while(1);
	}
	else
	{
		pid2 = fork();

		if ( pid2 == -1)
		{
			perror("Erreur au fork 2");
			return -1;
		}
		else if (pid2 > 0)
		{
			while(1);
		}
	}
}
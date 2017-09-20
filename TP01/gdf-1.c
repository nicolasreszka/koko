#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int u;
	u=fork();
	if(u == -1)
		{
			printf("erreur fork1");
			exit(-1);
		}

	printf("Id du proc : %d\n",getpid());
	while(1);
}
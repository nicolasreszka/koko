#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(void)
{
  int pid;
  pid = fork();
  if ( pid == -1 )
    {
      perror("Erreur lors du fork.");
      exit(-1);
    }
  
  else if ( pid > 0 )
    {
      while(1)
	{
	  printf("Je suis le père et je ne sait pas si mon fils est mort.\n");
	  sleep(3);
	}
    }
  else if ( pid == 0 )
	 {
	   exit(0);
	 }
}

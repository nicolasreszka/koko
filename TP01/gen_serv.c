#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(void)
{
  int pid;
  char lettre;
  while(1)
    {
      printf("Veuillez rentrer une lettre\n");
      scanf("%c",&lettre);
      getchar();
      pid = fork();
      if ( pid == -1 )
	{
	  perror("Erreur lors du fork.");
	  exit(-1);
	}
      else if ( pid == 0 )
	{
	  printf("La touche que vous avez pressee est %c\n",lettre);
	  exit(0);
	}
      else if ( pid > 0 )
	{
	  sleep(1);
	}
    }
}

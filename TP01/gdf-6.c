#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int cnt = 2;

void main(void)
{
  int pid01,pid02;
  pid01 = fork();
  if ( pid01 == -1 )
    {
      perror("Erreur lors du fork numero 1");
      exit(-1);
    }
  else if ( pid01 == 0 )
    {
      cnt++;
      printf("%d : addr(cnt)=%p cnt=%d \n",getpid(),&cnt,cnt);
      exit(0);
    }
  else if ( pid01 > 0 )
    {
      pid02 = fork();
      if ( pid02 == -1 )
	{
	  perror("Erreur lors du fork numero 2");
	  exit(-1);
	}
      else if ( pid02 == 0 )
	{
	  cnt--;
	  printf("%d : addr(cnt)=%p cnt=%d \n",getpid(),&cnt,cnt);
	  exit(0);
	}
      else if ( pid02 > 0 )
	{
	  printf("%d : addr(cnt)=%p cnt=%d \n",getpid(),&cnt,cnt);
	}
    }
}

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main(void)
{
  while(1)
    {
      printf("Coucou, ici %d \n",getpid());
      sleep(1);
    }
}

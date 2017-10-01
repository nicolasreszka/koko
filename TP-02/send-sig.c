#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void main(void)
{
  int k,l;
  while(1)
    {
      printf("Veuillez rentrer k : ");
      scanf("%d",&k);
      printf("Veuillez rentrer l : ");
      scanf("%d",&l);
      kill(l,k);
    }
}

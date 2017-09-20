#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(void)
{
  int sid;
  printf("Sid avant la creation de la session : %d \n",getsid(getpid()));
  sid = setsid(); /* Attention risque de ne pas fonctionne lorsque user non root */
  if ( sid == -1 )
    {
      perror("Erreur lors de la creation de la nouvelle session.");
      exit(-1);
    }
  printf("Sid apres la creation de la session : %d \n",getsid(getpid()));
}

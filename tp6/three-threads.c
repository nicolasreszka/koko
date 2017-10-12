#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<pthread.h>

pid_t gettid(void){
  return syscall(__NR_gettid);
}

void* first(void* d){
  char tab[6] = {"first "};
  int i = 0;

  while(1){
    putchar(tab[i]);
    fflush(NULL);

    if(i < 5)
      i++;
    else
      i = 0;
    usleep(atoi(d));
  }
}

void* second(void* d){
  char tab[7] = {"second "};
  int i = 0;

  while(1){
    putchar(tab[i]);
    fflush(NULL);

    if(i < 6)
      i++;
    else
      i = 0;
    usleep(atoi(d));
  }
}

void* third(void* d){
  char tab[6] = {"third "};
  int i =0;

  while(1){
    putchar(tab[i]);
    fflush(NULL);

    if(i < 5)
      i++;
    else
      i = 0;
    usleep(atoi(d));
  }
}

/* Le but est de créer 3 threads qui lanceront chacun
 * une des fonctions ci-dessus */
int main(int argc, char** argv){
  if(argc < 4){
    printf("Usage : %s <delay> <delay> <delay>\n",argv[0]);
    return EXIT_FAILURE;
  }

  pthread_t th[3];

  /* On créer donc chaque thread en leur donnant l'adresse d'une
   * des fonctions et en assignant à chaque fonction l'argument
   * de la ligne de commande correspondant à la durée
   * pendant laquelle ils devront attendre entre chaque putchar */
  pthread_create(&th[0], NULL, &first, argv[1]);
  pthread_create(&th[1], NULL, &second, argv[2]);
  pthread_create(&th[2], NULL, &third, argv[3]);

  pthread_join(th[0], NULL);

  return EXIT_SUCCESS;
}

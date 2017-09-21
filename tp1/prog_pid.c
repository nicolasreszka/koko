#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
  int x = fork();

  if(x == 0){
    printf("Je suis le fils et mon pid est %d\n",getpid());
    printf("Celui de mon père est %d\n",getppid());
  } else if (x > 1) {
    printf("Je suis le père, le pid de mon fils est %d\n",x);
    printf("Mon pid est %d\n",getpid());
  } else {
    perror("Problème avec fork\n");
    return EXIT_FAILURE;
  }

  sleep(10);
  return EXIT_SUCCESS;
}

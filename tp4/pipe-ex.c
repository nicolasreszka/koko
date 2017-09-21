#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char** argv[]){
  int y, x;
  int pp[2];
  int res = 1272;

  x = fork();

  if(x < 0){
    perror("Problème premier fork\n");
    return EXIT_FAILURE;
  }

  if(pipe(pp) == -1){ /* Usage de pipe puis traitement éventuel de l'erreur */
    perror("Problème pipe\n");
    return EXIT_FAILURE;
  } else {
    y = fork(); /* Les deux proc fork */

    if(y < 0){
      perror("Problème avec le second fork\n");
      return EXIT_FAILURE;
    } else if (y == 0){ /* Les fils gèrent le pipe */
      if(x == 0) {
        close(pp[1]); /* On close le canal d'écriture pour le lecteur */

        read(pp[0], &res, 4); /* On lit 4 octets depuis le canal read dans res */
        printf("%d", res);
        printf("\n");

        close(pp[0]); /* Close le canal de lecture pour terminer le pipe */
        return EXIT_SUCCESS;
      } else {
        close(pp[0]); /* On close le canal de lecture pour l'écrivain */
        write(pp[1], &res, 4); /* On écrit le contenu de res dans le canal write */
        close(pp[1]); /* Fermer le canal d'écriture pour avoir le EOF côté lecteur */
        wait(NULL);
        return EXIT_SUCCESS;
      }
    }
  }
}

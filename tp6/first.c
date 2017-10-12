#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void first(int d){
  char tab[6] = {"first "};
  int i = 0;
  
  while(1){
    putchar(tab[i]); // On écrit le i-ème caractère du tableau
    fflush(NULL); // On vide tous les buffers puisqu'il y a NULL en arg
    /* Si l'indice est inférieur à 5, alors on
     * est pas encore à la fin du tableau, donc 
     * il faut continuer de print le caractère suivant */
    if(i < 5)
      i++;
    else // Sinon, on retourne au début
      i = 0;
    usleep(d); // On dort pendant d microsecondes
  }
}

int main(int argc, char** argv){
  if(argc < 2){
    printf("Usage : %s <delay>\n", argv[0]);
    return EXIT_FAILURE;
  }

  first(atoi(argv[1]));

  return EXIT_SUCCESS;
}

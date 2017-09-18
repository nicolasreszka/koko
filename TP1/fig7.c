#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

/*
  But : apprendre les bases des Threads (fonctionnement, comment coder, etc).
  TP1, question 1, figure 7.
*/

int cnt = 2;
//On voit sur la feuille qu'avant tout processus
//On initialise une variable qui sera un compteur.


/* Fonction : gettid
 * Renvoie un pid_t, qui peut être lu comme un long int (%lu).
 * Cela permet de récupérer l'identifiant d'un thread.
 * De la même façon que getpid() permet de récupérer l'identifiant d'un processus.
 * Ces deux identifiants sont uniques.
 */
pid_t gettid(void){
  return syscall(__NR_gettid);
}


/* Fonctions décrémentation et incrémentation de la variable globale.
 * Ce sont ce que l'on appelle des "routines". Les routines, ce sont les
 * fonctions lancées par les threads à la création. C'est la seule portion
 * de code qu'ils executeront.
 */
void* inc(void* cnt){
  cnt++;
  printf("%lu : addr(cnt) = %p cnt=%d\n", gettid(), &cnt, cnt);
  sleep(10);
}

/*Un void*? Qu'est ce que c'est que ce truc ! Pourquoi on se fait chier?*/

/* Il faut pouvoir passer des arguments à un thread. Pour cela, on utilise
 * la fonction pour passer des arguments, comme on ferait avec une fonction normale.
 * Le problème, c'est que l'on ne peut pas choisir à l'avance le type d'argument
 * que l'on donnera au thread lors de sa création.

 * Du coup, on met void*, c'est à dire un pointeur vers une adresse, sans précision
 * de quel type d'adresse il s'agit (int, char, long int... etc).
 * Cela permet, grâce à une manipulation, de passer n'importe quel type d'argument
 * à notre thread.
*/

void* dec(void* cnt){
  cnt--;
  printf("%lu : addr(cnt) = %p cnt=%d\n", gettid(), &cnt, cnt);
  sleep(10);
}

int main(void){
  pthread_t th1; //On crée nos variables de type thread
  pthread_t th2;
  pthread_create(&th1, NULL, dec, NULL);
  /* On crée le thread, et on "associe" au thread que l'on a nommé th1
   * le code de la fonction "dec". On dit que "dec" sera la routine du thread
   * th1. th1 executera donc le code de dec.
   * Premier argument : l'adresse de la variable thread
   * Deuxième argument : osef, on met NULL tout le temps
   * Troisième : le nom de la fonction à executer, qui sera donc la routine.
   * Quatrième: l'adresse d'une variable de type void* à passer en argument.
  */
  pthread_create(&th2, NULL, inc, NULL);
  pthread_join(th1, NULL);
  /* On "lie" le thread principal avec le thread que l'on a créé, le th1.
   * Tant que ce dernier ne sera pas terminé, le thread principal ne
   * se terminera pas
   */
  pthread_join(th2, NULL);
  printf("%lu : addr(cnt) = %p cnt=%d\n", gettid(), &cnt, cnt);
  while(1);
  return EXIT_SUCCESS;
}

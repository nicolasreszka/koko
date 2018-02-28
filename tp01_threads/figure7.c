#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

/* Ce programme correspond au gdf suivant :
	|
	count = 2
	|
	main()
	|
	|__________________
	|       |         |
	|      dec       inc
	|       |         |
	|     count--   count++
	|       |         |
	|       |         |
	X       X         X

	Fig. 7
	
	Ce programme est très similaire à figure6.c
	La seul différence est l'utilisation des threads au lieu de fork()
*/


/* On initialise une variable qui servira de compteur */
int count = 2;

/* La gettid() renvoie un pid_t, qui peut être lu comme un long int (%lu).
 * Cela permet de récupérer l'identifiant d'un thread.
 * De la même façon que getpid() permet de récupérer l'identifiant d'un processus.
 * Ces deux identifiants sont uniques.
 */
pid_t gettid(void) {
 	return syscall(__NR_gettid);
}

/* Fonctions décrémentation et incrémentation de la variable globale.
 * Ce sont ce que l'on appelle des "routines". Les routines, ce sont les
 * fonctions lancées par les threads à la création. C'est la seule portion
 * de code qu'ils executeront.
 */

void* inc(void* arg){
	int count = *(int*) arg;
	count++;
	printf("Thread : %lu, addr(count)=%p, count=%d\n", gettid(), &count, count);
	sleep(1);
	pthread_exit(NULL);
}

void* dec(void* arg){
	int count = *(int*) arg;
	count--;
	printf("Thread : %lu, addr(count)=%p, count=%d\n", gettid(), &count, count);
	sleep(1);
	pthread_exit(NULL);
}

/* Un void* ? Qu'est ce que c'est que ce truc ?
 * Il faut pouvoir passer des arguments à un thread. Pour cela, on utilise
 * la fonction pour passer des arguments, comme on ferait avec une fonction normale.
 * Le problème, c'est que l'on ne peut pas choisir à l'avance le type d'argument
 * que l'on donnera au thread lors de sa création.
 * Du coup, on met void*, c'est à dire un pointeur vers une adresse, sans précision
 * de quel type d'adresse il s'agit (int, char, long int... etc).
 * Cela permet, grâce à une manipulation, de passer n'importe quel type d'argument
 * à notre thread.
*/

int main(void){

	/* Ici on va utiliser des "threads", leur fonctionnement est similaire aux
	 * processus mais ils sont créés différemment et là ou les processus ont leur
	 * propre mémoire virtuelle, les threads partagent la même mémoire.
	*/
	pthread_t threadDec;
	pthread_t threadInc; 

	/* On crée les threads et on "associe" à ces derniers
	 * le code de leur fonctions respectives. On les appelle des "routines".
	 * ex : dec() est la routine du thread 
	 * Arguments :
	 * 	-Premier argument   : l'adresse de la variable thread
	 * 	-Deuxième argument  : les attributs du thread, ici on ne s'en servira pas
	 * 	-Troisième argument : le nom de la routine à executer.
	 * 	-Quatrième argument : l'argument à passer au thread.
	*/
	pthread_create(&threadDec, NULL, dec, &count);
	pthread_create(&threadInc, NULL, inc, &count);

	/* On "lie" le thread principal avec le thread que l'on a créé.
	 * Tant que ce dernier ne sera pas terminé, le thread principal ne se terminera pas
	*/
	pthread_join(threadDec, NULL);
	pthread_join(threadInc, NULL);
	printf("Thread : %lu, addr(count)=%p, count=%d\n", gettid(), &count, count);

	while(1);

	return EXIT_SUCCESS;
}
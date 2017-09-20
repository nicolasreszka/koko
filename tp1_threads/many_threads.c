#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/types.h"
#include "sys/syscall.h"

/* Ce programme va créer une suite de 3 threads ou chaque thread execute
 * la même routine qui affiche toutes les 5sec son numéro d'itération,
 * son PID, TID, PTHID.
 * On observe que la valeur de la variable "i" passée en argument affiche
 * toujours 3.
*/

pid_t gettid(void) {
	return syscall(__NR_gettid);
}

void* start_routine(void *arg) {
    /* Ici on récupère l'argument, explications à la fin du code */
   	int x = *(int*) arg; 

	while(1){
		printf("Thread number : %d \n", *((int*) arg));
		printf("PID : %d\n", getpid());
		printf("TID : %d\n", gettid());
		printf("PTHID : %lu\n", pthread_self());
		sleep(5);
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	/* On crée trois variables threads */
	pthread_t thread[3];

	for (int i = 0; i < 3; i++) {
		/* On "cast" (transtype) i vers un void* ce qui nous permet 
		 * d'obtenir l'adresse de i, sans type
		*/
		pthread_create(&thread[i], NULL, start_routine, (void*)&i);	

		/* A chaque tour de boucle, on crée un thread auquel on associe la routine
		 * "start_routine", et on passe en argument la variable i, qui vaut donc
		 * 0 au premier tour, 1 au suivant, et 2 pour le dernier thread.
		*/
	}
	pthread_join(thread[0], NULL);

	/* Pourquoi le i vaut toujours 3 à l'affichage?
	 * Parce que les threads peuvent s'executer dans n'importe quel ordre.
	 * Du coup les 3 threads sont créés, et ils ont tous un pointeur vers une variable i.
	 * Celle ci est incrémentée à chaque tour de boucle.
	 * Donc une fois que tous les threads sont créés, la variable i vaut 3.
	 * Mais le fait que les threads soient créés ne veut pas dire que les threads ont terminé
	 * d'executer leur code.
	 * Ainsi quand la variable i arrive à 3, les threads n'ont pas encore affiché la valeur de la variable.
	 * Ils affichent donc tous 3.
	*/

	return EXIT_SUCCESS;
}

/* Explication de la ligne 21 : int x = *(int*) arg;
 * Lorsque l'on passe une variable via une adresse à une fonction, on a ça :
 *
 *	void ma_fonction(int* var){
 * 		printf("La valeur de ma variable est : %d\n", *var);
 *	}
 * 
 * /!\ Pour accéder à la valeur de var dans printf(), on met l'étoile devant. /!\
 * Parce que l'on pointe vers ce qu'il y a à l'adresse donnée en précisant le type, 
 * ici un int, la variable fera donc 4 octets.
 * 
 * Sauf que nous, ce qu'on veut, c'est pouvoir passer n'importe quel type de variable dans la fonction.
 * 
 * Pour cela, on enlève le typage grâce au void*, qui pointe juste vers une adresse sans indiquer le type 
 * C'est un type "abstrait"
 *
 * Sauf qu'un void*, c'est inexploitable tel quel, parce qu'on ne sait pas combien d'octets fait
 * notre variable en mémoire. Donc pour éviter les SEGFAULT, il faut le cast vers le type voulu.
 *   
 * Comment cast un void* ?
 *
 * 	void* start_routine(void *arg) {
 *		<type cible> x = *(<type cible>*) arg; 
 *	}
 *
 * Voilà :)
*/
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"

/* Ce programme écrit dans une variable dont l'adresse est partagée
 * l'identifiant du segment de mémoire partagée et la valeur de la variable 
 * sera passé sur la ligne de commande
*/
int main(int argc, char ** argv) {
	
	if (argc < 3) {
		printf("Usage : %s <identifiant du segment> <valeur à écrire> \n", argv[0]);
		return EXIT_FAILURE;
	}

	int id, x;
	int * adresse;

	id = atoi(argv[1]);
	x  = atoi(argv[2]);


	/* On utilise shmat() pour "attacher" une adresse à un segment
	 *
	 * void *shmat(int shmid, const void *shmaddr, int shmflg);
	 *
	 * Arguments : 
	 * 	- shmid : l'identifiant du segment
	 *	- shmaddr : l'adresse à "attacher" au segment, ici NULL
	 *	  pour que le système choisisse lui-même
	 *	- shmflg : les flags, ici 0 car on en a pas besoin
	*/ 
	adresse = (int *) shmat(id, NULL, 0);

	if (adresse < 0) {
		perror("shmat");
	} else {
		/* On met la valeur de x dans l'adresse */
		*adresse = x;
		printf("La valeur %d a été écrite à l'adresse %p\n", x, adresse);
	}

	return EXIT_SUCCESS;
}
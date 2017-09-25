#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"

/* Ce programme lit dans une variable dont l'adresse est partagée
 * l'identifiant du segment de mémoire partagée et l'adresse de la variable 
 * sera passé sur la ligne de commande
*/
int main(int argc, char ** argv) {

	if (argc < 3) {
		printf("Usage : %s <identifiant du segment> <adresse de la variable à afficher> \n", argv[0]);
		return EXIT_FAILURE;
	}

	int id;
	void * adresse;

	id = atoi(argv[1]);

	/* Lecture de l'adresse sur la ligne de commande grace à strtol() */
	adresse = (void *) strtol(argv[2], NULL, 16);

	/* Cette fois on utilise shmat() en passant l'adresse pour accéder à la variable qui s'y trouve */
	adresse = shmat(id, adresse, 0);

	if (adresse < 0) {
		perror("shmat");
	} else { 
		printf("La valeur %d se touvait à l'adresse %p\n", *((int*)adresse), adresse);
	}

	return EXIT_SUCCESS;
}
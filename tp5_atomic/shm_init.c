/* IPC = Inter Process Communication 
 * C'est les mécanismes qui permettent les échanges entre processus
*/

#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/ipc.h"

/* On importe le header qui contient ftok() et shmget() */
#include "sys/shm.h"


/* Ce programme initialise simplement un segment de k octets 
 * (passés sur la ligne de commande) qui seront partagés
*/
int main(int argc, char** argv) {
	
	if (argc < 2) {
		printf("Usage : %s <nombre d'octets à affecter>\n", argv[0]);
		return EXIT_FAILURE;
	}

	size_t size; 
	key_t key;
	int id;

	size = atoi(argv[1]);

	/* Ici on initialise la clé IPC System V à l'aide de ftok() pour le partage de la mémoire
	 *
	 * size_t ftok(const char *pathname, int proj_id); 
	 *
	 * Cette fonction crée la clé l'aide de la chaîne de charactères pathname 
	 * et des 8bits de poids faibles de key_t
	 *
	 * Arguments : 
	 * 	- pathname : le chemin vers le fichier
	 *	- proj_id : l'identifiant du projet, c'est un int mais seuls 
	 *	  les 8bits de poids faibles sont utilisés donc on peut mettre un char 
	*/ 
	key = ftok("/tmp",'a');

	if (key < 0) {
		perror("ftok");
	} else {
		printf("ftok success\n");
	}

	/* Ici on recupère l'identifiant du segment de mémoire partagé à l'aide de shmget()
	 *
	 * int shmget(key_t key, size_t size, int shmflg);
	 *
	 * Arguments : 
	 * 	- key : la clé créée avec ftok()
	 *	- size : le nombre d'octets k à partager
	 *	- shmflg : ici on utilise IPC_CREAT pour crééer un nouveau segment et 
	 *	  IPC_EXCL pour éviter que le segment ne se crée si il existe déjà
	 *	  0666 correspond aux permissions
	*/ 
	id = shmget(key, size, 0666|IPC_CREAT|IPC_EXCL);

	if (id < 0) {
		perror("shmget");
	} else {
		printf("shmget success\n");
	}

	printf("Shared segment id : %d\n", id);

	return EXIT_SUCCESS;
}

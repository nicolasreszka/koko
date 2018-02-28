#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"


/* Ce programme détruit le segment dont l'identifiant est passé sur la ligne de commande
*/
int main(int argc, char** argv) {
	
	if (argc < 2) {
		printf("Usage : %s <identifiant du segment à détruire>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int id, remove;
	id = atoi(argv[1]);

	/* On utilise shmctl() pour détruire le segment 
	 *
	 * int shmctl(int shmid, int cmd, struct shmid_ds *buf);
	 *
	 * Cette fonction permet de controller les segments de mémoire partagés
	 *
	 * Arguments : 
	 * 	- shmid : l'identifiant du segment
	 *	- cmd : la commande à effectuer
	 *	- buf : pointeur sur une structure shmid_ds, ici NULL
	*/ 
	remove = shmctl(id, IPC_RMID, NULL);

	if (remove < 0) {
		perror("shmctl");
	} else {
		printf("Remove success !\n");
	}

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Ce programme montre comment un processus devient un zombie.
 * On peut le vérifier grace à la commande "top" qui affiche le nombre de zombies
*/

int main() {
	int pid = fork();
	
	if (pid == -1) {
		perror("Erreur lors du fork.");
		exit(1);
	}
	
	if ( pid > 0 ) {
		while(1) {
			printf("Je suis le père et je ne sait pas que mon fils est mort.\n");
			sleep(3);
		}
	}
	
	/* Le fils meurt sans notifier le père, il devient donc un zombie */
	if ( pid == 0 ) {
		exit(0);
	}

	return EXIT_SUCCESS;
}
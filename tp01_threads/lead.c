#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Ce programme devient leader d'une session à l'aide de setsid();
 * On peut le voir avec la commande ps.
*/

int main() {
	pid_t SID;
	printf("SID avant la creation de la session : %d \n",getsid(getpid()));

	/* Attention, cette ligne risque de ne pas fonctionne lorsque user non root */
	SID = setsid(); 

	if (SID == -1){
		perror("Erreur lors de la creation de la nouvelle session.");
		exit(-1);
	}

	printf("SID apres la creation de la session : %d \n",getsid(getpid()));

	return EXIT_SUCCESS;
}
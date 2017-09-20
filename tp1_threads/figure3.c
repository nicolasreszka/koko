#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

/* Ce programme correspond au gdf suivant :
	Q
	|\
	| \
	|\ \
	| \ \
	|  \ \  
	|   \ \
	| Qf2\ \ Qf1
	|     \ \
	O     X  O

	Fig. 3

	Dans ce programme : 
		-Q crée Qf1 et Qf2 puis execute une boucle infinie -> O
		-Qf1 execute une boucle infinie -> O
		-Qf2 meurt -> X
*/

int main(int argc, char** argv) {
	
	int pid1 = fork();

	/* fork() à échoué */
	if (pid1 == -1) {
		perror("Fork error");
		exit(1);
	} 
	
	/* Code du premier fils */
	if (pid1 == 0) {
		printf("PID du premier fils : %d\n", getpid());
		while(1);
	}
	
	/* Code du père */
	if (pid1 > 0) {
		printf("PID père : %d\n", getpid());

		int pid2 = fork();

		/* Le deuxième fork() à échoué */
		if (pid2 == -1) {
			perror("Erreur au fork 2");
			exit(1);
		}
		
		/* Code du deuxième fils */
		if (pid2 == 0) {
			printf("PID du deuxième fils : %d\n", getpid());
			exit(0);
		}

		while(1);
	}

	return EXIT_SUCCESS;
}
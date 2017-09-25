#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

/* Ce programme correspond au gdf suivant :
	    Q
	    |
	|-->|
	|   |\
	|   | \Qf
	|___|  \
	        X

	Fig. 4

	Dans ce programme : 
		-Q crée Qf
		-Qf meurt -> X
		-Q revient au début 
		-Q crée Qf
		-Qf meurt -> X
		-Q revient au début 
		-jusqu'a ce que mort s'en suive...
*/

int main() {
	int pid;

	/* Etiquette pour revenir ici après création du fils */
	loop: 
	pid = fork();

	/* fork() à échoué */
	if (pid == -1) {
		perror("Fork error");
		exit(1);
	} 

	/* Code du fils */
	if (pid == 0) {
		printf("PID fils : %d\n", getpid());
		exit(0);
	}

	/* Code du père */
	if (pid > 0) {
		printf("PID père : %d\n", getpid());
		sleep(5);

		/* Retour au début */
		goto loop;
	}

	return EXIT_SUCCESS;
}

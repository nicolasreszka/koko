#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Ce programme correspond au gdf suivant :
	    Q
	    |
	|-->|
	|   |
	|Qf |
	|___|  
	    |
	    X

	Fig. 5

	Dans ce programme : 
		-Q crée Qf
		-Q meurt -> X
		-Qf crée Qff
		-Qf meurt -> X
		-Qff crée Qfff
		-Qff meurt -> X
		-Qfff crée Qffff
		-etc... 
	
	En utilisant la commande ps, on observe un seul 
	processus qui change de PID, on ne peut d'ailleurs pas tuer 
	le processus en utilisant ctrl-c, il faut utiliser kill 
	et être assez rapide...
*/

int main() {
	int pid;

	while(1) {
		pid = fork();

		/* fork() à échoué */
		if (pid == -1) {
			perror("Fork error");
			exit(1);
		} 
	    
		if (pid > 0) {
			printf("PID : %d\n", getpid());
			break;
		}

		/* attendre 10sec pour te laisser une chance de tuer le processus */
		sleep(10);
	}

	return EXIT_SUCCESS;
}
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

/* Ce programme correspond au gdf suivant :
	Q
	|\
	| \
	|  \
	|   \
	|   |\  
	|   | \
	| Qf|  \ Qff
	|   |   \
	O   x    S

	Fig. 2

	Dans ce programme : 
		-Q crée Qf puis execute une boucle infinie -> O, 
		-Qf crée Qff puis meurt -> X
		-Qff attend un évènement quelconque -> S
*/

int main(int argc, char** argv) {
	
	int pid = fork();
  
	/* fork() à échoué */
	if (pid == -1) {
		perror("Fork error");
		exit(1);
	} 

	/* Code du fils */
	if (pid == 0) {
		printf("PID fils : %d\n", getpid());

		int x;
		int pid2 = fork();

		/* le deuxième fork() à échoué */
		if (pid2 == -1) {
			perror("Fork error");
			exit(1);
		} 

		/* Code du fils du fils */
		if (pid2 == 0) {
			printf("PID du fils fils : %d\n", getpid());
			printf("x?\n");
			scanf("%d",&x);
			printf("x = %d\n",x);
		}
	}

	/* code du père */
	if (pid > 0) {
		printf("PID père : %d\n", getpid());
		while (1);
	}

	return EXIT_SUCCESS;
}
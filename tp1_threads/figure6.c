#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Ce programme correspond au gdf suivant :
	|
	count = 2
	|
	main()
	|
	|\
	| \ 
	|  \
	|\  \
	| \  \
	|  \  \  
	|   \  \
	|    \  \
	|     \  \ 
	|      \  \
	|count--\  \ count++
	|        \  \
	X        X   X

	Fig. 6

	Dans ce programme : 
		-Q crée Qf1 et Qf2 puis meurt
		-Qf1 incrémente count puis meurt
		-Qf2 décrémente count puis meurt
*/

int count = 2;


int main() {

    int pid1 = fork();

	/* fork() à échoué */
	if (pid1 == -1) {
		perror("Fork error");
		exit(1);
	} 
	
	/* Code du premier fils */
	if (pid1 == 0) {
		/* Qf1 incrémente count puis meurt */
		count++;
		printf("Qf1 : %d, adresse(count)=%p count=%d \n",getpid(),&count,count);
     	exit(0);
	}
	
	/* Code du père */
	if (pid1 > 0) {
		int pid2 = fork();

		/* Le deuxième fork() à échoué */
		if (pid2 == -1) {
			perror("Erreur au fork 2");
			exit(1);
		}
		
		/* Code du deuxième fils */
		if (pid2 == 0) {
			/* Qf2 décrémente count puis meurt */
			count--;
			printf("Qf2 : %d, adresse(count)=%p count=%d \n",getpid(),&count,count);
	     	exit(0);
		}

		if (pid2 > 0) {
			/* count reste inchangé pour Q */
			printf("Q : %d, adresse(count)=%p count=%d \n",getpid(),&count,count);
		}
	}

    return EXIT_SUCCESS;
}
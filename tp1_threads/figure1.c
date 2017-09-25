/* Terminologie :
Dans les arbres de processus de koko (appelés gdf) :
	- "Q"   = processus père
	- "Qf"  = processus fils
	- "Qff" = processus fils du fils
	etc...

	- "S" = le processus attend un évènement quelconque (ex: scanf())
	- "O" = le processus execute une boucle infinie (ex: while(1))
	- "x" = le processus meurt
*/

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

/* Ce programme correspond au gdf suivant :
	Q
	|\
	| \ Qf
	|  \
	O   O

	Fig. 1

	Dans ce programme : 
		-Q crée Qf puis execute une boucle infinie -> O, 
		-Qf execute une boucle infinie -> O
*/

int main(int argc, char** argv) {
	
	/* La fonction fork() permet de créer processus appelé "fils", 
	 * qui execute le même code que le "père", mais ne partage pas 
	 * la même place dans la mémoire. 
	 * Pour pouvoir les différencier, on utilise la valeur de retour
	 * de fork() :
	 * 	- "-1" signifie que fork à échoué
	 *	- " 0" si on execute le code du fils
	 *	- ">0" si on execute le code du père
	*/ 
	int pid = fork();

	/* fork() à échoué */
	if (pid == -1) {
		perror("Fork error");
		exit(1);
	} 

	/* code du fils */
	if (pid == 0) {
		printf("PID fils : %d\n", getpid());
		while (1);
	}

	/* code du père */
	if (pid > 0) {
		printf("PID père : %d\n", getpid());
		while (1);
	}

	return EXIT_SUCCESS;
}
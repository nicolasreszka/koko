#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"

/* Ce programme correspond au gdf suivant :
	
	P
	|\ 
	| \ 
	|  \ Pf1
	|   \ 
	|    \  
	|     \ 
	|\Pf2 |\Pf1f1  
	| \   | \ 
	O  O  O  O 
	   |_____|
	     pipe

	Dans ce programme : 
		-P crée Pf1 et Pf2 puis execute une boucle infinie -> O
		-Pf1 crée Pf1f1 puis execute une boucle infinie -> O
		-Un pipe est établi entre Pf1f1 et Pf2
		-Pf2 écrit toutes les 3 sec son PID dans le pipe et affiche ce qu'il écrit
		-Pf1f1 lit chaques secondes dans le pipe et affiche ce qu'il lit

	Un "pipe" (tube) sert à faire communiquer plusieurs processus entre eux,
	l'un écrit des informations dans l'entrée du tube, l'autre lit les 
	information à la sortie du tube.
*/


int main(int argc, char** argv) {

	int pidPf1, pidPf2, pidPf1f1, pipe_error;
	int pp[2];
	int message;

	/* Création du tube */
	pipe_error = pipe(pp);

	/* Erreur lors du pipe */
	if (pipe_error == -1){ 
		perror("pipe");
		return EXIT_FAILURE;
	}

	/* Création du processus Pf1 */
	pidPf1 = fork();

	/* Erreur lors du fork */
	if (pidPf1 == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}

	/* Code exécuté par Pf1 */ 
	if (pidPf1 == 0) {

		/* Création du processus Pf1f1 */
		pidPf1f1 = fork();

		/* Erreur lors du fork */
		if (pidPf1f1 == -1) {
			perror("fork");
			exit(-1);
		}

		/* Code exécuté par Pf1f1 */ 
		if (pidPf1f1 == 0) {

			/* On ferme l'entrée du côté lecteur */
			close(pp[1]);

			while (1) {
				/* Ecriture du message dans le pipe */
				read(pp[0], &message, 4);
				printf("\tPf1f1 (%d): recieved %d\n", getpid(), message);
				sleep(1);
			}
		}

		/* Code exécuté par Pf1 */ 
		if (pidPf1f1 > 0) {
			/* Fermeture du tube car Pf1 ne s'en sert pas */ 
			close(pp[0]);
			close(pp[1]);
			while (1);
		}
	}

	/* Code exécuté par P */ 
	if (pidPf1 > 0) {

		/* Création du processus Pf2 */
		pidPf2 = fork();

		/* Erreur lors du fork */
		if (pidPf2 == -1) {
			perror("fork");
			exit(-1);
		}

		/* Code exécuté par Pf2 */ 
		if (pidPf2 == 0) {

			/* On ferme la sortie du côté écrivain */
			close(pp[0]);	

			/* On veut envoyer le pid de l'écrivain au lecteur */
			message = getpid();

			while (1) {
				message++;

				/* Ecriture du message dans le pipe */
				write(pp[1],&message,4);
				printf("Pf2 (%d): sent %d\n", getpid(), message);
				sleep(3);
			}
		}

		/* Code exécuté par P */ 
		if (pidPf2 > 0) {
			/* Fermeture du tube car P ne s'en sert pas */ 
			close(pp[0]);
			close(pp[1]);
			while (1);
		}
	}
}

/*	Oservations :

	Lorsque l'on envoie SIGSTOP à Pf2, on observe que Pf1f1 et Pf2 s'arrêtent
	Lorsque l'on envoie ensuite SIGCONT à Pf2, on observe que Pf1f1 et Pf2 reprennent

	Lorsque l'on envoie SIGSTOP à Pf1f1, on observe que Pf1f1 s'arrête et que Pf2 continue à écrire
	Lorsque l'on envoie ensuite SIGCONT à Pf1f1, on observe que Pf1f1 reprend et "rattrape son retard" 
	(il va lire tout ce qui lui à été envoyé toutes les 1 secondes)
	
	-Sans fermer le tube pour les processus P et Pf1 :
		Lorsque l'on envoie SIGKILL à Pf2, on observe que Pf2 à été tué et que Pf1f1 s'arrête

		Lorsque l'on envoie SIGKILL à Pf1f1, on observe que Pf1f1 à été tué et que Pf2 continue à écrire

	-En fermant le tube pour les processus P et Pf1 :
		Lorsque l'on envoie SIGKILL à Pf2, on observe que Pf2 à été tué et que Pf1f1 continue à lire le message
		laissé par Pf2 avant son décès toutes les 1 secondes.

		Lorsque l'on envoie SIGKILL à Pf1f1, on observe que Pf1f1 à été tué et que Pf2 à été également tué

	Explications :

	Lorsque les "embouts" non utilisés du pipe ne sont pas explicitement fermés, "End Of File" (EOF) n'est 
	jamais envoyé, ce qui est à l'origine du comportement décrit ci-dessus. Il est donc important de fermer
	les embouts du tube pour les processus non concernés par celui-ci.

*/
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"

/* Ce programme est un exemple d'interblocage avec un pipe */

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

			while (1) {
				/* Lecture du message dans le pipe */
				read(pp[0], &message, 4);
				printf("\tPf1f1 (%d): recieved %d\n", getpid(), message);

				/* On veut envoyer le pid de Pf1f1 à Pf2 */
				message = getpid();

				/* Ecriture du message dans le pipe */
				write(pp[1],&message,4);
				printf("\tPf1f1 (%d): sent %d\n", getpid(), message);

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

			while (1) {
				/* Lecture du message dans le pipe */
				read(pp[0], &message, 4);
				printf("Pf2 (%d): recieved %d\n", getpid(), message);

				/* On veut envoyer le pid de Pf2 à Pf1f1 */
				message = getpid();

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
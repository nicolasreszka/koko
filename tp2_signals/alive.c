/*	Auteur : Nicolas Reszka 
*	Fonction : affiche toute les 2sec son PID et la phrase "I am alive" 
*/

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main() {
	while (1) {
		printf("pid : %d, I am alive\n", getpid());
		sleep(2);
	}

	return EXIT_SUCCESS;
}
/*	Auteur : Nicolas Reszka 
*	Fonction : envoie le signal k au processus l
*	Arguments : 
*	- k: numéro du signal
*	- l: PID du processus
*/

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"

int main(int argc, char** argv) {
	
	if (argc < 2) {
		printf("Usage : %s [numero du signal] [PID du processus] \n",argv[0]);
		return EXIT_FAILURE;
	}

	int k, l, result;
	
	k = atoi(argv[1]);
	l = atoi(argv[2]);
	
	result = kill(l,k);
	printf("result = %d\n", result);

	return EXIT_SUCCESS;
}
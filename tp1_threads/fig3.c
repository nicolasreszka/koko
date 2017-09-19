#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char** argv) {
	
	int x1 = fork();
	int x2 = fork();

	if (x1 == -1) {
		return EXIT_FAILURE;
	} else if (x1 == 0) {
		printf("%d : I am dad's first son.\n", getpid());
	} else if (x1 > 0) {
		printf("%d : I am dad.\n", getpid());
	}
	if (x2 == -1) {
		return EXIT_FAILURE;
	} else if (x2 == 0) {
		printf("%d : I am dad's second son.\n", getpid());
	} else if (x2 > 0) {
		printf("%d : I am dad.\n", getpid());
	}

	return EXIT_SUCCESS;
}
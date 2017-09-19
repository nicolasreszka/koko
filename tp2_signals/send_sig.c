#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("il faut deux args : k et l\n");
		return EXIT_FAILURE;
	}
	int k,l, result;
	k = atoi(argv[1]);
	l = atoi(argv[2]);
	result = kill(l,k);
	printf("result = %d\n", result);

	return EXIT_SUCCESS;
}
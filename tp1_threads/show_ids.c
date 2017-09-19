#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char** argv) {
	
	printf("pid = %d\ngroup id = %d\nsession id = %d\n", getpid(), getpgid(getpid()), getppid());

	return EXIT_SUCCESS;
}
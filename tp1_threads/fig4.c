#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"


int main() {
	int x;
	loop:
	x = fork();

	if (x == -1) {
		printf("error");
		sleep(5);
		exit(1);
	}

	if (x == 0) {
		printf("%d : son\n", getpid());
		sleep(5);
		exit(0);
	}

	if (x > 0) {
		printf("%d : dad\n", getpid());
		sleep(5);
		goto loop;
	}

	return EXIT_SUCCESS;
}

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char** argv) {
	
	int pid = fork();
  
	if (pid == -1) {
		return EXIT_FAILURE;
	} else if (pid == 0) {
		int x = fork();
		if (x == -1) {
			return EXIT_FAILURE;
		} else if (x == 0) {
			printf("%d : Hello ! I am son's son !\n", getpid());
		} else if (x > 0) {
			printf("%d : Hello ! I am dad's son !\n", getpid());
		}
	} else if (pid > 0) {
		while (1) {
			if (getchar()) {
				printf("Dad PID : %d\n", getpid());
				return EXIT_SUCCESS;
			}
		}
	}

	return EXIT_SUCCESS;
}
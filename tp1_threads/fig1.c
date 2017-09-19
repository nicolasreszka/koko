#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char** argv) {
	
	int pid = fork();

	if (pid == -1) {
		return EXIT_FAILURE;
	} 
	if (pid == 0) {
		while (1) {
			if (getchar()) {
				printf("Child PID : %d\n", getpid());
				return EXIT_SUCCESS;
			}
		}
	}
	if (pid > 0) {
		while (1) {
			if (getchar()) {
				printf("Dad PID : %d\n", getpid());
				return EXIT_SUCCESS;
			}
		}
	}
}
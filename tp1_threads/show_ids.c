#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"

int main() {
	printf("PID = %d\n Group ID = %d\n Session ID = %d\n", getpid(), getpgid(getpid()), getsid(getppid()));

	return EXIT_SUCCESS;
}
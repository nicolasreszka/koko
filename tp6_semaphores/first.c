#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "time.h"


void first(int d) {
	struct timespec delay;
	delay.tv_sec = 0;
	delay.tv_nsec = d * 10000L;

	char word[6] = "first";
	int i = 0;

	while (1) {
		putchar(word[i]);
		
		i++;
		if (i > 5) {
			i = 0;
		}

		fflush(stdout);
		if (nanosleep(&delay, NULL) > 0) {
			perror("nanosleep");
		}
	}
}

int main(int argc, char** argv) {
	
	if (argc < 2) {
		printf("Usage : %s <délai d'affichage (en ms)>\n", argv[0]);
	}

	first(atoi(argv[1]));

	return EXIT_SUCCESS;
}
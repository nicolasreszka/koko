#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"


void print_word_letter_by_letter(char* word, int delay) {
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = delay * 10000L;

	int length;
	length = strlen(word);

	int i = 0;

	while (1) {
		putchar(word[i]);
		
		i++;
		if (i > length) {
			putchar(' ');
			i = 0;
		}

		fflush(stdout);
		if (nanosleep(&ts, NULL) > 0) {
			perror("nanosleep");
		}
	}
}

int main(int argc, char** argv) {
	
	if (argc < 2) {
		printf("Usage : %s <délai d'affichage (en ms)>\n", argv[0]);
		return EXIT_FAILURE;
	}

	print_word_letter_by_letter("second", atoi(argv[1]));

	return EXIT_SUCCESS;
}
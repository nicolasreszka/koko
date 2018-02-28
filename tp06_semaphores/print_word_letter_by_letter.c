#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

int 	print_word_letter_by_letter(char* word, int delay) 
{
	
	struct 	timespec ts;
	int 	success = 1;
	int 	i;
	size_t 	word_length;

	ts.tv_sec = 0;
	ts.tv_nsec = delay * 1000000L;

	word_length = strlen(word);

	for (i = 0; i < word_length; i++)
	{
		putchar(word[i]);
		fflush(stdout);

		if (nanosleep(&ts, NULL) == -1) 
		{
			perror("nanosleep");
			success = 0;
		}
	}
	putchar(' ');

	return success;
}

int 	main(int argc, char** argv) 
{
	
	if (argc != 3) 
	{
		printf("Usage : %s <mot a afficher> <délai d'affichage en ms>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int delay, print_success;
	delay = atoi(argv[2]);

	if (delay > 1000) 
	{
		printf("le delai ne doit pas exceder 1000ms\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		print_success = print_word_letter_by_letter(argv[1],delay);
		if (!print_success)
		{
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}

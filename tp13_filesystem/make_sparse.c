#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h" 
#include "errno.h"
#include "unistd.h"

int 	main(int argc, char** argv)
{
	if (argc < 3) 
	{
		printf("usage : %s <file name> <hole size (in bytes)>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int 				file, i, write_error;
	unsigned int		hole_size;
	char 				one, zero;
	off_t 				lseek_error;
	
	one 	= 0x11;

	hole_size = (unsigned int) strtoul(argv[2],NULL,0);

	file = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY|0640);

	if (file == -1)
	{
		perror("open");
		exit(errno);
	}
	
	for (i = 0; i < hole_size; i++)
	{
		write_error = write(file,&one,1);
		if (write_error == -1)
		{
			perror("write");
			exit(errno);
		}

	}
	
	lseek_error = lseek(file, hole_size, SEEK_CUR);

	if (lseek_error == -1)
	{
		perror("lseek");
		exit(errno);
	}

	for (i = 0; i < hole_size; i++)
	{
		write_error = write(file,&one,1);
		if (write_error == -1)
		{
			perror("write");
			exit(errno);
		}
	}

	close(file);

	exit(EXIT_SUCCESS);
}
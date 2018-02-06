#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"

#define ENCRYPTION_DEPTH	32

unsigned int	delta = 0x9e3779b9;

void	decrypt(unsigned int key[4], int block[2])
{
	int		i;

	for (i = ENCRYPTION_DEPTH-1; i >= 0 ; i--)
	{	
		block[1] -= (key[2] + (block[0] << 4))
	              ^((delta *i)+block[0])
	              ^ (key[3] + (block[0] >> 5));

	    block[0] -= (key[0] + (block[1] << 4)) 
	              ^((delta *i)+block[1]) 
	              ^ (key[1] + (block[1] >> 5));
	}
}

int 	main(int argc, char** argv)
{
	if (argc < 2)
	//if (argc < 3)
	{
		printf("usage : %s <file to encrypt> <128 bit key>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned int	key[4];
	unsigned int	block[2];
	int 			file_in, file_out;
	ssize_t			read_result, write_result;
	
	key[0] = 15;
	key[1] = 1357;
	key[2] = 7830;
	key[3] = 7159;

	//key[0]  = strtoull(argv[2], NULL, 0);

	// printf("%x %x %x %x\n", key[0], key[1], key[2], key[3]);

	printf("%d %d %d %d\n", key[0], key[1], key[2], key[3]);

	file_in = open(argv[1], O_RDONLY, 0655);

	if (file_in == -1)
	{
		perror("open");
		exit(errno);
	}

	file_out = open("decrypt_out.dat", O_WRONLY|O_CREAT|O_TRUNC, 0655);
	//file_out = open("decrypt_out.jpg", O_WRONLY|O_CREAT|O_TRUNC, 0655);

	if (file_out == -1)
	{
		perror("open");
		exit(errno);
	}

	read_result = 1;

	while (read_result > 0) 
	{
		read_result = read(file_in, block, 8);

		if (read_result == -1)
		{
			perror("read");
			exit(errno);
		}

		decrypt(key,block);

		write_result = write(file_out, block, 8);

		if (write_result == -1)
		{
			perror("write");
			exit(errno);
		}
	}

	close(file_in);
	close(file_out);

	exit(EXIT_SUCCESS);
}
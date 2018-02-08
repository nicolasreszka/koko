#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"

#define ENCRYPTION_DEPTH	32

unsigned int	delta = 0x9e3779b9;

void	encrypt(unsigned int key[4], int block[2])
{
	int		i;

	for (i = 0; i < ENCRYPTION_DEPTH; i++)
	{
		block[0] += (key[0] + (block[1] << 4)) 
		          ^((delta *i)+block[1]) 
		          ^ (key[1] + (block[1] >> 5));
		
		block[1] += (key[2] + (block[0] << 4))
		          ^((delta *i)+block[0])
		          ^ (key[3] + (block[0] >> 5));
	}
}

int 	main(int argc, char** argv)
{

	if (argc < 3)
	{
		printf("usage : %s <file to encrypt> <file containing 128 bit key>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned int    key[4];
	unsigned int    block[2];
	int             file_key, file_in, file_out;
	ssize_t         read_result, write_result;

	memset(key, 0x0, sizeof(unsigned int) * 4);

	file_key = open(argv[2], O_RDONLY, 0655);

	if (file_key == -1)
	{
		perror("open");
		exit(errno);
	}

	read_result = read(file_key, key, 16);

	if (read_result == -1)
	{
		perror("read");
		exit(errno);
	}

	printf("%x %x %x %x\n", key[0], key[1], key[2], key[3]);

	file_in = open(argv[1], O_RDONLY, 0655);

	if (file_in == -1)
	{
		perror("open");
		exit(errno);
	}

	file_out = open("encrypt_out.dat", O_WRONLY|O_CREAT|O_TRUNC, 0655);

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

		encrypt(key,block);

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
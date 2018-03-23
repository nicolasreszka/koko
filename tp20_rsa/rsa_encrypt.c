#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"
#include "elong.h"

#define BLOCK_SIZE 	8

int 	main(int argc, char** argv)
{
	if (argc < 5)
	{
		printf("usage : %s <file in> <file out> <e> <n>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned char        b[BLOCK_SIZE];
	unsigned long int    block, key, modulus;
	int                  file_key, file_in, file_out;
	ssize_t              read_result, write_result;

	file_in = open(argv[1], O_RDONLY, 0655);

	if (file_in == -1)
	{
		perror("open");
		exit(errno);
	}

	file_out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0655);

	if (file_out == -1)
	{
		perror("open");
		exit(errno);
	}

	key     = strtoul(argv[3],NULL,0);
	modulus = strtoul(argv[4],NULL,0);

	read_result = 1;

	while (read_result > 0) 
	{
		block = 0x0;
		memset(b,0x0,BLOCK_SIZE);

		read_result = read(file_in, b, BLOCK_SIZE);

		if (read_result == -1)
		{
			perror("read");
			exit(errno);
		}

		// printf("ptext %16lx\n", block);

		memcpy(&block,b,BLOCK_SIZE);

		block = el_modular_exponent(block,key,modulus);

		// printf("ctext %16lx\n", block);

		write_result = write(file_out, &block, BLOCK_SIZE);

		if (write_result == -1)
		{
			perror("write");
			exit(errno);
		}
	}
	// printf("end\n", block);

	close(file_in);
	close(file_out);
	
	exit(EXIT_SUCCESS);
}
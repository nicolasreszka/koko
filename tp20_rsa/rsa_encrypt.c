#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"
#include "elong.h"

int 	main(int argc, char** argv)
{
	if (argc < 5)
	{
		printf("usage : %s <file in> <file out> <e> <n>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char*                block_pointer;
	unsigned char        block_size, i;
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

	block_size = (64-zero_prefix(modulus))/8;

	read_result = 1;

	while (read_result > 0) 
	{
		block = 0x0;

		read_result = read(file_in, &block, block_size-1);

		if (read_result == -1)
		{
			perror("read");
			exit(errno);
		}

		printf("ptext %16lx\n", block);

		block = el_modular_exponent(block,key,modulus);

		printf("ctext %16lx\n", block);

		block_pointer = (void*) &block;

		for (i = 0; i < block_size; i++)
		{
			write_result = write(file_out, block_pointer+i, 1);

			if (write_result == -1)
			{
				perror("write");
				exit(errno);
			}
		}
	}

	printf("end\n");

	close(file_in);
	close(file_out);
	
	exit(EXIT_SUCCESS);
}
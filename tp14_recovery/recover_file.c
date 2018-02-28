#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "errno.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "string.h"

int main(int argc, char** argv) 
{
	if (argc < 5)
	{
		printf("usage : %s <image> <filename> <block> <block count> <block size> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int 	input_image, output_file;	
	int 	block_to_read_from;
	int 	number_of_blocks_to_read;
	int 	block_size, file_size;
	int* 	file_buffer;
	int 	read_error, write_error;

	input_image = open(argv[1], O_RDONLY, 0655);
	if (input_image == -1)
	{
		perror("open");
		exit(errno);
	}
	output_file = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0665);

	if (output_file == -1)
	{
		perror("open");
		exit(errno);
	}

	block_to_read_from = (int) strtol(argv[3], NULL, 0);
	number_of_blocks_to_read = (int) strtol(argv[4], NULL, 0);
	block_size = (int) strtol(argv[5], NULL, 0);

	file_size = block_size * number_of_blocks_to_read;
	file_buffer = malloc(sizeof(int) * block_size);

	if (lseek(input_image, block_size * block_to_read_from, SEEK_SET) == -1)
	{
		perror("lseek");
		exit(errno);
	}

	for(int i = 0; i < number_of_blocks_to_read; i++)
	{
		memset(file_buffer, 0x0, block_size);
		
		read_error = read(input_image, file_buffer, block_size);
		if (read_error == -1)
		{
			perror("read");
			exit(errno);
		}

		write_error = write(output_file, file_buffer, block_size);
		if (write_error == -1)
		{
			perror("write");
			exit(errno);
		}
	}

	printf("Yeaaah boy !\n");
	exit(EXIT_SUCCESS);
}
/* ça marche pas :/ */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"

unsigned char 	substitution_array[16] = {}
unsigned char 	permutation_array[8]  = {3,7,1,6,4,0,2,5};


void	substitution(unsigned char* block)
{
	int             i;
	unsigned char   high,low;

	high = (*block & 0xF0) >> 4;
	low  = *block & 0x0F;

	high = substitution_array[high];
	low  = substitution_array[low];

	*block = (high << 4) | low;
}

void	permutation(unsigned char* block)
{
	int		        i;
	unsigned int    mask;
	unsigned char	bit,buffer;

	mask   = 0x01;
	bit    = 0;
	buffer = 0x00;

	for (i = 0; i < sizeof(unsigned char) * 8; i++)
	{
		bit = *block & mask;

		if (permutation_array[i] - i < 0)
		{
			buffer = buffer | (bit >> (-1 * (permutation_array[i] - i)));
		}
		else
		{
			buffer = buffer | (bit << (permutation_array[i] - i));
		}
		
		mask = mask << 1;
	}

	*block = buffer;
}

void 	decrypt(unsigned char* block, unsigned char key[2])
{
	int 	i;

	for (i = 1; i >= 0; i--)
	{	
		permutation(block);
		substitution(block);
		*block = *block ^ key[i];
	}
}

int 	main(int argc, char** argv)
{

	if (argc < 3)
	{
		printf("usage : %s <file to encrypt> <file containing 16 bit key>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned char   key[2];
	unsigned char   block;
	int             file_key, file_in, file_out;
	ssize_t         read_result, write_result;

	memset(key, 0x0, sizeof(unsigned char) * 2);

	file_key = open(argv[2], O_RDONLY, 0655);

	if (file_key == -1)
	{
		perror("open");
		exit(errno);
	}

	read_result = read(file_key, key, 2);

	if (read_result == -1)
	{
		perror("read");
		exit(errno);
	}

	printf("%x %x\n", key[0], key[1]);

	file_in = open(argv[1], O_RDONLY, 0655);

	if (file_in == -1)
	{
		perror("open");
		exit(errno);
	}

	file_out = open("decrypt_out.dat", O_WRONLY|O_CREAT|O_TRUNC, 0655);

	if (file_out == -1)
	{
		perror("open");
		exit(errno);
	}

	read_result = 1;

	while (read_result > 0) 
	{
		read_result = read(file_in, &block, 1);

		if (read_result == -1)
		{
			perror("read");
			exit(errno);
		}

		printf("before :%x\n", block);

		decrypt(&block,key);

		printf("after :%x\n", block);

		write_result = write(file_out, &block, 1);

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
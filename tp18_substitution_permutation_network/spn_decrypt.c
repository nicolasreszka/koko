#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"

#define	SUBSTITUTION_SIZE 16
#define PERMUTATION_SIZE 8

unsigned char 	substitution_array[SUBSTITUTION_SIZE] = {3,8,14,1,12,5,10,0,2,7,9,11,4,6,15,13};
unsigned char 	permutation_array[PERMUTATION_SIZE]   = {5,2,0,4,6,1,7,3};

unsigned char	get_index_from_value(unsigned char value, unsigned char* array, int size)
{
	unsigned char 	i;
	for (i = 0; i < size; i++)
	{
		if (array[i] == value)
		{
			return i;
		}
	}
}

void	inverse_substitution(unsigned char* block)
{
	unsigned char   high,low;

	high = *block >> 4;
	low  = *block & 0x0F;

	high = get_index_from_value(high,substitution_array,SUBSTITUTION_SIZE);
	low  = get_index_from_value(low,substitution_array,SUBSTITUTION_SIZE);

	*block = (high << 4) | low;
}

void	inverse_permutation(unsigned char* block)
{
	unsigned char i, mask, bit, buffer;

	buffer = 0x00;
	mask   = 0x01;

	for (i = 0; i < 8; i++)
	{	   
		bit     = (*block & mask);
		bit   >>= i;       
		bit   <<= get_index_from_value(i,permutation_array,PERMUTATION_SIZE);
		buffer |= bit;
		mask  <<= 1;
	}	

	*block = buffer;
}

void 	decrypt(unsigned char* block, unsigned char key[2])
{
	int 	i;

	for (i = 1; i >= 0; i--)
	{	
		inverse_permutation(block);
		inverse_substitution(block);
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

		decrypt(&block,key);

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
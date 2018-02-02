/* 	Affiche les informations d'un inode 
*	dont le dump est passé sur la ligne 
*	de commande, bien faire attention 
*	que l'encodage de ce fichier soit "hexadecimal" 
*/

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"

int 	main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		printf("usage %s <filename> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int					inode_file;
	unsigned short int	short_buffer;
	unsigned int		int_buffer;
	int 				i;

	inode_file = open(argv[1], O_RDONLY, 0655);

	if (inode_file == -1)
	{
		perror("open");
		exit(errno);
	}

	/* File mode */
	read(inode_file, &short_buffer, 2);
	printf("File mode : %d\n", short_buffer);

	/* User ID */
	read(inode_file, &short_buffer, 2);
	printf("Low 16 bits of user ID : %d\n", short_buffer);

	/* Size */
	read(inode_file, &int_buffer, 4);
	printf("File size : %d bytes\n", int_buffer);

	/* Access time */
	read(inode_file, &int_buffer, 4);
	printf("Access time : %d\n", int_buffer);

	/* Inode change time */
	read(inode_file, &int_buffer, 4);
	printf("Inode change time : %d\n", int_buffer);

	/* Modification time */
	read(inode_file, &int_buffer, 4);
	printf("Modification time : %d\n", int_buffer);

	/* Deletion time */
	read(inode_file, &int_buffer, 4);
	printf("Deletion time : %d\n", int_buffer);

	/* Group ID */
	read(inode_file, &short_buffer, 2);
	printf("Low 16 bits of Group ID : %d\n", short_buffer);

	/* Links count */
	read(inode_file, &short_buffer, 2);
	printf("Links count : %d\n", short_buffer);

	/* Blocks count */
	read(inode_file, &int_buffer, 4);
	printf("Blocks count : %d\n", int_buffer);

	/* Flags */
	read(inode_file, &int_buffer, 4);
	printf("File flags : %d\n", int_buffer);

	/* Union */
	read(inode_file, &int_buffer, 4);

	/* First direct block address */
	read(inode_file, &int_buffer, 4);
	printf("First direct block : %d\n", int_buffer);

	/* Skip 12 direct blocks */
	for (i = 0; i < 12; i++)
	{
		read(inode_file, &int_buffer, 4);
	}

	/* Indirect block */
	printf("Indirect block : %d\n", int_buffer);

	/* Double indirect block */
	read(inode_file, &int_buffer, 4);
	printf("Double indirect block : %d\n", int_buffer);

	close(inode_file);

	exit(EXIT_SUCCESS);
}
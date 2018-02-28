#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "arpa/inet.h"

/*	Ce programme prend un format d'adresse et un nom de fichier sur 
	la ligne de commande, lit l'adresse en format réseau dans ce fichier, 
	et la convertit dans le format "humain". 
*/

int 	main(int argc, char** argv)
{
	if (argc != 3) 
	{
		fprintf(stderr, "Usage: %s <numéro de format d'adresse (4 ou 6)> <nom du fichier>\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
 
	int 			address_domain, file_source;
	size_t			address_size = sizeof(struct in6_addr);
	unsigned char 	address_buffer[address_size];
	char			address_destination[INET6_ADDRSTRLEN];
	ssize_t			read_result;

	address_domain = atoi(argv[1]);

	if (address_domain == 4) 
	{
		address_domain = AF_INET;
	} 
	else if (address_domain == 6)
	{
		address_domain = AF_INET6;
	}
	else 
	{
		fprintf(stderr, "erreur : format d'adresse inconnu\n");
		exit(EXIT_FAILURE);
	}

	file_source = open(argv[2], O_RDONLY);

	if (file_source == -1) 
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	else 
	{
		read_result = read(file_source, address_buffer, address_size);
		close(file_source);

		if (read_result == -1) 
		{
			perror("read");
			exit(EXIT_FAILURE);
		} 
		else 
		{
			if (inet_ntop(address_domain, address_buffer, address_destination, INET6_ADDRSTRLEN) == NULL)
			{
				perror("inet_ntop");
				exit(EXIT_FAILURE);
			} 
			else
			{
				printf("%s\n", address_destination);
			} 
		}
	}

	exit(EXIT_SUCCESS);
}
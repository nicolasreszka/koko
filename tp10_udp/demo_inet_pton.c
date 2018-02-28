#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "arpa/inet.h"

/*	Ce programme prend une adresse IPv4 ou IPv6 et un nom de fichier
	sur la ligne de commande, convertit cette adresse vers le format
	réseau et écrit le résultat dans le fichier.
*/

int 	main(int argc, char** argv)
{
	if (argc != 3) 
	{
		fprintf(stderr, "Usage: %s <adresse IPv4 ou IPv6> <nom du fichier>\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
 
	int 			address_domain, inet_pton_result, file_destination;
	size_t			address_size = sizeof(struct in6_addr);
	unsigned char 	address_buffer[address_size];
	ssize_t			write_result;

	if (strchr(argv[1], '.')) 
	{
		address_domain = AF_INET;
	} 
	else if (strchr(argv[1], ':'))
	{
		address_domain = AF_INET6;
	}
	else 
	{
		fprintf(stderr, "erreur : format d'adresse incorrect\n");
		exit(EXIT_FAILURE);
	}

	inet_pton_result = inet_pton(address_domain, argv[1], address_buffer);
	
	if (inet_pton_result == -1) 
	{
		perror("inet_pton");
		exit(EXIT_FAILURE);
	}
	else if (inet_pton_result == 0)
	{
		fprintf(stderr, "erreur : format d'adresse incorrect\n");
		exit(EXIT_FAILURE);
	} 
	else 
	{
		file_destination = open(argv[2], O_CREAT|O_WRONLY);

		if (file_destination == -1) 
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		else 
		{
			write_result = write(file_destination, address_buffer, address_size);
			close(file_destination);

			if (write_result == -1) 
			{
				perror("write");
				exit(EXIT_FAILURE);
			} 
			else 
			{
				printf("Ecriture dans le fichier %s réussie !\n", argv[2]);
			}
		}
	}

	exit(EXIT_SUCCESS);
}
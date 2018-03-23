#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "rsa.h"

int 	main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("usage : %s <p> <q>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned long int   p,q;
	rsa_public_key      public_key;
	rsa_private_key     private_key;

	srand(time(NULL));

	p = strtoul(argv[1], NULL, 0);
	q = strtoul(argv[2], NULL, 0);

	if (!is_prime(p))
	{
		printf("p must be a prime number !\n");
		exit(EXIT_FAILURE);
	}

	if (!is_prime(q))
	{
		printf("q must be a prime number !\n");
		exit(EXIT_FAILURE);
	}

	public_key  = rsa_generate_public_key(p,q);
	private_key = rsa_generate_private_key(public_key,p,q);

	printf("Public key :  \ne = %lx \nn = %lx\n", public_key.e , public_key.n);
	printf("Private key : \nd = %lx \nn = %lx\n", private_key.d, private_key.n);

	exit(EXIT_SUCCESS);
}
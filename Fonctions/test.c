#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main(int argc,char** argv)
{
	int key[4] = { 45 , 46 , 47 , 48 };
	if ( argc < 2 )
	{
		printf("Usage : %s <nom du fichier à tester\n", argv[0]);
		exit(-1);
	}

	tea_encrypt_file(argv[1],key,32);
	tea_decrypt_file(argv[1],key,32);
}
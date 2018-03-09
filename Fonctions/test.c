#include <stdio.h>
#include <stdlib.h>
#include "cryptmath.h"

int main(int argc,char** argv)
{
	int key[4] = { 45 , 46 , 47 , 48 };
	if ( argc < 2 )
	{
		printf("Usage : %s <nom du fichier à tester\n", argv[0]);
		exit(-1);
	}

	unsigned long int test = 0xffffffffffffffff;
	test &= mask(7,0);
	printf("res = %lu \n", test);
	test = cut(test,7,5);
	printf("res = %lu \n", test);
}
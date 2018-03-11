#include <stdio.h>
#include <stdlib.h>
#include "cryptmath.h"

int main(int argc,char** argv)
{
	int key[4] = { 45 , 46 , 47 , 48 };
	int i;
	if ( argc < 2 )
	{
		printf("Usage : %s <nom du fichier à tester\n", argv[0]);
		exit(-1);
	}

	struct elong test = { 0x0 , 0xff83546348000000};
	struct elong test2 = { 0x8000000000000000 , 0x0};
	test = eladd(test,test2);
	muli(test.h);
	muli(test.l);
}
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i,x=0x11223344;
	char * a;
	short z;
/**/  a=(char *)&x;
	for (i=0;i<5;i++)
		printf("%02hhx",*(a+i));
	putchar('\n');
	z=*(short*)a;
	printf("z=%hx\n",z);
	exit(0); 
}

// il compile
/*
il affiche :
4433221104
z=3344
*/
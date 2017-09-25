#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i,x=0x11223344;
	char * a;
	short z;
/**/  a=&x;
	for (i=0;i<5;i++)
		printf("%02hhx",*(a+i));
	putchar('\n');
	z=*(short*)a;
	printf("z=%hx\n",z);
	exit(0); 
}
/*
/export/home/an16/cau/ASR-2/Bonus/foo1.c: In function ‘int main()’:
/export/home/an16/cau/ASR-2/Bonus/foo1.c:9:10: error: cannot convert ‘int*’ to ‘char*’ in assignment
   /**/  //a=&x;
//            ^
//[Finished in 0.7s with exit code 1]
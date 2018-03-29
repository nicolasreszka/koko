#include <stdio.h>
#include <stdlib.h>
#include "cryptmath.h"

int main(int argc,char** argv)
{
	if ( argc < 2 )
	{
		printf("Usage : %s <nom du fichier à tester\n", argv[0]);
		exit(-1);
	}
	unsigned long int i;
	struct elong r;
	unsigned long int z;
	/* egcd(4611686250355624704,65537);*/
	/* for ( i = 0 ; i < 64 ; i++ )
	{
		z = elexpm(2,i,0x8100000000000000);
		muli(z);
	}*/
	
	z= elexpm(0xc724c788,0x2c830001,0x10070006f);
	printf("%llx\n",z);

	/*
	struct elong a = { 0x3 , 0x6000000000000085  };
	struct elong b = { 0x1 , 0xffffffffffffffff };
	struct elong c = { 0x3 , 0x0060000000000085  };
	struct elong d = { 0x1 , 0x00ffffffffffffff };
	struct elong e = { 0x3 , 0x60  };
	struct elong f = { 0x1 , 0xfffffff };
	struct elong g = { 0x3 , 0x60  };
	struct elong h = { 0x1 , 0x1111 };
	printf("%lx.%lx + %lx.%lx = ",a.h,a.l,b.h,b.l);
	r = eladd(a,b);
	aff_elong_hex(r);
	printf("%lx.%lx - %lx.%lx = ",a.h,a.l,b.h,b.l);
	r = elsub(a,b);
	aff_elong_hex(r);
	printf("%lx.%lx + %lx.%lx = ",c.h,c.l,d.h,d.l);
	r = eladd(c,d);
	aff_elong_hex(r);
	printf("%lx.%lx - %lx.%lx = ",c.h,c.l,d.h,d.l);
	r = elsub(c,d);
	aff_elong_hex(r);
	printf("%lx.%lx + %lx.%lx = ",e.h,e.l,f.h,f.l);
	r = eladd(e,f);
	aff_elong_hex(r);
	printf("%lx.%lx - %lx.%lx = ",e.h,e.l,f.h,f.l);
	r = elsub(e,f);
	aff_elong_hex(r);
	printf("%lx.%lx + %lx.%lx = ",g.h,g.l,h.h,h.l);
	r = eladd(g,h);
	aff_elong_hex(r);
	printf("%lx.%lx - %lx.%lx = ",g.h,g.l,h.h,h.l);
	r = elsub(g,h);
	aff_elong_hex(r); */
}
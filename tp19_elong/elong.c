#include "stdio.h"
#include "stdlib.h"

/* Structure pour entier sur 128 bit */
typedef struct elong_s 
{
	unsigned long int high;
	unsigned long int low;
} elong;


/* Renvoie un masque dont les bornes sont left et right */
unsigned long int 	mask(unsigned char left, unsigned char right)
{
	unsigned long int 	mask;

	mask = 0xFFFFFFFFFFFFFFFF;
	left = (sizeof(unsigned long int)-1) - left;
	mask = (mask << left)  >> left;
	mask = (mask >> right) << right;

	return 	mask;
}

/* Coupe un entier x aux bornes left et right */
unsigned long int 	cut(unsigned long int x, unsigned char left, unsigned char right)
{
	return (x & mask(left, right)) >> right;
}

/* Addition */
elong 	el_add(elong a, elong b)
{
	unsigned long int    z,u;
	elong                sum;

	z = cut(a.low, 62,  0) + cut(b.low, 62,  0);
	u = cut(a.low, 63, 63) + cut(b.low, 63, 63) + cut(z,63,63); 

	sum.high = a.high + y.high + cut(u,1,1);
	sum.low  = (cut(u,0,0)<<63)| cut(z,62,0);

	return 	sum;
}

/* Multiplication */
elong 	el_multiply(unsigned long a, unsigned long b)
{
	unsigned long int    a_high, a_low, b_high, b_low;
	elong                z1, z2, z3, z4;

	a_high = cut(a,63,32);
	a_low  = cut(a,31, 0);

	b_high = cut(b,63,32);
	b_low  = cut(b,31, 0);

	z1.high = a_high * b_high;
	z1.low  = 0;

	z2.high = cut(a_high * b_low , 63, 32);
	z2.low  = cut(a_low  * b_high, 31,  0) << 32;

	z3.high = cut(a_low  * b_high, 63, 32);
	z3.low  = cut(a_high * b_low , 31,  0) << 32;

	z4.high = 0;
	z4.low  = a_low * b_low;

	return 	el_add(z1,el_add(z2,el_add(z3,z4)));
}

/* Complément à 2 */
elong 	el_two_complement(elong n)
{

}

/* Décalage vers la gauche */
elong 	el_shift_left(elong n, unsigned char length)
{

}

/* Remainder modulus : module < 2^64 */
unsigned long int 	el_mod(elong n, elong mod)
{

}

/* Modular exponent : (a**b) mod m */
unsigned long int 	el_exp(unsigned long a, unsigned long b, unsigned long m)
{

}



int 	main(int argc, char** argv)
{
	
	exit(EXIT_SUCCESS);
}
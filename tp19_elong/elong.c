#include "stdio.h"
#include "stdlib.h"

/* Structure pour entier sur 128 bit */
typedef struct elong_s 
{
	unsigned long int high;
	unsigned long int low;
} elong;


void 	el_print_hex(elong n)
{
	if (n.high == 0)
	{
		printf("0x%lx\n",n.low);
	}
	else
	{
		printf("0x%lx%lx\n", n.high,n.low);
	}
}

void	el_print_dec(elong n)
{
	if (n.high == 0)
	{
		printf("%lu\n",n.low);
	}
	else
	{
		printf("%lu%lu\n", n.high,n.low);
	}
}

void 	el_print_hex_format(elong n)
{
	printf("%016lx.%016lx\n", n.high,n.low);
}


/* Renvoie un masque dont les bornes sont left et right */
unsigned long int 	mask(unsigned char left, unsigned char right)
{
	unsigned long int 	mask;

	mask = 0xFFFFFFFFFFFFFFFF;
	left = (sizeof(unsigned long int)*8)-1-left;
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

	sum.high = a.high + b.high + cut(u,1,1);
	sum.low  = (cut(u,0,0)<<63)| cut(z,62,0);

	return 	sum;
}

/* Multiplication */
elong 	el_multiply(unsigned long a, unsigned long b)
{
	unsigned long int    a_high, a_low, b_high, b_low;
	elong                z1, z2, z3, z4;

	a_high  = cut(a,63,32);
	a_low   = cut(a,31, 0);

	b_high  = cut(b,63,32);
	b_low   = cut(b,31, 0);

	z1.high = a_high * b_high;
	z1.low  = 0;

	z2.high = cut(a_high * b_low , 63, 32);
	z2.low  = cut(a_low  * b_high, 31,  0) << 32;

	z3.high = cut(a_low  * b_high, 63, 32);
	z3.low  = cut(a_high * b_low , 31,  0) << 32;

	z4.high = 0;
	z4.low  = a_low * b_low;

	return  el_add(z1,el_add(z2,el_add(z3,z4)));
}

/* Décalage de k vers la gauche */
elong 	el_shift_left(elong n, unsigned char k)
{
	elong 	result;

	result.high = (n.high << k) | cut(n.low,63,64-k);
	result.low  = (n.low  << k);

	return 	result;
}

/* Décalage de k vers la droite */
elong 	el_shift_right(elong n, unsigned char k)
{
	elong 	result;

	result.high = (n.high >> k);
	result.low  = (n.low  >> k) | (cut(n.high,k-1,0) << (64-k));

	return 	result;
}

/* Complément à 2 */
elong 	el_twos_complement(elong n)
{
	elong           a,b;
	unsigned char   i;

	a.high = 0;
	a.low  = 0;

	for (i = 0; i < 64; i++)
	{
		a.high |= (cut(n.high,i,i) ^ 1) << i;
		a.low  |= (cut(n.low ,i,i) ^ 1) << i;
	}

	b.high = 0;
	b.low  = 1;

	n = el_add(a,b);

	return n;
}


/* Remainder modulus : m < 2^64 */
unsigned long int 	el_mod(elong n, unsigned long m)
{
	unsigned char       shift_length,i;
	elong               result,divisor;

	if (n.high == 0)
	{
		result.low = n.low % m;
	}
	else
	{
		shift_length = 63;

		while (cut(m,shift_length,shift_length) == 0)
		{
			shift_length--;
		}

		shift_length = (63 - shift_length);

		printf("shift_length :  %d\n", shift_length);

		divisor.high = 0;
		divisor.low  = m;

		divisor = el_shift_left(el_shift_left(divisor,64),shift_length);

		printf("%016llx\n%016llx\n", divisor.high, n.high);

		el_print_hex_format(divisor);

		result.high = n.high;
		result.low  = n.low;

		for (i = 0; i < shift_length+64; i++)
		{
			result  = el_add(result, el_twos_complement(divisor));
			divisor = el_shift_right(divisor,1);
		}
	}

	return 	result.low;
}

/* Modular exponent : (a**b) mod m */
// unsigned long int 	el_exp(unsigned long a, unsigned long b, unsigned long m)
// {

// }

int 	main(int argc, char** argv)
{		
	elong i;
	i.high = 0x3;
	i.low  = 0x60;

	el_print_hex_format(i);

	printf("remainder modulus by %016lx : %016lx\n", 0x8001, el_mod(i,0x8001));

	exit(EXIT_SUCCESS);
}
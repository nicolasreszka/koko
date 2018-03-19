#ifndef ELONG_H
#define ELONG_H

/* Structure pour entier sur 128 bit */
typedef struct elong_s 
{
	unsigned long int high;
	unsigned long int low;
} elong;

/* Print un elong n en base 16 */
void 	el_print_hex(elong n);

/* Print un elong n en base 10 */
void	el_print_dec(elong n);

/* Print un elong n en base 16 sous le format 0000000000000000.0000000000000000 */
void 	el_print_hex_format(elong n);

/* Renvoie un masque dont les bornes sont left et right */
unsigned long int 	mask(unsigned char left, unsigned char right);

/* Coupe un entier x aux bornes left et right */
unsigned long int 	cut(unsigned long int x, unsigned char left, unsigned char right);

/* Revoie le nombre de zéros de poids fort */
unsigned char	zero_prefix(unsigned long int x);

/* Addition */
elong 	el_add(elong a, elong b);

/* Multiplication */
elong 	el_multiply(unsigned long a, unsigned long b);

/* Décalage de k vers la gauche */
elong 	el_shift_left(elong n, unsigned char k);

/* Décalage de 1 vers la droite */
elong 	el_shift_right(elong n);

/* Complément à 2 */
elong 	el_twos_complement(elong n);

/* Remainder modulus : m < 2^64 */
unsigned long int 	el_mod(elong n, unsigned long m);

/* Modular exponent : (a**b) mod m */
unsigned long int 	el_modular_exponent(unsigned long a, unsigned long b, unsigned long m);

#endif
#ifndef RSA_H
#define RSA_H

/* Identité de Bézout : ax + by = gcd(a,b) */
typedef struct bezout_identity_s
{
	unsigned long int 	a;
	unsigned long int 	b;
	unsigned long int 	gcd;
} bezout_identity;

/* La clé publique */
typedef struct rsa_public_key_s
{
	unsigned long int 	e;
	unsigned long int 	n;
} rsa_public_key;

/* La clé privée */
typedef struct rsa_private_key_s
{
	unsigned long int 	d;
	unsigned long int 	n;
} rsa_private_key;

int 	is_prime(unsigned long int n);

/* Propritété de la fonction d'euler : phi(p*q) = (p-1) * (q-1) */
unsigned long int 	euler(unsigned long int p, unsigned long int q);

/* Plus grand diviseur commun de a et b : algorithme d'Euclide */
unsigned long int	euclide(unsigned long int a, unsigned long int b);

/* Théorème de Bézout, renvoie l'identité de Bézout : ax + by = gcd(a,b)*/
bezout_identity 	bezout(unsigned long int a, unsigned long int b);

rsa_public_key	rsa_generate_public_key(unsigned long int p, unsigned long int q);

rsa_private_key	rsa_generate_private_key(rsa_public_key public_key, unsigned long int p, unsigned long int q);

#endif
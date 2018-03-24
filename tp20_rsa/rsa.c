#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "rsa.h"

/* La méthode RSA consiste à :
** - Choisir deux nombres premiers p et q "assez grands" 
** - Calculer le modulus n = p * q
** - Calculer phi = euler(n)
** - Choisir e < phi tel que e et phi premiers entre eux 
** - Choisir d < phi tel que (e * d) % phi == 1
** - Le couple (n, e) est la clef publique, le cypher du "plain text" est : (b ** e) mod n
** - Le couple (n, d) est la clef privée, le "plain text" est : (b ** d) mod n 
*/

/* Verifie si un nombre est premier */
int 	is_prime(unsigned long int n)
{
	int 	i, result;

	result = 1;

	if ((n <= 1) || (n % 2 == 0 && n > 2))
	{
		result = 0;
	}
	else
	{	
		for (i = 3; i < n / 2; i += 2)
		{
			if (n % i == 0) 
			{
				result = 0;
			}
		}
	}


	return 	result;
}

/* Propritété de la fonction d'euler : phi(p*q) = (p-1) * (q-1) */
unsigned long int 	euler(unsigned long int p, unsigned long int q)
{
	return 	(p-1) * (q-1);
}

/* Plus grand diviseur commun de a et b : algorithme d'Euclide */
unsigned long int	euclide(unsigned long int a, unsigned long int b)
{
	unsigned long int 	r; /* Reste de la division euclidienne */ 
	unsigned long int 	result;
	
	do
	{
		r = a % b;

		if (r == 0)
		{
			result = b;
		}
		else
		{
			a = b;
			b = r;
		}
	} 
	while (r != 0);

	return 	result;
}

/* Théorème de Bézout, renvoie l'identité de Bézout : ax + by = gcd(a,b)*/
bezout_identity 	bezout(unsigned long int a, unsigned long int b)
{
	bezout_identity 	result;
	bezout_identity 	temp;

	if (b == 0)
	{
		result.gcd = a;
		result.a   = 1;
		result.b   = 0;
	}
	else
	{
		temp = bezout(b,a%b);
		result.gcd = a;
		result.a   = temp.b;
		result.b   = temp.a - (a/b) * temp.b;
	}

	return result;
}

/* Choisit e < phi tel que e et phi premiers entre eux */
rsa_public_key	rsa_generate_public_key(unsigned long int p, unsigned long int q)
{
	rsa_public_key      result;
	unsigned long int 	phi;

	phi = euler(p,q);

	do
	{
		result.e = (unsigned long int) rand()%phi;
	}
	while (euclide(result.e,phi) != 1);

	result.n = (p * q);

	return 	result;
}

/* Choisit d < phi tel que (e * d) % phi == 1 */
rsa_private_key	rsa_generate_private_key(rsa_public_key public_key, unsigned long int p, unsigned long int q)
{
	rsa_private_key 	result;
	bezout_identity 	b;
	unsigned long int 	phi;

	phi = euler(p,q);
	b   = bezout(public_key.e, phi);

	result.d = (b.a % phi);
	result.n = public_key.n; 

	return 	result;
}
#include "stdio.h"
#include "stdlib.h"
#include "elong.h"

/* La méthode RSA consiste à :
** - Choisir deux nombres premiers p et q "assez grands" 
** - Calculer le modulus n = p * q
** - Calculer phi = euler(m)
** - Choisir e < phi tel que e et phi premiers entre eux 
** - Choisir d < phi tel que (e * d) % phi == 1
** - Le couple (n, e) est la clef publique, le cypher du "plain text" est : (b**e) mod n
** - Le couple (n, d) est la clef privée, le "plain text" est : (b ** d) mod n 
*/

/* Plus grand diviseur commun de a et b */
unsigned long int	gcd(unsigned long int a, unsigned long int b)
{
	unsigned long int 	result, remain;
	
	do
	{
		remain = a % b;

		if (remain == 0)
		{
			result = b;
		}
		else
		{
			a = b;
			b = remain;
		}
	} 
	while (remain != 0);

	return 	result;
}


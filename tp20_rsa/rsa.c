#include "stdio.h"
#include "stdlib.h"
#include "elong.h"

/* La méthode RSA consiste à :
** - Choisir deux nombres premiers p et q "assez grands" 
** - Calculer le modulus n = p * q
** - Calculer phi = euler(n)
** - Choisir e < phi tel que e et phi premiers entre eux 
** - Choisir d < phi tel que (e * d) % phi == 1
** - Le couple (n, e) est la clef publique, le cypher du "plain text" est : (b**e) mod n
** - Le couple (n, d) est la clef privée, le "plain text" est : (b ** d) mod n 
*/


/* Il faut donc coder : 
** - alogrithme d'euclide(a,b) -> renvoie le plus grand diviseur commun de a et b
** - théorème de bézout(a,b) -> renvoie les coefficients de bézout ( ax + by = pgcd(a,b) )
** - fonction d'euler(n) -> phi(n) =  (1 - n ** 1) * (1 - n ** 2) ... * (1 - n ** k)
**   finalement on n'a pas besoin de euler grâce à la propiété suivante : phi(p*q) = (p-1) * (q-1) 
** - generate_public_key(p,q)
** - generate_private_key(k, p,q) avec k = e ou d
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


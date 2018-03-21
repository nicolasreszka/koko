#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BLOCK_SIZE 3 //(taille modulus)32 bits - 8bits = 24 bits = 3octets

/* encrypt  : (val**e) mod m */

/* decrypt  : (val**d) mod m */

typedef struct encrypt_key{
  long m;
  long e;
} encrypt_key;

typedef struct decrypt_key{
  long n;
  long d;
} decrypt_key;

void printBezout(long r, long q, long u, long v){
  printf("<%ld> <%ld> <%ld> <%ld>\n", r, q, u, v);
}
long bezout( long a,  long b){

  printf("\t\tBEZOUT from %ld and %ld\n",a , b);
  long r0 = a, r1 = b;
  long u0 = 1, u1 = 0;
  long v0 = 0, v1 = 1;
  long u2 = 0, v2 = 0;
  while(r1 != 0){
    long q2 = r0 / r1;
    long r2 = r0 % r1;
    u2 = u0 - (q2 * u1);
    v2 = v0 - (q2 * v1);

    printBezout(r2, q2, u2, v2);
    u0 = u1;
    u1 = u2;
    v0 = v1;
    v1 = v2;
    r0 = r1;
    r1 = r2;

  }

  return u0;
}


unsigned long mask(unsigned char left, unsigned char right){
  unsigned long mask = 0xFFFFFFFFFFFFFFFF;
  left = (sizeof(unsigned long) * 8) - 1 - left;
  mask = (mask << left) >> left;
  mask = (mask >> right) << right;
  return mask;
}

unsigned long cut(unsigned long x, unsigned char left, unsigned char right){
  return (x & mask(left, right)) >> right;
}

/* Modular exponent : (a**b) mod m */
unsigned long int el_modular_exponent(unsigned long a, unsigned long b, unsigned long m){
	unsigned long int result,previous;
	unsigned char i;
	previous = 1;
	for (i = 1; i <= 64; i++){
		if (cut(b,64-i,64-i) == 0){
			result = ((previous * previous) % m);
		}
		else{
			result = ((((previous * previous) % m) * a) % m);
		}
		previous = result;
	}
	return	result;
}


long findDecryptKeyFromBezout(long bezoutResult, long phi){
  while(bezoutResult < 0){
    bezoutResult += phi;
  }
  //printf("D = %d\n", bezoutResult);
  return bezoutResult;
}




unsigned int findP(unsigned long racineDeN, unsigned long modulus){

  printf("Finding p from the odd number %lu ...\n", racineDeN);
  int result = -1;
  for(long i = racineDeN; i > 0; i -= 2){
    if((modulus % i) == 0){
      printf("Result found : %lu mod %lu = 0\n", modulus, i);
      if(i != 1) result = i;
    }
  }
  printf("\n\n \t\tDone !\n\n\n" );
  return result;
}

unsigned long int encrypt_value(long value, encrypt_key encr_key){
  return el_modular_exponent(value, encr_key.e, encr_key.m);
}
unsigned long decr_value(long value, decrypt_key decr_key){
  return el_modular_exponent(value, decr_key.d, decr_key.n);
}


unsigned long calculatePhi(long p, long q){
  printf("Calculating Phi, (p-1) * (q-1) = %ld\n", (p-1) * (q-1));
  return (unsigned long)(((unsigned long)p - 1) * ((unsigned long)q - 1));
}

int main(int argc, char const *argv[]) {
  if(argc != 3){
    printf("Usage : %s <m> <e>\n", argv[0]);

  }
  printf("%ld\n", strtol(argv[1], NULL, 10));

  long modulus = strtol(argv[1], NULL, 10);
  long e = strtol(argv[2], NULL, 10);
  printf("Public key <%ld, %ld>\n", modulus, e);
  long p, q;



  unsigned int racineDeN = sqrt(modulus);

  p = findP(racineDeN, modulus);
  if(p == -1){
    printf("No P found\n");
    exit(1);
  }
  q = modulus / p;

  printf("p = %ld, q = %lu\n", p, q);
  unsigned long phi = calculatePhi(p, q);
  printf("Phi(p, q) = %lu\n", phi);
  printf("\n\n\t\t e = %lu, phi = %ld\n", e, phi);

  long d = findDecryptKeyFromBezout(bezout(e, phi), phi);


  printf("D = %ld\n", d);
  printf("private key found ! <%lu, %ld>\n", modulus, d);


  encrypt_key encr_key = {modulus, e};


  decrypt_key decr_key = {modulus, d};

  printf("\n\n\t\t public  key = <mod, e> <%ld, %ld>\n", encr_key.m, encr_key.e);
  printf("\t\t private key = <mod, d> <%ld, %ld>\n\n\n", decr_key.n, decr_key.d);


  printf("\tChecking if D is correct...\n");
  printf("\td * e mod phi = %ld\n", (decr_key.d*e)%phi);
  if(((decr_key.d*e)%phi) != 1){
    printf("\td*e%%phi != 1, Wrong D... Exiting\n\n");
    exit(1);
  } else {
    printf("\tD is correct !\n\n");
  }

  printf("value = %d, encr = %ld, decr = %ld\n", 2, encrypt_value(2, encr_key), decr_value(encrypt_value(2, encr_key), decr_key));
  //Result expected encrypting 2 : 429158736789
  return 0;
}

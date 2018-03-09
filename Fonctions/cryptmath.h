#ifndef H_GL_CRYPTMATH
#define H_GL_CRYPTMATH

struct elong
{
	unsigned long int h;
	unsigned long int l;
};

void rotOctetD(unsigned char * octet,int cycle);
void rotOctetG(unsigned char * octet, int cycle);
void rotNibbleD(unsigned char * nibble,int cycle);
void rotNibbleG(unsigned char * nibble,int cycle);
void rotDiade(unsigned char * diade,int cycle);
void permBitOctet(unsigned char * octet, unsigned int permListe[8]);
void permBitNibble(unsigned char * nibble, unsigned int permListe[4]);
void permBitDiade(unsigned char * diade, unsigned int permListe[2]);
void substNibbleOctet(unsigned char * octet, unsigned int substListe[16],int cycle);
void substDiadeOctet(unsigned char * octet, unsigned int substListe[4],int cycle);
void mOctet(unsigned char octet);
unsigned int key_shuffle_tea(unsigned int key[4],unsigned int demi, unsigned int delta, char test);
void tea_encrypt_bloc(unsigned int tour, unsigned int key[4], unsigned int bloc[2]);
void tea_decrypt_bloc(unsigned int tour, unsigned int key[4], unsigned int bloc[2]);
void tea_encrypt_file(char * file_name,unsigned int key[4], unsigned int tour);
void tea_decrypt_file(char * file_name,unsigned int key[4], unsigned int tour);
unsigned long int mask(unsigned char l,unsigned char r);
unsigned long int cut(unsigned long int x,unsigned char l,unsigned char r);
struct elong eladd(struct elong a, struct elong b);
struct elong elmul(unsigned long a, unsigned long b);
unsigned long int elmod(struct elong a, unsigned long m);
unsigned long int elexpm(unsigned long x, unsigned long y, unsigned long m);
struct elong elshiftl(struct elong a, unsigned char z);
struct elong elshiftr(struct elong a, unsigned char z);
struct elong elsub(struct elong a,struct elong b);

#endif
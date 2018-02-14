#ifndef H_GL_CRYPTMATH
#define H_GL_CRYPTMATH

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
void tea_encrypt_file(char * file_name,unsigned int key[4]);
void tea_decrypt_file(char * file_name,unsigned int key[4]);
unsigned char get_char_key_from_file(char * file_name);
unsigned short get_short_key_from_file(char * file_name);
unsigned int get_int_key_from_file(char * file_name);
unsigned long get_long_key_from_file(char * file_name);
unsigned long long get_long_long_key_from_file(char * file_name);
void * get_unkown_key_from_file(char * file_name);

#endif
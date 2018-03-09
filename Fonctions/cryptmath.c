#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cryptmath.h"

/* ATTENTION, les fonctions non commentés ne doivent pas être utilisés, risque de bug et/ou de perte de données. */


void rotOctetD(unsigned char * octet,int cycle)
{
  unsigned char buff,mask = 0x1;
  int i;
  buff = *octet;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *octet >>= 1;
      buff <<= 7;
      *octet |= buff;
    }
}

void rotOctetG(unsigned char * octet, int cycle)
{
  unsigned char buff,mask = 0x80;
  int i;
  buff = *octet;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *octet <<= 1;
      buff >>= 7;
      *octet |= buff;
    }
}

void rotNibbleD(unsigned char * nibble,int cycle)
{
  unsigned char buff,mask = 0x1;
  int i;
  buff = *nibble;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *nibble >>= 1;
      buff <<= 3;
      *nibble |= buff;
    }
}

void rotNibbleG(unsigned char * nibble,int cycle)
{
  unsigned char buff,mask = 0x8;
  int i;
  buff = *nibble;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff &= mask;
      *nibble <<= 1;
      buff >>= 3;
      *nibble |= buff;
    }
}

void rotDiade(unsigned char * diade,int cycle)
{
  unsigned char buff;
  int i;
  buff = *diade;
  for ( i = 0 ; i < cycle ; i++ )
    {
      *diade >>= 1;
      buff <<= 1;
      *diade |= buff;
    }
}

void permBitOctet(unsigned char * octet, unsigned int permListe[8])
{
  unsigned char buff=0x0,buff2 = 0x0 ,mask = 0x1;
  int i;
  for ( i = 0 ; i < 8 ; i++)
    {
      buff2 =(*octet & mask);
      buff2 >>= i;
      buff2 <<= permListe[i];
      buff |= buff2;
      mask <<= 1;
    }
  *octet = buff;
}

void permBitNibble(unsigned char * nibble, unsigned int permListe[4])
{
  unsigned char buff=0x0,buff2=0x0,mask=0x1;
  int i;
  for ( i = 0 ; i < 4 ; i++)
    {
      buff2 = (*nibble & mask);
      buff2 >>= i;
      buff2 <<= permListe[i];
      buff |= buff2;
      mask <<= 1;
    }
  *nibble = buff;
}

void permBitDiade(unsigned char * diade, unsigned int permListe[2])
{
  int i;
  unsigned char buff=0x0,buff2=0x0,mask=0x1;
  for ( i = 0 ; i < 2 ; i++ )
    {
      buff2 = (*diade & mask);
      buff2 >>= i;
      buff2 <<= permListe[i];
      buff |= buff2;
      mask <<= 1;
    }
  *diade = buff;
}

void substNibbleOctet(unsigned char * octet, unsigned int substListe[16],int cycle)
{
  int i;
  unsigned char buff=0x0,buff2=0x0, mask = 0xf;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff = *octet;
      buff &= mask;
      mask <<= 4;
      buff = substListe[buff];
      
      buff2 = *octet;
      buff2 &= mask;
      buff2 >>= 4;
      buff2 = substListe[buff];
      buff |= buff2;
      *octet = buff;
    }
}

void substDiadeOctet(unsigned char * octet, unsigned int substListe[4],int cycle)
{
   int i;
   unsigned char buff=0x0,buff2=0x0,buff3=0x0,buff4=0x0, mask = 0x3;
  for ( i = 0 ; i < cycle ; i++ )
    {
      buff = *octet;
      buff &= mask;
      mask <<= 2;
      buff = substListe[buff];
      
      buff2 = *octet;
      buff2 &= mask;
      mask <<= 2;
      buff2 >>= 2;
      buff2 = substListe[buff];

      buff3 = *octet;
      buff3 &= mask;
      mask <<= 2;
      buff3 >>= 4;
      buff3 = substListe[buff];
 
      buff4 = *octet;
      buff4 &= mask;
      buff4 >>=6;
      buff4 = substListe[buff];
      
      buff |= buff2;
      buff |= buff3;
      buff |= buff4;
      *octet = buff;
    }
}

void mOctet(unsigned char octet)
{
  int i;
  unsigned char buff[8],mask=0x1;
  for ( i = 0 ; i < 8 ; i++ )
    {
      buff[i] = ( octet & (mask<<i) ) >> i;
    }
  for ( i = 7 ; i >= 0 ; i-- )
    {
      printf("%d",buff[i]);
    }
  putchar('\n');
}
  



/* 
  Fonction qui s'occupe de la gestion unitaire d'un demi bloc lors d'un tour 
  Utile dans tea_encrypt 
*/
unsigned int key_shuffle_tea(unsigned int key[4],unsigned int demi, unsigned int delta, char test)
{
  unsigned int top;
  unsigned int mid;
  unsigned int bot;
  bot = demi >> 5;
  top = demi << 4;
  if(!test)
  {
    top+=key[0];
    bot+=key[1];

  }
  else
  {
    top += key[2];
    bot += key[3];
  }
  mid = demi + delta;
  return top^mid^bot;
}

/*
  Fonction tea_encrypt
  On lui donne dans un tableau 1 bloc divisé en 2 sous blocs et la clef
*/

void tea_encrypt_bloc(unsigned int tour, unsigned int key[4], unsigned int bloc[2])
{
  unsigned int i;
  unsigned int l = bloc[0];
  unsigned int r = bloc[1];
  unsigned int delta = 0x9e3779b9;
  for ( i = 0 ; i < tour ; i++ )
  {
    l += key_shuffle_tea(key,r,delta,0);
    r += key_shuffle_tea(key,l,delta,1);
    delta += delta;
  }
  bloc[0] = l;
  bloc[1] = r;
}

 void tea_decrypt_bloc(unsigned int tour, unsigned int key[4], unsigned int bloc[2])
 {
  unsigned i;
  unsigned l = bloc[0];
  unsigned int r = bloc[1];
  unsigned int delta = 0x9e3779b9;
  for ( i = 0 ; i < tour ; i++ )
  {
    l -= key_shuffle_tea(key,r,delta,0);
    r -= key_shuffle_tea(key,l,delta,1);
    delta += delta;
  }
  bloc[0] = l;
  bloc[1] = r;
}


/* Fonction tea_encrypt_file   NON FONCTIONNELLE
 * arguments :
 * file_name : chaine de caractères qui contient le nom du fichier
 * key[4] : tableau d'unsigned int qui contient la clef de chiffrement divisée en 4.
 * tour : int qui représente le nombre de "tour"/cycle à effectuer lors du chiffrement. 
 *
 * retour : aucun
 *
 * Effets : Lors du cas nominal ( sans problemes ) chiffre le fichier en utilisant la méthode tea.
 * Le fichier de l'utilisateur est modifié ( chiffré ) et ne pourra donc pas être lu avant d'être déchiffré.
 * Lors d'une erreur lors d'un read, le fichier de l'utilisateur n'est pas corrompu.
 * Lors d'une erreur lors d'un write sur le fichier à chiffrer, le fichier risque d'être corrompu.
 * Pour recover le fichier, vous pouver regarder dans le repertoire courant, un fichier bufferfile.dat à été créer.
 * Celui-ci est le fichier chiffré sous un autre nom.
 * En cas d'erreur lors d'un write sur bufferfile.dat, le fichier à chiffrer n'a pas été altéré ou modifié.
 * Vous pouvez donc reessayer la méthode qui à pu échouer à cause de certaine erreurs système ou abandonner.
 */

void tea_encrypt_file(char * file_name,unsigned int key[4],unsigned int tour)
{

  int input_file_descriptor; /* Descripteur de fichier du fichier à chiffrer */
  int buffer_file_descriptor; /* Descripteur de fichier du fichier temporaire */

  unsigned int bloc[2]; /* Tableau qui contient les deux moitiées du bloc à chiffrer */

  int end; /* Variable utilisé par le read pour déterminer la fin du fichier */
  int err; /* Variable utilisé pour la gestion des erreurs */

  /* On ouvre le fichier à chiffrer en readonly en premier temps. */
  input_file_descriptor = open(file_name,O_RDONLY,0444);
  if ( input_file_descriptor < 0 )
  {
    perror("tea_encrypt_file(cryptmath.c) : Erreur lors du open de input_file_descriptor en mode readonly ");
    exit(-1);
  }

  /* On ouvre/creer temporaire. */
  buffer_file_descriptor = open("bufferfile.dat",O_CREAT|O_TRUNC|O_WRONLY,0644);
  if ( buffer_file_descriptor < 0 )
  {
    perror("tea_encrypt_file(cryptmath.c) : Erreur lors du open de buffer_file_descriptor en mode writeonly ");
    exit(-1);
  }

  /* Boucle qui parcours le fichier.
   * S'arrete à la fin du fichier ( lorsque read return 0 )
   * Pour chaque bloc du fichier à chiffrer, le chiffrer puis l'écrire dans le fichier temporaire.
   */
  while(1)
  {
    memset(bloc, '\0', 8);
    end = read(input_file_descriptor,bloc,8);
    if ( end == -1)
    {
      perror("tea_encrypt_file(cryptmath.c) : Erreur lors du read de input_file_name ");
      exit(-1);
    }
    if( end == 0 )
    {
      break;
    }
    tea_encrypt_bloc(tour,key,bloc);
    err = write(buffer_file_descriptor,bloc,8);
    if ( err < 0 )
    {
      perror("tea_encrypt_file(cryptmath.c) : Erreur lors du write sur buffer_file_name ");
      exit(-1);
    }
  }

  close(input_file_descriptor);
  close(buffer_file_descriptor);

  input_file_descriptor = open(file_name,O_TRUNC|O_WRONLY,0644);
  if( input_file_descriptor < 0 )
  {
    perror("tea_encrypt_file(cryptmath.c) : Erreur lors du open de input_file en mode writeonly ");
    exit(-1);
  }

  buffer_file_descriptor = open("bufferfile.dat",O_RDONLY,0444);
  if( buffer_file_descriptor < 0 )
  {
    perror("tea_encrypt_file(cryptmath.c) : Erreur lors du open de buffer_file en mode readonly ");
    exit(-1);
  }

  while(1)
  {
    memset(bloc, '\0', 8);
    end = read(buffer_file_descriptor,bloc,8);
    if ( end < 0 )
    {
      perror("tea_encrypt_file(cryptmath.c) : Erreur lors du write sur buffer_file_descriptor ");
      exit(-1);
    }
    if( end == 0 )
    {
      break;
    }
    err = write(input_file_descriptor,bloc,8);
    if ( err < 0 )
    {
      perror("tea_encrypt_file(cryptmath.c) : Erreur lors du write sur input_file_name ");
      exit(-1);
    }
  }

  close(input_file_descriptor);
  close(buffer_file_descriptor);
}


/* Fonction tea_decrypt_file    NON FONCTIONNELLE
 *
 * arguments :
 * file_name : chaine de caractères qui contient le nom du fichier
 * key[4] : tableau d'unsigned int qui contient la clef de chiffrement divisée en 4.
 * tour : int qui représente le nombre de "tour"/cycle à effectuer lors du chiffrement.
 *
 * retour : aucun
 *
 * Effet : lors du cas nominal, cette fonction dechiffre le fichier input_file.
 * En cas d'erreur lors du read input_file ou du write buffer_file, input_file n'a pas été altéré
 * En cas d'erreur lors du read buffer_file ou du write input_file, input_file a été altéré.
 * Il est cependant possible de récupérer le fichier en regardant buffer_file qui est decrypter et non altéré.
 */

void tea_decrypt_file(char * file_name,unsigned int key[4],unsigned int tour)
{
  int input_file_descriptor;
  int buffer_file_descriptor;
  unsigned int bloc[2];
  int end;
  int err;
  input_file_descriptor = open(file_name,O_RDONLY,0444);
  if ( input_file_descriptor < 0 )
  {
    perror("tea_decrypt_file(cryptmath.c) : Erreur lors du open de input_file en mode readonly ");
    exit(-1);
  }
  buffer_file_descriptor = open("bufferfile.dat",O_WRONLY|O_TRUNC|O_CREAT,0644);
  if ( buffer_file_descriptor < 0 )
  {
    perror("tea_decrypt_file(cryptmath.c) : Erreur lors du open de buffer_file en mode writeonly ");
    exit(-1);
  }
  while(1)
  {
    memset(bloc, '\0', 8);
    end = read(input_file_descriptor,bloc,8);
    if ( end < 0 )
    {
      perror("tea_decrypt_file(cryptmath.c) : Erreur lors du read sur input_file ");
      exit(-1);
    }
    if( end == 0 )
    {
      break;
    }
    tea_decrypt_bloc(tour,key,bloc);
    end = write(buffer_file_descriptor,bloc,8);
    if ( end == -1 )
    {
      perror("tea_decrypt_file(cryptmath.c) : Erreur lors du write sur buffer_file ");
      exit(-1);
    }
  }
  close(input_file_descriptor);
  close(buffer_file_descriptor);

  input_file_descriptor = open(file_name,O_WRONLY|O_TRUNC,0644);
  if ( input_file_descriptor < 0 )
  {
    perror("tea_decrypt_file(cryptmath.c) : Erreur lors du open de input_file en mode writeonly ");
    exit(-1);
  }

  buffer_file_descriptor = open("bufferfile.dat",O_RDONLY,0444);
  if ( buffer_file_descriptor < 0 )
  {
    perror("tea_decrypt_file(cryptmath.c) : Erreur lors du open de buffer_file en mode readonly ");
    exit(-1);
  }

  while(1)
  {
    memset(bloc,'\0', 8);

    end = read(buffer_file_descriptor,bloc,8);
    if ( end < 0 )
    {
      perror("tea_decrypt_file(cryptmath.c) : Erreur lors du read sur buffer_file ");
      exit(-1);
    }
    if ( end == 0 )
    {
      break;
    }

    err = write(input_file_descriptor,bloc,8);
    if ( err < 0 )
    {
      perror("tea_decrypt_file(cryptmath.c) : Erreur lors du write sur input_file ");
      exit(-1);
    }

  }

  close(input_file_descriptor);
  close(buffer_file_descriptor);

}



/* Fonction mask
 * 
 * arguments : 
 * unsigned char l => bord gauche inclus
 * unsigned char r -> bord droit inclus
 *
 * return : unsigned char mask  ( masque qui contient des 1 entre les borne spécifiées )
 *
 * Exemple : l = 7 , r = 0  => renvoie 0x11111111
 * Exemple 2 : Exemple : l = 7 , r = 1  => renvoie 0x11111110
 */ 

unsigned long int mask(unsigned char l,unsigned char r)
{
  unsigned long int c = 0x0;
  unsigned char i;
  unsigned long int msk = 0x1;
  unsigned long int res = 0x0;
  for ( i = 0 ; i < r ; i++ )
  {
    msk <<= 1;
  }
  for ( i = 0 ; i <= l-r ; i++ )
  {
    printf("mask : %lu\n", msk);
    res |= msk;
    msk <<= 1;
  }
  return res;
}

unsigned long int cut(unsigned long int x,unsigned char l,unsigned char r)
{
  return (x&mask(l,r))>>r;
}

struct elong elshiftr(struct elong a, unsigned char z)
{
  if ( z == 0 ) return a;
  if ( z >= 64 )
  {
    a.l = a.h;
    a.l >>= z-64;
    a.h = 0;
  }
  else
  {
    a.l >>= z;
    a.l |= cut(a.h,z,0);
    a.h >>= z;
  }
  return a;
}

struct elong elshiftl(struct elong a, unsigned char z)
{
  if ( z == 0 ) return a;
  if ( z >= 64 )
  {
    a.h = a.l;
    a.h <<= z-64;
    a.l = 0;
  }
  else
  {
    a.h <<= z;
    a.h |= ( a.l & mask(63,63-r));
    a.l <<= z;
  }
}


struct elong eladd(struct elong a,struct elong b )
{
  unsigned long int a63;
  unsigned long int b63;
  struct elong d;
  unsigned long int head_mask = 0x8000000000000000;

  a63 = ( a.h & head_mask ) >> 63;
  b63 = ( b.h & head_mask ) >> 63;
  d.l = a.l+b.l;
  d.h = a.h + b.h + a63 + b63;

  return d;

}

struct elong elmul(unsigned long a, unsigned long b)
{

}